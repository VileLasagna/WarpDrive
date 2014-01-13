#include "Billboard.h"
#include <GL/glut.h>


void Billboard::Draw() const
{
	glDisable(GL_LIGHTING);
	GLfloat m[16];
	glGetFloatv(GL_MODELVIEW_MATRIX,m);
	Vec3f UP (0,1,0);
	if(!absUp)
	{
		UP = Vec3f(m[1],m[5],m[9]);
	}
	Vec3f RIGHT (m[0], m[4], m[8]);
	float halfsize = size/2;
	Vec3f RT = pos+ (RIGHT+UP)*halfsize;
	
	//RT *= halfsize;
	Vec3f RB = pos + (RIGHT-UP)*halfsize;
	//RB *= halfsize;
	Vec3f LT = pos + (- RIGHT + UP)*halfsize;
	//LT *= halfsize;
	Vec3f LB = pos + ( -RIGHT - UP)*halfsize;
	//LB *= halfsize;
	glEnable(GL_COLOR);

	glBegin(GL_TRIANGLE_STRIP);

		glTexCoord2f(0,0);
		//glColor3f(1,1,1);
		glVertex3f(LT.X(),LT.Y(),LT.Z());
		//glColor3f(0,0,1);
		glTexCoord2f(1,0);
		glVertex3f(RT.X(),RT.Y(),RT.Z());
		glTexCoord2f(0,1);
		//glColor3f(1,0,0);
		glVertex3f(LB.X(),LB.Y(),LB.Z());
		glTexCoord2f(1,1);
		//glColor3f(0,1,0);
		glVertex3f(RB.X(),RB.Y(),RB.Z());

		

	glEnd();
	glEnable(GL_LIGHTING);
		


}