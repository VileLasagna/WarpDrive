#ifndef GLSHADER_HPP
#define GLSHADER_HPP

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
