#include "Shader.h"



Shader::Shader():ProgramID(0)
{
}


Shader::~Shader()
{
}

GLint Result = GL_FALSE;
int InfoLogLength;
GLuint ShaderID[MAX_SHADER_NUM] = { 0 };
GLuint Shader::CreateProgram_and_LinkShaders() {
	//create program
	GLuint ProgramID = glCreateProgram();

	// Link the program
	// attach
	for (int i = 0; i < MAX_SHADER_NUM; i++) {
		if (ShaderID[i] == 0) break;
		glAttachShader(ProgramID, ShaderID[i]);
	}


	glLinkProgram(ProgramID);


	//detach, delete
	for (int i = 0; i < MAX_SHADER_NUM; i++) {
		if (ShaderID[i] == 0) break;
		glDetachShader(ProgramID, ShaderID[i]);
		glDeleteShader(ShaderID[i]);
	}



	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}
	return ProgramID;
}
GLuint Shader::Load_single_shader(const char* shader_path, int mod) {
	/*single shader*/
	// Read the Vertex Shader code from the file

	GLuint single_ShaderID = glCreateShader(mod);

	std::string ShaderCode;
	std::ifstream ShaderStream(shader_path, std::ios::in);
	if (ShaderStream.is_open()) {
		std::string Line = "";
		while (getline(ShaderStream, Line))
			ShaderCode += "\n" + Line;
		ShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", shader_path);
		getchar();
		return 0;
	}

	// Compile Shader
	printf("Compiling shader : %s\n", shader_path);
	char const * ShaderSourcePointer = ShaderCode.c_str();
	glShaderSource(single_ShaderID, 1, &ShaderSourcePointer, NULL);
	glCompileShader(single_ShaderID);

	// Check Vertex Shader
	glGetShaderiv(single_ShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(single_ShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(single_ShaderID, InfoLogLength, NULL, &ShaderErrorMessage[0]);
		printf("%s\n", &ShaderErrorMessage[0]);
	}

	return single_ShaderID;
}


GLuint Shader::Load_shader(const char * vertex_file_path, const char * fragment_file_path) {

	//배열로 정리해서 shaderID를 연결. ver, tcs, tcd, geo, fs 꼴로 올 것이지. 순서는 유저가 잘 입력해주고
	//입력 갯수에 따라 shader id 다르게 받아 주는 함수 짜자.
	// Create the shaders
	ShaderID[0] = Load_single_shader(vertex_file_path, GL_VERTEX_SHADER);
	ShaderID[1] = Load_single_shader(fragment_file_path, GL_FRAGMENT_SHADER);

	ProgramID = CreateProgram_and_LinkShaders();
	return ProgramID;
}