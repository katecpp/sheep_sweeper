#ifndef CTABLEMODEL_H
#define CTABLEMODEL_H

#include <QAbstractTableModel>
#include <CModel.h>

namespace SSw
{

class CTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:

    explicit CTableModel(int32_t width, int32_t height, int32_t sheep, QObject *parent = 0);
    ~CTableModel();

    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    int      rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int      columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    void     resetModel(int32_t width, int32_t height, int32_t sheep);

signals:
    void     gameStarted();
    void     gameLost();
    void     gameWon();
    void     sheepDisplay(int32_t sheepCount);

public slots:
    void     onTableClicked(const QModelIndex &index);
    void     onRightClicked(const QModelIndex &index);
    void     onBothClicked(const QModelIndex &index);

private:
    void     init(const QModelIndex &index);
    void     discover(const QModelIndex &index);

    CModel   m_model;
    int32_t  m_sheepDisplay;
    bool     m_initialized;
};

} // namespace SSw

#endif // CTABLEMODEL_H
