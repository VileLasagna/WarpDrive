
#ifdef WIN32
    #include <windows.h>
#endif //WIN32

#include <SDL/SDL_opengl.h>
#include "BaseMaths/Plane.hpp"
#include "BaseMaths/Matrix44.hpp"
#include "BaseMaths/Quaternion.hpp"
#include <GL/glu.h>





Plane::Plane()
{ 
	Nx = 0;
	Ny = 0;
	Nz = 0; 
	D = 0; 
	DrawnCells = std::pair<int,int>(2,2); 
	cellSize = 1; 
	Colour = Vec3f(0,1,0);
	drawWire = true;
	Origin = Vec3f();
	D0 = D;
	showNormal = 0;
    TEX = nullptr;
}

Plane::Plane (float A, float B, float C, float d) 
{
	float sqmod = A*A+B*B+C*C;
	if(sqmod > 1.00001 || sqmod < 0.999999)
	{
		float mod = sqrt(sqmod);
		A /= mod;
		B /= mod;
		C /= mod;
	}
	Nx = A; 
	Ny = B; 
	Nz = C; 
	D = d; 
	DrawnCells = std::pair<int,int>(2,2); 
	cellSize = 1; 
	Colour = Vec3f(0,1,0);
	drawWire = true;
	Origin = Vec3f(Nx*D,Ny*D,Nz*D);
	D0 = D;
    showNormal = false;
    TEX = nullptr;
}

void Plane::useTexture(Texture *tex, bool Tile)
{
	TEX = tex;
	tile = Tile;
}

Plane::Plane (const Vec3f& Normal, float Distance) 
{ 
	Nx = Normal.X(); 
	Ny = Normal.Y(); 
	Nz = Normal.Z(); 
	D = Distance;
	DrawnCells = std::pair<int,int>(2,2); 
	cellSize = 1;
	Colour = Vec3f(0,1,0);
	drawWire = true;
	Origin = Vec3f(Nx*D,Ny*D,Nz*D);
	D0 = D;
    showNormal = false;
    TEX = nullptr;
}

Plane::Plane (const Vec3f& P1, const Vec3f& P2, const Vec3f& P3) 
{     
	Vec3f N = triNormal(P1,P2,P3);
	Nx = N.X();
	Ny = N.Y();
	Nz = N.Z();
	D = dotProd(P1, N);
	DrawnCells = std::pair<int,int>(2,2); 
	cellSize = 1;
	drawWire = true;
	Origin = Vec3f(Nx*D,Ny*D,Nz*D);
	D0 = D;
    showNormal = false;
	TEX = 0;
}

void Plane::setNormal(const Vec3f& N)
{
	//This function is for "rotating" the plane around the origin of the WORLD
	float M = N.sqMod();
	if(M > 1.0000001 || M < 0.9999999)
		//check if N is normalised and do so if it isn't.
	{
		Vec3f norm = N;
		norm.normalise();
		Nx = norm.X();
		Ny = norm.Y();
		Nz = norm.Z();
	}
	else
	{
		Nx = N.X();
		Ny = N.Y();
		Nz = N.Z();
	}
}

void Plane::RotateAroundOrigin(const Vec3f &angles)
{
	Matrix44 rot;
	rot.setRotation(angles.X(), angles.Y(), angles.Z());
	Vec3f newNorm = Vec3f(Nx,Ny,Nz);
	newNorm = (Matrix44::Multiply(rot,Vec4f(newNorm))).toVec3();
	Vec3f Norm = newNorm;
	D = D0*dotProd(Norm,newNorm);
	Nx = newNorm.X();
	Ny = newNorm.Y();
	Nz = newNorm.Z();



}

void Plane::DrawAsWireframe(bool b)
{
	drawWire = b;
}

void Plane::setDrawn(int X, int Y, float size)
{
	DrawnCells.first = X;
	DrawnCells.second = Y;
	cellSize = size;
}

void Plane::setColour(const Vec3f &rgb)
{
	Colour = rgb;
}

void Plane::setColour(float r, float g, float b)
{
	Colour = Vec3f(r,g,b);
}

