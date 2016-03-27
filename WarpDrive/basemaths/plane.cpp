#include "basemaths/plane.hpp"

#ifdef WIN32
    #include <windows.h>
#endif //WIN32


#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include "basemaths/matrix44.hpp"
#include "basemaths/quaternion.hpp"
#include <GL/glu.h>

Plane::Plane()
{ 
    nX = 0;
    nY = 0;
    nZ = 0;
    d = 0;
    drawnCells = std::pair<int,int>(2,2);
	cellSize = 1; 
	colour = Vec3f(0,1,0);
	drawWire = true;
	origin = Vec3f();
    d0 = d;
	showNormal = 0;
    tex = nullptr;
}

Plane::Plane (float A, float B, float C, float D)
{
	float sqmod = A*A+B*B+C*C;
	if(sqmod > 1.00001 || sqmod < 0.999999)
	{
        float mod = static_cast<float>(sqrt(sqmod));
		A /= mod;
		B /= mod;
		C /= mod;
	}
    nX = A;
    nY = B;
    nZ = C;
    d = D;
    drawnCells = std::pair<int,int>(2,2);
	cellSize = 1; 
	colour = Vec3f(0,1,0);
	drawWire = true;
    origin = Vec3f(nX*D,nY*D,nZ*D);
    d0 = D;
    showNormal = false;
    tex = nullptr;
}

void Plane::useTexture(Texture *t, bool Tile)
{
    tex = t;
	tile = Tile;
}

Plane::Plane (const Vec3f& Normal, float Distance) 
{ 
    nX = Normal.X();
    nY = Normal.Y();
    nZ = Normal.Z();
    d = Distance;
    drawnCells = std::pair<int,int>(2,2);
	cellSize = 1;
	colour = Vec3f(0,1,0);
	drawWire = true;
    origin = Vec3f(nX*d,nY*d,nZ*d);
    d0 = d;
    showNormal = false;
    tex = nullptr;
}

Plane::Plane (const Vec3f& P1, const Vec3f& P2, const Vec3f& P3) 
{     
	Vec3f N = triNormal(P1,P2,P3);
    nX = N.X();
    nY = N.Y();
    nZ = N.Z();
    d = dotProd(P1, N);
    drawnCells = std::pair<int,int>(2,2);
	cellSize = 1;
	drawWire = true;
    origin = Vec3f(nX*d,nY*d,nZ*d);
    d0 = d;
    showNormal = false;
    tex = 0;
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
        nX = norm.X();
        nY = norm.Y();
        nZ = norm.Z();
	}
	else
	{
        nX = N.X();
        nY = N.Y();
        nZ = N.Z();
	}
}

void Plane::rotateAroundOrigin(const Vec3f &angles)
{
	Matrix44 rot;
	rot.setRotation(angles.X(), angles.Y(), angles.Z());
    Vec3f newNorm = Vec3f(nX,nY,nZ);
	newNorm = (Matrix44::multiply(rot,Vec4f(newNorm))).toVec3();
	Vec3f Norm = newNorm;
    d = d0*dotProd(Norm,newNorm);
    nX = newNorm.X();
    nY = newNorm.Y();
    nZ = newNorm.Z();

}

void Plane::drawAsWireframe(bool b) noexcept
{
	drawWire = b;
}

void Plane::setDrawn(int X, int Y, float size)
{
    drawnCells.first = X;
    drawnCells.second = Y;
	cellSize = size;
}

void Plane::setColour(const Vec3f &rgb) noexcept
{
	colour = rgb;
}

void Plane::setColour(float r, float g, float b) noexcept
{
	colour = Vec3f(r,g,b);
}

void Plane::drawNormal(bool b) noexcept
{
	showNormal = b;

}
void Plane::draw() const noexcept
{

    //glMatrixMode(GL_MODELVIEW);
    float thetaZ = static_cast<float>(asin( dotProd(Vec3f(0,nY,nZ), Vec3f(0,0,1)) ) );
    float thetaX = static_cast<float>(asin( dotProd(Vec3f(nX,nY,0), Vec3f(1,0,0)) ) );

	Matrix44 rot;

	rot.setRotationRad(0,thetaZ,-thetaX);

	glPushMatrix();

		glTranslatef(origin.X(),origin.Y(),origin.Z()); //Drawing by Local
		glMultMatrixf(rot.Elements().data());

		if (showNormal)
		{
			glDisable(GL_LIGHTING);
			glEnable(GL_COLOR);
			glColor3f(1,1,1);
			glBegin(GL_LINES);

				glVertex3f(0,0,0);
                glVertex3f(nX*60,nY*60,nZ*60);

            glEnd();
			glDisable(GL_COLOR);
			glEnable(GL_LIGHTING);
		}

        glTranslatef(-cellSize*drawnCells.first/2,0,-cellSize*drawnCells.second/2);
		glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,128);
        GLfloat cl[3] = {colour.R(),colour.G(),colour.B()};
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cl);
        float texStepX = 1.0f/drawnCells.first;
        float texStepY = 1.0f/drawnCells.second;

        if(drawWire)
        {

            glDisable(GL_LIGHTING);
            glEnable(GL_COLOR);
            glColor3f(1,1,1);
            glBegin(GL_LINES);

            for(int x = 0; x < drawnCells.first; x++)
            {
                for(int z = 0; z<drawnCells.second; z++)
                {

                        glNormal3f(0,1,0);
                        glVertex3f(x*cellSize,0,z*cellSize);
                        //glNormal3f(Nx,Ny,Nz);
                        glVertex3f((x+1)*cellSize,0,z*cellSize);

                        glVertex3f((x+1)*cellSize,0,z*cellSize);
                        //glNormal3f(Nx,Ny,Nz);
                        glVertex3f((x+1)*cellSize,0,(z+1)*cellSize);

                        glVertex3f((x+1)*cellSize,0,(z+1)*cellSize);
                        //glNormal3f(Nx,Ny,Nz);
                        glVertex3f(x*cellSize,0,(z+1)*cellSize);


                }
            }

            glEnd();
            glDisable(GL_COLOR);
            glEnable(GL_LIGHTING);
        }
        else
        {
            if (tex != nullptr)
            {
                tex->useThisTexture();
                glBegin(GL_QUADS);
                if(!tile)
                {
                    for(int x = 0; x < drawnCells.first; x++)
                    {
                        for(int z = 0; z<drawnCells.second; z++)
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
                    }
                }
                else
                {
                    for(int x = 0; x < drawnCells.first; x++)
                    {
                        for(int z = 0; z<drawnCells.second; z++)
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
                    }
                }
            glEnd();
            }
            else
            {
            glBegin(GL_QUADS);

            for(int x = 0; x < drawnCells.first; x++)
            {
                for(int z = 0; z<drawnCells.second; z++)
                {
                    glNormal3f(0,-1,0);
                    glVertex3f(x*cellSize,0,z*cellSize);
                    glNormal3f(0,-1,0);
                    glVertex3f((x+1)*cellSize,0,z*cellSize);
                    glNormal3f(0,-1,0);
                    glVertex3f((x+1)*cellSize,0,(z+1)*cellSize);
                    glNormal3f(0,-1,0);
                    glVertex3f(x*cellSize,0,(z+1)*cellSize);
                }
            }

            glEnd();
            }
        }

		glColor3f(1,1,1);
	glPopMatrix();

}
