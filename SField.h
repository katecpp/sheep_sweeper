#ifndef SFIELD
#define SFIELD
#include <stdint.h>
#include <QMetaType>

struct SField
{
    SField() : sheep(0),
               discovered(0),
               disarmed(0),
               neighbours(0)
    {}

    uint8_t sheep       : 1;
    uint8_t discovered  : 1;
    uint8_t disarmed    : 2;
    uint8_t neighbours  : 4;
};

Q_DECLARE_METATYPE(SField)

#endif // SFIELD

