#pragma once
#include "Model.h"
#include <GLFW\glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Shader.h"
#include "Light.h"
class Renderer
{
public:
	GLuint ProgramID;
	Shader myShader;
	Model myObject[1];
	Camera CAM;
	Light lightsource;
private:
	GLuint ObjectSize = 1;
	
public:
	Renderer();
	~Renderer();
	void startup();
	void draw();
	void update();

	void Bind_Light(Light);

protected:
	void render();

private:
	GLuint vao;
	GLuint ubo;
};

