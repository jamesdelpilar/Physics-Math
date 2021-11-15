#include <iostream>

#include "Mat3.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Main.h"
#include "Ray.h"
#include "Plane.h"

using namespace std;

int main()
{
	Vec3 V(2, 2, 1);
	Vec3 U(4, 2, 1);

	Vec3 tempV(2, 2, 1);
	Vec3 tempU(4, 2, 1);

	Vec3 OverloadResult;
	
	cout << "Vec3 V(2, 2, 1)" << endl;
	cout << "Vec3 V(4, 2, 1)" << endl;
	cout << "-------------------" << endl;

	//Overload Operators
	cout << "Overload Operators" << endl;
	cout << "-------------------" << endl;
	
	OverloadResult = V + U;
	cout << "Addition = (" << OverloadResult.x << ", " << OverloadResult.y << ", " << OverloadResult.z << ")" << endl;
	
	OverloadResult = V - U;
	cout << "Subtraction = (" << OverloadResult.x << ", " << OverloadResult.y << ", " << OverloadResult.z << ")" << endl;
	
	OverloadResult = V.ScalarMultiplication(3);
	cout << "ScalarMultiplication = (" << OverloadResult.x << ", " << OverloadResult.y << ", " << OverloadResult.z << ")" << endl;

	OverloadResult = (V * 5);
	cout << "Multiply Vector by a # = (" << OverloadResult.x << ", " << OverloadResult.y << ", " << OverloadResult.z << ")" << endl;
	cout << "-------------------" << endl;
	
	//Magnitude
	cout << "Magnitude of V is: " << V.Mag() << endl;
	cout << "-------------------" << endl;

	V.Normalize();
	cout << "Normalized V is: (" << V.x << ", " << V.y << ", " << V.z << ")" << endl;
	cout << "-------------------" << endl;

	// Dot Product
	cout << "Dot Product V.U is: " << tempV.Dot(U) << endl;
	cout << "-------------------" << endl;

	//CrossProduct

	Vec3 CrossResult = tempU.Cross(tempV);
	cout << "Cross Product UxV is:" << endl;
	CrossResult.Print();
	cout << "-------------------" << endl;
	
	// If NV = 0 | NO INTERSECTION/PARALLEL
	Vec3 start(0.0f, 0.0f, 0.0f);
	Vec3 dir(0.0f, 0.0f, 0.0f);
	Plane L(2.0f, 1.0f, 0.0f, -4.0f);

	// If LS = 0 | INFNITY
	//Plane L(0.0f, 0.0f, 0.0f, 0.0f);
	//Vec3 start(1.0f, 0.0f, 1.0f);
	//Vec3 dir(3.0f, 2.0f, 1.0f);

	//Assignment
	/*Plane L(2.0f, 1.0f, 0.0f, -4.0f);
	Vec3 start(1.0f, 0.0f, 1.0f);
	Vec3 dir(3.0f, 2.0f, 1.0f);*/

	Ray ray(start, dir);
	Vec3 answer;
	answer = L.intersectionPoint(ray);
	
	cout << "Intersection Point = (" << answer.x << ", " << answer.y << ", " << answer.z << ")" << endl;

	return 0;

}