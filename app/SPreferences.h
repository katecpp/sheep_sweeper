#ifndef SPREFERENCES_H
#define SPREFERENCES_H

#include <Constants.h>
#include <stdint.h>

namespace SSw
{

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

} // namespace SSw

#endif // SPREFERENCES_H

