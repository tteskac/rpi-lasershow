#include "Points.h"

Points::Points() {
    this->index = 0;
}

bool Points::next() {
    this->index++;
    if (this->index >= this->size) {
        this->index = 0;
        // If there's no next point in the array.
        return false;
    }
    // If has next point in the array.
    return true;
}
