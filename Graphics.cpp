#include<DSMGL\Graphics.h>
#include<DSMGL\Framework.h>
#include<DSMGL\Shader.h>

//Shader putsShader;
#define NUTS 0

Graphics::Graphics()
{
	windowWidth		= 500;
	windowHeight	= 500;
	windowTitle		= "Default";
	windowXPosition = 100;
	windowYPosition = 100;

	//putsShader.init("../../Libs/src/shader source/putsShader.vert", "../../../Libs/src/shader source/putsShader.frag");

}

Graphics::Graphics(int argc, char** argv, int windowW, int windowH, int windowPosX, int windowPosY, char* title)
{
	initEngine(argc, argv, windowWidth, windowHeight, windowPosX, windowPosY, title);

	windowWidth		= windowW;
	windowHeight	= windowH;
	windowTitle		= title;
	windowXPosition	= windowPosX;
	windowYPosition = windowPosY;

	// TODO: generalize this path

	//putsShader.init("C:\\Users\\David\\New folder\\Dropbox\\Software Projects\\Mop!\\dev\\Libs\\src\\shader source\\putsShader.vert", "C:\\Users\\David\\New folder\\Dropbox\\Software Projects\\Mop!\\dev\\Libs\\src\\shader source\\putsShader.frag");
}

Graphics::~Graphics()
{
	if (Framework::mainWindowID != 0)
		glutDestroyWindow(Framework::mainWindowID);
}
void Graphics::initEngine(int argc, char** argv, int windowW, int windowH, int windowPosX, int windowPosY, char* title)
{
	windowWidth = windowW;
	windowHeight = windowH;
	windowTitle = title;
	windowXPosition = windowPosX;
	windowYPosition = windowPosY;

	Framework::initGlutInstance(argc, argv, windowW, windowH, windowPosX, windowPosY, title);
}

void Graphics::initGlutFuncs(void(*display)(), void(*reshape)(int winWidth, int winHieght), void(*mouseButton)(int mouseButton, int state, int mouseX, int mouseY),
	void(*mouseDrag)(int mouseX, int mouseY), void(*keyboardHandler)(int key, int x, int y))
{
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseDrag);
	glutSpecialFunc(keyboardHandler);
}


void Graphics::putS(Texture image, GLPoint3D start, float rotationAngle, float scaleFactor)
{
	if (NUTS)
	{
		int textureLocation = 0;

		if (image.getTextureID() == NULL)
		{
			std::cerr << "Texture not initialized" << std::endl;
		}

	//	putsShader.bind();
		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_TEXTURE_2D);
		//textureLocation = glGetUniformLocation(putsShader.id(), "color_texture");
		glUniform1i(textureLocation, 0);
		image.bindTexture();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, windowWidth, windowHeight, 0);


		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);	glVertex3f(-1, -1, 0);
		glTexCoord2f(1, 0); glVertex3f(1, -1, 0);
		glTexCoord2f(1, 1);	glVertex3f(1, 1, 0);
		glTexCoord2f(0, 1);	glVertex3f(-1, 1, 0);
		glEnd();

		image.unbindTexture();
		//putsShader.unbind();
	}
	else
	{
		if (image.getTextureID() == NULL)
		{
			std::cerr << "Texture not initialized" << std::endl;
		}

		glEnable(GL_TEXTURE_2D);
		image.bindTexture();

		glEnable(GL_BLEND);
		image.transparentBlend();

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, windowWidth, windowHeight, 0);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(start.x, start.y, start.z);

		if (rotationAngle >= 0 && rotationAngle < 360)
			glRotatef(rotationAngle, 0, 0, 1);

		if (scaleFactor <= 1)
			glScalef(scaleFactor, scaleFactor, 0);				// TODO: check usage

		glBegin(GL_QUADS);
		glTexCoord2d(0, 1); glVertex3f(0, 0, 0);
		glTexCoord2d(0, 0);	glVertex3f(0, image.getTextureH(), 0);
		glTexCoord2d(1, 0); glVertex3f(image.getTextureW(), image.getTextureH(), 0);
		glTexCoord2d(1, 1);	glVertex3f(image.getTextureW(), 0, 0);
		glEnd();

		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();

		image.unbindTexture();
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);

		glutPostRedisplay();
	}
}

