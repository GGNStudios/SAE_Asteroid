#pragma once

#include <iostream>
#include <string>
#include <GL\glew.h>
#include <glm.hpp>

#include "Camera.h"
#include "Transform.h"

class Shader
{
public:
	Shader();
	Shader(const std::string & filename, GLuint & program);

	void Bind(GLuint program);
	void Update(const Transform& transform, Camera cam);

	GLuint GetProgram() { return m_program; }

	virtual ~Shader();

private:
	static const unsigned int NUM_SHADERS = 2;

	enum
	{
		MVP_U,
		TRANSFORM_U,
		POSITION_U,
		NUM_UNIFORMS
	};

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
};

