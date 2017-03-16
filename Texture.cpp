#include "Texture.h"
Texture::Texture()
{
}


Texture::~Texture()
{
}


GLuint Texture::myLoadBMP24(const char* textpath) {
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int width, height, imageSize;
	unsigned char* data; //실제 rgb data

	FILE* file = fopen(textpath, "rb");
	if (!file) { printf("Image can't be opened\n"); return 0;}

	//BMP첫 54bit는 header. 이 문서가 bmp인지, 가로세로는 어떤지 담김
	if (fread(header, 1, 54, file) != 54) {
		printf("incorrect BMP file\n"); return 0;
	}

	//진짜 BMP파일인가
	if (header[0] != 'B' || header[1] != 'M') {
		printf("incorrect BMP file\n"); return 0;
	}

	//나머지 정보 읽어오기
	dataPos = *(int*)&(header[0x0A]); //이게 뭘까???
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	//정보가 불완전한 경우
	if (imageSize == 0) imageSize = width*height * 3;
	if (dataPos == 0) dataPos = 54;

	data = new unsigned char [imageSize];//이건 뭐람!
	fread(data, 1, imageSize, file);
	fclose(file);

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	//target, level, 저장할형식, wid, height, 0, 읽어올형식, type, data)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	TextureID = textureID;
	return textureID;
}