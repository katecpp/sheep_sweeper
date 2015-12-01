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
    buttonStyle.state |= QStyle::State_Raised | QStyle::State_Enabled | option.state;
    buttonStyle.rect = option.rect;

    if (field.sheep != 0)
    {
        buttonStyle.icon = QIcon(QPixmap(":/images/images/small_sheep.png"));
        buttonStyle.iconSize = QSize(16, 16);
    }
    else
    {
        buttonStyle.text = QString::number(field.neighbours);
    }

    QApplication::style()->drawControl(QStyle::CE_PushButton, &buttonStyle, painter,
                                       qobject_cast<QWidget *>(this->parent()) );
}

QSize CFieldDelegate::sizeHint(const QStyleOptionViewItem & /* option */,
                              const QModelIndex & /* index */) const
{
    return QSize(m_fieldSize, m_fieldSize);
}
