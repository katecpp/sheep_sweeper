#include <model/CModel.h>
#include <cstdlib>
#include <ctime>
#include <QDebug>

namespace SSw
{

using std::rand;

CModel::CModel()
    : m_width(0),
      m_height(0),
      m_totalSheepNr(0),
      m_discoveredFieldsNr(0),
      m_data()
{
}

bool CModel::checkIfWon() const
{
    return (size() - m_discoveredFieldsNr) == m_totalSheepNr;
}

void CModel::reset(int32_t width, int32_t height, int32_t sheepNumber)
{
    m_width         = width;
    m_height        = height;
    m_totalSheepNr  = sheepNumber;
    m_discoveredFieldsNr = 0;
    m_data.clear();

    int64_t fieldsNr = size();
    m_data.reserve(fieldsNr);
    m_data.insert(m_data.begin(), fieldsNr, SField());

    srand(std::time(0));
}

void CModel::populate(int32_t x, int32_t y)
{
    populateSheepCrew(x, y);
    populateNeighbourhood();
}

void CModel::populateSheepCrew(int32_t x, int32_t y)
{
    Q_ASSERT(m_totalSheepNr < size());
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
                    getSheep   (x-1,   y-1) // up
                    + getSheep (x,     y-1)
                    + getSheep (x+1,   y-1)
                    + getSheep (x-1,   y)   // mid
                    + getSheep (x,     y)
                    + getSheep (x+1,   y)
                    + getSheep (x-1,   y+1) // down
                    + getSheep (x,     y+1)
                    + getSheep (x+1,   y+1);

            field(x,y).neighbours = sheepValue;
        }
    }
}

uint8_t CModel::getFlag(int32_t x, int32_t y) const
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
    return getFlag    (x-1,   y-1) // up
            + getFlag (x,     y-1)
            + getFlag (x+1,   y-1)
            + getFlag (x-1,   y)   // mid
            + getFlag (x,     y)
            + getFlag (x+1,   y)
            + getFlag (x-1,   y+1) // down
            + getFlag (x,     y+1)
            + getFlag (x+1,   y+1);
}

uint8_t CModel::getNeighbours(int32_t x, int32_t y) const
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

uint8_t CModel::getSheep(int32_t x, int32_t y) const
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

uint8_t CModel::getDiscovered(int32_t x, int32_t y) const
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
    Q_ASSERT(id >= 0 && id < size());
    return m_data.at(id);
}

SField& CModel::field(int32_t x, int32_t y)
{
    int32_t id = y * m_width + x;
    Q_ASSERT(id >= 0 && id < size());
    return m_data[id];
}

} // namespace SSw

