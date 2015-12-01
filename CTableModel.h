#ifndef CTABLEMODEL_H
#define CTABLEMODEL_H

#include <QAbstractTableModel>
#include <CModel.h>

class CTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit CTableModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
signals:

public slots:

private:
    CModel* m_model;
};

#endif // CTABLEMODEL_H
