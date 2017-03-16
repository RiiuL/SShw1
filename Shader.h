#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <GL/glew.h>

#define MAX_SHADER_NUM 5
class Shader
{
public:
	GLuint ProgramID;
	GLuint vao;

public:
	Shader(); ~Shader();
	GLuint Load_shader(const char *, const char *);

private:
	GLuint Load_single_shader(const char* shader_path, int mod);
	GLuint CreateProgram_and_LinkShaders();
};

