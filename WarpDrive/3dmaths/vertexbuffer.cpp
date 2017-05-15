#include "WarpDrive/3dmaths/vertexbuffer.hpp"

#include <assert.h>
#include "GL/glew.h"

void VertexBuffer::registerBuffers(std::vector<VertexBuffer> buffers)
{
    std::vector<unsigned int> indexes(buffers.size());
    glGenBuffers(static_cast<int>(indexes.size()), indexes.data());
    for(size_t i = 0; i < indexes.size(); i++)
    {
        assert(!buffers[i].registered && "VertexBuffer already registered!");

        buffers[i].ID = indexes[i];
    }
}

VertexBuffer::VertexBuffer()
   :data(),
    registered{false},
    ID{0},
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

void VertexBuffer::bindBuffer()
{
    if(!registered)
    {
        glGenBuffers(1, &ID);
        registered = true;
    }

    glBindBuffer(GL_ARRAY_BUFFER, ID);
    switch(type)
    {
        case DataType::STATIC :
            glBufferData(GL_ARRAY_BUFFER, sizeof(data), data.data(), GL_STATIC_DRAW);
            break;
        case DataType::DYNAMIC :
            glBufferData(GL_ARRAY_BUFFER, sizeof(data), data.data(), GL_DYNAMIC_DRAW);
            break;
        case DataType::STREAM :
            glBufferData(GL_ARRAY_BUFFER, sizeof(data), data.data(), GL_STREAM_DRAW);
            break;
    }


}
