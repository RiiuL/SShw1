#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Texture.h"

#pragma warning(disable:4996)

#define VVec3 std::vector<glm::vec3> //vec3의 벡터
#define Num_SubModel 3

class Model
{
public:
	VVec3 vertex_list, texture_list, normal_list; //따로 떼서 pointer로 불러오자
	Texture TEX;

//하위 항목
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

	//class 생성될 때 마다 고유 id만들어 주기.
	const uint32_t m_id; //생성과 동시에 초기화해야만 쓸 수 있다.
	static uint32_t idmapper;//얘가 초기화해줌.
};



