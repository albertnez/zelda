#include "cTexture.h"
#include "Globals.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

cTexture::cTexture(void)
{
}

cTexture::~cTexture(void)
{
}

bool cTexture::Load(char *filename,int type,int wraps,int wrapt,int magf,int minf,bool mipmap)
{
        int components;
        switch (type) {
                case GL_RGB: components = 3; break;
                case GL_RGBA: components = 4; break;
                default: return false;
        }

        int image_components = 0;
	unsigned char *data = stbi_load(filename, &width, &height, &image_components, components);
        if (!data) {
                std::cerr << "Error loading texture: " << stbi_failure_reason() << std::endl;
                return false;
        }

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D,id);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,wraps);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,wrapt);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,magf);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,minf);

	if(!mipmap)
	{
		glTexImage2D(GL_TEXTURE_2D,0,components,width,height,0,type,
					 GL_UNSIGNED_BYTE,data);
	}
	else
	{
		gluBuild2DMipmaps(GL_TEXTURE_2D,components,width,height,type,
						  GL_UNSIGNED_BYTE,data);
	}
	return true;
}
int cTexture::GetID()
{
	return id;
}
void cTexture::GetSize(int *w,int *h)
{
	*w = width;
	*h = height;
}
