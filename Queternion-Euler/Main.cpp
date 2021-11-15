#include <iostream>
#include "Quaternion.h"

using std::cout;
using std::endl;

int main()
{	
	// Quaternion Test

		Quaternion Rotate(Vec3(0.0f, 0.0f, 1.0f), 90.0f);
		Vec3 v(1.0f, 0.0f, 0.0f);
		v = Rotate.Rotate(v);
		cout << "RotateZ.Rotate(Vector) = (" << v.x << "," << v.y << "," << v.z << ")\n" << std::endl;

		Quaternion q1(1.0f, 2.0f, 2.0f, 3.0f); Quaternion q2(2.0f, 1.0f, 2.0f, 5.0f);

		Quaternion q = q1 * q2;
		cout << "Quaternion Multiplication (q1 * q2) = (" << q.quaternion.x << "," << q.quaternion.y << "," << q.quaternion.z << "," << q.quaternion.w << ")" << std::endl;
		//cout << "q1 * q2 = (" << q.x << "," << q.y << "," << q.z << "," << q.w << ")" << std::endl;

		Mat3 test = q1.ConvertToMatrix();

		cout << "[" << test.m[0] << "]\t" << "[" << test.m[1] << "]\t" << "[" << test.m[2] << "]\t" << endl;
		cout << "[" << test.m[3] << "]\t" << "[" << test.m[4] << "]\t" << "[" << test.m[5] << "]\t" << endl;
		cout << "[" << test.m[6] << "]\t" << "[" << test.m[7] << "]\t" << "[" << test.m[8] << "]\t" << endl;

		EulerAngles testQuaternionToEulerAngles;

		Quaternion qEulerTest(Vec3(1.0f, 0.0f, 0.0f), 90.0f);

		testQuaternionToEulerAngles = qEulerTest.ConvertEuler();

		cout << "testQuaternionToEulerAngles = (" << testQuaternionToEulerAngles.roll << "," << testQuaternionToEulerAngles.pitch << "," << testQuaternionToEulerAngles.yaw << ")" << std::endl;

		//Testing Vec3 Rotate(Vec3 vec)
		/*	- First create a quaternion that represents a rotation of 90 degrees about the z axis
			- Then rotate the vector[1, 0, 0] by this quaternion
			- Your result should be[0, 1, 0]

			Testing Quaternion operator * (Quaternion otherQuat)
			- Take two quaternions :
		-q1 = [x, y, z, w] = [1, 2, 2, 3]
			- q2 = [2, 1, 2, 5]
			- Your answer should be q1 × q2 = [13, 15, 13, 7]*/

	return 0;
}