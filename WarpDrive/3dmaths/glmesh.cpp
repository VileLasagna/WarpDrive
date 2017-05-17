#include "glmesh.hpp"

#include "glm.h"


GLMesh::GLMesh()
{
    mesh = 0;
    flags = 0;
}

GLMesh::GLMesh(const char *objfile, bool Textured, bool Smooth , bool TwoSidedPolys)
{
    mesh = glmReadOBJ(objfile);
    flags = 0;
    if (Textured)
    {
        flags |= GLM_TEXTURE;
    }
    else
    {
        flags |= GLM_MATERIAL;
    }
        if (Smooth)
    {
        flags |= GLM_SMOOTH;
    }
    else
    {
        flags |= GLM_FLAT;
    }
    if (TwoSidedPolys)
    {
        flags |= GLM_2_SIDED;
    }
}

bool GLMesh::load(const char *objfile, bool Textured, bool Smooth , bool TwoSidedPolys)
{
    mesh = glmReadOBJ(objfile);
    flags = 0;
    if (Textured)
    {
        flags |= GLM_TEXTURE;
    }
    else
    {
        flags |= GLM_MATERIAL;
    }
    if (Smooth)
    {
        flags |= GLM_SMOOTH;
    }
    else
    {
        flags |= GLM_FLAT;
    }
    if (TwoSidedPolys)
    {
        flags |= GLM_2_SIDED;
    }
    return true;
}

bool GLMesh::setSize(float f)
{
    glmUnitize( reinterpret_cast<GLMmodel*>(mesh) );
    glmScale(reinterpret_cast<GLMmodel*>(mesh),f);
    return true;
}

void GLMesh::draw() const
{
    glmDraw(reinterpret_cast<GLMmodel*>(mesh), flags);
}

GLMesh::~GLMesh()
{
    glmDelete(reinterpret_cast<GLMmodel*>(mesh));
}
