
#ifndef MATRIX_4X4_H
#define MATRIX_4X4_H


#include <stdio.h>

#include "Vec4.h"





class Matrix44
{
public:

	Matrix44();
	Matrix44(float* mat);

	void setIdentity();

	void Multiply(const Matrix44& rhs);
	 
	

	void setTranslation(float x, float y, float z);
	void setScaling(float x, float y, float z);
	void setRotation(float degx, float degy, float degz);
	void setRotationRad( float radx, float rady, float radz);
	void Print();

	const float* getElements() const {return elements;}

	void applyMatrix();		//Apply this to the current Display Matrix
	void setMatrix();		//SET the current Display Matrix to be THIS

	void getModelview();
	void getProjection();


	static Vec4f Multiply( const Matrix44& mat, const Vec4f& vec)
		{
			const float* e = mat.getElements();
			return Vec4f(e[0]*vec.X()+e[4]*vec.Y()+e[8]*vec.Z()+e[12]*vec.W(),
						e[1]*vec.X()+e[5]*vec.Y()+e[9]*vec.Z()+e[13]*vec.W(),
						e[2]*vec.X()+e[6]*vec.Y()+e[10]*vec.Z()+e[14]*vec.W(),
						e[3]*vec.X()+e[7]*vec.Y()+e[11]*vec.Z()+e[15]*vec.W());
		}



private:

	float elements[16];



};







#endif //MATRIX_4X4_H