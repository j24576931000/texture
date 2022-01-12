#include "DrawPickingFaceShader.h"
//#include "ResourcePath.h"
#include<stb_image.h>


DrawPickingFaceShader::DrawPickingFaceShader()
{
}


DrawPickingFaceShader::~DrawPickingFaceShader()
{
}

bool DrawPickingFaceShader::Init()
{
	if (!ShaderObject::Init())
	{
		return false;
	}

	if (!AddShader(GL_VERTEX_SHADER,"drawPickingFace.vs.glsl"))
	{
		return false;
	}

	if (!AddShader(GL_GEOMETRY_SHADER, "drawPickingFace.gs.glsl"))
	{
		return false;
	}

	if (!AddShader(GL_FRAGMENT_SHADER, "drawPickingFace.fs.glsl"))
	{
		return false;
	}


	if (!Finalize())
	{
		printf("Error %s\n", glewGetErrorString(glGetError()));
		puts("DrawPickingFaceShader error");
		return false;
	}
	GLuint texture;
	int image_width;
	int image_height;
	int imgcor;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load("111.jpg", &image_width, &image_height, &imgcor, 0);
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	//glGenTextures(1, &textureid);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glGenerateMipmap(GL_TEXTURE_2D);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);

	mvLocation = GetUniformLocation("um4mv");
	if (mvLocation == -1)
	{
		puts("Get uniform loaction error: um4mv");
		return false;
	}

	pLocation = GetUniformLocation("um4p");
	if (pLocation == -1)
	{
		puts("Get uniform loaction error: um4p");
		return false;
	}
	TexLocation = GetUniformLocation("tex0");
	if (pLocation == -1)
	{
		puts("Get uniform loaction error: tex0");
		return false;
	}
	//uLocation = GetUniformLocation("um4u");
	if (uLocation == -1)
	{
		puts("Get uniform loaction error: um4u");
		return false;
	}

	return true;
}

void DrawPickingFaceShader::SetMVMat(const GLfloat *value)
{
	glUniformMatrix4fv(mvLocation, 1, GL_FALSE, value);
}

void DrawPickingFaceShader::SetPMat(const GLfloat *value)
{
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, value);
}
void DrawPickingFaceShader::SetTex()
{
	glUniform1i(TexLocation, 0);
}
void DrawPickingFaceShader::SetUMat(const GLfloat *value)
{
	glUniformMatrix4fv(uLocation, 1, GL_FALSE, value);
}
