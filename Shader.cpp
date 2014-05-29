#define FREEGLUT_STATIC
#define GLEW_STATIC
#define _CRT_SECURE_NO_WARNINGS

#include<stdlib.h>
#include<iostream>
#include<glew.h>
#include<glut.h>
#include<string>
#include<DSMGL\Shader.h>

static void validateShader(GLuint shader, const char* file = 0)
{
	// TODO: variable length shaders/program with glGetShaderiv/glGetProgramiv
	const unsigned int BUFFER_SIZE = 512;
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);
	GLsizei length = 0;
    
	glGetShaderInfoLog(shader, BUFFER_SIZE, &length, buffer);
	if (length > 0) {
		std::cout << "Shader " << shader << " (" << (file?file:"") << ") compile error: " << buffer << std::endl;
	}
}

static void validateProgram(GLuint program)
{
	const unsigned int BUFFER_SIZE = 512;
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);
	GLsizei length = 0;
    
	memset(buffer, 0, BUFFER_SIZE);
	glGetProgramInfoLog(program, BUFFER_SIZE, &length, buffer);
	if (length > 0)
		std::cout << "Program " << program << " link error: " << buffer << std::endl;
    
	glValidateProgram(program);
	GLint status;
	glGetProgramiv(program, GL_VALIDATE_STATUS, &status);
	if (status == GL_FALSE)
		std::cout << "Error validating shader " << program << std::endl;
}

static const char* textFileRead(const char* fileName)
{
	int count;
	char* text = "";
	FILE* file;

    if (fileName != NULL) 
	{
        FILE* file = fopen(fileName, "rt");

        if (file != NULL) 
		{
            fseek(file, 0, SEEK_END);
            count = ftell(file);										// gets filesize
            rewind(file);
            
            if (count > 0) 
			{
				text = (char*)malloc(sizeof(char)* (count + 1));			
                count = fread(text, sizeof(char), count, file);				// reads from file the # of characters as the filesize
                text[count] = '\0';
            }
            fclose(file);
        }
    }
    return text;
}

Shader::Shader()
{
	shader_id = 0;
	shader_fp = 0;
	shader_vp = 0;
}

Shader::~Shader()
{
	glDetachShader(shader_id, shader_fp);
	glDetachShader(shader_id, shader_vp);

	glDeleteShader(shader_fp);
	glDeleteShader(shader_vp);
	glDeleteProgram(shader_id);
}

Shader::Shader(const char* vsFile, const char* fsFile)
{
	init(vsFile, fsFile);
}

void Shader::init(const char* vsFile, const char* fsFile)
{
	shader_vp = glCreateShader(GL_VERTEX_SHADER);
	shader_fp = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vsText = textFileRead(vsFile);
	const char* fsText = textFileRead(fsFile);
	 
	if (vsText == NULL || fsText == NULL) 
	{
        std::cerr << "Either vertex shader or fragment shader file not found." << std::endl;
        return;
    }

	glShaderSource(shader_vp, 1, &vsText, 0);					// we assign the shader to the shader_** object whatever
	glShaderSource(shader_fp, 1, &fsText, 0);					

	glCompileShader(shader_vp);
	validateShader(shader_vp, vsFile);
	glCompileShader(shader_fp);
	validateShader(shader_fp, fsFile);

	shader_id = glCreateProgram();
}
void Shader::link()
{
	glAttachShader(shader_id, shader_fp);
	glAttachShader(shader_id, shader_vp);
	glLinkProgram(shader_id);
	validateProgram(shader_id);
}
unsigned int Shader::id()
{
	return shader_id;
}

void Shader::bind()
{
	glUseProgram(shader_id);
}

void Shader::unbind()
{
	glUseProgram(NULL);
}