#include <CTableModel.h>
#include <QPixmap>
#include <QSize>
#include <QDebug>

CTableModel::CTableModel(QObject *parent)
    : QAbstractTableModel(parent),
      m_model(nullptr)
{
    newGame();
    //TODO: delay populating until user clicks first field
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

void CTableModel::newGame()
{
    qDebug() << "New game";

    if (m_model != nullptr)
    {
        delete m_model;
        m_model = nullptr;
    }

    m_model = new CModel(10,10);
    m_model->populate();
}

void CTableModel::onTableClicked(const QModelIndex &index)
{
    qDebug() << "Clicked: " << index.row() << "," << index.column();

    discover(index);

    if (m_model->field(index.row(), index.column()).sheep)
    {
        qDebug() << "You loose!";
        emit gameLost();
        //TODO: freeze the view
    }

    if (m_model->checkIfWon())
    {
        qDebug() << "You win!";
        emit gameWon();
        //TODO: discover all when won
    }
}

//TODO: do not discover secured fields
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
    qDebug() << "Right clicked: " << index.row() << "," << index.column();
    m_model->disarm(index.row(), index.column());
    qDebug() << m_model->field(index.row(), index.column()).disarmed;
    emit dataChanged(index, index);
}
