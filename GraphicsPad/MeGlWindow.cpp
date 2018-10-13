#include <GL\glew.h>
#include "MeGlWindow.h"


MeGlWindow::MeGlWindow()
{
}


MeGlWindow::~MeGlWindow()
{
}

void MeGlWindow::initializeGL()
{
	glewInit();

	GLfloat verts[] =
	{
		-1.0f, +1.0f,
		+1.0f, +1.0f,
		+0.0f, -0.0f,
		+1.0f, -1.0f,
		-1.0f, -1.0f,
	};
	GLushort indices[] = { 0, 1, 2, 2, 3, 4 };
	GLuint vertexBufferID;
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts),
				 verts, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	GLuint indexBufferID;
	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void MeGlWindow::paintGL()
{
	glViewport(0, 0, width(), height());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}

