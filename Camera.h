#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> 
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

class Camera
{
public:
	float fovy = 50.f;
	float aspect = 1260 / 760;
	float near = 0.1f;
	float far = 100.f;

	glm::vec3 eye = { 0.f, 0, 10 };
	glm::vec3 at = { 0.0f, 0.0f, 0.0f };
	glm::vec3 up = { 0.0f, 1.0f, 0.0f };
	glm::quat pastQ = { 1.0f, 0.f, 0.f, 0.f };
	//virtual void move() = 0;
	//virtual void rotate() = 0;
	glm::mat4 lookat_mat = glm::lookAt(eye, at, up);
	glm::mat4 view_mat = lookat_mat;
	glm::mat4 model_mat = glm::toMat4(pastQ);
	glm::mat4 proj_mat = glm::perspective(fovy, aspect, near, far); //fovy, aspect_ratio, near, far
public:
	Camera();
	~Camera();
protected:
	//fps카메라, trackball카메라를 camera상속받아서 만들기
	//책 6~9챕터 읽기
};

