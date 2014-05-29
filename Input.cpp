#include "DSMGL\Input.h"
#include<iostream>

std::vector<Dot> dots;
std::vector<Line> lines;
std::vector<Circle> circles;
//Circle mop;
GLPoint3D mopPos = { 0, 0, 0 };
int mouseDragCount = 0;
Line tempLine;
bool leftClickFlag = false;
int x = 0;
int y = 0;

void Input::MouseButtonClick(int button, int state, int x, int y)
{
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		
		GLPoint3D p;
		p.x = (GLfloat) x;
		p.y = (GLfloat) y;
		p.z = 0.0f;

		Dot temp(p);			
		dots.push_back(temp);	// slap the dot coords into our "dot" display container
		
	}
	
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

		GLPoint3D p;
		p.x = (GLfloat) x;
		p.y = (GLfloat) y;
		p.z = 0.0f;

		if(leftClickFlag)
		{
			GLPoint3D newPos;
			newPos.x = (GLfloat)x;
			newPos.y = (GLfloat)y;
			newPos.z = 0.0;
		
			tempLine.setEnd(newPos);
			lines.push_back(tempLine);
		}
		else
		{
			tempLine.setStart(p);
		}
		
		leftClickFlag = !leftClickFlag;

		std::cout << "Flag: " << leftClickFlag << "\nX coord: " << p.x << "\nY coord: " << p.y << std::endl;
	}
}

void Input::MouseDrag(int x, int y)
{
	GLPoint3D point;

	point.x = (GLfloat) x;
	point.y = (GLfloat) y;
	point.z = 0.0;
	
	if(mouseDragCount == 0)
	{
		tempLine.setStart(point);
		mouseDragCount++;
	}
}
void Input::moveViewPort(int key, int x, int y)
{

	switch (key)
	{
	case GLUT_KEY_UP:
		y += 10;
		break;
	case GLUT_KEY_DOWN:
		y -= 10;
		break;
	case GLUT_KEY_LEFT:
		x -= 10;
		break;
	case GLUT_KEY_RIGHT:
		x += 10;
		break;
	}

	gluLookAt(x, y, 0,
		x, y, 0,
		0, 1, 0);
	glutPostRedisplay();
}
void Input::MopControls(int key, int x, int y)
{

	switch(key)
	{
	case GLUT_KEY_UP:
		if (mopPos.y >= 0)			
			mopPos.y -= 10;
		break;
	case GLUT_KEY_DOWN:		 // gl window coords have the origin in top left corner so down = add, up = subtract y coords
		if (mopPos.y < 2556) // size of our level texture
			mopPos.y += 10;	 // adjust position by 10 pxls
		break;
	case GLUT_KEY_LEFT:
		if (mopPos.x >= 0)
			mopPos.x -= 10;
		break;
	case GLUT_KEY_RIGHT:
		if (mopPos.x < 2275)
			mopPos.x += 10;
		break;
	}
	glutPostRedisplay();
}