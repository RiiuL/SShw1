#include "Viewer.h"



Viewer::Viewer()
{
}


Viewer::~Viewer()
{
}


void Viewer::myCreateWindow() {
	if (!glfwInit()) { std::cout << "ERROR"; glfwTerminate(); return; }



	if (!(WindowID = glfwCreateWindow(WINDOWSIZEx, WINDOWSIZEy, ":o", NULL, NULL))) {
		std::cout << "ERROR"; glfwTerminate(); return;
	}
	glfwMakeContextCurrent(WindowID); // window maker와 opengl연결


	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		const GLubyte *e = glewGetErrorString(err);
		printf("Error: %s\n", e);
	}

}

void Viewer::run() {

	while (!glfwWindowShouldClose(WindowID))
	{
		/* Render here */
		update();
		draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(WindowID); // 윈도우로 뿌려줌

		/* Poll for and process events */
		glfwPollEvents(); //마우스 위치변화
	}


	glfwTerminate();
}


void Viewer::bootup() {
	double init_xpos, init_ypos;
	glfwGetCursorPos(WindowID, &init_xpos, &init_ypos);
	winpos = glm::vec2(init_xpos, init_ypos);
	//cout << "hwere"<<winpos.x << " " << winpos.y << endl;

	//key input

	//각각의 경우 해당하는 함수의 형식이 있음. 찾아 볼 것
	// static 형식의 함수만 쓸 수 있음. 근데 class안의 함수는 static일 수가 없다(여러번 선언될 수 있다)
	// 그래서 []함수 이용. []함수 안에서 class함수를 불러오는 형식
	glfwSetWindowUserPointer(WindowID, reinterpret_cast<void*>(this));

	glfwSetKeyCallback(WindowID, [](GLFWwindow* WindowIDptr, int key, int scancode, int action, int mods) {
		reinterpret_cast<Viewer*>(glfwGetWindowUserPointer(WindowIDptr))->keyboard(WindowIDptr, key, scancode, action, mods);
	}); //keyboard 클릭
	glfwSetMouseButtonCallback(WindowID, [](GLFWwindow* WindowIDptr, int button, int action, int mods) {
		reinterpret_cast<Viewer*>(glfwGetWindowUserPointer(WindowIDptr))->mouse(WindowIDptr, button, action, mods);
	}); //mouse 클릭
	glfwSetCursorPosCallback(WindowID, [](GLFWwindow* WindowIDptr, double xpos, double ypos) {
		reinterpret_cast<Viewer*>(glfwGetWindowUserPointer(WindowIDptr))->move(WindowIDptr, xpos, ypos);
	}); //mouse 움직임
}

void Viewer::keyboard(GLFWwindow* WindowIDptr, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_LEFT_CONTROL&&action == GLFW_PRESS) lctrl = true;
	if (key == GLFW_KEY_LEFT_CONTROL&&action == GLFW_RELEASE) lctrl = false;
}

void Viewer::mouse(GLFWwindow* window, int button, int action, int mods) { //다양한 인풋 모드가 있고 그에 따라 동작하는 게 다름.
	double xpos, ypos;
	if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS) {
		glfwGetCursorPos(window, &xpos, &ypos);
		std::cout << "mid" << xpos << " " << ypos << std::endl;
	}
	if (lctrl && button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) { scaling = true; std::cout << "scaling true" << std::endl; }
		else if (action == GLFW_RELEASE) { scaling = false; std::cout << "scaling false" << std::endl; }
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) { tracking = true; std::cout << "tracking true" << std::endl; }
		else if (action == GLFW_RELEASE) { tracking = false; std::cout << "tracking false" << std::endl; }
	}
}




static float project_to_sphere(float r, float x, float y)
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
glm::quat computeRotationStart2Target(const glm::vec3 &start, const glm::vec3 &target)
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

void Viewer::move(GLFWwindow* window, double xpos, double ypos) {

	//cout << "cur pos: " << xpos << ", " << ypos << endl;
	if (scaling) {
		//이것 말고 카메라의 위치를 수정하는 방식으로.
		if (ypos > winpos.y) {//감소
			CAM.lookat_mat *= glm::scale(glm::vec3(0.9f, 0.9f, 0.9f));
			CAM.view_mat = CAM.lookat_mat*glm::toMat4(CAM.pastQ);
		}
		else if (ypos < winpos.y) {//증가
			CAM.lookat_mat *= glm::scale(glm::vec3(1.1f, 1.1f, 1.1f));
			CAM.view_mat = CAM.lookat_mat*glm::toMat4(CAM.pastQ);
		}
	}
	if (tracking) { //trackball
		std::cout << "cur pos: " << xpos << ", " << ypos << std::endl;

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

		//위치 update
		CAM.pastQ = myQuaternion * CAM.pastQ;
		CAM.view_mat = CAM.lookat_mat*glm::toMat4(CAM.pastQ);
		winpos.x = xpos; winpos.y = ypos;
	}
	winpos.x = xpos; winpos.y = ypos;
}

