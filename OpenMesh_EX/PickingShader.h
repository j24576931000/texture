#pragma once
#include "ShaderObject.h"
#include "Common.h"
class PickingShader : public ShaderObject
{
public:
	PickingShader();
	~PickingShader();

	bool Init();
	void SetMVMat(const GLfloat *value);
	void SetPMat(const GLfloat *value);

private:
	GLuint mvLocation;
	GLuint pLocation;
};

