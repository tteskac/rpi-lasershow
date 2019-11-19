#include "IldaReader.h"
#include "Frame.h"
#include "Points.h"

#include <fstream>
#include <string>
using namespace std;

IldaReader::IldaReader() {}

bool IldaReader::openFile(string fileName)
{
	// Open file.
	this->file = std::ifstream(fileName, std::ifstream::binary);
	if (!this->file)
	{
		return false;
	}

	// Read first 32 header bytes from the file to check if valid, get ILDA format, etc.".
	return readHeader();
}

bool IldaReader::readHeader()
{
	char buffer[Frame::NUMBER_OF_HEADER_BYTES];
	this->file.read(buffer, Frame::NUMBER_OF_HEADER_BYTES);

	// Check if file starts with "ILDA".
	if (buffer[0] != 'I' || buffer[1] != 'L' || buffer[2] != 'D' || buffer[3] != 'A') {
		// Invalid file.
		return false;
	}

	// Read format.
	this->format = buffer[Frame::FORMAT_CODE_BYTE];
	if (this->format != 1 && this->format != 5)
	{
		printf("Only ILDA formats 1 and 5 are supported! This file format is ILDA %d.\n", this->format);
		return false;
	}

	// Return back to start of the file.
	this->file.seekg(0);

	return true;
}

bool IldaReader::getNextFrame(Points *points)
{
	// Read all points from next frame.
	Frame frame;
	return frame.getNext(this->file, this->format, points);
}

void IldaReader::closeFile()
{
	this->file.close();
}
