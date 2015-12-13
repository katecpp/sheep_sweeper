#include <CActiveDelegate.h>
#include <Constants.h>
#include <QStylePainter>
#include <QApplication>

namespace SSw
{

CActiveDelegate::CActiveDelegate(QObject *parent)
    : QAbstractItemDelegate(parent),
      m_fieldSize(FIELD_SIZE)
{
}

void CActiveDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
{
    SField field = index.model()->data(index, Qt::UserRole).value<SField>();
    QStyleOptionButton buttonStyle;
    getStyleForField(field, option, buttonStyle);
    QApplication::style()->drawControl(QStyle::CE_PushButton, &buttonStyle, painter,
                                       qobject_cast<QWidget *>(this->parent()));
}

QSize CActiveDelegate::sizeHint(const QStyleOptionViewItem & /* option */,
                              const QModelIndex & /* index */) const
{
    return QSize(m_fieldSize, m_fieldSize);
}

void CActiveDelegate::getStyleForField(const SField& field, const QStyleOptionViewItem &option, QStyleOptionButton& buttonStyle) const
{
    buttonStyle.rect        = option.rect;
    buttonStyle.iconSize    = QSize(ICON_SIZE, ICON_SIZE);
    buttonStyle.state      |= QStyle::State_Enabled | option.state;

    if (field.discovered)
    {
        buttonStyle.state |= QStyle::State_Sunken;

        if (field.neighbours != 0)
        {
            buttonStyle.text = QString::number(field.neighbours);
        }
    }
    else
    {
        buttonStyle.state |= QStyle::State_Raised;

        if (field.disarmed == 1)
        {
            buttonStyle.icon = QIcon(QPixmap(DISARMED_PATH));
        }
        else if (field.disarmed == 2)
        {
            buttonStyle.icon = QIcon(QPixmap(QUESTION_PATH));
        }
    }
}

} // namespace SSw
