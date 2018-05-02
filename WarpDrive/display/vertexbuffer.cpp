#include "WarpDrive/display/vertexbuffer.hpp"

#include <assert.h>
#include "GL/glew.h"

#include <iostream>

void VertexBuffer::registerBuffers(std::vector<VertexBuffer> buffers)
{
    std::vector<unsigned int> indexes(buffers.size());
    glGenBuffers(static_cast<int>(indexes.size()), indexes.data());
    for(size_t i = 0; i < indexes.size(); i++)
    {
        assert((buffers[i].id == 0) && "VertexBuffer already registered!");
        buffers[i].id = indexes[i];
    }
}

VertexBuffer::VertexBuffer()
   :data(),
    id{0},
    type{DataType::STATIC}
{}

void VertexBuffer::push_back(Vertex& v)
{
   data.push_back(v);
}
void VertexBuffer::push_back(Vertex&& v)
{
    data.push_back(v);
}

void VertexBuffer::clear()
{
    data.clear();
}

void VertexBuffer::bindBuffer()
{
    if(!Registered())
    {
        glGenBuffers(1, &id);
    }

    glBindBuffer(GL_ARRAY_BUFFER, id);

    glBufferData(   GL_ARRAY_BUFFER,
                    static_cast<GLsizeiptr>(sizeof(Vertex)*data.size()),
                    data.data(),
                    static_cast<GLenum>(type)   );

}
