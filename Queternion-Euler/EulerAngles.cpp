#include "EulerAngles.h"
EulerAngles::EulerAngles()
{
	roll = 0.0f;
	pitch = 0.0f;
	yaw = 0.0f;
}

EulerAngles::~EulerAngles()
{
}

EulerAngles::EulerAngles(float roll_, float pitch_, float yaw_)
{
	roll = roll_;
	pitch = pitch_;
	yaw = yaw_;
}
