#include "PickingShader.h"
//#include "ResourcePath.h"


PickingShader::PickingShader()
{
}


PickingShader::~PickingShader()
{
}

bool PickingShader::Init()
{
	if (!ShaderObject::Init())
	{
		return false;
	}

	if (!AddShader(GL_VERTEX_SHADER, "picking.vs.glsl"))
	{
		return false;
	}
	

	if (!AddShader(GL_FRAGMENT_SHADER, "picking.fs.glsl"))
	{
		return false;
	}

	if (!Finalize())
	{
		return false;
	}

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

	return true;
}

void PickingShader::SetMVMat(const GLfloat *value)
{
	glUniformMatrix4fv(mvLocation, 1, GL_FALSE, value);
}

void PickingShader::SetPMat(const GLfloat *value)
{
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, value);
}