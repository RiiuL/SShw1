#include "Renderer.h"



Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}


void Renderer::startup() {
	ProgramID = myShader.Load_shader("shader.vs", "shader.fs");
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//object loading
	myObject.Load_Object();
	//myObject.Bind_VBO(myObject.vertex_list, myObject.texture_list, myObject.normal_list);
	//myObject.Bind_Texture("teapottex.bmp");
	glBindVertexArray(0);

	Bind_Light(lightsource);

	glUseProgram(ProgramID); //�� shader�� ����� ���α׷����� �����. �װ� �� �ž�
	glUniformMatrix4fv(glGetUniformLocation(ProgramID, "Mproj"), 1, GL_FALSE, glm::value_ptr(CAM.proj_mat));
	glUniformMatrix4fv(glGetUniformLocation(ProgramID, "Mview"), 1, GL_FALSE, glm::value_ptr(CAM.view_mat));
	glUniform1i(glGetUniformLocation(ProgramID, "TEX"), 0); //texture
	glUseProgram(0);

	glEnable(GL_CULL_FACE); // back face culling
	glEnable(GL_DEPTH_TEST); // depth test 
}


void Renderer::update() {
	glUseProgram(ProgramID);
	glUniformMatrix4fv(glGetUniformLocation(ProgramID, "Mview"), 1, GL_FALSE, glm::value_ptr(CAM.view_mat));
	glUseProgram(0);
}


void Renderer::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.f, 1.f, 1.f, 1.f);

	render();
}
void Renderer::render(void) {
	glUseProgram(ProgramID); //�� shader�� ����� ���α׷����� �����. �װ� �� �ž�
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, myObject.vertex_list.size()); //�� ��° ��Ʈ = vertex����.
	glUseProgram(0);
}



void Renderer::Bind_Light(Light lightsource) {
	glGenBuffers(1, &ubo); //ubo
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(Light), &lightsource, GL_STATIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 3, ubo);
}