// Format spec: https://www.ilda.com/resources/StandardsDocs/ILDA_IDTF14_rev011.pdf

class FrameData
{
public:
	FrameData();
	short getNumberOfDataBytes(short format);

public:
	static const int NUMBER_OF_DATA_BYTES_FORMAT_1 = 6;
	static const int NUMBER_OF_DATA_BYTES_FORMAT_5 = 8;

	static const int X_BYTE = 0;			// byte 1-2
	static const int Y_BYTE = 2;			// byte 3-4
	static const int STATUS_BYTE = 4;		// byte 5
	static const int LAST_POINT_BIT = 8;	// byte 5, bit 8 (1=last)
	static const int LASER_ON_BIT = 7;		// byte 5, bit 7 (0=on,1=off)

	int x;
	int y;
	bool laserOn;
};
