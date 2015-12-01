#include <CModel.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <assert.h>

using std::cout;
using std::rand;

CModel::CModel(int32_t size, int32_t sheepNumber)
    : m_size(size)
    , m_sheepNumber(sheepNumber)
{
    uint64_t fieldsNumber = m_size * m_size;
    m_data.reserve(fieldsNumber);
    m_data.insert(m_data.begin(), fieldsNumber, SField{0,0,0,0,0});

    srand(std::time(0));

    cout << "CModel initialized succesfully" << std::endl;
}

void CModel::populate()
{
    populateSheepCrew();
    populateNeighbourhood();
}

void CModel::populateSheepCrew()
{
    uint64_t sheepMade = 0;

    while (sheepMade < m_sheepNumber)
    {
        uint64_t fieldId = rand() % count();
        assert(fieldId < m_data.size());

        if (0 == m_data[fieldId].sheep)
        {
            m_data[fieldId].sheep = 1;
            sheepMade++;
            cout << "Sheep made on field " << fieldId << std::endl;
        }
    }

    cout << "Sheep crew is ready..." << std::endl;
}

void CModel::populateNeighbourhood()
{
    for (uint32_t x = 0; x < m_size; ++x)
    {
        for (uint32_t y = 0; y < m_size; ++y)
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

void CModel::discover(int32_t x, int32_t y)
{
    field(x, y).discovered = 1;
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
            cout << std::endl;
        }

        std::string f = "[" + (m_data[i].sheep ? "x" : std::to_string(m_data[i].neighbours)) + "]";
        cout << f;
    }
}

