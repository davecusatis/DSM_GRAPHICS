#include<DSMGL\Circle.h>
#define num_segments 100.0f

Circle mop;

Circle::Circle()
{
	
}

Circle::Circle(GLPoint3D c, float r)
{
	GLColorRGBA wht = {255.0f, 255.0f, 255.0f, 1.0f} ;
	setCircleValues(c, r, wht );
}


void Circle::setCircleValues(GLPoint3D c, float r, GLColorRGBA color)
{
	setCenter(c);
	setRadius(r);
	setColor(color.r, color.g, color.b, color.a);
}

void Circle::setCenter(GLPoint3D c)
{
	center = c;
}

void Circle::setCenter(float x, float y, float z)
{
	center.x = x;
	center.y = y;
	center.z = z;
}
void Circle::setRadius(float r)
{
	radius = r;
}

void Circle::setColor(float r, float g, float b, float a)
{
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
}

GLPoint3D Circle::getCenter() const
{
	return center;
}

GLColorRGBA Circle::getColor() const
{
	return color;
}

float Circle::getRadius() const
{
	return radius;
}

void Circle::drawCircle()
{
	float theta = 2 * 3.1415926 / num_segments;

	float c = cosf(theta); //precalculate the sine and cosine
	float s = sinf(theta);
	float t;

	float x = this->getRadius(); //we start at angle = 0 
	float y = 0; 
   
	float filledRadius = this->getRadius();

	glColor4f(this->getColor().r, this->getColor().g, this->getColor().b, this->getColor().a);

	glBegin(GL_LINE_LOOP); 
	for(int ii = 0; ii < num_segments; ii++) 
	{ 
		glVertex2f(x + this->getCenter().x, y + this->getCenter().y);//output vertex 
        
		//apply the rotation matrix
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	} 
	glEnd(); 
}

void Circle::drawFilledCircle()
{
	// data dictionary son
	float radius = this->getRadius();
	float x		 = this->getCenter().x - radius/2;  // a bit handwavey here...
	float y		 = this->getCenter().y - radius/2;
	float twoPI	 = 2.0f * 3.1415926;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for(int i = 0; i < 360; i++)
	{
		glVertex2f(x + radius * sin(i), y + radius * cos(i));
	}
	glEnd();
}

