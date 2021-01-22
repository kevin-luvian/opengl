#pragma once

#include "ScreenState.h"
#include "universe/Sector.h"
#include "universe/UniverseState.h"
#include "universe/SectorGenerator.h"

class Camera
{
private:
    bool firstMoveFlag;
    float turnSpeed = 0.1f, deltaTime = 0.0f, lastFrame = 0.0f, viewRange = 1500.0f;
    glm::mat4 projection;
    glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 worldUp, camFront, camRight, camUp;
    glm::vec2 viewTarget, curViewTarget;
    float yaw, pitch;

    Camera();
    void updateValues();

public:
    Sector lastSectorPosition = {0, 0, 0};
    bool autoMoveForward = false;
    float moveSpeed = 50.0f;

    void initiate();
    void checkKeys();
    void mouseMove(float x, float y);
    void updateScreenSize();
    glm::mat4 getViewProjection();

    static Camera &GET();
    static glm::mat4 ViewProjection() { return GET().getViewProjection(); }
    static glm::vec3 CurrentPos() { return GET().pos; }

    static Sector CurrentSector()
    {
        glm::vec3 campos = CurrentPos();
        Sector camsec;
        camsec.x = util::DivideLong(campos.x, UniverseState::SectorSize / 2);
        camsec.y = util::DivideLong(campos.y, UniverseState::SectorSize / 2);
        camsec.z = util::DivideLong(campos.z, UniverseState::SectorSize / 2);
        return camsec;
    }

    static bool OutOfNearViewSectorRange()
    {
        long range = UniverseState::NearViewSectorRange;
        auto dist = CurrentSector() - GET().lastSectorPosition;
        if (std::abs(dist.x) >= range ||
            std::abs(dist.y) >= range ||
            std::abs(dist.z) >= range)
        {
            GET().lastSectorPosition = CurrentSector();
            return true;
        }
        // std::cout << "distx: " << dist.x << " disty: " << dist.y << " distz: " << dist.z << std::endl;
        return false;
    }

    static DetailedArray<Sector> GetSurroundingActiveSector()
    {
        return SectorGenerator::GenerateSurroundingActiveSectors(
            CurrentSector(),
            UniverseState::TotalStarCount(),
            UniverseState::SectorDepthLimit,
            UniverseState::SectorSize,
            UniverseState::StarProbability);
    }
};