#include "Rendering/Shader/Shader.h"
#include <glad/glad.h>
#include <iostream>

static GLuint Compile(GLenum type, const char* src)
{
	GLuint s = glCreateShader(type);
	glShaderSource(s, 1, &src, nullptr);
	glCompileShader(s);

	GLint ok = 0;
	glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
	if (!ok)
	{
		char log[2048];
		glGetShaderInfoLog(s, 2048, nullptr, log);
		std::cerr << "Shader compile failed:\n" << log << "\n";
	}

	return s;
}

Shader::Shader(const char* vertexSrc, const char* fragmentSrc)
{
	GLuint vs = Compile(GL_VERTEX_SHADER, vertexSrc);
	GLuint fs = Compile(GL_FRAGMENT_SHADER, fragmentSrc);

	m_program = glCreateProgram();
	glAttachShader(m_program, vs);
	glAttachShader(m_program, fs);
	glLinkProgram(m_program);

	GLint ok = 0;
	glGetProgramiv(m_program, GL_LINK_STATUS, &ok);
	if (!ok)
	{
		char log[2048];
		glGetShaderInfoLog(m_program, 2048, nullptr, log);
		std::cerr << "Program link failed:\n" << log << "\n";
	}

	// No longer need after linking
	glDeleteShader(vs);
	glDeleteShader(fs);
}

Shader::~Shader()
{
	// Guard for OpenGL
	if(m_program != 0)
		glDeleteProgram(m_program);
}

void Shader::Bind() const
{
	glUseProgram(m_program);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetMat4(const char* name, const float* value16) const
{
	GLint loc = glGetUniformLocation(m_program, name);
	glUniformMatrix4fv(loc, 1, GL_FALSE, value16);
}
