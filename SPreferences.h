#ifndef SPREFERENCES_H
#define SPREFERENCES_H

#include <Constants.h>
#include <stdint.h>

struct SPreferences
{
    SPreferences() : width(DEFAULT_HEIGHT),
                     height(DEFAULT_WIDTH),
                     sheep(DEFAULT_SHEEP)
    {}

    int32_t width;
    int32_t height;
    int32_t sheep;
};

#endif // SPREFERENCES_H

