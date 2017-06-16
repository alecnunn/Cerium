#include "../include/Cerium/ShaderProgram.hpp"

#include <fstream>
#include <iostream>

namespace cerium
{
    ShaderProgram::ShaderProgram(const std::string & vertexShaderPath, const std::string & fragmentShaderPath)
    {
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        std::string vertexShaderFileSource;
        std::ifstream vertexShaderFile;

        std::string line;
        while(std::getline(vertexShaderFile, line))
        {
            vertexShaderFileSource += line + "\n";
        }
        vertexShaderFile.close();

        std::string fragmentShaderFileSource;
        std::ifstream fragmentShaderFile;

        while(std::getline(fragmentShaderFile, line))
        {
            fragmentShaderFileSource += line + "\n";
        }
        fragmentShaderFile.close();

        GLint vertexShaderCompilationSuccess;
        GLchar vertexShaderCompilationLog[512];

        const char * vertexShaderSource = vertexShaderFileSource.c_str();
        glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShader);
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShaderCompilationSuccess);
        if(!vertexShaderCompilationSuccess)
        {
            glGetShaderInfoLog(vertexShader, 512, nullptr, vertexShaderCompilationLog);
            std::cout << vertexShaderCompilationLog << std::endl;
        }

        GLint fragmentShaderCompilationSuccess;
        GLchar fragmentShaderCompilationLog[512];

        const char * fragmentShaderSource = vertexShaderFileSource.c_str();
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
        glCompileShader(fragmentShader);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentShaderCompilationSuccess);
        if(!fragmentShaderCompilationSuccess)
        {
            glGetShaderInfoLog(fragmentShader, 512, nullptr, fragmentShaderCompilationLog);
            std::cout << fragmentShaderCompilationLog << std::endl;
        }

        program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);

        glLinkProgram(program);

        glDetachShader(program, vertexShader);
        glDetachShader(program, fragmentShader);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }


    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(program);
    }


    void ShaderProgram::use(void)
    {
        glUseProgram(program);
    }
}