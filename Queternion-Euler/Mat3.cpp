#include "Mat3.h"

void Mat3::Print()
{
	cout << "[" << m[0] << "]\t" << "[" << m[1] << "]\t" << "[" << m[2] << "]\t" << endl;
	cout << "[" << m[3] << "]\t" << "[" << m[4] << "]\t" << "[" << m[5] << "]\t" << endl;
	cout << "[" << m[6] << "]\t" << "[" << m[7] << "]\t" << "[" << m[8] << "]\t" << endl;
}

void Mat3::PrintInverse()
{
	cout << "[" << m[0] << "]\t" << "\t[" << m[1] << "]\t" << "\t[" << m[2] << "]\t" << endl;
	cout << "[" << m[3] << "]\t" << "\t[" << m[4] << "]\t" << "[" << m[5] << "]\t" << endl;
	cout << "[" << m[6] << "]\t" << "[" << m[7] << "]\t" << "[" << m[8] << "]\t" << endl;
}
/* Matrix Constructor
	Set matrix entries to the identity matrix */
Mat3::Mat3()
{
	Mat3::SetIdentity();
}

/* SetIdentity Member Function
	Set matrix entries to the identity matrix */
void Mat3::SetIdentity()
{
	m[0] = 1; m[1] = 0; m[2] = 0;
	m[3] = 0; m[4] = 1; m[5] = 0;
	m[6] = 0; m[7] = 0; m[8] = 1;
}

/* RotateZ Member Function
	Set matrix entries to the rotation matrix */
void Mat3::RotateZ(float ang)
{
	m[0] = cos(ang); m[1] = -sin(ang); m[2] = 0;
	m[3] = sin(ang); m[4] = cos(ang);  m[5] = 0;
	m[6] = 0;        m[7] = 0;         m[8] = 1;
}

/* Scale Member Function
	Set matrix entries to the scale matrix */
void Mat3::Scale(float x, float y, float z)
{
	m[0] = x; m[1] = 0; m[2] = 0;
	m[3] = 0; m[4] = y; m[5] = 0;
	m[6] = 0; m[7] = 0; m[8] = z;
}

/* Transpose Member Function
	Set matrix entries to the transpose matrix */
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

/* Multiplication Member Function
	Calculate the multiplication of two matrices and return the result */
Mat3 Mat3::operator*(Mat3 otherMat)
{
	Mat3 tempa;

	tempa.m[0] = m[0] * otherMat.m[0] + m[1] * otherMat.m[3] + m[2] * otherMat.m[6];
	tempa.m[1] = m[0] * otherMat.m[1] + m[1] * otherMat.m[4] + m[2] * otherMat.m[7];
	tempa.m[2] = m[0] * otherMat.m[2] + m[1] * otherMat.m[5] + m[2] * otherMat.m[8];

	tempa.m[3] = m[3] * otherMat.m[0] + m[4] * otherMat.m[3] + m[5] * otherMat.m[6];
	tempa.m[4] = m[3] * otherMat.m[1] + m[4] * otherMat.m[4] + m[5] * otherMat.m[7];
	tempa.m[5] = m[3] * otherMat.m[2] + m[4] * otherMat.m[5] + m[5] * otherMat.m[8];

	tempa.m[6] = m[6] * otherMat.m[0] + m[7] * otherMat.m[3] + m[8] * otherMat.m[6];
	tempa.m[7] = m[6] * otherMat.m[1] + m[7] * otherMat.m[4] + m[8] * otherMat.m[7];
	tempa.m[8] = m[6] * otherMat.m[2] + m[7] * otherMat.m[5] + m[8] * otherMat.m[8];

	return tempa;
}

/* Matrix and Vector Multiplication Member Function
	Calculate the multiplication of a matrix and vector, and return the result */
Vec3 Mat3::operator*(Vec3 Vinput)
{
	Vec3 VResult;

	VResult.x = m[0] * Vinput.x + m[1] * Vinput.y + m[2] * Vinput.z;
	VResult.y = m[3] * Vinput.x + m[4] * Vinput.y + m[5] * Vinput.z;
	VResult.z = m[6] * Vinput.x + m[7] * Vinput.y + m[8] * Vinput.z;

	return VResult;
}

/* Determinant Member Function
	Calculate the determinant of a matrix */
float Mat3::Det()
{
	return (m[0] * (m[4] * m[8] - m[5] * m[7]) - m[1] * (m[3] * m[8] - m[5] * m[6]) + m[2] * (m[3] * m[7] - m[4] * m[6]));
}
//CW_DEFAULT
/* Inverse Member Function
	Calculate the inverse matrix */
Mat3 Mat3::Inverse()
{
	Mat3 tempAdjugates;
	Mat3 inverseResult;

	tempAdjugates.m[0] = m[4] * m[8] - m[5] * m[7];	//ei - fg
	tempAdjugates.m[1] = m[2] * m[7] - m[1] * m[8];	// ch - bi
	tempAdjugates.m[2] = m[1] * m[5] - m[2] * m[4]; // bf - ce

	tempAdjugates.m[3] = m[5] * m[6] - m[3] * m[8];	//fg - di
	tempAdjugates.m[4] = m[0] * m[8] - m[2] * m[6];	//ai - cg
	tempAdjugates.m[5] = m[2] * m[3] - m[0] * m[5];	//cd - af

	tempAdjugates.m[6] = m[3] * m[7] - m[4] * m[6];	//df - eg
	tempAdjugates.m[7] = m[1] * m[6] - m[0] * m[7];	//bg - ah
	tempAdjugates.m[8] = m[0] * m[4] - m[1] * m[3];	//ae - bd

	for (int i = 0; i < 9; i++) {
		inverseResult.m[i] = 1 / Mat3::Det() * tempAdjugates.m[i];
	}

	return inverseResult;
}