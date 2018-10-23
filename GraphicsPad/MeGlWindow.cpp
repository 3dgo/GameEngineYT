#include <GL\glew.h>
#include "MeGlWindow.h"

extern const char* vertexShaderCode;
extern const char* fragmentShaderCode;

MeGlWindow::MeGlWindow()
{
}


MeGlWindow::~MeGlWindow()
{
}

void SendDataToOpenGL()
{
	GLfloat verts[] =
	{
		-1.0f, +1.0f,
		+1.0f, +0.0f, +0.0f,

		+1.0f, +1.0f,
		+1.0f, +0.0f, +0.0f,

		+0.0f, -0.0f,
		+1.0f, +0.0f, +0.0f,

		+1.0f, -1.0f,
		+1.0f, +0.0f, +0.0f,

		-1.0f, -1.0f,
		+1.0f, +0.0f, +0.0f,
	};
	GLushort indices[] = { 0, 1, 2, 2, 3, 4 };
	GLuint vertexBufferID;
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts),
				 verts, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (char*)(2 * sizeof(float)));

	GLuint indexBufferID;
	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),
				 indices, GL_STATIC_DRAW);
}

void InstallShaders()
{
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const char* adapter[1];
	adapter[0] = vertexShaderCode;
	glShaderSource(vertexShaderID, 1, adapter, 0);
	adapter[0] = fragmentShaderCode;
	glShaderSource(fragmentShaderID, 1, adapter, 0);

	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);

	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	glUseProgram(programID);
}

void MeGlWindow::initializeGL()
{
	glewInit();
	SendDataToOpenGL();
	InstallShaders();

}

void MeGlWindow::paintGL()
{
	glViewport(0, 0, width(), height());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}

