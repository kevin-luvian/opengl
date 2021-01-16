#include "Shader.h"

Shader::Shader()
{
    programID = 0;
    mvpID = 0;
}

Shader::~Shader()
{
    clear();
}

void Shader::bind() { glUseProgram(programID); }

void Shader::unbind() { glUseProgram(0); }

void Shader::clear()
{
    if (programID != 0)
        glDeleteProgram(programID);
    programID = 0;
    mvpID = 0;
}

GLuint Shader::getProgramID() { return programID; }

GLuint Shader::getMVPID() { return mvpID; }

void Shader::setMVP(glm::mat4 mvp)
{
    glUniformMatrix4fv(mvpID, 1, GL_FALSE, glm::value_ptr(mvp));
}

GLuint Shader::getViewProjection() { return viewProjectionID; }

void Shader::setViewProjection(glm::mat4 matrix)
{
    glUniformMatrix4fv(viewProjectionID, 1, GL_FALSE, glm::value_ptr(matrix));
}

GLuint Shader::getModel() { return modelID; }

void Shader::setModel(glm::mat4 matrix)
{
    glUniformMatrix4fv(modelID, 1, GL_FALSE, glm::value_ptr(matrix));
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

    mvpID = glGetUniformLocation(programID, "mvp");

    viewProjectionID = glGetUniformLocation(programID, "viewProjection");
}

void Shader::addShader(const char *shaderCode, GLenum shaderType)
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

void Shader::readFile(const char *filepath, std::string *content)
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

void Shader::compileFromFile(const char *vPath, const char *fPath)
{
    BENCHMARK_PROFILE();
    std::string vContent;
    std::string fContent;

    readFile(vPath, &vContent);
    readFile(fPath, &fContent);

    // std::cout << "v content:: " << vContent << "\n\nf content:: " << fContent << std::endl;

    compileShader(vContent.c_str(), fContent.c_str());
}