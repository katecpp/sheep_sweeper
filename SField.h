#ifndef SFIELD
#define SFIELD
#include <stdint.h>
#include <QMetaType>

struct SField
{
    uint8_t sheep       : 1;
    uint8_t discovered  : 1;
    uint8_t disarmed    : 1;
    uint8_t secured     : 1;
    uint8_t neighbours  : 4;
};

Q_DECLARE_METATYPE(SField)

#endif // SFIELD

