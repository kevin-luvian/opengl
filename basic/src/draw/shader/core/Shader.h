#pragma once

#include <cstring>
#include <unordered_map>
#include <glm/gtc/type_ptr.hpp>

#include "glComponent/Camera.h"
#include "GLSLInterface.h"
#include "ShaderType.h"

class Shader
{
private:
    std::unordered_map<std::string, unsigned int> ulookup;

    unsigned int getUniformLocation(const std::string &name);

    // add shader to opengl state
    void addShader(const char *shaderCode, GLenum shaderType) const;

    // read from filepath and pass data to content
    void readFile(const char *filepath, std::string &content) const;

protected:
    unsigned int programID;
    ShaderType shaderType;

    Shader()
    {
        std::cout << "creating Shader\n";
        programID = 0;
    }

    virtual ShaderType mShaderType() = 0;
    void compileFromFile(const char *vPath, const char *fPath);
    void compileShader(const char *vCode, const char *fCode);

public:
    virtual ~Shader() {}

    unsigned int getProgramID() const;
    ShaderType getShaderType() { return shaderType; };

    void clear();
    void bind() const;
    void unbind() const;
    void setMat4(const std::string &name, const glm::mat4 &mat);
    virtual void compile() { shaderType = mShaderType(); };
    virtual void attachCamera()
    {
        setMat4(GLSLI::VVIEW_PROJECTION, Camera::ViewProjection());
    }
};