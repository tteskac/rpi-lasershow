#include "Points.h"

#include <string>
#include <fstream>
using namespace std;

class IldaReader {
    public:
        IldaReader();
        bool readFile(string fileName);
        bool checkHeader();
        bool getNextFrame(Points* points);
        void closeFile();

    public:
        std::ifstream file;
};
