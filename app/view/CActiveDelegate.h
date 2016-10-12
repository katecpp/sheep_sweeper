#ifndef CFIELDDELEGATE_H
#define CFIELDDELEGATE_H

#include <QAbstractItemDelegate>
#include <QModelIndex>
#include <QStylePainter>

namespace SSw
{

struct SField;

class CActiveDelegate : public QAbstractItemDelegate
{
public:
    CActiveDelegate(QObject *parent = 0);

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

    virtual QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index ) const override;

protected:
    virtual void getStyleForField(const SField& field,
                          QStyleOptionButton& buttonStyle) const;

    virtual void getGeneralsForField(const SField& field, const QStyleOptionViewItem &option,
                          QStyleOptionButton& buttonStyle) const;

    int32_t m_fieldSize;
};

} // namespace SSw

#endif // CFIELDDELEGATE_H
