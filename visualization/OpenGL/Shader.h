#ifndef GUARD_SHADER_H
#define GUARD_SHADER_H

#include <string>
#include<GL\glew.h>

class Shader {
public:
    Shader(const std::string &fileName);

    ~Shader();

    void Bind();

    std::string LoadShader(const std::string &fileName);

    void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string &errorMessage);

    GLuint CreateShader(const std::string &text, GLenum shaderType);


private:
    static const unsigned int NUM_SHADERS = 2;
    GLuint m_progam;
    GLuint m_sharders[NUM_SHADERS];
};

#endif