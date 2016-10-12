#ifndef CMODEL_H
#define CMODEL_H

#include <stdint.h>
#include <vector>
#include <model/SField.h>

namespace SSw
{

class CModel
{
public:
    CModel();

    int32_t         width()  const { return m_width; }
    int32_t         height() const { return m_height; }
    int64_t         size()   const { return m_width * m_height; }

    void            reset(int32_t width, int32_t height, int32_t sheepNumber);
    void            populate(int32_t xToSkip, int32_t yToSkip);

    uint8_t         countFlagsAround(int32_t x, int32_t y) const;
    uint8_t         getNeighbours(int32_t x, int32_t y) const;
    uint8_t         getSheep(int32_t x, int32_t y) const;
    uint8_t         getFlag(int32_t x, int32_t y) const;
    bool            getDiscovered(int32_t x, int32_t y) const;

    void            discover(int32_t x, int32_t y);
    void            disarm(int32_t x, int32_t y);
    bool            checkWinCondition() const;

    SField&         field(int32_t x, int32_t y);
    const SField&   field(int32_t x, int32_t y) const;

private:
    void            populateSheepCrew(int32_t xToSkip, int32_t yToSkip);
    void            populateNeighbourhood();
    bool            isValidIndex(int32_t x, int32_t y) const;

    int32_t             m_width;
    int32_t             m_height;
    int32_t             m_totalSheepNr;
    int32_t             m_discoveredFieldsNr;
    std::vector<SField> m_data;
};

} // namespace SSw

#endif // CMODEL_H
