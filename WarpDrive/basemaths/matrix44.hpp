#ifndef WD_MATRIX_4X4_HPP_DEFINED
#define WD_MATRIX_4X4_HPP_DEFINED

#include <array>

#include "WarpDrive/basemaths/vec4.hpp"

#ifdef WIN32
    #include <Windows.h>
#endif //WIN32

#include <GL/gl.h>


using float16 = std::array<float,16>;

/**
 * @brief The Matrix44 class represents a 4 by 4 matrix. It is represented in "OpenGL style",
 *      left to right, top to bottom. So elements [5] is the second collumn in the second row
 */

class Matrix44
{
public:

    Matrix44();
    explicit Matrix44(float16& mat);
    explicit Matrix44(GLdouble* mat);


    void setIdentity();

    void multiply(const Matrix44& rhs);

    void setTranslation(float x, float y, float z);
    void setScaling(float x, float y, float z);
    void setRotation(float degx, float degy, float degz);
    void setRotationRad( float radx, float rady, float radz);
    //void Print();

    const float16& Elements() const {return elements;}

    void applyMatrix() const;   //Apply this to the current Display Matrix
    void setMatrix() const;     //SET the current Display Matrix to be THIS

    void getModelview();
    void getProjection();


    static Vec4f multiply( const Matrix44& mat, const Vec4f& vec)
        {
            auto e = mat.Elements();
            return Vec4f(  e[0]*vec.X()+e[4]*vec.Y()+e[8]*vec.Z()+e[12]*vec.W(),
                        e[1]*vec.X()+e[5]*vec.Y()+e[9]*vec.Z()+e[13]*vec.W(),
                        e[2]*vec.X()+e[6]*vec.Y()+e[10]*vec.Z()+e[14]*vec.W(),
                        e[3]*vec.X()+e[7]*vec.Y()+e[11]*vec.Z()+e[15]*vec.W()   );
        }



private:

    float16 elements;

};

#endif //WD_MATRIX_4X4_HPP_DEFINED
