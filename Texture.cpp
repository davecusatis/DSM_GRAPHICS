#include<DSMGL\Texture.h>
#include<DSMGL\Framework.h>

Texture::Texture()
{
	textureID = 0;
	setTextureW(0);
	setTextureH(0);
}

Texture::~Texture()
{
	//deleteTexture();
}

void Texture::loadTexture(char* filename, float width, float height)
{
	textureID = SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	
	bindTexture();															// bind the texture to the GL instance 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Filtering
	unbindTexture();														// unbind 

	setTextureW(width);
	setTextureH(height);

	Framework::glErrorCheck();
}

void Texture::loadNormalMap(char* filename, float width, float height)
{
	textureID = SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	bindTexture();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	unbindTexture();

	setTextureW(width);
	setTextureH(height);

	Framework::glErrorCheck();
}
void Texture::deleteTexture()
{
	if (textureID != 0)
	{
		glDeleteTextures(1, &textureID);
		textureID = 0;
	}

	setTextureH(0);
	setTextureW(0);
}
void Texture::transparentBlend()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);	// needed for that alpha blending

}
void Texture::bindTexture()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::unbindTexture()
{
	glBindTexture(GL_TEXTURE_2D, NULL);
}
void Texture::setID(GLuint id)
{
	textureID = id;
}
void Texture::setTextureW(GLfloat w)
{
	textureW = w;
}

void Texture::setTextureH(GLfloat h)
{
	textureH = h;
}

float Texture::getTextureH() const
{
	return textureH;
}

float Texture::getTextureW() const
{
	return textureW;
}

unsigned int Texture::getTextureID() const
{
	return textureID;
}