void Graphics::putRepeatBackgroundSpecial(Texture background)
{
	if (background.getTextureID() == NULL)
	{
		std::cerr << "Texture not initialized" << std::endl;
	}

	double texw, texh;
	double bgw, bgh;

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	background.bindTexture();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	bgw = background.getTextureW();
	bgh = background.getTextureH();

	texw = (floor(windowWidth / ((double)bgw)) + 1) * bgw;
	texh = (floor(windowHeight / ((double)bgh)) + 1) * bgh;

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, windowWidth, windowHeight, 0);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			glTranslatef(0, 0, -1);

			glBegin(GL_QUADS);
				glTexCoord2f(0.0, 0.0);
				glVertex2d(0.0, texh);

				glTexCoord2f(texw / 48, 0.0);
				glVertex2d(texw, texh);

				glTexCoord2f(texw / 48, texh / 48);
				glVertex2f(texw, 0.0);

				glTexCoord2f(0.0, texh / 48);
				glVertex2f(0.0, 0.0);
			glEnd();

			background.unbindTexture();
			glTranslatef(0, 0, 1);

		glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	glutPostRedisplay();
}

void Graphics::drawFlexJointSegment(Texture texture, GLPoint3D p0, GLPoint3D p1, GLPoint3D p2, GLPoint3D p3, float percentCeiling, float percentFloor)
{
	if (texture.getTextureID() == NULL)
	{
		std::cerr << "Texture not initialized" << std::endl;
	}


	glEnable(GL_TEXTURE_2D);
	texture.bindTexture();
	glEnable(GL_BLEND);
	texture.transparentBlend();

	glMatrixMode(GL_PROJECTION);
		glPushMatrix(); 
		glLoadIdentity();
		gluOrtho2D(0, windowWidth, windowHeight, 0);

		glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glBegin(GL_QUADS);
				glTexCoord2d(0, percentCeiling); glVertex2d(p0.x, p0.y);
				glTexCoord2d(0, percentFloor);	 glVertex2d(p1.x, p1.y);
				glTexCoord2d(1, percentFloor);	 glVertex2d(p2.x, p2.y);
				glTexCoord2d(1, percentCeiling); glVertex2d(p3.x, p3.y);
			glEnd();
		glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

void Graphics::drawFlexLeg(Texture texture, GLPoint3D** points)
{
	// num of rows = num of segments in the flex joint
	// point [numSegments][4] -> [p0][p1][p2][p3] - first segment
	//						  -> [p0][p1][p2][p3] - second segment
	//							   ............
	//						  -> [p0][p1][p2][p3] - numSegments'th segment

	// im working on this currently in the car and jasmine is driving and i'm fearful for my life, apologies for not figuring this out at the time.

	int   numSegments;							
	float percentStep;					
	float percent;

	numSegments = sizeof(points) / sizeof(*points);			// total mem of points / 4 points i think
	percentStep = 1.0 / numSegments;
	percent = 1;

	for (int i = 0; i < numSegments; i++)
	{
		drawFlexJointSegment(texture, points[i][0], points[i][1], points[i][2], points[i][3], percent, percent - percentStep);
		percent -= percentStep;
	}
}
void Graphics::sync()
{
	glutPostRedisplay(); 
}
void Graphics::flushAndSwapBuffers()
{
	glFlush();
	glutSwapBuffers();
}

void Graphics::startMainLoop()
{
	glutMainLoop();
}

void Graphics::setHeight(int h)
{
	windowHeight = h;
}

void Graphics::setWidth(int w)
{
	windowWidth = w;
}
void Graphics::resize(int w, int h)
{
	setWidth(w);
	setHeight(h);
	glViewport(0, 0, windowWidth, windowHeight);
}

void Graphics::clearDisplay()
{
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Graphics::toggleFullScreen()
{
	if (fullscreen)
	{
		glutReshapeWindow(windowWidth, windowWidth);
		glutPositionWindow(windowXPosition, windowYPosition);
		fullscreen = false;
	}
	else
	{
		glutFullScreen();
		fullscreen = true;
	}
	
}

int Graphics::getWindowWidth()
{
	return windowWidth;
}

int Graphics::getWindowHeight()
{
	return windowHeight;
}
