#ifndef WD_VERTEXARR_DEFINED
#define WD_VERTEXARR_DEFINED

#include <vector>

#include <GL/glew.h>
#include "WarpDrive/display/vertexbuffer.hpp"

class VertexArray
{

public:

    enum class DrawType : GLenum
    {
        POINTS = GL_POINTS,
        LINESTRIP = GL_LINE_STRIP,
        LINELOOP = GL_LINE_LOOP,
        LINES = GL_LINES,
        TRISTRIP = GL_TRIANGLE_STRIP,
        TRIFAN = GL_TRIANGLE_FAN,
        TRIS = GL_TRIANGLES,
        QUADSTRIP = GL_QUAD_STRIP,
        QUADS = GL_QUADS,
        POLY = GL_POLYGON
    };


    VertexArray();

    void ElementBuffer(std::vector<unsigned int> &&EBO);
    void Verts(VertexBuffer&& VBO);

    void draw() const;
    void bind();

private:

    unsigned int id, ebid;
    VertexBuffer buffer;
    std::vector<unsigned int> indices;
    VertexBuffer::DataType type;
    DrawType primitives;

};

#endif //WD_VERTEXARR_DEFINED
