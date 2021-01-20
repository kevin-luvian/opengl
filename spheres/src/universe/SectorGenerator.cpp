#include "SectorGenerator.h"

void SectorGenerator::CombineSectors(SectorArray &target, SectorArray &source, long offset, long moveSize)
{
    for (long i = 0; i < moveSize; i++)
    {
        target.sectors[offset + i] = source.sectors[i];
    }
}

void SectorGenerator::CombineSectors(SectorArray &target, SectorArray &source, long offset)
{
    // for (long i = 0; i < source.size; i++)
    // {
    //     target.sectors[offset + i] = source.sectors[i];
    // }
    CombineSectors(target, source, offset, source.size);
}

SectorArray SectorGenerator::GenerateSurroundingActiveSectors(Sector center, unsigned int total, double limit, double sectorSize, unsigned int starProbability)
{
    SectorArray activeSectors;
    activeSectors.sectors = std::make_unique<Sector[]>(total);
    activeSectors.size = total;

    unsigned int bound = 0;
    SectorArray sectorsToVisit = GenerateSurroundingSectors(bound++);

    Sector currentSector;
    unsigned int activeSectorCount = 0;
    unsigned int stvCounter = 0;
    for (unsigned int i = 0; i < limit; i++)
    {
        if (activeSectorCount == total)
            break;
        currentSector = sectorsToVisit.sectors[stvCounter];
        currentSector.appendPos(center.x, center.y, center.z);
        if (RGEN::NoUpdateRandom(currentSector.seed(), 0, starProbability) == 0)
        {
            activeSectors.sectors[activeSectorCount++] = currentSector;
        }
        stvCounter++;
        if (stvCounter == sectorsToVisit.size)
        {
            stvCounter = 0;
            sectorsToVisit = GenerateSurroundingSectors(bound++);
        }
    }
    SectorArray res;
    res.sectors = std::make_unique<Sector[]>(activeSectorCount);
    res.size = activeSectorCount;
    CombineSectors(res, activeSectors, 0, activeSectorCount);
    // std::cout << "active sectors found: " << activeSectorCount << std::endl;
    return res;
}

SectorArray SectorGenerator::GenerateSurroundingSectors(long bound)
{
    if (bound == 0)
    {
        SectorArray res;
        res.sectors = std::make_unique<Sector[]>(1);
        res.sectors[0] = {0.0, 0.0, 0.0};
        res.size = 1;
        return res;
    }

    long totalSize = std::pow(2 * bound + 1, 3) - std::pow(2 * bound - 1, 3);
    long offset = 0;

    SectorArray res;
    res.sectors = std::make_unique<Sector[]>(totalSize);
    res.size = totalSize;

    SectorArray topBottomSectors = GenerateTopBottomSurroundingSectors(bound);
    CombineSectors(res, topBottomSectors, offset);
    offset += topBottomSectors.size;

    long segSize = bound - 1;
    for (long y = -segSize; y <= segSize; y++)
    {
        SectorArray temp = GenerateHorizontalSectors(bound, y);
        CombineSectors(res, temp, offset);
        offset += temp.size;
    }

    return res;
}

SectorArray SectorGenerator::GenerateTopBottomSurroundingSectors(long bound)
{
    SectorArray res;
    uint32_t count = 0;
    long segCount = (bound * 2 + 1);
    long totalCount = 2 * segCount * segCount;
    std::unique_ptr<Sector[]> sectors = std::make_unique<Sector[]>(totalCount);
    for (const long &y : {-bound, bound})
    {
        for (long x = -bound; x <= bound; x++)
        {
            for (long z = -bound; z <= bound; z++)
            {
                sectors[count++] = {x + 0.0, y + 0.0, z + 0.0};
            }
        }
    }
    res.sectors = std::move(sectors);
    res.size = totalCount;
    return res;
}

SectorArray SectorGenerator::GenerateHorizontalSectors(long bound, long y)
{
    SectorArray res;
    long segCount = (bound * 2 + 1);
    long totalCount = 2 * segCount + 2 * (segCount - 2);
    std::unique_ptr<Sector[]> sectors = std::make_unique<Sector[]>(totalCount);
    long count = 0;
    for (long z = -bound; z <= bound; z++)
    {
        if (z == -bound || z == bound)
        {
            for (long x = -bound; x <= bound; x++)
            {
                sectors[count++] = {x + 0.0, y + 0.0, z + 0.0};
            }
        }
        else
        {
            sectors[count++] = {-bound + 0.0, y + 0.0, z + 0.0};
            sectors[count++] = {bound + 0.0, y + 0.0, z + 0.0};
        }
    }
    res.sectors = std::move(sectors);
    res.size = totalCount;
    return res;
}