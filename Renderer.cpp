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

	glUseProgram(ProgramID); //�� shader�� ����� ���α׷����� �����. �װ� �� �ž�
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
	glUseProgram(ProgramID); //�� shader�� ����� ���α׷����� �����. �װ� �� �ž�
	glBindVertexArray(vao);
	for (int i = 0; i < ObjectSize; i++) {
		for (int j = 0; j < 3; j++) { //j=0 ��, j=1�߰�, j=2 ��
			glm::mat4 ModelView_mat;
			myObject[i].Model_mat[j] = glm::mat4(1.0);
			glm::vec3 Color;
			switch (j) {
			case 0:
				Color = glm::vec3(0.7, 0, 0);
				break;
			case 1:
				myObject[i].Model_mat[j] = glm::translate(glm::vec3(0.5, 0.5, 0.5));  //A*=B �̷� A=A*B. �ڿ� ����.
				Color = glm::vec3(0, 0.7, 0);
				break;
			case 2:
				myObject[i].Model_mat[j] = glm::translate(glm::vec3(-0.5, -0.5, -0.5));
				Color = glm::vec3(0, 0, 0.7);
				break;
			}
			ModelView_mat = CAM.view_mat*myObject[i].Model_mat[j];

			glm::vec3& myOb_HBox = myObject[i].HittingBox[j].center;
			myOb_HBox = ModelView_mat*glm::vec4(myOb_HBox, 1.f);

			glUniform3fv(glGetUniformLocation(ProgramID, "Color"), 1, glm::value_ptr(Color));
			glUniformMatrix4fv(glGetUniformLocation(ProgramID, "Mview"), 1, GL_FALSE, glm::value_ptr(ModelView_mat));
			glDrawArrays(GL_TRIANGLES, 0, myObject[i].vertex_list.size()); //�� ��° ��Ʈ = vertex����.
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