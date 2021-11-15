#ifndef AAB_H
#define AAB_H

#include "Plane.h"

//  Axis Aligned Box
class AAB 
{
public:

// Width, height, and depth of box
	float rx;
	float ry;
	float rz;

// Box, 6 planes
	Plane box[6];
	
//Constructors
		
AAB(float width, float height, float depth);
		
AAB();


};

#endif
