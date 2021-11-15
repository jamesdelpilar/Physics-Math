#ifndef RAY_H
#define RAY_H

class Ray	
{
public:
	Ray();
	// Starting position of ray
	Vec3 start;

	// Direction of ray
	Vec3 dir;

	Ray(Vec3 start_, Vec3 dir_);

	Vec3 currentPosition(float t);
};

#endif
