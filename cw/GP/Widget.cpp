#include "Widget.h"

void Widget::Update(Vector3 position)
{
	position_ = position;

}

void Widget::Render()
{
	scale_ = Vector3(1, 1, 1);
	BeginObjectDrawing();

	glLineWidth(2.5);
	//x dir
	
	glColor4f(1.0, 0.0, 0.0,1);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(1, 0, 0);
	glEnd();


	//y dir
	
	
	glColor4f(1.0, 1.0, 0.0,1);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0, 1, 0);
	glEnd();
	

	//z dir

	glLineWidth(2.5);
	glColor4f(0.0, 0.0, 1.0,1);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0, 0, 1);
	glEnd();


	EndObjectDrawing();

}