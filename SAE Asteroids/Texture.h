#pragma once

#include <string>
#include <GL\glew.h>

class Texture
{
public:
	Texture();
	Texture(const std::string& path, GLuint & texture);

	void Bind(unsigned int unit, GLuint texture);

	virtual ~Texture();

private:
	//Texture(const Texture& other) {}
	//void operator=(const Texture& other) {}

	GLuint m_texture;
};

