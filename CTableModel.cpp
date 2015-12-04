#include <CTableModel.h>
#include <QPixmap>
#include <QSize>
#include <QDebug>

CTableModel::CTableModel(int32_t xSize, int32_t ySize, int32_t sheep, QObject *parent)
    : QAbstractTableModel(parent),
      m_xSize(xSize),
      m_ySize(ySize),
      m_sheep(sheep),
      m_model(nullptr)
{
    newGame();
    //TODO: delay populating until user clicks first field
}

int CTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_model->xSize();
}
int CTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_model->xSize();
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

void CTableModel::newGame()
{
    qDebug() << "New game";

    if (m_model != nullptr)
    {
        delete m_model;
        m_model = nullptr;
    }

    m_model = new CModel(m_xSize, m_sheep);
    m_model->populate();
}

void CTableModel::onTableClicked(const QModelIndex &index)
{
    int32_t x = index.row();
    int32_t y = index.column();
    qDebug() << "Clicked: " << x << "," << y;

    if (m_model->field(x, y).disarmed == 0)
    {
        discover(index);

        if (m_model->field(index.row(), index.column()).sheep)
        {
            qDebug() << "You loose!";
            emit gameLost();
        }

        if (m_model->checkIfWon())
        {
            qDebug() << "You win!";
            emit gameWon();
            //TODO: discover all when won
        }
    }
}

void CTableModel::discover(const QModelIndex &index)
{
    const int32_t x = index.row();
    const int32_t y = index.column();

    m_model->discover(x, y);

    if (m_model->field(x, y).neighbours == 0 && m_model->field(x, y).sheep == 0)
    {
        if (!m_model->getDiscoverValue(x-1, y-1))   discover(index.sibling(x-1, y-1)); // up
        if (!m_model->getDiscoverValue(x, y-1))     discover(index.sibling(x,   y-1));
        if (!m_model->getDiscoverValue(x+1, y-1))   discover(index.sibling(x+1, y-1));
        if (!m_model->getDiscoverValue(x-1, y))     discover(index.sibling(x-1, y));   // mid
        if (!m_model->getDiscoverValue(x+1, y))     discover(index.sibling(x+1, y));
        if (!m_model->getDiscoverValue(x-1, y+1))   discover(index.sibling(x-1, y+1)); // down
        if (!m_model->getDiscoverValue(x, y+1))     discover(index.sibling(x,   y+1));
        if (!m_model->getDiscoverValue(x+1, y+1))   discover(index.sibling(x+1, y+1));
    }

    emit dataChanged(index, index);
}

void CTableModel::onRightClicked(const QModelIndex &index)
{
    int32_t x = index.row();
    int32_t y = index.column();
    qDebug() << "Right clicked: " << x << "," << y;

    if (m_model->field(x, y).discovered == 0)
    {
        m_model->disarm(x, y);
        emit dataChanged(index, index);
    }
}
