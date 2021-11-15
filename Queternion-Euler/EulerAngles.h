#ifndef EULERANGLES_H
#define EULERANGLES_H

struct EulerAngles {

	float roll;
	float pitch;
	float yaw;

	EulerAngles();
	~EulerAngles();
	EulerAngles(float roll, float picth, float yaw);

};

#endif