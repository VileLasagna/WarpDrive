#include "WarpDrive/display/vertexarray.hpp"

#include "WarpDrive/basesystem/err.hpp"

#include <GL/glew.h>

VertexArray::VertexArray()
    :id{0},
     ebid{0},
     buffer{},
     indices{},
     type{VertexBuffer::DataType::STATIC}
{}

void VertexArray::pushElementBuffer(ElementBuffer::Data&& EBO)
{
    size_t offset = indices.size()*sizeof(unsigned int);
    EBOData.emplace_back(offset);
    EBOData.back().setLength(EBO.size());
    appendIndices(EBO);

}

void VertexArray::pushElementBuffer(ElementBuffer &&EBO)
{
    EBOData.push_back(EBO.Info());
    EBOData.back().setOffset(indices.size()*sizeof(unsigned int));
    EBOData.back().setLength(EBO.Indices().size());
    appendIndices(EBO.Indices());
}

void VertexArray::Verts(VertexBuffer &&VBO)
{
    buffer = VBO;
}

void VertexArray::draw(std::string buffer, bool autobind) const noexcept
{
    if(autobind)
    {
        glBindVertexArray(id);
        for(ElementBuffer::Header h: EBOData)
        {
            if((buffer == "") || h.Name() == buffer )
            {
                glDrawElements(static_cast<GLenum>(h.Primitive()), static_cast<GLsizei>(h.Length()), GL_UNSIGNED_INT, reinterpret_cast<void*>(h.Offset()));
            }
        }
        glBindVertexArray(0);
    }
    else
    {
        for(ElementBuffer::Header h: EBOData)
        {
            if((buffer == "") || h.Name() == buffer )
            {
                glDrawElements(static_cast<GLenum>(h.Primitive()), static_cast<GLsizei>(h.Length()), GL_UNSIGNED_INT, reinterpret_cast<void*>(h.Offset()));
            }
        }
    }
}

void VertexArray::Load()
{
    if(id != 0)
    {
        #ifndef NDEBUG
        Err::log("WARNING::VERTEXARRAY:: Attempting to bind VAO multiple times");
        #endif
        return;
    }
    if(indices.size() == 0)
    {

        Err::log("WARNING::VERTEXARRAY:: auto-generating EBO indices");

#ifndef NDEBUG
        //this is a silly check no one wants to make on a release build
        if(buffer.size() < 2)
        {
            Err::report("ERROR::VERTEXARRAY:: vertex buffer size too small");
            return;
        }
#endif
        for(unsigned int i = 2; i < buffer.size(); i+=3)
        {
            indices.push_back(i-2);
            indices.push_back(i-1);
            indices.push_back(i);
        }
    }

    glGenVertexArrays(1, &id);
    glGenBuffers(1, &ebid);

    glBindVertexArray(id);

        if(buffer.Registered())
        {
            Err::log("WARNING::VERTEXARRAY:: Attempting to bind Vertex Buffer multiple times");
        }
        buffer.bindBuffer();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebid);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(unsigned int)*indices.size()),
                     indices.data(), static_cast<GLenum>(type));



        //glVertexAttribPointer(index, size, type, normalized,
        //                      stride, first   );
        //Position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                              21 * sizeof(GLfloat), nullptr);
        glEnableVertexAttribArray(0);

        //Normal
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE,
                              21 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)) );
        glEnableVertexAttribArray(1);

        //UV
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                              21 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(6 * sizeof(GLfloat)) );
        glEnableVertexAttribArray(2);

        //Ambient Colour
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE,
                              21 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(8 * sizeof(GLfloat)) );
        glEnableVertexAttribArray(3);

        //Diffuse Colour
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE,
                              21 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(12 * sizeof(GLfloat)) );
        glEnableVertexAttribArray(4);

        //Specular Colour
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE,
                              21 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(16 * sizeof(GLfloat)) );
        glEnableVertexAttribArray(5);

        //Shyniness
        glVertexAttribPointer(6, 1, GL_FLOAT, GL_FALSE,
                              21 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(20 * sizeof(GLfloat)) );
        glEnableVertexAttribArray(6);


    glBindVertexArray(0);

}

void VertexArray::Bind() const noexcept
{
    glBindVertexArray(id);
}

void VertexArray::Unbind()
{
    glBindVertexArray(0);
}

void VertexArray::appendIndices(ElementBuffer::Data& d)
{
    if(indices.empty())
    {
        indices = d;
    }
    else
    {
        indices.insert(indices.end(),d.begin(), d.end());
    }
}

void VertexArray::appendIndices(ElementBuffer::Data&& d)
{
    if(indices.empty())
    {
        indices = d;
    }
    else
    {
        indices.insert(indices.end(),d.begin(), d.end());
    }
}
