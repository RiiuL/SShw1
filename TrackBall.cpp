#include "TrackBall.h"



TrackBall::TrackBall()
{
}


TrackBall::~TrackBall()
{
}
/*void TrackBall::Tracking(double xpos, double ypos) {
	cout << "cur pos: " << xpos << ", " << ypos << endl;

	//rotation
	glm::vec3 p1, p2;

	// cartesian_to_sphere
	//normalize
	p1[0] = 1 - winpos.x * 2 / WINDOWSIZEx;//-1~1
	p1[1] = winpos.y * 2 / WINDOWSIZEy - 1; // -1~1
	p1[2] = project_to_sphere(1, p1[0], p1[1]);
	//p1[2] = sqrt(1 - p1[0] * p1[0] - p1[1] * p1[1]); //cartesian_to_sphere
	p2[0] = 1 - xpos * 2 / WINDOWSIZEx;
	p2[1] = ypos * 2 / WINDOWSIZEy - 1;
	p2[2] = project_to_sphere(1, p2[0], p2[1]);
	

	glm::quat myQuaternion = computeRotationStart2Target(p1, p2);

	//À§Ä¡ update
	CAM.pastQ = myQuaternion * CAM.pastQ;
	CAM.view_mat = CAM.lookat_mat*glm::toMat4(CAM.pastQ);
	winpos.x = xpos; winpos.y = ypos;
}
winpos.x = xpos; winpos.y = ypos;
}
*/
float
TrackBall::project_to_sphere(float r, float x, float y)
{
	float d, t, z;

	d = sqrt(x*x + y*y);
	if (d < r * 0.70710678118654752440) {    /* Inside sphere */
		z = sqrt(r*r - d*d);
	}
	else {           /* On hyperbola */
		t = r / 1.41421356237309504880;
		z = t*t / d;
	}
	return z;
}
glm::quat TrackBall::computeRotationStart2Target(const glm::vec3 &start, const glm::vec3 &target)
{
	glm::vec3 begin = glm::normalize(start);
	glm::vec3 end = glm::normalize(target);
	float cosTheta = glm::dot(begin, end);
	glm::vec3 rotationAxis;

	// if start and end vector is parallel
	if (cosTheta < -1 + 0.001f)
	{
		rotationAxis = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), begin);
		if (glm::length(rotationAxis) < 0.01)
			rotationAxis = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), begin);
		rotationAxis = glm::normalize(rotationAxis);
		return glm::angleAxis(180.0f, rotationAxis);
	}

	rotationAxis = glm::cross(begin, end);
	float s = sqrt((1 + cosTheta) * 2);
	float invs = 1 / s;

	return glm::quat(
		s *  0.5f,
		rotationAxis.x * invs,
		rotationAxis.y * invs,
		rotationAxis.z * invs
	);

}
