#include "SectorGenerator.h"

DetailedArray<Sector> SectorGenerator::GenerateSurroundingActiveSectors(Sector center, unsigned int total, double limit, double sectorSize, unsigned int starProbability)
{
    BENCHMARK_PROFILE();
    DetailedArray<Sector> activeSectors;
    activeSectors.data = std::make_unique<Sector[]>(total);
    activeSectors.size = total;

    unsigned int bound = 0;
    DetailedArray<Sector> sectorsToVisit = GenerateSurroundingSectors(bound++);

    Sector currentSector;
    unsigned int activeSectorCount = 0;
    unsigned int stvCounter = 0;
    for (unsigned int i = 0; i < limit; i++)
    {
        if (activeSectorCount == total)
            break;
        currentSector = sectorsToVisit[stvCounter++];
        currentSector.appendPos(center.x, center.y, center.z);
        if (RGEN::NoUpdateRandom(currentSector.seed(), 0, starProbability) == 0)
        {
            activeSectors[activeSectorCount++] = currentSector;
        }
        if (stvCounter == sectorsToVisit.size)
        {
            stvCounter = 0;
            sectorsToVisit = GenerateSurroundingSectors(bound++);
        }
    }
    DetailedArray<Sector> res;
    res.make_empty(activeSectorCount);
    res.insert(activeSectors);
    // std::cout << "active sectors found: " << activeSectorCount << std::endl;
    return res;
}

DetailedArray<Sector> SectorGenerator::GenerateSurroundingSectors(long bound)
{
    if (bound == 0)
    {
        DetailedArray<Sector> res;
        res.make_empty(1);
        res[0] = {0.0, 0.0, 0.0};
        return res;
    }

    long totalSize = std::pow(2 * bound + 1, 3) - std::pow(2 * bound - 1, 3);
    long offset = 0;

    DetailedArray<Sector> sectors;
    sectors.make_empty(totalSize);

    GenerateTopBottomSurroundingSectors(sectors, bound, offset);

    long segSize = bound - 1;
    for (long y = -segSize; y <= segSize; y++)
    {
        GenerateHorizontalSectors(sectors, bound, y, offset);
    }

    return sectors;
}

void SectorGenerator::GenerateTopBottomSurroundingSectors(DetailedArray<Sector> &target, long bound, long &offset)
{
    for (const long &y : {-bound, bound})
    {
        for (long x = -bound; x <= bound; x++)
        {
            for (long z = -bound; z <= bound; z++)
            {
                target[offset++] = {x + 0.0, y + 0.0, z + 0.0};
            }
        }
    }
}

void SectorGenerator::GenerateHorizontalSectors(DetailedArray<Sector> &target, long bound, long y, long &offset)
{
    for (long z = -bound; z <= bound; z++)
    {
        if (z == -bound || z == bound)
        {
            for (long x = -bound; x <= bound; x++)
            {
                target[offset++] = {x + 0.0, y + 0.0, z + 0.0};
            }
        }
        else
        {
            target[offset++] = {-bound + 0.0, y + 0.0, z + 0.0};
            target[offset++] = {bound + 0.0, y + 0.0, z + 0.0};
        }
    }
}