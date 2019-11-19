#include "FrameData.h"

// Format spec: https://www.ilda.com/resources/StandardsDocs/ILDA_IDTF14_rev011.pdf

FrameData::FrameData() {}

short FrameData::getNumberOfDataBytes(short format)
{
	if (format == 1) {
		return FrameData::NUMBER_OF_DATA_BYTES_FORMAT_1;
	}
	if (format == 5) {
		return FrameData::NUMBER_OF_DATA_BYTES_FORMAT_5;
	}

	throw "Invalid ILDA format.";
}