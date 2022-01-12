#include "PickingTexture.h"

//#include"stb_image.h"
PickingTexture::PickingTexture()
{
}


PickingTexture::~PickingTexture()
{
	Clear();
}

bool PickingTexture::Init(int width, int height)
{
	Clear();
	//int image_width;
	//int image_height;
	//int imgcor;
	//stbi_set_flip_vertically_on_load(true);
	//unsigned char* bytes = stbi_load("111.png", &width, &height, &imgcor, 0);
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glGenTextures(1, &fboColor);
	glBindTexture(GL_TEXTURE_2D, fboColor);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32UI, width, height, 0, GL_RED_INTEGER, GL_UNSIGNED_INT, NULL);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32UI, width, height, 0, GL_RED_INTEGER, GL_UNSIGNED_INT, bytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glGenRenderbuffers(1, &fboDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, fboDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, fboDepth);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, fboColor, 0);

	GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawBuffers);

	if (!Common::CheckFrameBufferStatus())
	{
		return false;
	}
	//stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return Common::CheckGLError();
}

GLuint PickingTexture::MY_TEX(int width, int height)
{
	GLuint textureId = 0;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_LINEAR); // 为MipMap设定filter方法
	// Step4 加载纹理
	GLubyte *imageData = NULL;
	int channels = 0;

	stbi_set_flip_vertically_on_load(true);
	imageData = stbi_load("111.png", &width, &height, &channels, 3);
	//imageData = SOIL_load_image(filename, &picWidth, &picHeight, &channels, loadChannels);
	if (imageData == NULL)
	{
		std::cerr << "Error::Texture could not load texture file:" <<"111.png" << std::endl;
		return 0;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
		0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(GL_TEXTURE_2D);
	// Step5 释放纹理图片资源
	stbi_image_free(imageData);
	//SOIL_free_image_data(imageData);
	glBindTexture(GL_TEXTURE_2D, 0);

	return textureId;
}





void PickingTexture::Clear()
{
	//std::cout << fboColor << std::endl;
	if (fboColor != 0)
	{
		glDeleteTextures(1, &fboColor);
	}
	//std::cout << fboDepth << std::endl;
	if (fboDepth != 0)
	{
		glDeleteRenderbuffers(1, &fboDepth);
	}
	//std::cout << fbo << std::endl;
	if (fbo != 0)
	{
		glDeleteFramebuffers(1, &fbo);
	}
}

void PickingTexture::Enable()
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	//std::cout << fbo << std::endl;
}

void PickingTexture::Disable()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint PickingTexture::ReadTexture(unsigned int x, unsigned int y)
{
	//std::cout << "x=" << x << "  y=" << y << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glReadBuffer(GL_COLOR_ATTACHMENT0);

	GLuint data;
	glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_UNSIGNED_INT, &data);
	//std::cout << "data=" << data << std::endl;
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//std::cout << "ReadTexture" << std::endl;
	return data;
}
