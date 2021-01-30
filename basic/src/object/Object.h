#pragma once

#include "Renderable.h"
#include "draw/renderer/RendererManager.h"
#include "mesh/Meshes.h"

class Object : public Renderable
{
protected:
    glm::mat4 mModel;
    glm::vec4 mColour;
    glm::vec3 mPosition;
    float mSize;
    bool shouldUpdate;

    virtual void setMesh() override = 0;
    virtual void setMaterial() override { material = std::make_unique<Material>(); }
    virtual void setShaderType() override { shaderType = Enum::ShaderType::Simple; }
    virtual void setRenderer() override
    {
        auto gRenderer = RendererManager::CreateRendererFromShaderType(shaderType);
        renderer = std::unique_ptr<Renderer>(gRenderer);
    }

public:
    Object()
    {
        shouldUpdate = true;
        mModel = glm::mat4(1);
        mPosition = glm::vec3(0);
        mSize = 1.0f;
        mColour = glm::vec4(1);
    }
    virtual ~Object() {}
    glm::mat4 getModel() { return mModel; }
    glm::vec3 getPosition() { return mPosition; }
    glm::vec4 getColour() { return mColour; }
    float getSize() { return mSize; }
    void setPosition(glm::vec3 position)
    {
        shouldUpdate = true;
        mPosition = position;
    }
    void setSize(float size)
    {
        shouldUpdate = true;
        mSize = size;
    }
    void setColour(glm::vec4 colour) { mColour = colour; }
    void update()
    {
        if (shouldUpdate)
        {
            shouldUpdate = false;
            mModel = glm::mat4(1.0f);
            mModel = glm::translate(mModel, mPosition);
            mModel = glm::scale(mModel, glm::vec3(mSize, mSize, mSize));
        }
    }
};