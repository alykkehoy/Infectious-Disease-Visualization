#include "Shader.h"
#include <fstream>
#include <iostream>

Shader::Shader(const std::string &fileName) {
    m_progam = glCreateProgram();
    m_sharders[0] = CreateShader(LoadShader(fileName + ".vert"), GL_VERTEX_SHADER);
    m_sharders[1] = CreateShader(LoadShader(fileName + ".frag"), GL_FRAGMENT_SHADER);

    for (int i = 0; i < NUM_SHADERS; i++) {
        glAttachShader(m_progam, m_sharders[i]);
    }

    glBindAttribLocation(m_progam, 0, "position");

    glLinkProgram(m_progam);
    CheckShaderError(m_progam, GL_LINK_STATUS, true, "Error: failed to link: ");

    glValidateProgram(m_progam);
    CheckShaderError(m_progam, GL_VALIDATE_STATUS, true, "Error: program is invalid: ");
}


Shader::~Shader() {
    for (int i = 0; i < NUM_SHADERS; i++) {
        glDetachShader(m_progam, m_sharders[i]);
        glDeleteShader(m_sharders[i]);
    }
    glDeleteProgram(m_progam);
}

void Shader::Bind() {
    glUseProgram(m_progam);
}

GLuint Shader::CreateShader(const std::string &text, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);
    if (shader == 0) {
        std::cerr << "Error: shader creation failed" << std::endl;
    }

    const GLchar *p[1];
    p[0] = text.c_str();
    GLint lengths[1];
    lengths[0] = text.length();

    glShaderSource(shader, 1, p, lengths);
    glCompileShader(shader);

    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");
    return shader;
}

std::string Shader::LoadShader(const std::string &fileName) {
    std::ifstream file;
    file.open((fileName).c_str());

    std::string output;
    std::string line;

    if (file.is_open()) {
        while (file.good()) {
            getline(file, line);
            output.append(line + "\n");
        }
    } else {
        std::cerr << "Unable to load shader: " << fileName << std::endl;
    }

    return output;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string &errorMessage) {
    GLint success = 0;
    GLchar error[1024] = {0};

    if (isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if (success == GL_FALSE) {
        if (isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}