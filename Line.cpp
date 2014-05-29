#include"DSMGL\Line.h"

Line::Line()
{

}

Line::Line(GLPoint3D s, GLPoint3D e, GLfloat t = 0, bool bSticky = false)
{
	start = s;
	end	  = e;
	thickness = t;
	sticky = bSticky;
}

void Line::drawLine(GLfloat t)
{
	glBegin(GL_LINES);
	glVertex3f(start.x, start.y, 0.0f);
	glVertex3f(end.x, end.y, 0.0f);
	glEnd();
}

void Line::drawSquare()
{
	glBegin(GL_LINES);
	glVertex3f(start.x, start.y, 0.0f);
	glVertex3f(end.x, start.y, 0.0f);

	glVertex3f(end.x, start.y, 0.0f);
	glVertex3f(end.x, end.y, 0.0f);

	glVertex3f(end.x, end.y, 0.0f);
	glVertex3f(start.x, end.y, 0.0f);
	
	glVertex3f(start.x, end.y, 0.0f);
	glVertex3f(start.x, start.y, 0.0f);
	glEnd();
}

void Line::drawSquareTex(GLuint texture, float alphaVal)
{
	glEnable(GL_TEXTURE_2D); 
	glEnable(GL_BLEND);
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // Linear Filtering
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // Linear Filtering
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);	// needed for that alpha blending
	/*glPushMatrix();
	glLoadIdentity();
	glRotatef(45, 0,0,1);*/
	glBegin(GL_QUADS);
	glColor4f(1.0f, 1.0f, 1.0f, 0.60f);

	if(start.y > end.y && start.x < end.x)							// bottom left to top right
	{
		glTexCoord2d(0,0);
		glVertex3f(start.x, start.y, 0.0f);

		glTexCoord2d(1,0);
		glVertex3f(end.x, start.y, 0.0f);

		glTexCoord2d(1,1);
		glVertex3f(end.x, end.y, 0.0f);

		glTexCoord2d(0,1);
		glVertex3f(start.x, end.y, 0.0f);
		
	} else if(start.y < end.y && start.x < end.x)					// top left to bottom right
	{
		glTexCoord2d(0,1);
		glVertex3f(start.x, start.y, 0.0f);

		
		glTexCoord2d(0,0);
		glVertex3f(start.x, end.y, 0.0f);

		
		glTexCoord2d(1,0);
		glVertex3f(end.x, end.y, 0.0f);

		glTexCoord2d(1,1);
		glVertex3f(end.x, start.y, 0.0f);
	} else if(start.y > end.y && start.x > end.x)					// bottom right to top left
	{
		glTexCoord2d(1,0);
		glVertex3f(start.x, start.y, 0.0f);

		glTexCoord2d(1,1);
		glVertex3f(start.x, end.y, 0.0f);

		glTexCoord2d(0,1);
		glVertex3f(end.x, end.y, 0.0f);

		glTexCoord2d(0,0);
		glVertex3f(end.x, start.y, 0.0f);
	}else if(start.y < end.y && start.x > end.x)					// top right to bottom left
	{
		glTexCoord2d(1,1);
		glVertex3f(start.x, start.y, 0.0f);

		
		glTexCoord2d(0,1);
		glVertex3f(end.x, start.y, 0.0f);

		
		glTexCoord2d(0,0);
		glVertex3f(end.x, end.y, 0.0f);

		glTexCoord2d(1,0);
		glVertex3f(start.x, end.y, 0.0f);
		
	}
	glEnd();
	//glPopMatrix();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

}
void Line::setSticky(bool bSticky)
{
	sticky = bSticky;
}

void Line::setStart(GLPoint3D s)
{
	start = s;
}

void Line::setEnd(GLPoint3D e)
{
	end = e;
}

GLPoint3D Line::getStart()
{
	return start;
}

GLPoint3D Line::getEnd()
{
	return end;
}
