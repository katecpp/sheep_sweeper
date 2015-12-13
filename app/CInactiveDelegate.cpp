#include <CInactiveDelegate.h>
#include <Constants.h>

namespace SSw
{

CInactiveDelegate::CInactiveDelegate(QObject *parent)
    : CActiveDelegate(parent)
{
}

void CInactiveDelegate::getStyleForField(const SField& field, const QStyleOptionViewItem &option,
                      QStyleOptionButton& buttonStyle) const
{
    buttonStyle.rect        = option.rect;
    buttonStyle.iconSize    = QSize(ICON_SIZE, ICON_SIZE);
    buttonStyle.state      |= QStyle::State_Enabled | option.state;

    if (field.discovered)
    {
        buttonStyle.state |= QStyle::State_Sunken;
    }
    else
    {
        buttonStyle.state |= QStyle::State_Raised;
    }

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
