#include "Mat3.h"

using namespace std;

void Mat3::Print() {
	cout << "[" << m[0] << "]" << "[" << m[1] << "]" << "[" << m[2] << "]" << endl;
	cout << "[" << m[3] << "]" << "[" << m[4] << "]" << "[" << m[5] << "]" << endl;
	cout << "[" << m[6] << "]" << "[" << m[7] << "]" << "[" << m[8] << "]" << endl;
}

Mat3::Mat3()
{
Mat3::SetIdentity();
}

void Mat3::SetIdentity()
{
	m[0] = 1; m[1] = 0; m[2] = 0;
	m[3] = 0; m[4] = 1; m[5] = 0;
	m[6] = 0; m[7] = 0; m[8] = 1;
}

void Mat3::RotateZ(float ang)
{
	m[0] = cos(ang); m[1] = -sin(ang); m[2] = 0;
	m[3] = sin(ang); m[4] = cos(ang);  m[5] = 0;
	m[6] = 0;        m[7] = 0;         m[8] = 1;
}

void Mat3::Scale(float x, float y, float z)
{
	m[0] = x; m[1] = 0; m[2] = 0;
	m[3] = 0; m[4] = y; m[5] = 0;
	m[6] = 0; m[7] = 0; m[8] = z;
}

void Mat3::Transpose()
{
	float tempm[9];
	tempm[0] = m[0]; tempm[1] = m[3]; tempm[2] = m[6];
	tempm[3] = m[1]; tempm[4] = m[4]; tempm[5] = m[7];
	tempm[6] = m[2]; tempm[7] = m[5]; tempm[8] = m[8];
	
	for (int i = 0; i < 9; i++) {
		m[i] = tempm[i];
	}
}

