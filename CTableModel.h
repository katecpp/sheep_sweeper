#ifndef CTABLEMODEL_H
#define CTABLEMODEL_H

#include <QAbstractTableModel>
#include <CModel.h>

class CTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit CTableModel(int32_t xSize = 10, int32_t ySize = 10, int32_t sheep = 10, QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
signals:
    void gameWon();
    void gameLost();
public slots:
    void newGame();
    void onTableClicked(const QModelIndex &index);
    void onRightClicked(const QModelIndex &index);
private:
    void discover(const QModelIndex &index);

    int32_t m_xSize;
    int32_t m_ySize;
    int32_t m_sheep;
    CModel* m_model;
};

#endif // CTABLEMODEL_H
