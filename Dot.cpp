#include<DSMGL\Dot.h>

Dot::Dot()
{

}

Dot::Dot(GLPoint3D p)
{
	setPos(p);
}

void Dot::drawDot()
{
	glPointSize(10);
	glBegin(GL_POINTS);
	glVertex3f(pos.x, pos.y, 0.0f);
	glEnd();

}

void Dot::setPos(GLPoint3D p)
{
	pos = p;
}

void Dot::setPos(float x, float y, float z)
{
	GLPoint3D p;
	p.x = x;
	p.y = y;
	p.z = z;

	setPos(p);
}
GLPoint3D Dot::getPos() const
{
	return pos;
}