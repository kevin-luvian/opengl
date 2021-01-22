#pragma once

namespace UniverseState
{
    static long SectorSize = 100;
    static long NearViewSectorRange = 5;
    static double CameraViewRange = 700.0;
    static double SectorDepthLimit = std::pow(200.0, 3);
    static unsigned int StarProbability = 1;
    static float StarRadius[2] = {3.0f, 15.0f};           // order: min, max
    static unsigned int StarQuality[3] = {5, 15, 30};     // order: low, mid, high
    static unsigned int StarCount[3] = {1000, 0, 2}; // order: low, mid, high

    static unsigned int TotalStarCount()
    {
        return StarCount[0] + StarCount[1] + StarCount[2];
    }
} // namespace UniverseState