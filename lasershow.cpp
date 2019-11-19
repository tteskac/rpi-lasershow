#include <string>

#include <wiringPi.h>	// IO pins.
#include <thread>		// For server.
#include <chrono>		// Precise timing.

// To catch program interruptions.
#include <signal.h>
#include <unistd.h>

// Custom classes.
#include "Points.h"
#include "IldaReader.h"
#include "Communication.h"

// DAC lib
#include "ABE_ADCDACPi.h"
using namespace ABElectronics_CPP_Libraries;

void onInterrupt(int);
void serverTask();
bool running = true;

int main(int argc, char **argv)
{
	// Validate arguments.
	if (argc < 3)
	{
		printf("ERROR: Arguments missing.\n");
		printf("Required: [pointDelay] [fileName]\n");
		return 1;
	}

	// Read arguments.
	int pointDelay = atoi(argv[1]);
	string fileName = argv[2];
	double frameDuration = 0.033; // ~30fps (1/30=0.033..).

	// Try to open provided file.
	Points points;
	IldaReader ildaReader;
	if (ildaReader.openFile(fileName))
	{
		printf("Provided file is a valid ILDA file, format %d\n", ildaReader.format);
		ildaReader.getNextFrame(&points);
		printf("Points loaded in the first frame: %d\n", points.size);
	}
	else
	{
		printf("Error opening ILDA file.\n");
		return 1;
	}

	// Setup hardware communication stuff.
	wiringPiSetup();
	ADCDACPi adcdac;
	// Control laser diode on wiringPi pin 0 (GPIO17, D1, header pin 11).
	pinMode(0, OUTPUT);
	// Open the DAC SPI channel.
	if (adcdac.open_dac() != 1)
		return 1;
	// Set the DAC gain to 1 which will give a voltage range of 0 to 2.048V.
	adcdac.set_dac_gain(1);

	// Subscribe program to exit/interrupt signal.
	signal(SIGINT, onInterrupt);

	// Start server for receiving commands.
	std::thread serverThread(serverTask);

	// Start the scanner loop with the current time.
	std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
	while (running)
	{
		// Exit if no points found.
		if (points.size == 0)
			break;

		// Move galvos to x,y position. (4096 is to invert horizontally)
		adcdac.set_dac_raw(4096 - points.store[points.index * 3], 1);
		adcdac.set_dac_raw(points.store[(points.index * 3) + 1], 2);

		// Turn on/off laser diode.
		if (points.store[(points.index * 3) + 2] == 1)
			digitalWrite(0, HIGH);
		else
			digitalWrite(0, LOW);

		// Maybe wait a while there.
		if (pointDelay > 0)
			usleep(pointDelay);

		// In case there's no more points in the current frame check if it's time to load next frame.
		if (!points.next())
		{
			std::chrono::duration<double> elapsedSeconds = std::chrono::system_clock::now() - start;
			if (elapsedSeconds.count() > frameDuration)
			{
				start = std::chrono::system_clock::now();
				digitalWrite(0, LOW);
				ildaReader.getNextFrame(&points);
			}
		}
	}

	// Cleanup and exit.
	printf("Cleanup...\n");
	digitalWrite(0, LOW);
	ildaReader.closeFile();
	adcdac.close_dac();
	printf("Exit.\n");
	return 0;
}

// Function that is called when program needs to be terminated.
void onInterrupt(int)
{
	printf("Program was interrupted.\n");
	running = false;
}

// Starts thread with socket listener.
void serverTask()
{
	printf("Starting server thread...\n");
	Communication comm;
	comm.start();
}
