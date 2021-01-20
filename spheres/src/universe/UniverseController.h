#pragma once

#include "SectorGenerator.h"
#include "glcomponent/Camera.h"

class UniverseController
{
private:
    UniverseController() {}

public:
    Sector LastCameraSector = {0, 0, 0};
    unsigned int StarCount = 25000;
    unsigned int StarProbability = 100;
    long SectorSize = 100;
    double SectorDepthLimit = std::pow(1000.0, 3);
    unsigned int HighQualitySectorRange = 5;
    float MinStarRadius = 3.0f;
    float MaxStarRadius = 15.0f;
    int HighStarQuality = 100;
    int MidStarQuality = 17;
    int LowStarQuality = 5;
    double StarQualityRatio[3] = {1.0, 30.0, 300.0};

    static UniverseController &GET()
    {
        static UniverseController instance;
        return instance;
    }

    static void PrintSectors(Sector *sectors, uint32_t count)
    {
        for (uint32_t i = 0; i < count; i++)
        {
            sectors[i].print();
        }
    }

    static SectorArray SurroundingActiveSector()
    {
        UniverseController UC = GET();
        return SectorGenerator::GenerateSurroundingActiveSectors(CameraSector(), UC.StarCount, UC.SectorDepthLimit, UC.SectorSize, UC.StarProbability);
    }

    static Sector CameraSector()
    {
        float sectorSize = GET().SectorSize;
        glm::vec3 campos = Camera::CurrentPos();
        Sector camsec;
        camsec.x = util::DivideLong(campos.x, sectorSize / 2);
        camsec.y = util::DivideLong(campos.y, sectorSize / 2);
        camsec.z = util::DivideLong(campos.z, sectorSize / 2);
        return camsec;
    }

    static bool IsCameraOutOfHighQualityRange()
    {
        auto range = GET().HighQualitySectorRange;
        auto dist = CameraSector() - GET().LastCameraSector;
        if (std::abs(dist.x) >= range ||
            std::abs(dist.y) >= range ||
            std::abs(dist.z) >= range)
        {
            GET().LastCameraSector = CameraSector();
            return true;
        }
        // std::cout << "distx: " << dist.x << " disty: " << dist.y << " distz: " << dist.z << std::endl;
        return false;
    }

    static double TotalQualityRatio()
    {
        auto UC = GET();
        return UC.StarQualityRatio[0] + UC.StarQualityRatio[1] + UC.StarQualityRatio[2];
    }
};