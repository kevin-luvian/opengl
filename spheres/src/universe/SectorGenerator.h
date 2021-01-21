#pragma once

#include "Sector.h"
#include "randoms/RGEN.h"

class SectorGenerator
{
private:
    SectorGenerator() {}

public:
    static DetailedArray<Sector> GenerateSurroundingActiveSectors(Sector center, unsigned int total, double limit, double sectorSize, unsigned int starProbability);
    static DetailedArray<Sector> GenerateSurroundingSectors(long bound);
    static void GenerateTopBottomSurroundingSectors( DetailedArray<Sector> &target, long bound,long &offset);
    static void GenerateHorizontalSectors(DetailedArray<Sector> &target, long bound, long y, long &offset);
};