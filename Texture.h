#pragma once
#include <GL/glew.h>
#include <fstream>
#pragma warning(disable:4996)
class Texture
{
public:
	Texture();
	~Texture(); 
	GLuint TextureID;
	GLuint myLoadBMP24(const char* textpath);
};

