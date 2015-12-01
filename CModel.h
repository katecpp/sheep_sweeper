#ifndef CMODEL_H
#define CMODEL_H

#include <stdint.h>
#include <vector>
#include <SField.h>

class CModel
{
public:
    CModel(int32_t size, int32_t sheepNumber);

    uint8_t     getSheepValue(int32_t x, int32_t y) const;
    int32_t     size() const { return m_size; }
    uint64_t    count() const { return m_size * m_size; }
    void        populate();
    void        printDebug() const;

    void discover(int32_t x, int32_t y);
    void disarm(int32_t x, int32_t y);
    void secure(int32_t x, int32_t y);

    SField& field(int32_t x, int32_t y);
    const SField& field(int32_t x, int32_t y) const;

private:
    void populateSheepCrew();
    void populateNeighbourhood();

    int32_t             m_size;
    int32_t             m_sheepNumber;
    std::vector<SField> m_data;
};


#endif // CMODEL_H
