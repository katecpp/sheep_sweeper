#include <CInactiveDelegate.h>
#include <Constants.h>

namespace SSw
{

CInactiveDelegate::CInactiveDelegate(QObject *parent)
    : CActiveDelegate(parent)
{
}

void CInactiveDelegate::getStyleForField(const SField& field,
                      QStyleOptionButton& buttonStyle) const
{
    if (field.disarmed > 0 && field.sheep == 1)
    {
        buttonStyle.icon = QIcon(QPixmap(DISARMED_GREEN_PATH));
    }
    else if (field.disarmed > 0 && field.sheep == 0)
    {
        buttonStyle.icon = QIcon(QPixmap(DISARMED_RED_PATH));
    }
    else if (field.discovered == 0 && field.sheep == 1)
    {
        buttonStyle.icon = QIcon(QPixmap(SMALL_SHEEP_PATH));
    }
    else if (field.discovered == 1 && field.sheep == 1)
    {
        buttonStyle.icon = QIcon(QPixmap(SMALL_RED_SHEEP_PATH));
    }
    else if (field.sheep == 0 && field.neighbours != 0)
    {
        buttonStyle.text = QString::number(field.neighbours);
    }
}

}
