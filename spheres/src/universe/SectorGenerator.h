#pragma once

#include "Sector.h"
#include "randoms/RGEN.h"

struct SectorArray
{
    std::unique_ptr<Sector[]> sectors;
    uint32_t size;
};

class SectorGenerator
{
private:
    SectorGenerator() {}
    static void CombineSectors(SectorArray &target, SectorArray &source, long offset, long moveSize);
    static void CombineSectors(SectorArray &target, SectorArray &source, long offset);

public:
    static SectorArray GenerateSurroundingActiveSectors(Sector center, unsigned int total, double limit, double sectorSize, unsigned int starProbability);
    static SectorArray GenerateSurroundingSectors(long bound);
    static SectorArray GenerateTopBottomSurroundingSectors(long bound);
    static SectorArray GenerateHorizontalSectors(long bound, long y);
};