#include <CTableModel.h>
#include <QPixmap>
#include <QSize>
#include <QDebug>

CTableModel::CTableModel(QObject *parent)
    : QAbstractTableModel(parent),
      m_model(nullptr)
{
    m_model = new CModel(10,10);
    m_model->populate();
}

int CTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_model->size();
}
int CTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_model->size();
}

QVariant CTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (Qt::UserRole == role)
    {
        QVariant variant;
        variant.setValue(m_model->field(index.row(), index.column()));
        return variant;
    }

    return QVariant();
}
