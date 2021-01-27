#pragma once

#include <glm/gtc/type_ptr.hpp>
#include <fstream>

class Shader
{
public:
    Shader();
    ~Shader();

    // return shader program ID
    GLuint getProgramID();

    void setMat4(const char *name, const glm::mat4 &mat) const { glUniformMatrix4fv(glGetUniformLocation(programID, name), 1, GL_FALSE, glm::value_ptr(mat)); }
    void set4f(const char *name, const glm::vec4 &val) const { glUniform4f(glGetUniformLocation(programID, name), val.x, val.y, val.z, val.w); }
    void set3f(const char *name, const glm::vec3 &vec) const { glUniform3f(glGetUniformLocation(programID, name), vec.x, vec.y, vec.z); }
    void set1f(const char *name, float val) const { glUniform1f(glGetUniformLocation(programID, name), val); }

    // bind program state
    void bind();

    // unbind program state
    void unbind();

    // clear opengl shader program
    void clear();

    // create shaders from file
    void compileFromFile(const char *vPath, const char *fPath);

    // create shaders from chars
    void compileShader(const char *vCode, const char *fCode);

private:
    GLuint programID, mvpID;

    // add shader to opengl state
    void addShader(const char *shaderCode, GLenum shaderType);

    // read from filepath and pass data to content
    void readFile(const char *filepath, std::string *content);
};