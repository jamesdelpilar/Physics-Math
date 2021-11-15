#include "AAB.h"

AAB::AAB(float width, float height, float depth)
{
	rx = width; ry = height; rz = depth;

// We will only use boxes lined up with the origin
// First three planes go through the origin
box[0] = Plane(1, 0, 0, 0);
box[1] = Plane(0, 1, 0, 0);
box[2] = Plane(0, 0, 1, 0);

// Last three planes are a distance away from origin (width, height, and depth)

box[3] = Plane(1, 0, 0, -rx);
box[4] = Plane(0, 1, 0, -ry);
box[5] = Plane(0, 0, 1, -rz);

}

AAB::AAB()
{
	rx = 1.0f;
	ry = 1.0f;
	rz = 1.0f;

	box[0] = Plane(1, 0, 0, 0);
	box[1] = Plane(0, 1, 0, 0);
	box[2] = Plane(0, 0, 1, 0);

	box[3] = Plane(1, 0, 0, -rx);
	box[4] = Plane(0, 1, 0, -ry);
	box[5] = Plane(0, 0, 1, -rz);
}
