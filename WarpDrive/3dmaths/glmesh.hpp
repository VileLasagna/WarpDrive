#ifndef WD_GLMESH_HPP_DEFINED
#define WD_GLMESH_HPP_DEFINED

#ifdef WIN32
    #include <Windows.h>
#endif //WIN32
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
    bool load(const char* objfile, bool Textured = true, bool Smooth = true, bool TwoSidedPolys = false);
	bool setSize(float f) {glmUnitize(mesh); glmScale(mesh,f); return true;}
    void draw() const;
	~GLMesh();

private:

	GLMmodel* mesh;
	GLuint flags;


};


#endif //WD_GLMESH_HPP_DEFINED
