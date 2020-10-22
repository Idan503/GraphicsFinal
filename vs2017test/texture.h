#pragma once
using namespace std;
#include<vector>
#include "glut.h"

class Texture
{
private:
	vector<vector<vector<unsigned char>>> data; // [width][height][3=rgb/4=rgba]
	int tid; // texture id

public:
	Texture(int tid, int w, int h, bool alpha);
	void Bind();
	int GetTid();
	vector<vector<vector<unsigned char>>> GetData();
	void SetData(vector<vector<vector<unsigned char>>> data);


};

