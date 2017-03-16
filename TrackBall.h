#pragma once
#include "Camera.h"
class TrackBall:Camera
{
public:
	TrackBall();
	~TrackBall();
	//void Tracking(double xpos, double ypos);
protected:
	static float project_to_sphere(float, float, float);
	glm::quat computeRotationStart2Target(const glm::vec3 &start, const glm::vec3 &target);
};

