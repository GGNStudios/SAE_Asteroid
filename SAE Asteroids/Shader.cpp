#include "Shader.h"
#include <fstream>
#include <gtc\type_ptr.hpp>

static std::string LoadShader(const std::string& fileName);
static void CheckShaderErrors(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static GLuint CreateShader(const std::string& text, GLenum shaderType);

Shader::Shader()
{

}

Shader::Shader(const std::string & filename, GLuint & program)
{
	m_program = glCreateProgram();
	m_shaders[0] = CreateShader(LoadShader(filename + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(filename + ".frag"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(m_program,m_shaders[i]);
	}

	glBindAttribLocation(m_program, 0, "coord2d");
	glBindAttribLocation(m_program, 1, "TexCoord");

	glLinkProgram(m_program);
	CheckShaderErrors(m_program, GL_LINK_STATUS, true, "Error: Program Failed to link: ");

	glValidateProgram(m_program);
	CheckShaderErrors(m_program, GL_VALIDATE_STATUS, true, "Error: Program Failed to Validate: ");

	m_uniforms[MVP_U] = glGetUniformLocation(m_program, "MVP");
	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
	m_uniforms[POSITION_U] = glGetUniformLocation(m_program, "position");

	program = m_program;
}

void Shader::Bind(GLuint program)
{
	glUseProgram(program);
}

void Shader::Update(const Transform& transform, Camera cam)
{
	glm::vec3 position = transform.GetPosition();
	glUniformMatrix4fv(m_uniforms[MVP_U], 1, GL_FALSE, glm::value_ptr(cam.GetMVP()));
	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, glm::value_ptr(transform.GetModel()));
	glUniform3f(m_uniforms[POSITION_U], position.x,position.y,position.z);
}

Shader::~Shader()
{
	/*for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program,m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}

	glDeleteProgram(m_program);*/
}

static GLuint CreateShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
		std::cerr << "Error: Shader Creation failed!" << std::endl;

	const GLchar* shaderSource[1];
	GLint shaderSourceStringLengths[1];

	shaderSource[0] = text.c_str();
	shaderSourceStringLengths[0] = text.length();

	glShaderSource(shader, 1, shaderSource, shaderSourceStringLengths);
	glCompileShader(shader);

	CheckShaderErrors(shader, GL_COMPILE_STATUS, false, "Error: Shader failed to Compile: ");

	return shader;
}

static std::string LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;

}

static void CheckShaderErrors(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}