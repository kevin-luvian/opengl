#pragma once

#include <cstring>
#include <unordered_map>
#include <glm/gtc/type_ptr.hpp>

#include "glComponent/Camera.h"
#include "ShaderType.h"

class Shader
{
private:
    std::unordered_map<std::string, unsigned int> ulookup;

    unsigned int getUniformLocation(std::string name);

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
    void setMat4(std::string name, const glm::mat4 &mat);
    void set1i(std::string name, int i);
    void set1f(std::string name, float f);
    void set3f(std::string name, unit::color c);
    void set3f(std::string name, unit::vec3 v);
    void set3f(std::string name, float x, float y, float z);
    virtual void compile() { shaderType = mShaderType(); };
    virtual void attachCamera()
    {
        setMat4(GLSLI::VVIEW_PROJECTION, Camera::ViewProjection());
    }
};