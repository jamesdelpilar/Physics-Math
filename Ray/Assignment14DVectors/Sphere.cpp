#include "Sphere.h"

Sphere::Sphere(Vec3 position_, float radius_)
{
	position = position_;
	radius = radius_;

}

Sphere::Sphere()
{
	position = Vec3(0.0f, 0.0f, 0.0f);
	radius = 1.0f;
}
