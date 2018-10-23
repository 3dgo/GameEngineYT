#include <GL\glew.h>
#include <iostream>
#include <fstream>
#include "MeGlWindow.h"
using namespace std;

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
		-1.0f, -1.0f, +0.5f,
		+1.0f, +0.0f, +0.0f,
		+0.0f, +1.0f, -1.0f,
		+1.0f, +0.0f, +0.0f,
		+1.0f, -1.0f, +0.5f,
		+1.0f, +0.0f, +0.0f,

		-1.0f, +1.0f, -0.5f,
		+0.0f, +0.0f, +1.0f,
		+0.0f, -1.0f, -0.5f,
		+0.0f, +0.0f, +1.0f,
		+1.0f, +1.0f, -0.5f,
		+0.0f, +0.0f, +1.0f,
	};
	GLushort indices[] = { 0, 1, 2, 3, 4, 5 };
	GLuint vertexBufferID;
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts),
				 verts, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (char*)(3 * sizeof(float)));

	GLuint indexBufferID;
	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),
				 indices, GL_STATIC_DRAW);
}

bool CheckStatus(
	GLuint objectID,
	PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
	PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
	GLenum statusType
)
{
	GLint status;
	objectPropertyGetterFunc(objectID, statusType, &status);
	if (status != GL_TRUE)
	{
		GLint infoLogLength;
		objectPropertyGetterFunc(objectID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		getInfoLogFunc(objectID, infoLogLength, &bufferSize, buffer);
		cout << buffer << endl;

		delete[] buffer;
		return false;
	}
	return true;
}

bool CheckShaderStatus(GLuint shaderID)
{
	return CheckStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}

bool CheckProgramStatus(GLuint programID)
{
	return CheckStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}

string ReadShaderCode(const char* fileName)
{
	ifstream meInput(fileName);
	if (!meInput.good())
	{
		cout << "File failed to load..." << fileName;
		exit(1);
	}
	return std::string(
		std::istreambuf_iterator<char>(meInput),
		std::istreambuf_iterator<char>());
}

void InstallShaders()
{
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const char* adapter[1];
	string temp = ReadShaderCode("VertexShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(vertexShaderID, 1, adapter, 0);
	temp = ReadShaderCode("FragmentShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(fragmentShaderID, 1, adapter, 0);

	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);

	if (!CheckShaderStatus(vertexShaderID)
		|| !CheckShaderStatus(fragmentShaderID))
	{
		return;
	}
	
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	if (!CheckProgramStatus(programID))
	{
		return;
	}

	glUseProgram(programID);
}

void MeGlWindow::initializeGL()
{
	glewInit();
	glEnable(GL_DEPTH_TEST);
	SendDataToOpenGL();
	InstallShaders();
}

void MeGlWindow::paintGL()
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, width(), height());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}

