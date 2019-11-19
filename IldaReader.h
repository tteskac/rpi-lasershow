#include "Points.h"

#include <string>
#include <fstream>
using namespace std;

class IldaReader
{
public:
	IldaReader();
	bool openFile(string fileName);
	bool readHeader();
	bool getNextFrame(Points *points);
	void closeFile();

public:
	std::ifstream file;
	short format;					// 0 or 5
	unsigned short numberOfRecords; // 2 bytes
	unsigned short totalFrames;		// 2 bytes
};
