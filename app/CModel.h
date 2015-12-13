#ifndef CMODEL_H
#define CMODEL_H

#include <stdint.h>
#include <vector>
#include <SField.h>

namespace SSw
{

class CModel
{
public:
    CModel(int32_t width, int32_t height, int32_t sheepNumber);

    int32_t         width()  const { return m_width; }
    int32_t         height() const { return m_height; }
    int64_t         size()   const { return m_width * m_height; }

    void            reset(int32_t width, int32_t height, int32_t sheepNumber);
    void            populate(int32_t x, int32_t y);

    uint8_t         countFlagsAround(int32_t x, int32_t y) const;
    uint8_t         getNeighbours(int32_t x, int32_t y) const;
    uint8_t         getSheep(int32_t x, int32_t y) const;
    uint8_t         getFlag(int32_t x, int32_t y) const;
    uint8_t         getDiscovered(int32_t x, int32_t y) const;

    void            discover(int32_t x, int32_t y);
    void            disarm(int32_t x, int32_t y);
    bool            checkIfWon() const;

    SField&         field(int32_t x, int32_t y);
    const SField&   field(int32_t x, int32_t y) const;

private:
    void            createBoard();
    void            populateSheepCrew(int32_t x, int32_t y);
    void            populateNeighbourhood();

    int32_t             m_width;
    int32_t             m_height;
    int32_t             m_totalSheepNr;
    int32_t             m_discoveredFieldsNr;
    std::vector<SField> m_data;
};

} // namespace SSw

#endif // CMODEL_H
