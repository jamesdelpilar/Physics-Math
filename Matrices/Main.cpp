#include <iostream>

#include "Mat3.h"

using namespace std;

int main()
{
	Mat3 a;
	Mat3 b;
	Mat3 c;

	Mat3 d;

	Vec3 v1(1, 2, 3);
	
	Vec3 v2;

	a.m[0] = 1;
	a.m[1] = 4;
	a.m[2] = 7;
	a.m[3] = 2;
	a.m[4] = 5;
	a.m[5] = 8;
	a.m[6] = 3;
	a.m[7] = 6;
	a.m[8] = 9;

	b.m[0] = 1;
	b.m[1] = 2;
	b.m[2] = 3;
	b.m[3] = 4;
	b.m[4] = 5;
	b.m[5] = 6;
	b.m[6] = 7;
	b.m[7] = 8;
	b.m[8] = 9;

	d.m[0] = 1;
	d.m[1] = 5;
	d.m[2] = 0;
	d.m[3] = 2;
	d.m[4] = 4;
	d.m[5] = 3;
	d.m[6] = 0;
	d.m[7] = 6;
	d.m[8] = 9;

	// Matrix a * b
	c = a * b;
	cout << "Matrix a * b = \t" << endl;
	c.Print();

	// Matrix a * v1
	v2 = a * v1; 
	
	cout << "Matrix a * v1 = (" << v2.x << ", " << v2.y << ", " << v2.z << ")" << endl;
	
	//Determinant of d
	cout << "The determinant of d = \t" << d.Det() << endl;
	
	// Inverse Matrix of d
	cout << "The inverse matrix of d = \t" << endl;

	Mat3 inverseResult = d.Inverse();
	inverseResult.PrintInverse();
	
	return 0;
}