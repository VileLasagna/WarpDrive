#ifndef WD_VERTEXBUF_DEFINED
#define WD_VERTEXBUF_DEFINED

#include <vector>
#include <cstddef>

#include "GL/glew.h"

#include "WarpDrive/display/vertex.hpp"

class VertexBuffer
{

public:

    enum class DataType : GLenum
    {
        STATIC = GL_STATIC_DRAW,
        DYNAMIC = GL_DYNAMIC_DRAW,
        STREAM = GL_STREAM_DRAW
    };

    static void registerBuffers(std::vector<VertexBuffer> buffers);

    VertexBuffer();

    void push_back(Vertex& v);
    void push_back(Vertex&& v);
    void clear();

    size_t size() const noexcept {return data.size();}

    void bindBuffer();
    inline bool Registered() const noexcept {return id != 0;}
    DataType Type() const noexcept {return type;}
    void Type(DataType t) {type = t;}

private:

    std::vector<Vertex> data;
    unsigned int id;
    DataType type;
};

#endif //WD_VERTEXBUF_DEFINED
