#include "Frame.h"
#include "FrameData.h"
#include "Points.h"

#include <fstream>
using namespace std;

// Format spec: https://www.ilda.com/resources/StandardsDocs/ILDA_IDTF14_rev011.pdf

Frame::Frame(){}

bool Frame::getNext(std::ifstream& file, Points* points) {

    FrameData data;
    char bytes[FrameData::NUMBER_OF_DATA_BYTES];

    unsigned int position = file.tellg();

    // get size of file:
    file.seekg(0, file.end);
    int fileSize = file.tellg();
    file.seekg(position);

    // End of file...
    if (fileSize - (position + Frame::NUMBER_OF_HEADER_BYTES) < Frame::NUMBER_OF_HEADER_BYTES + FrameData::NUMBER_OF_DATA_BYTES) {
        // return false to nofity end of file but jump to begining of the file in case we will loop the file again. 
        file.seekg(0);
        return false;
    }

    // Skip header data.
    file.seekg(position + Frame::NUMBER_OF_HEADER_BYTES);

    points->size = 0;
    points->index = 0;

    do {
        // Read next point in the frame.
        file.read(bytes, FrameData::NUMBER_OF_DATA_BYTES);
        data.x = (bytes[FrameData::X_BYTE] << 8 ) + bytes[FrameData::X_BYTE + 1];
        data.y = (bytes[FrameData::Y_BYTE] << 8 ) + bytes[FrameData::Y_BYTE + 1];
        data.laserOn = !getBit(bytes[FrameData::STATUS_BYTE], FrameData::LASER_ON_BIT);

        // ILDA format has a weird way of storing values. Positive numbers are stored nomally
        // but negative numbers are stored in second part of 'unsigned short' (>32768) so e.g. 
        // the number "-1" is storead as "65535".
        if (data.x > 32768) data.x = data.x - 65536;
        if (data.y > 32768) data.y = data.y - 65536;

        // Map ILDA values to DAC value range and store the data to array. 
        points->store[points->size*3] = map(data.x, -32768, +32767, 0, 4095);
        points->store[(points->size*3)+1] = map(data.y, -32768, +32767, 0, 4095);
        points->store[(points->size*3)+2] = data.laserOn;
        points->size++;

    // Read next if current not last.
    } while (!isLastPoint(bytes));

    // true = no more points in current frame to read.
    return true;
}

// Get the last-point-bit-flag from status byte x.
bool Frame::isLastPoint(char* bytes) {
    return getBit(bytes[FrameData::STATUS_BYTE], FrameData::LAST_POINT_BIT);
}

// Helpter function to get arbitrary bit value from byte.
bool Frame::getBit(char b, int bitNumber) {
    return (b & (1 << (bitNumber - 1))) != 0;
}

// Helper function to map a value between two value ranges.
int Frame::map(int x, int in_min, int in_max, int out_min, int out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
