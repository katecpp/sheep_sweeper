#include <CFieldDelegate.h>
#include <QPainter>
#include <QStylePainter>
#include <QApplication>
#include <SField.h>

CFieldDelegate::CFieldDelegate(QObject *parent)
    : QAbstractItemDelegate(parent),
      m_fieldSize(24)
{
}

void CFieldDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
{
    SField field = index.model()->data(index, Qt::UserRole).value<SField>();

    QStyleOptionButton buttonStyle;
    buttonStyle.rect = option.rect;
    buttonStyle.iconSize = QSize(16, 16);

    if (field.discovered)
    {
        buttonStyle.state |= QStyle::State_Sunken | QStyle::State_Enabled | option.state;

        if (field.sheep != 0)
        {
            buttonStyle.icon = QIcon(QPixmap(":/images/images/small_sheep.png"));

        }
        else if (field.neighbours != 0)
        {
            buttonStyle.text = QString::number(field.neighbours);
        }
    }
    else
    {
        buttonStyle.state |= QStyle::State_Raised | QStyle::State_Enabled | option.state;

        if (field.disarmed == 1)
        {
            buttonStyle.icon = QIcon(QPixmap(":/images/images/disarmed.png"));
        }
        else if (field.disarmed == 2)
        {
            buttonStyle.icon = QIcon(QPixmap(":/images/images/question.png"));
        }
    }

    QApplication::style()->drawControl(QStyle::CE_PushButton, &buttonStyle, painter,
                                       qobject_cast<QWidget *>(this->parent()) );
}

QSize CFieldDelegate::sizeHint(const QStyleOptionViewItem & /* option */,
                              const QModelIndex & /* index */) const
{
    return QSize(m_fieldSize, m_fieldSize);
}
