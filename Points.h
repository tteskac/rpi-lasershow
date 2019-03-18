#pragma once

class Points {  
    public:
        Points();
        bool next();

    public:
        static const short MAX_POINTS = 3000; // 18KB of memory.

        short store[MAX_POINTS*3];
        short size = 0;
        short index;
};
