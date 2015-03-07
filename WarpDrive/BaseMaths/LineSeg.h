#ifndef LINE_SEGMENT_H
#define LINE_SEGMENT_H


#include "BaseMaths/Vec3.h"

#include <utility>


class LineSeg
{

public:
	LineSeg() {p0 = Vec3f(0,0,0); p1 = Vec3f(0,0,0);}

	LineSeg(const Vec3f& a, const Vec3f& b) {p0 = a; p1 = b;}
	LineSeg(float ax, float ay, float az, float bx, float by, float bz){ p0 = Vec3f(ax,ay,az); p1 = Vec3f(bx,by,bz);}


	Vec3f getStart() const {return p0;}
	Vec3f getEnd() const {return p1;}

	void Draw() ;

	bool contains(const Vec3f& ) const {return true;}
	std::pair<bool, Vec3f> intersects (const LineSeg& other) const ;
	bool parallel(const LineSeg& other) const;
	float sqDistToPoint ( const Vec3f& p) const;


private:

	Vec3f p0;
	Vec3f p1;




};

#endif //LINESEG_H
