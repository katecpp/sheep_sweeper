#ifndef CINACTIVEDELEGATE_H
#define CINACTIVEDELEGATE_H

#include <CActiveDelegate.h>

namespace SSw
{

class CInactiveDelegate : public CActiveDelegate
{
public:
    CInactiveDelegate(QObject *parent = 0);

protected:
    virtual void getStyleForField(const SField& field,
                          QStyleOptionButton& buttonStyle) const;
};

}
#endif // CINACTIVEDELEGATE_H
