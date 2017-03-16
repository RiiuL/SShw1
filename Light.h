#pragma once
class Light
{
public:
	float pos[4] = { 100.0f, 0.0f, 0.0f, 0.0f };
	float ambient[4] = { 0.0f, 0.0f, 0.0f ,0.0f };
	float diffuse[4] = { 0.8f, 0.0f, 0.0f ,0.0f };
	float specular[4] = { 1.0f, 1.0f, 1.0f ,0.0f };
public:
	Light();
	~Light();

};

