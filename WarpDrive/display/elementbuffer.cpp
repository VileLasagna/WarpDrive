#include "WarpDrive/display/elementbuffer.hpp"


ElementBuffer::Header::Header(size_t off)
   :id{0},
    type{ElementBuffer::DrawType::TRIS},
    name{"Elements"},
    offset{off},
    length{0}
{}

ElementBuffer::ElementBuffer(ElementBuffer::DrawType t, std::initializer_list<unsigned int> indices, std::string name)
{
    info.setPrimitive(t);
    info.setName(name);
    data = indices;
}

ElementBuffer::ElementBuffer(ElementBuffer::DrawType t, ElementBuffer::Data indices, std::string name)
{
    info.setPrimitive(t);
    info.setName(name);
    data = indices;
}

void ElementBuffer::push_back(unsigned int idx)
{
    data.push_back(idx);
}

void ElementBuffer::clear()
{
    data.clear();
}
