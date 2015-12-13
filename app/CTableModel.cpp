#include <CTableModel.h>
#include <QPixmap>
#include <QSize>
#include <QDebug>

namespace SSw
{

CTableModel::CTableModel(int32_t width, int32_t height, int32_t sheep, QObject *parent)
    : QAbstractTableModel(parent),
      m_sheepDisplay(sheep),
      m_model(width, height, sheep),
      m_initialized(false)
{
    emit sheepRemainedDisplay(sheep);
}

CTableModel::~CTableModel()
{
}

void CTableModel::init(const QModelIndex &index)
{
    qDebug() << "CTableModel::init";
    m_model.populate(index.row(), index.column());
    m_initialized = true;
    emit gameStarted();
}

int CTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_model.width();
}
int CTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_model.height();
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
        variant.setValue(m_model.field(index.row(), index.column()));
        return variant;
    }

    return QVariant();
}

void CTableModel::newGame(int32_t width, int32_t height, int32_t sheep)
{
    qDebug() << "New game: " << width << ", " << height << ", " << sheep;
    m_initialized = false;
    m_model.reset(width, height, sheep);
    m_sheepDisplay = sheep;
    emit sheepRemainedDisplay(sheep);
    emit layoutChanged();
}

void CTableModel::onTableClicked(const QModelIndex &index)
{
    int32_t x = index.row();
    int32_t y = index.column();
    qDebug() << "Clicked: " << x << "," << y;

    if (m_model.field(x, y).disarmed == 0)
    {
        discover(index);
    }
}

void CTableModel::discover(const QModelIndex &index)
{
    if (!m_initialized)
    {
        qDebug() << "First click!";
        init(index);
    }

    const int32_t x = index.row();
    const int32_t y = index.column();

    m_model.discover(x, y);

    if (m_model.field(x, y).neighbours == 0
            && m_model.field(x, y).sheep == 0)
    {
        if (!m_model.getDiscovered(x-1, y-1))   discover(index.sibling(x-1, y-1)); // up
        if (!m_model.getDiscovered(x, y-1))     discover(index.sibling(x,   y-1));
        if (!m_model.getDiscovered(x+1, y-1))   discover(index.sibling(x+1, y-1));
        if (!m_model.getDiscovered(x-1, y))     discover(index.sibling(x-1, y));   // mid
        if (!m_model.getDiscovered(x+1, y))     discover(index.sibling(x+1, y));
        if (!m_model.getDiscovered(x-1, y+1))   discover(index.sibling(x-1, y+1)); // down
        if (!m_model.getDiscovered(x, y+1))     discover(index.sibling(x,   y+1));
        if (!m_model.getDiscovered(x+1, y+1))   discover(index.sibling(x+1, y+1));
    }

    emit dataChanged(index, index);

    if (m_model.field(x, y).sheep && m_model.field(x, y).disarmed == 0)
    {
        qDebug() << "You loose! : " << x << "," << y;
        emit gameLost();
    }
    else if (m_model.checkIfWon())
    {
        qDebug() << "You win!";
        emit gameWon();
        //TODO: discover all when won
    }
}

void CTableModel::onRightClicked(const QModelIndex &index)
{
    int32_t x = index.row();
    int32_t y = index.column();

    bool crtDisarmed = (m_model.field(x, y).disarmed > 0);

    if (m_model.field(x, y).discovered == 0)
    {
        m_model.disarm(x, y);

        if (crtDisarmed == false)
        {
            m_sheepDisplay--;
        }
        else if ((crtDisarmed == true) && (m_model.field(x, y).disarmed == 0))
        {
            m_sheepDisplay++;
        }

        emit sheepRemainedDisplay(m_sheepDisplay);
        emit dataChanged(index, index);
    }
}

void CTableModel::onBothClicked(const QModelIndex &index)
{
    int32_t x = index.row();
    int32_t y = index.column();

    if (m_model.getDiscovered(x, y)
            && m_model.getNeighbours(x, y) == m_model.countFlagsAround(x, y))
    {
        qDebug() << "Discover neighbourhood!";
        if (!m_model.getDiscovered(x-1, y-1))   discover(index.sibling(x-1, y-1)); // up
        if (!m_model.getDiscovered(x, y-1))     discover(index.sibling(x,   y-1));
        if (!m_model.getDiscovered(x+1, y-1))   discover(index.sibling(x+1, y-1));
        if (!m_model.getDiscovered(x-1, y))     discover(index.sibling(x-1, y));   // mid
        if (!m_model.getDiscovered(x+1, y))     discover(index.sibling(x+1, y));
        if (!m_model.getDiscovered(x-1, y+1))   discover(index.sibling(x-1, y+1)); // down
        if (!m_model.getDiscovered(x, y+1))     discover(index.sibling(x,   y+1));
        if (!m_model.getDiscovered(x+1, y+1))   discover(index.sibling(x+1, y+1));
    }
}

} // namespace SSw
