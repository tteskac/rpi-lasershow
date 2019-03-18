#include "IldaReader.h"
#include "Frame.h"
#include "Points.h"

#include <fstream>
#include <string>
using namespace std;

IldaReader::IldaReader() {}

bool IldaReader::readFile(string fileName) {

    // Open file.
    this->file = std::ifstream(fileName, std::ifstream::binary);
    if (!this->file) {
        return false;
    }

    // Read first 32 header bytes from the file and check if the first 4 bytes in ASCII are "ILDA".
    return checkHeader();
}

// Read first 32 header bytes from the file and check if the first 4 bytes in ASCII are "ILDA".
bool IldaReader::checkHeader() {
    char buf[Frame::NUMBER_OF_HEADER_BYTES];
    this->file.read(buf, Frame::NUMBER_OF_HEADER_BYTES);

    string header = "";
    for (int i = 0; i < 4; i++) {
        header += buf[i];
    }

    if (header != "ILDA") {
        // Invalid file.
        return false;
    }

    // Return back to start of the file.
    this->file.seekg(0);

    return true;
}

bool IldaReader::getNextFrame(Points* points) {
    // Read all points from next frame.
    Frame frame;
    return frame.getNext(this->file, points);
}

void IldaReader::closeFile() {
    this->file.close();
}
