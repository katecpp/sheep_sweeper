#ifndef CMODEL_H
#define CMODEL_H

#include <stdint.h>
#include <vector>
#include <SField.h>

class CModel
{
public:
    CModel(int32_t width, int32_t height, int32_t sheepNumber);

    bool        checkIfWon() const;

    uint8_t     getSheepValue(int32_t x, int32_t y) const;
    uint8_t     getDiscoverValue(int32_t x, int32_t y) const;

    int32_t     width() const { return m_width; }
    int32_t     height() const { return m_height; }
    int64_t     size() const { return m_width * m_height; }

    void        populate();

    void discover(int32_t x, int32_t y);
    void disarm(int32_t x, int32_t y);

    SField& field(int32_t x, int32_t y);
    const SField& field(int32_t x, int32_t y) const;

private:
    void populateSheepCrew();
    void populateNeighbourhood();

    int32_t             m_width;
    int32_t             m_height;
    int32_t             m_totalSheepNr;
    int32_t             m_lurkingSheepNr;
    int32_t             m_discoveredFieldsNr;
    std::vector<SField> m_data;
};


#endif // CMODEL_H
