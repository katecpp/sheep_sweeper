#ifndef CFIELDDELEGATE_H
#define CFIELDDELEGATE_H

#include <QAbstractItemDelegate>
#include <QModelIndex>
#include <SField.h>

class CFieldDelegate : public QAbstractItemDelegate
{
public:
    CFieldDelegate(QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const Q_DECL_OVERRIDE;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index ) const Q_DECL_OVERRIDE;

private:
    void getStyleForField(const SField& field, const QStyleOptionViewItem &option,
                          QStyleOptionButton& buttonStyle) const;

    int32_t m_fieldSize;
};

#endif // CFIELDDELEGATE_H
