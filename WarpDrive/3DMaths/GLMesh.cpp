#include "GLMesh.h"



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

bool GLMesh::Load(const char *objfile, bool Textured, bool Smooth , bool TwoSidedPolys)
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

void GLMesh::Draw()
{
	glmDraw(mesh, flags);

}

GLMesh::~GLMesh()
{
	glmDelete(mesh);
}
