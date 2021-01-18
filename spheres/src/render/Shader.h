#pragma once

#include <glm/gtc/type_ptr.hpp>
#include <fstream>

class Shader
{
public:
    Shader() {}
    ~Shader();

    // return shader program ID
    GLuint getProgramID();

    // return shader uniform ID for 'mvp'
    GLuint getMVPID();

    // bind program state
    void bind();

    // unbind program state
    void unbind();

    // clear opengl shader program
    void clear();

    // set uniform of matrix 4x4
    void setMat4(const char *name, const glm::mat4 &mat) const;

    // create shaders from file
    void compileFromFile(const char *vPath, const char *fPath);

    // create shaders from chars
    void compileShader(const char *vCode, const char *fCode);

private:
    GLuint programID;

    // add shader to opengl state
    void addShader(const char *shaderCode, GLenum shaderType);

    // read from filepath and pass data to content
    void readFile(const char *filepath, std::string *content);
};