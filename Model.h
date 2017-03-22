#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Texture.h"

#pragma warning(disable:4996)

#define VVec3 std::vector<glm::vec3> //vec3�� ����
#define Num_SubModel 3

class Model
{
public:
	VVec3 vertex_list, texture_list, normal_list; //���� ���� pointer�� �ҷ�����
	Texture TEX;

//���� �׸�
public:
	typedef struct boundarybox {
		glm::vec3 center;
		float radius;
	} BoundaryBox;
	BoundaryBox HittingBox[Num_SubModel]; //xyz, R
	glm::mat4 Model_mat[Num_SubModel];
	bool inside_the_box(double,double );
//

public:
	Model(); ~Model();
	void Load_Triangle();
	void Load_Object();
	void Load_Object2();
	void Load_Objfile(const char*);
	void Bind_VBO(const VVec3, const VVec3, const VVec3);
	void Bind_Texture(const char*);

private:
	GLuint vertex_buffer, normal_buffer, texture_buffer;
	GLuint vbo_count = 0;

	//class ������ �� ���� ���� id����� �ֱ�.
	const uint32_t m_id; //������ ���ÿ� �ʱ�ȭ�ؾ߸� �� �� �ִ�.
	static uint32_t idmapper;//�갡 �ʱ�ȭ����.
};



