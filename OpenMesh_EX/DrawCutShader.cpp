#include "DrawCutShader.h"
//#include "ResourcePath.h"


DrawCutShader::DrawCutShader()
{
}


DrawCutShader::~DrawCutShader()
{
}

bool DrawCutShader::Init()
{
	if (!ShaderObject::Init())
	{
		return false;
	}

	if (!AddShader(GL_VERTEX_SHADER, "cut.vs.glsl"))
	{
		return false;
	}
	else


		/*if (!AddShader(GL_GEOMETRY_SHADER, "drawModel.gs.glsl"))
		{
			return false;
		}*/

		if (!AddShader(GL_FRAGMENT_SHADER, "cut.fs.glsl"))
		{
			return false;
		}

	if (!Finalize())
	{
		return false;
	}

	um4mvLocation = GetUniformLocation("um4mv");
	if (um4mvLocation == -1)
	{
		puts("Get uniform loaction error: um4mv");
		return false;
	}

	um4pLocation = GetUniformLocation("um4p");
	if (um4pLocation == -1)
	{
		puts("Get uniform loaction error: um4p");
		return false;
	}

	um3nLocation = GetUniformLocation("um3n");
	if (um3nLocation == -1)
	{
		puts("Get uniform loaction error: um3n");
		return false;
	}

	um4uLocatoin = GetUniformLocation("um4u");
	if (um4uLocatoin == -1)
	{
		puts("Get uniform loaction error: um4u");
		return false;
	}

	drawTexCoordLocation = GetUniformLocation("drawTexCoord");
	if (drawTexCoordLocation == -1)
	{
		puts("Get uniform loaction error: drawTexCoord");
		return false;
	}

	drawTextureLocation = GetUniformLocation("drawTexture");
	if (drawTextureLocation == -1)
	{
		puts("Get uniform loaction error: drawTexture");
		return false;
	}

	useLightingLocation = GetUniformLocation("useLighting");
	if (useLightingLocation == -1)
	{
		puts("Get uniform loaction error: useLighting");
		return false;
	}


	/*drawWireframeLocation = GetUniformLocation("drawWireframe");
	if (drawWireframeLocation == -1)
	{
		puts("Get uniform loaction error: drawWireframe");
		return false;
	}*/

	faceColorLocation = GetUniformLocation("faceColor");
	if (faceColorLocation == -1)
	{
		puts("Get uniform loaction error: faceColor");
		return false;
	}

	/*wireColorLocation = GetUniformLocation("wireColor");
	if (wireColorLocation == -1)
	{
		puts("Get uniform loaction error: wireColor");
		return false;
	}
*/

	return true;
}

void DrawCutShader::SetMVMat(const glm::mat4& mat)
{
	glUniformMatrix4fv(um4mvLocation, 1, GL_FALSE, glm::value_ptr(mat));
}

void DrawCutShader::SetPMat(const glm::mat4& mat)
{
	glUniformMatrix4fv(um4pLocation, 1, GL_FALSE, glm::value_ptr(mat));
}

void DrawCutShader::SetNormalMat(const glm::mat3& mat)
{
	glUniformMatrix3fv(um3nLocation, 1, GL_FALSE, glm::value_ptr(mat));
}

void DrawCutShader::SetUVRotMat(const glm::mat4& mat)
{
	glUniformMatrix4fv(um4uLocatoin, 1, GL_FALSE, glm::value_ptr(mat));
}

void DrawCutShader::SetFaceColor(const glm::vec4& faceColor)
{
	glUniform4fv(faceColorLocation, 1, glm::value_ptr(faceColor));
}

void DrawCutShader::SetWireColor(const glm::vec4& wireColor)
{
	glUniform4fv(wireColorLocation, 1, glm::value_ptr(wireColor));
}

void DrawCutShader::UseLighting(bool use)
{
	glUniform1i(useLightingLocation, use);
}

void DrawCutShader::DrawWireframe(bool draw)
{
	glUniform1i(drawWireframeLocation, draw);
}

void DrawCutShader::DrawTexCoord(bool draw)
{
	glUniform1i(drawTexCoordLocation, draw);
}

void DrawCutShader::DrawTexture(bool draw)
{
	glUniform1i(drawTextureLocation, draw);
}