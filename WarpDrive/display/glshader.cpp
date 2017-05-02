#include "WarpDrive/display/glshader.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

GLShader::GLShader()
   :program{0},
    vertID{0},
    fragID{0},
    initialised{false},
    vertLoaded{false},
    fragLoaded{false}
{}

GLShader::GLShader(std::string vertex, std::string fragment)
    :program{0},
     vertID{0},
     fragID{0},
     initialised{false},
     vertLoaded{false},
     fragLoaded{false}
{
    load(vertex,fragment);
}

bool GLShader::load(std::string vertex, std::string fragment)
{
    return loadVertex(vertex) && loadFragment(fragment);
}

bool GLShader::loadVertex(std::string path)
{
    if(initialised || vertLoaded)
    {
        std::cout << "ERROR::SHADER::VERTEX::SHADER_ALREADY_LOADED" << std::endl;
        return false;
    }

    std::string src;
    std::ifstream vertFile;
    try
    {
        vertFile.open(path);
        std::stringstream vertStream;

        vertStream << vertFile.rdbuf();

        vertFile.close();
        src = vertStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::VERTEX::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const GLchar* glsrc = src.c_str();
    GLint success = 0;
    GLint length[1] ={static_cast<GLint>(src.length())};
    GLchar info[512];

    vertID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertID, 1, &glsrc, length);
    glCompileShader(vertID);
    glGetShaderiv(vertID, GL_COMPILE_STATUS, &success);
    if(success == 0)
    {
        glGetShaderInfoLog(vertID, 512, NULL, info);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info << std::endl;
        return false;
    }
    else
    {
        vertLoaded = true;
        if(fragLoaded)
        {
            assemble();
        }
    }
    return true;
}

bool GLShader::loadFragment(std::string path)
{
    if(initialised || fragLoaded)
    {
        std::cout << "ERROR::SHADER::FRAGMENT::SHADER_ALREADY_LOADED" << std::endl;
        return false;
    }

    std::string src;
    std::ifstream fragFile;
    try
    {
        fragFile.open(path);
        std::stringstream fragStream;

        fragStream << fragFile.rdbuf();

        fragFile.close();
        src = fragStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FRAGMENT::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const GLchar* glsrc = src.c_str();
    GLint success = 0;
    GLint length[1] ={static_cast<GLint>(src.length())};
    GLchar info[512];

    fragID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragID, 1, &glsrc, length);
    glCompileShader(fragID);
    glGetShaderiv(fragID, GL_COMPILE_STATUS, &success);
    if(success == 0)
    {
        glGetShaderInfoLog(fragID, 512, NULL, info);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info << std::endl;
        return false;
    }
    else
    {
        fragLoaded = true;
        if(vertLoaded)
        {
            assemble();
        }
    }
    return true;
}

bool GLShader::use() const
{
    if(!initialised)
    {
        return false;
    }
    else
    {
        glUseProgram(program);
        return true;
    }
}

int GLShader::Program() const noexcept
{
    return initialised ? static_cast<int>(program) : -1;
}

GLShader::~GLShader()
{
    if(initialised)
    {
        glDeleteProgram(program);
    }
}

void GLShader::assemble()
{
    GLint success = 0;
    GLchar info[512];

    program = glCreateProgram();
    glAttachShader(program, vertID);
    glAttachShader(program, fragID);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, info);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info << std::endl;
    }
    else
    {
        initialised = true;
        glDeleteShader(vertID);
        glDeleteShader(fragID);
    }

}
