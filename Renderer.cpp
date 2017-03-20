#include "Renderer.h"



Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}


void Renderer::startup() {
	ProgramID = myShader.Load_shader("shader.vs", "shader.fs");
	
	


	Bind_Light(lightsource);

	glUseProgram(ProgramID); //두 shader와 연결된 프로그램명이 담겼지. 그걸 쓸 거야
	glUniformMatrix4fv(glGetUniformLocation(ProgramID, "Mproj"), 1, GL_FALSE, glm::value_ptr(CAM.proj_mat));
	glUniformMatrix4fv(glGetUniformLocation(ProgramID, "Mview"), 1, GL_FALSE, glm::value_ptr(CAM.view_mat));
	//glUniform1i(glGetUniformLocation(ProgramID, "TEX"), 0); //texture
	glUseProgram(0);

	glEnable(GL_CULL_FACE); // back face culling
	glEnable(GL_DEPTH_TEST); // depth test 


	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//object loading
	myObject[0].Load_Object();
	//myObject.Bind_Texture("teapottex.bmp");
	glBindVertexArray(0);

	//glGenVertexArrays(1, &vao);
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
	glUseProgram(ProgramID); //두 shader와 연결된 프로그램명이 담겼지. 그걸 쓸 거야
	glBindVertexArray(vao);
	for (int i = 0; i < ObjectSize; i++) {
		for (int j = 0; j < 3; j++) { //j=0 앞, j=1중간, j=2 뒤
			glm::mat4 ModelView_mat;
			glm::mat4 Model_mat = glm::mat4(1.0);
			glm::vec3 Color;
			switch (j) {
			case 0:
				Color = glm::vec3(0.7, 0, 0);
				break;
			case 1:
				Model_mat = glm::translate(glm::vec3(0.5, 0.5, 0.5));  //A*=B 이럼 A=A*B. 뒤에 붙음.
				Color = glm::vec3(0, 0.7, 0);
				break;
			case 2:
				Model_mat = glm::translate(glm::vec3(-0.5, -0.5, -0.5));
				Color = glm::vec3(0, 0, 0.7);
				break;
			}
			ModelView_mat = CAM.view_mat*Model_mat;

			glUniform3fv(glGetUniformLocation(ProgramID, "Color"), 1, glm::value_ptr(Color));
			glUniformMatrix4fv(glGetUniformLocation(ProgramID, "Mview"), 1, GL_FALSE, glm::value_ptr(ModelView_mat));
			glDrawArrays(GL_TRIANGLES, 0, myObject[i].vertex_list.size()); //세 번째 파트 = vertex갯수.
		}
	}
	glUseProgram(0);
}



void Renderer::Bind_Light(Light lightsource) {
	glGenBuffers(1, &ubo); //ubo
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(Light), &lightsource, GL_STATIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 3, ubo);
}