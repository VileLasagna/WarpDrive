#ifndef WD_VERTEXARR_DEFINED
#define WD_VERTEXARR_DEFINED

#include <vector>

#include <GL/glew.h>
#include "WarpDrive/display/vertexbuffer.hpp"
#include "WarpDrive/display/elementbuffer.hpp"

class VertexArray
{

public:

    VertexArray();

    void pushElementBuffer(ElementBuffer::Data &&EBO);
    void pushElementBuffer(ElementBuffer &&EBO);
    void Verts(VertexBuffer&& VBO);
    void draw(std::string buffer = "", bool autobind = true) const noexcept;
    void Load();
    void Bind() const noexcept;
    static void Unbind();

private:

    unsigned int id, ebid;
    VertexBuffer buffer;
    std::vector<unsigned int> indices;
    std::vector<ElementBuffer::Header> EBOData;
    VertexBuffer::DataType type;

    void appendIndices(ElementBuffer::Data& d);
    void appendIndices(ElementBuffer::Data&& d);


};

#endif //WD_VERTEXARR_DEFINED
