#pragma once
#include <QtWidgets/qopenglwidget.h>

class MeGlWindow : public QOpenGLWidget
{
public:
	MeGlWindow();
	~MeGlWindow();

protected:
	void initializeGL() override;
	void paintGL() override;
};

