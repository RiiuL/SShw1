#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Texture.h"

#pragma warning(disable:4996)

#define VVec3 std::vector<glm::vec3> //vec3¿« ∫§≈Õ

class Model
{
public:
	VVec3 vertex_list, texture_list, normal_list;
	Texture TEX;

public:
	Model(); ~Model();
	void Load_Triangle();
	void Load_Object();
	void Load_Objfile(const char*);
	void Bind_VBO(const VVec3, const VVec3, const VVec3);
	void Bind_Texture(const char*);

private:
	GLuint vertex_buffer, normal_buffer, texture_buffer;
	GLuint vbo_count = 0;
};

