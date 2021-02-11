#include "Shader.h"

void Shader::bind() const
{
    glUseProgram(programID);
    // std::cout << "binding :: " << int(shaderType) << "\n";
}
void Shader::unbind() const
{
    glUseProgram(0);
}
void Shader::clear()
{
    if (programID != 0)
        glDeleteProgram(programID);
    programID = 0;
}
void Shader::compileFromFile(const char *vPath, const char *fPath)
{
    std::string vContent;
    std::string fContent;

    readFile(vPath, vContent);
    readFile(fPath, fContent);

    compileShader(vContent.c_str(), fContent.c_str());
}
void Shader::compileShader(const char *vCode, const char *fCode)
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
void Shader::addShader(const char *shaderCode, GLenum shaderType) const
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
        std::cout << "ShaderCode:: " << shaderCode << "\n";
        return;
    }

    glAttachShader(programID, shaderID);
}
void Shader::readFile(const char *filepath, std::string &content) const
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
        content.append(line + "\n");
    }

    in_file.close();
}
unsigned int Shader::getUniformLocation(const std::string &name)
{
    auto it = ulookup.find(name);
    if (it != ulookup.end())
        return it->second;
    unsigned int location = glGetUniformLocation(programID, name.c_str());
    ulookup.insert(std::make_pair(name, location));
    return location;
}
void Shader::setMat4(const std::string &name, const glm::mat4 &mat)
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
}