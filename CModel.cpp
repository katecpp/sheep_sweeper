#include <CModel.h>
#include <cstdlib>
#include <ctime>
#include <QDebug>

using std::rand;

CModel::CModel(int32_t size, int32_t sheepNumber)
    : m_size(size)
    , m_totalSheepNr(sheepNumber)
    , m_lurkingSheepNr(sheepNumber)
    , m_discoveredFieldsNr(0)
    , m_data()
{
    uint64_t fieldsNumber = m_size * m_size;
    m_data.reserve(fieldsNumber);
    m_data.insert(m_data.begin(), fieldsNumber, SField());

    srand(std::time(0));
}

bool CModel::checkIfWon() const
{
    return (count() - m_discoveredFieldsNr) == m_totalSheepNr;
}

void CModel::populate()
{
    populateSheepCrew();
    populateNeighbourhood();
}

void CModel::populateSheepCrew()
{
    Q_ASSERT(m_totalSheepNr <= count());
    int64_t sheepMade = 0;

    while (sheepMade < m_totalSheepNr)
    {
        uint64_t fieldId = rand() % count();
        Q_ASSERT(fieldId < m_data.size());

        if (0 == m_data[fieldId].sheep)
        {
            m_data[fieldId].sheep = 1;
            sheepMade++;
        }
    }

    qDebug() << "Sheep crew is ready...";
}

void CModel::populateNeighbourhood()
{
    for (int32_t x = 0; x < m_size; ++x)
    {
        for (int32_t y = 0; y < m_size; ++y)
        {
            uint8_t sheepValue =
                    getSheepValue   (x-1,   y-1) // up
                    + getSheepValue (x,     y-1)
                    + getSheepValue (x+1,   y-1)
                    + getSheepValue (x-1,   y)   // mid
                    + getSheepValue (x,     y)
                    + getSheepValue (x+1,   y)
                    + getSheepValue (x-1,   y+1) // down
                    + getSheepValue (x,     y+1)
                    + getSheepValue (x+1,   y+1);

            field(x,y).neighbours = sheepValue;
        }
    }
}

uint8_t CModel::getSheepValue(int32_t x, int32_t y) const
{
    if (x >= 0 && x < m_size && y >= 0 && y < m_size)
    {
        return field(x,y).sheep;
    }
    else
    {
        return 0;
    }
}

uint8_t CModel::getDiscoverValue(int32_t x, int32_t y) const
{
    if (x >= 0 && x < m_size && y >= 0 && y < m_size)
    {
        return field(x,y).discovered;
    }
    else
    {
        return true;
    }
}

void CModel::discover(int32_t x, int32_t y)
{
    if (field(x, y).discovered == 0 && field(x,y).disarmed == 0 && field(x,y).secured == 0)
    {
        field(x, y).discovered = 1;
        m_discoveredFieldsNr++;
    }
}

void CModel::disarm(int32_t x, int32_t y)
{
    field(x, y).disarmed = 1;
}

void CModel::secure(int32_t x, int32_t y)
{
    field(x, y).secured = 1;
}

const SField& CModel::field(int32_t x, int32_t y) const
{
    return m_data[y * m_size + x];
}

SField& CModel::field(int32_t x, int32_t y)
{
    return m_data[y * m_size + x];
}

void CModel::printDebug() const
{
    for (uint64_t i = 0; i < count(); ++i)
    {
        if (i > 0 && i % m_size == 0)
        {
            qDebug() << "\n";
        }

        QString f = "[" + (m_data[i].sheep ? "x" : QString::number(m_data[i].neighbours)) + "]";
        qDebug() << f;
    }
}

