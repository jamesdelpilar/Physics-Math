#include <iostream>

#include "Vec3.h"
#include "Mat3.h"

using namespace std;

int main()
{
	Vec3 v1(-6, 8, 1);
	Vec3 v2(5, 12, 1);
	Vec3 v3(1, 1, 1);

	cout << "v1 = (" << v1.x << ", " << v1.y << ", " << v1.z << ")" << endl;

	v1.Add(v2);

	cout << "The addition of vectors results in v1 = (" << v1.x << ", " << v1.y << ", " << v1.z << ")" << endl;

	v1.Subtract(v3);

	cout << "The subtraction of vectors result in v1 = (" << v1.x << ", " << v1.y << ", " << v1.z << ")" << endl;

	v1.ScalarMultiplication(5);

	cout << "The scalar multiplication of 5 times vector v1 = (" << v1.x << ", " << v1.y << ", " << v1.z << ")" << endl;

	cout << "The magnitude of vector v1 = " << v1.Mag() << endl;

	v1.Normalize();

	cout << "The normalized vector v1 = (" << v1.x << ", " << v1.y << ", " << v1.z << ")" << endl;

	// Dot Product
	cout << "The dot product of vectors result in v1 = " << v1.Dot(v2) << endl;
	
	v1.Lerp(v2, 1);
	cout << "The lerp of vectors result in v1 = (" << v1.x << ", " << v1.y << ", " << v1.z << ")" << endl;

	v1.RotateZ(90);
	cout << "The rotation around the angle results in v1 = (" << v1.x << ", " << v1.y << ", " << v1.z << ")" << endl;

	Mat3 a;	

	cout << "Matrix a = \t" << endl;
	a.Print();

	a.Scale(2, 2, 2);
	cout << "The Scaling Matrix a = \t" << endl;
	a.Print();

	a.SetIdentity();
	cout << "The Identity Matrix a = \t" << endl;
	a.Print();
	
	a.RotateZ(90);
	cout << "The Rotation Matrix a = \t" << endl;
	a.Print();

	a.Transpose();
	cout << "The Transpose Matrix a = \t" << endl;
	a.Print();
	
	return 0;
}