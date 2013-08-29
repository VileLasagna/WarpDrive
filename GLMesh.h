#ifndef GLMESH_H
#define GLMESH_H

#include <windows.h>
#include <GL/gl.h>
#include "glm.h"

class GLMesh
{

private:

	GLMesh operator=(const GLMesh& ref);
	GLMesh(const GLMesh& ref);

public:

	GLMesh();
	GLMesh(const char* objfile, bool Textured = true, bool Smooth = true, bool TwoSidedPolys = false);
	bool Load(const char* objfile, bool Textured = true, bool Smooth = true, bool TwoSidedPolys = false);
	bool setSize(float f) {glmUnitize(mesh); glmScale(mesh,f); return true;}
	void Draw();
	~GLMesh();

private:

	GLMmodel* mesh;
	GLuint flags;


};


#endif //GL_MESH_H