#include "Texture.h"




Texture::Texture(int tid, int w, int h, bool alpha)
{
	this->width = w;
	this->height = h;
	this->alpha = alpha;
	this->tid = tid;
	this->colorbytes = (alpha) ? 4 : 3; //3 for rgb, 4 for rgba


}

int Texture::GetTid()
{
	return this->tid;
}


int Texture::GetWidth()
{
	return this->width;
}

int Texture::GetHeight()
{
	return this->height;
}

bool Texture::IsAlpha()
{
	return this->alpha;
}

int Texture::GetColorbytes()
{
	return this->colorbytes;
}