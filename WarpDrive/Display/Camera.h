
#ifndef CAMERA_H
#define CAMERA_H

#include "BaseMaths/Vec3.h"
#include "BaseSystem/GameObject.h"
#include <utility>
#include <GL/gl.h>

class Camera: public GameObject
{
public:

	Camera();
	void Update();
	void Draw();
	void Use();

	void setTarget(const Vec3f& targetPos);
	void setTarget(const GameObject* targetObject);
	std::pair<bool, Vec3f> getTarget() const;
	void setRelativePos(const Vec3f& Relative); //Relative Position to a targeted Object
	Vec3f getRelativePos() const {return relativePos;}

private:

	Vec3f up;
	const GameObject* targetObj;
	Vec3f target;
	Vec3f relativePos;


	




};

#endif //CAMERA_H
