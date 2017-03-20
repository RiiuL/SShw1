#pragma once
#include "Renderer.h"
class Viewer: public Renderer //Viewer==windowâ
{
public:
	GLFWwindow* WindowID = nullptr;
	GLuint WINDOWSIZEx = 500;//1260;
	GLuint WINDOWSIZEy = 500;// 760;

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
	//mod
	bool lctrl = false;
	bool scaling = false;
	bool tracking = false;
	bool picking = false;
	bool tracing = false;
private:
};

