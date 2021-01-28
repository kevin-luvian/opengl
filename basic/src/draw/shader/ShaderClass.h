#pragma once

#include <unordered_map>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include "shape/ShapeClass.h"

class ShaderClass
{
public:
    std::unordered_map<std::string, unsigned int> uniformLookup;

    explicit ShaderClass() { programID = 0; };
    virtual ~ShaderClass() { clear(); };

    // return shader program ID
    unsigned int getProgramID() const { return programID; };

    virtual void compile() = 0;
    virtual void attachShape(ShapeClass *shape) = 0;

    unsigned int getUniformLocation(std::string name)
    {
        auto it = uniformLookup.find(name);
        if (it != uniformLookup.end())
            return it->second;
        unsigned int uLoc = glGetUniformLocation(programID, name.c_str());
        uniformLookup.insert(std::make_pair(name, uLoc));
        return uLoc;
    }
    void setMat4(std::string name, const glm::mat4 &mat)
    {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
    }
    void set4f(std::string name, const glm::vec4 &val)
    {
        glUniform4f(getUniformLocation(name), val.x, val.y, val.z, val.w);
    }
    void set3f(std::string name, const glm::vec3 &vec)
    {
        glUniform3f(getUniformLocation(name), vec.x, vec.y, vec.z);
    }
    void set1f(std::string name, float val)
    {
        glUniform1f(getUniformLocation(name), val);
    }

    // bind program state
    virtual void bind() { glUseProgram(programID); }

    // unbind program state
    virtual void unbind() { glUseProgram(0); }

    // clear opengl shader program
    virtual void clear()
    {
        if (programID != 0)
            glDeleteProgram(programID);
        programID = 0;
    }

protected:
    unsigned int programID;

    // create shaders from file
    void compileFromFile(const char *vPath, const char *fPath)
    {
        BENCHMARK_PROFILE();
        std::string vContent;
        std::string fContent;

        readFile(vPath, &vContent);
        readFile(fPath, &fContent);

        // std::cout << "v content:: " << vContent << "\n\nf content:: " << fContent << std::endl;

        compileShader(vContent.c_str(), fContent.c_str());
    }

    // create shaders from chars
    void compileShader(const char *vCode, const char *fCode)
    {
        programID = glCreateProgram();
        if (!programID)
        {
            printf("Error creating shader program!\n");
            return;
        }

        addShader(vCode, GL_VERTEX_SHADER);
        addShader(fCode, GL_FRAGMENT_SHADER);

        GLint result = 0;
        GLchar eLog[1024] = {0};

        glLinkProgram(programID);
        glGetProgramiv(programID, GL_LINK_STATUS, &result);
        if (!result)
        {
            glGetProgramInfoLog(programID, sizeof(eLog), NULL, eLog);
            printf("Error linking program: '%s'\n", eLog);
            return;
        }

        glValidateProgram(programID);
        glGetProgramiv(programID, GL_VALIDATE_STATUS, &result);
        if (!result)
        {
            glGetProgramInfoLog(programID, sizeof(eLog), NULL, eLog);
            printf("Error validating program: '%s'\n", eLog);
            return;
        }
    }

private:
    // add shader to opengl state
    void addShader(const char *shaderCode, GLenum shaderType)
    {
        GLuint shaderID = glCreateShader(shaderType);

        GLint codeLength = strlen(shaderCode);

        glShaderSource(shaderID, 1, &shaderCode, &codeLength);
        glCompileShader(shaderID);

        GLint result = 0;
        GLchar eLog[1024] = {0};

        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
        if (!result)
        {
            glGetShaderInfoLog(shaderID, sizeof(eLog), NULL, eLog);
            printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
            return;
        }

        glAttachShader(programID, shaderID);
    }

    // read from filepath and pass data to content
    void readFile(const char *filepath, std::string *content)
    {
        std::ifstream in_file{filepath};

        if (!in_file)
        {
            std::cout << "path: " << filepath << " file cant be read\n";
            return;
        }

        std::string line;
        while (!in_file.eof())
        {
            std::getline(in_file, line);
            content->append(line + "\n");
        }

        in_file.close();
    }
};