void Plane::DrawNormal(bool b)
{
	showNormal = b;

}
void Plane::Draw() const
{

	//glMatrixMode(GL_MODELVIEW);
	float thetaZ = asin( dotProd(Vec3f(0,Ny,Nz), Vec3f(0,0,1)) );
	float thetaX = asin( dotProd(Vec3f(Nx,Ny,0), Vec3f(1,0,0)) );

	Matrix44 rot;

	rot.setRotationRad(0,thetaZ,-thetaX);

	//Vec3f RN = crossProd(Vec3f(Nx,Ny,Nz), Vec3f(0,1,0));
	//GLfloat pink[] = {1,0,1};
	//glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,pink);
	//glBegin(GL_LINES);
	//	glVertex3f(0,0,0);
	//	glVertex3f(RN.X()*3, RN.Y()*3,RN.Z()*3);
	//glEnd();
	//pink[0] = Colour.X();
	//pink[1] = Colour.Y();
	//pink[2] = Colour.Z();
	//glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,pink);

	//Quaternion quat(acos(dotProd(RN,Vec3f(0,1,0))), RN);
	//quat.Normalise();
	//

	//float m[16];
	//quat.ToMatrix(m);
	//Does not load identity so the plane is drawn relative to the LOCAL orientation!!!

	glPushMatrix();

		glTranslatef(Origin.X(),Origin.Y(),Origin.Z()); //Drawing by Local
		glMultMatrixf(rot.getElements().data());
		//glMultMatrixf(m);
		//glTranslatef(0,D,0); //Drawing by world


		if (showNormal)
		{
			glDisable(GL_LIGHTING);
			glEnable(GL_COLOR);
			glColor3f(1,1,1);
			glBegin(GL_LINES);
				glVertex3f(0,0,0);
				glVertex3f(Nx*3,Ny*3,Nz*3);
			glEnd();
			glDisable(GL_COLOR);
			glEnable(GL_LIGHTING);
		}

		glTranslatef(-cellSize*DrawnCells.first/2,0,-cellSize*DrawnCells.second/2);
		glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,128);
	
		//float colour[3] = {Colour.X(),Colour.Y(),Colour.Z()};
		float colour[3] = {1,1,1};
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colour);
		float texStepX = 1.0f/DrawnCells.first;
		float texStepY = 1.0f/DrawnCells.second;
		for(int x = 0; x < DrawnCells.first; x++)
		{
			for(int z = 0; z<DrawnCells.second;z++)
			{
				if(drawWire)
				{
//                    glDisable(GL_LIGHTING);
//                    glEnable(GL_COLOR);
//                    glColor3f(1,1,1);
					glBegin(GL_LINE_LOOP);
						
						glNormal3f(0,1,0);
						glVertex3f(x*cellSize,0,z*cellSize);
						//glNormal3f(Nx,Ny,Nz);
						glVertex3f((x+1)*cellSize,0,z*cellSize);
						//glNormal3f(Nx,Ny,Nz);
						glVertex3f((x+1)*cellSize,0,(z+1)*cellSize);
						//glNormal3f(Nx,Ny,Nz);
						glVertex3f(x*cellSize,0,(z+1)*cellSize);

					glEnd();
//                    glDisable(GL_COLOR);
//                    glEnable(GL_LIGHTING);
				}
				else
				{
                    if (TEX != nullptr)
					{
						TEX->UseThisTexture();
                        glBegin(GL_QUADS);
						if(!tile)
						{
							glTexCoord2f(1- texStepX*x, 1-texStepY*z);
							glNormal3f(0,1,0);
							glVertex3f(x*cellSize,0,z*cellSize);
							glTexCoord2f(1-texStepX*(x+1),1- texStepY*z);
							glNormal3f(0,1,0);
							glVertex3f((x+1)*cellSize,0,z*cellSize);
							glNormal3f(0,1,0);
							glTexCoord2f(1-texStepX*(x+1),1-texStepY*(z+1));
							glVertex3f((x+1)*cellSize,0,(z+1)*cellSize);
							glNormal3f(0,1,0);
							glTexCoord2f(1-texStepX*x,1-texStepY*(z+1));
							glVertex3f(x*cellSize,0,(z+1)*cellSize);
						}
						else
						{
							glTexCoord2f(1, 1);
							glNormal3f(0,1,0);
							glVertex3f(x*cellSize,0,z*cellSize);
							glTexCoord2f(0,1);
							glNormal3f(0,1,0);
							glVertex3f((x+1)*cellSize,0,z*cellSize);
							glNormal3f(0,1,0);
							glTexCoord2f(0,0);
							glVertex3f((x+1)*cellSize,0,(z+1)*cellSize);
							glNormal3f(0,1,0);
							glTexCoord2f(1,0);
							glVertex3f(x*cellSize,0,(z+1)*cellSize);
						}

					glEnd();
					}
					else
					{
					glBegin(GL_QUADS);
						
						glNormal3f(0,-1,0);
						glVertex3f(x*cellSize,0,z*cellSize);
						glNormal3f(0,-1,0);
						glVertex3f((x+1)*cellSize,0,z*cellSize);
						glNormal3f(0,-1,0);
						glVertex3f((x+1)*cellSize,0,(z+1)*cellSize);
						glNormal3f(0,-1,0);
						glVertex3f(x*cellSize,0,(z+1)*cellSize);

					glEnd();
					}
				}
			}
		}
		glColor3f(1,1,1);
	glPopMatrix();

}
