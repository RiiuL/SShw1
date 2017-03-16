#pragma once
#include "Renderer.h"
class Viewer: public Renderer //Viewer==windowâ
{
public:
	GLFWwindow* WindowID = nullptr;
	GLuint WINDOWSIZEx = 500;
	GLuint WINDOWSIZEy = 500;

public:
	void myCreateWindow();
	void bootup(); //mouse&key control
	void run();

	Viewer();
	~Viewer();
	void keyboard(GLFWwindow*, int, int, int, int);
	void mouse(GLFWwindow* window, int button, int action, int mods);
	void move(GLFWwindow* window, double xpos, double ypos);

protected:
	glm::vec2 winpos = glm::vec2(0, 0);
private:
	bool lctrl = false;
	bool scaling = false;
	bool tracking = false;
private:
};

