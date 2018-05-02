#ifndef GLSHADER_HPP
#define GLSHADER_HPP

#ifdef WIN32
    #include <Windows.h>
#endif //WIN32

#include <GL/glew.h>
#include <string>

class GLShader
{

public:

    GLShader();
    GLShader(std::string vertex, std::string fragment);

    bool load(std::string vertex, std::string fragment);
    bool loadVertex(std::string path);
    bool loadFragment(std::string path);
    bool use() const;

    //Use operator [] to get uniforms from the shader
    GLint operator[](std::string uniform) const;

    int Program() const noexcept;

    ~GLShader();

private:

    void assemble();

    GLuint program;
    GLuint vertID;
    GLuint fragID;
    bool initialised;
    bool vertLoaded;
    bool fragLoaded;

};

#endif // GLSHADER_HPP
