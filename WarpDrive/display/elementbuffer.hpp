#ifndef WD_ELEMENTBUF_DEFINED
#define WD_ELEMENTBUF_DEFINED

#include <vector>
#include <cstddef>
#include <string>

#include "GL/glew.h"

class ElementBuffer
{

public:

    using Data = std::vector<unsigned int>;

    //QUADS and QUAD_STRIP seem to have been removed and don't draw any more
    enum class DrawType : GLenum
    {
        POINTS = GL_POINTS,
        LINESTRIP = GL_LINE_STRIP,
        LINELOOP = GL_LINE_LOOP,
        LINES = GL_LINES,
        TRISTRIP = GL_TRIANGLE_STRIP,
        TRIFAN = GL_TRIANGLE_FAN,
        TRIS = GL_TRIANGLES,
        POLY = GL_POLYGON
    };

    class Header
    {
        public:

            Header(size_t off = 0);

            size_t Offset()                     const noexcept {return offset;}
            unsigned int ID()                   const noexcept {return id;}
            ElementBuffer::DrawType Primitive() const noexcept {return type;}
            std::string Name()                  const noexcept {return name;}
            size_t Length()                     const noexcept {return length;}

            void setOffset(size_t off)    noexcept {offset = off;}
            void setName(std::string n)   noexcept {name = n;}
            void setPrimitive(DrawType t) noexcept {type = t;}
            void setID(unsigned int n)    noexcept {id = n;}
            void setLength(size_t n)      noexcept {length = n;}

        private:

            unsigned int id;
            DrawType type;
            std::string name;
            size_t offset;
            size_t length;
    };

    ElementBuffer() = default;
    ElementBuffer(DrawType t, std::initializer_list<unsigned int> indices, std::string name = "Elements");
    ElementBuffer(DrawType t, ElementBuffer::Data indices, std::string name = "Elements");


    void push_back(unsigned int idx);
    void clear();

    size_t size() const noexcept {return data.size();}

    void bindBuffer();
    inline bool Registered() const noexcept {return info.ID() != 0;}
    DrawType Primitive() const noexcept {return info.Primitive();}
    void setPrimitive(DrawType t) {info.setPrimitive(t);}

    ElementBuffer::Data& Indices() {return data;}
    ElementBuffer::Header& Info() {return info;}

private:

    ElementBuffer::Data data;
    ElementBuffer::Header info;
};

#endif //WD_ELEMENTBUF_DEFINED
