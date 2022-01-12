#pragma once
#include "Common.h"
#include"stb_image.h"
class PickingTexture
{
public:
	PickingTexture();
	~PickingTexture();

	bool Init(int width, int height);
	void Enable();
	void Disable();
	GLuint ReadTexture(unsigned int x, unsigned int y);

	GLuint GetColorTex() { return fboColor; }
	GLuint PickingTexture::MY_TEX(int width, int height);
private:
	GLuint fbo;
	GLuint fboColor;
	GLuint fboDepth;

	void Clear();

};