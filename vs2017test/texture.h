#pragma once
using namespace std;
#include<vector>
#include "glut.h"


class Texture
{
private:
	int width;
	int height;
	int tid; // texture id
	int colorbytes; //3 for rgb, 4 for rgba
	bool alpha; // true for grba

public:
	Texture(int tid, int w, int h, bool alpha);
	int GetTid();
	int GetWidth();
	int GetHeight();
	bool IsAlpha();
	int GetColorbytes();
	


};

