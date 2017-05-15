#ifndef WD_VERTEXBUF_DEFINED
#define WD_VERTEXBUF_DEFINED

#include <vector>
#include <cstddef>

#include "WarpDrive/3dmaths/vertex.hpp"

class VertexBuffer
{

public:

    enum class DataType{STATIC, DYNAMIC, STREAM};

    static void registerBuffers(std::vector<VertexBuffer> buffers);

    VertexBuffer();

    void push_back(Vertex& v);
    void push_back(Vertex&& v);

    size_t size() const noexcept {return data.size();}

    void bindBuffer();
    DataType Type() const noexcept {return type;}
    void Type(DataType t) {type = t;}

private:

    std::vector<Vertex> data;
    bool registered;
    unsigned int ID;
    DataType type;
};


#endif //WD_VERTEXBUF_DEFINED
