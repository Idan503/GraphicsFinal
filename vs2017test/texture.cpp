#include "Texture.h"


Texture::Texture(int tid, int w, int h, bool alpha)
{
	this->tid = tid;
	if (alpha)
	{
		data.resize(w, vector<vector<unsigned char>>(h, vector<unsigned char>(4)));
	}
	else
	{
		data.resize(w, vector<vector<unsigned char>>(h, vector<unsigned char>(3))); 
	}
}

int Texture::GetTid()
{
	return this->tid;
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, tid);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	if (data[0][0].size() == 3) // rgb
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, data.size(), data[0].size(), 0, GL_RGB, GL_UNSIGNED_BYTE, data.data());
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data.size(), data[0].size(), 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
}

vector<vector<vector<unsigned char>>> Texture::GetData()
{
	return this->data;
}

void Texture::SetData(vector<vector<vector<unsigned char>>> data)
{
	this->data = data;
}