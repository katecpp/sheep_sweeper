#include <CModel.h>
#include <cstdlib>
#include <ctime>
#include <QDebug>

namespace SSw
{

using std::rand;

CModel::CModel(int32_t width, int32_t height, int32_t sheepNumber)
    : m_width(width),
      m_height(height),
      m_totalSheepNr(sheepNumber),
      m_discoveredFieldsNr(0),
      m_data()
{
    createBoard();
}

//BUG: Once returned false positive
bool CModel::checkIfWon() const
{
    return (size() - m_discoveredFieldsNr) == m_totalSheepNr;
}

void CModel::createBoard()
{
    int64_t fieldsNr = size();
    m_data.reserve(fieldsNr);
    m_data.insert(m_data.begin(), fieldsNr, SField());

    srand(std::time(0));
}

void CModel::reset(int32_t width, int32_t height, int32_t sheepNumber)
{
    qDebug() << "CModel::reset " << width << ", " << height << ", " << sheepNumber;
    m_width = width;
    m_height = height;
    m_totalSheepNr = sheepNumber;
    m_discoveredFieldsNr = 0;
    m_data.clear();

    createBoard();
}

void CModel::populate(int32_t x, int32_t y)
{
    populateSheepCrew(x, y);
    populateNeighbourhood();
}

void CModel::populateSheepCrew(int32_t x, int32_t y)
{
    Q_ASSERT(m_totalSheepNr <= size());
    uint64_t noSheepFieldId = y * m_width + x;
    int64_t sheepMade       = 0;

    while (sheepMade < m_totalSheepNr)
    {
        uint64_t fieldId = rand() % size();
        Q_ASSERT(fieldId < m_data.size());

        if ((0 == m_data[fieldId].sheep) && (fieldId != noSheepFieldId))
        {
            m_data[fieldId].sheep = 1;
            sheepMade++;
        }
    }
}

void CModel::populateNeighbourhood()
{
    for (int32_t x = 0; x < m_width; ++x)
    {
        for (int32_t y = 0; y < m_height; ++y)
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

uint8_t CModel::getFlagValue(int32_t x, int32_t y) const
{
    if (x >= 0 && x < m_width && y >= 0 && y < m_height)
    {
        return field(x,y).disarmed == 1 ? 1 : 0;
    }
    else
    {
        return 0;
    }
}

uint8_t CModel::countFlagsAround(int32_t x, int32_t y) const
{
    return getFlagValue    (x-1,   y-1) // up
            + getFlagValue (x,     y-1)
            + getFlagValue (x+1,   y-1)
            + getFlagValue (x-1,   y)   // mid
            + getFlagValue (x,     y)
            + getFlagValue (x+1,   y)
            + getFlagValue (x-1,   y+1) // down
            + getFlagValue (x,     y+1)
            + getFlagValue (x+1,   y+1);
}

uint8_t CModel::getNeighboursCount(int32_t x, int32_t y) const
{
    if (x >= 0 && x < m_width && y >= 0 && y < m_height)
    {
        return field(x,y).neighbours;
    }
    else
    {
        return 0;
    }
}

uint8_t CModel::getSheepValue(int32_t x, int32_t y) const
{
    if (x >= 0 && x < m_width && y >= 0 && y < m_height)
    {
        return field(x,y).sheep;
    }
    else
    {
        return 0;
    }
}

uint8_t CModel::isDiscovered(int32_t x, int32_t y) const
{
    if (x >= 0 && x < m_width && y >= 0 && y < m_height)
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
    if (field(x, y).discovered == 0 && field(x,y).disarmed == 0)
    {
        field(x, y).discovered = 1;
        m_discoveredFieldsNr++;
    }
}

void CModel::disarm(int32_t x, int32_t y)
{
    if (field(x, y).disarmed < 2)
    {
        field(x, y).disarmed++;
    }
    else if (field(x, y).disarmed == 2)
    {
        field(x, y).disarmed = 0;
    }
}

const SField& CModel::field(int32_t x, int32_t y) const
{
    int32_t id = y * m_width + x;
    Q_ASSERT(id < size());
    Q_ASSERT(id >= 0);
    return m_data.at(id);
}

SField& CModel::field(int32_t x, int32_t y)
{
    int32_t id = y * m_width + x;
    Q_ASSERT(id < size());
    Q_ASSERT(id >= 0);
    return m_data[id];
}

} // namespace SSw

