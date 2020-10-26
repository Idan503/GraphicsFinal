#define _CRT_SECURE_NO_WARNINGS
#include "texture_manager.h"
#include "glut.h"
#include "globals.h"
#include "Texture.h"
#include <math.h>
#include <stdio.h>

//Texture Declaration

//Terrain 0-9
Texture* terrain_tex = new Texture(0, 256, 256);
unsigned char terrain_data[256][256][3]; // 3 stands for rgb

//Rail 10-19
Texture* rail_tex = new Texture(10, 256, 256, true);
unsigned char rail_data[256][256][4]; // 4 stands for rgba

//Bridge 20-29
Texture* bridge_road_tex = new Texture(20, 1024, 512);
unsigned char bridge_road_data[1024][512][3];

//Train 30-49
Texture* train_tube_tex = new Texture(30, 1024, 512);
unsigned char train_tube_data[1024][512][3];

Texture* train_tube_lines_tex = new Texture(31, 128, 512);
unsigned char train_tube_lines_data[128][512][3];

Texture* train_nose_tex = new Texture(32, 256, 256);
unsigned char train_nose_data[256][256][3];

Texture* metal_accent_tex= new Texture(33, 512, 256);
unsigned char metal_accent_data[512][256][3];

Texture* metal_bright_tex = new Texture(34, 512, 512);
unsigned char metal_bright_data[512][512][3];

//Tree 50-59
Texture* tree_log_tex = new Texture(50, 512, 512);
unsigned char tree_log_data[512][512][3];

Texture* tree_leaves_tex = new Texture(51, 512, 512,true);
unsigned char tree_leaves_data[512][512][4];


unsigned char* bmp;

void InitAllTextures()
{
	InitRailTexture();
	InitTerrainTexture();
	InitBridgeRoadTexture();
	InitTrainTubeTexture();
	InitTrainTubeLinesTexture();
	InitTrainNoseTexture();
	InitMetalAccentTexture();
	InitMetalBrightTexture();
	InitTreeLeavesTexture();
	InitTreeLogTexture();

	//Texture properties
}

// support rgb bitmaps only 
void ReadBitmap(const char* fname, bool alpha)
{
	FILE* fp;
	fp = fopen(fname,"rb");
	// bitmap file start bf
	BITMAPFILEHEADER bf;
	// after that: bi
	BITMAPINFOHEADER bi;
	// after that: bgr,bgr,bgr

	fread(&bf, sizeof(BITMAPFILEHEADER), 1, fp);
	fread(&bi, sizeof(BITMAPINFOHEADER), 1, fp);

	int size;
		if(alpha)
			size = bi.biHeight * bi.biWidth * 4; //rgba
		else
			size = bi.biHeight * bi.biWidth * 3; //rgb

	bmp = (unsigned char*)malloc(size);
	fread(bmp, 1, size, fp);
	
	fclose(fp);
}

void InitRailTexture()
{
	int i, j, noise, side_noise; // noise change color a bit to make it more realistic

	const int width = rail_tex->GetWidth();
	const int height = rail_tex->GetHeight();
	const int colorbytes = rail_tex->GetColorbytes();

	for (j = 0; j < width; j++){
		side_noise = 5 - rand() % 10;
		for (i = 0; i < height; i++) {
			noise = 10 - rand() % 20;
			if ((j > width * 0.75 && j < width * 0.85) ||
				(j < width * 0.25 && j >width * 0.15))
			{
				// Continues lines on sides
				rail_data[i][j][0] = 50 + side_noise + (noise * 0.5);
				rail_data[i][j][1] = 45 + side_noise + (noise * 0.5);
				rail_data[i][j][2] = 46 + side_noise + (noise * 0.5);
				rail_data[i][j][3] = 255;
			}
			else if (i % (width / 4) > 10 && i % (width / 4) < 42) {
				// Striped  lines of rails
				rail_data[i][j][0] = 38 + noise;
				rail_data[i][j][1] = 38 + noise;
				rail_data[i][j][2] = 39 + noise;
				rail_data[i][j][3] = 255;
			}
			else {
				rail_data[i][j][0] = 255;
				rail_data[i][j][1] = 255;
				rail_data[i][j][2] = 255;
				rail_data[i][j][3] = 0;
			}
		}
	}
	
	BindTexture(rail_tex, rail_data);
	
}


void InitTerrainTexture() {
	int i, j, noise;

	const int width = terrain_tex->GetWidth();
	const int height = terrain_tex->GetHeight();
	const int colorbytes = terrain_tex->GetColorbytes();

	for (i = 0; i < width; i++)
		for (j = 0; j < height; j++)
		{
			noise = 5 - rand() % 10;
			terrain_data[i][j][0] = 15 + noise;
			terrain_data[i][j][1] = 65 + noise;
			terrain_data[i][j][2] = 25 + noise;
			if (rand() % 4 == 0)
				terrain_data[i][j][1] -= 10;
			if ((i + j) % (256 / 4) > 10 && (i + j) % (256 / 4) < 35)
			{
				terrain_data[i][j][0] = 30;
				terrain_data[i][j][1] = 70;
				terrain_data[i][j][2] = 20;
			}
		}

	BindTexture(terrain_tex, terrain_data);
}

void InitBridgeRoadTexture()
{
	ReadBitmap("bridge_road.bmp");

	int width = bridge_road_tex->GetWidth();
	int height = bridge_road_tex->GetHeight();

	int i, j, k;
	for(i=0,k=0;i< width;i++)
		for (j = 0; j < height; j++, k+=3)
		{
			bridge_road_data[i][j][0] = bmp[k + 2];
			bridge_road_data[i][j][1] = bmp[k + 1];
			bridge_road_data[i][j][2] = bmp[k]; //in the file(bmp): bgrbgrbgr...
		}

	BindTexture(bridge_road_tex, bridge_road_data);
	
	free(bmp);
	
}

void InitTrainTubeTexture()
{
	ReadBitmap("train_tube.bmp");

	int i, j, k;
	for (i = 0, k = 0; i < train_tube_tex->GetWidth(); i++)
		for (j = 0; j < train_tube_tex->GetHeight(); j++, k += 3)
		{
			train_tube_data[i][j][0] = bmp[k + 2];
			train_tube_data[i][j][1] = bmp[k + 1];
			train_tube_data[i][j][2] = bmp[k]; //in the file(bmp): bgrbgrbgr...
		}

	BindTexture(train_tube_tex, train_tube_data);

	free(bmp);
}


void InitTrainTubeLinesTexture()
{
	ReadBitmap("train_tube_lines.bmp");

	int i, j, k;
	for (i = 0, k = 0; i < train_tube_lines_tex->GetWidth(); i++)
		for (j = 0; j < train_tube_lines_tex->GetHeight(); j++, k += 3)
		{
			train_tube_lines_data[i][j][0] = bmp[k + 2];
			train_tube_lines_data[i][j][1] = bmp[k + 1];
			train_tube_lines_data[i][j][2] = bmp[k]; //in the file(bmp): bgrbgrbgr...
		}

	BindTexture(train_tube_lines_tex, train_tube_lines_data);

	free(bmp);
}

void InitTrainNoseTexture()
{
	ReadBitmap("train_nose.bmp");

	int i, j, k;
	for (i = 0, k = 0; i < train_nose_tex->GetWidth(); i++)
		for (j = 0; j < train_nose_tex->GetHeight(); j++, k += 3)
		{
			train_nose_data[i][j][0] = bmp[k + 2];
			train_nose_data[i][j][1] = bmp[k + 1];
			train_nose_data[i][j][2] = bmp[k]; //in the file(bmp): bgrbgrbgr...
		}

	BindTexture(train_nose_tex, train_nose_data);

	free(bmp);
}

void InitMetalAccentTexture()
{
	ReadBitmap("metal_accent.bmp");

	int i, j, k;
	for (i = 0, k = 0; i < metal_accent_tex->GetWidth(); i++)
		for (j = 0; j < metal_accent_tex->GetHeight(); j++, k += 3)
		{
			metal_accent_data[i][j][0] = bmp[k + 2];
			metal_accent_data[i][j][1] = bmp[k + 1];
			metal_accent_data[i][j][2] = bmp[k]; //in the file(bmp): bgrbgrbgr...
		}

	BindTexture(metal_accent_tex, metal_accent_data);

	free(bmp);
}

void InitMetalBrightTexture()
{
	ReadBitmap("metal_bright.bmp");

	int i, j, k;
	for (i = 0, k = 0; i < metal_bright_tex->GetWidth(); i++)
		for (j = 0; j < metal_bright_tex->GetHeight(); j++, k += 3)
		{
			metal_bright_data[i][j][0] = bmp[k + 2];
			metal_bright_data[i][j][1] = bmp[k + 1];
			metal_bright_data[i][j][2] = bmp[k]; //in the file(bmp): bgrbgrbgr...
		}

	BindTexture(metal_bright_tex, metal_bright_data);

	free(bmp);
}

void InitTreeLeavesTexture()
{
	ReadBitmap("leaves.bmp", true);

	int i, j, k;
	for (i = 0, k = 0; i < tree_leaves_tex->GetWidth(); i++)
		for (j = 0; j < tree_leaves_tex->GetHeight(); j++, k += 4)
		{
			tree_leaves_data[i][j][0] = bmp[k + 2];
			tree_leaves_data[i][j][1] = bmp[k + 1];
			tree_leaves_data[i][j][2] = bmp[k];
			tree_leaves_data[i][j][3] = bmp[k + 3]; //in the file(bmp): bgrabgrabgra...
		}

	BindTexture(tree_leaves_tex, tree_leaves_data);

	free(bmp);
}

void InitTreeLogTexture()
{
	ReadBitmap("wood.bmp", true);

	int i, j, k;
	for (i = 0, k = 0; i < tree_log_tex->GetWidth(); i++)
		for (j = 0; j < tree_log_tex->GetHeight(); j++, k += 3)
		{
			tree_log_data[i][j][0] = bmp[k + 2];
			tree_log_data[i][j][1] = bmp[k + 1];
			tree_log_data[i][j][2] = bmp[k];
		}

	BindTexture(tree_log_tex, tree_log_data);

	free(bmp);
}


void BindTexture(Texture* texture, GLvoid* pixels)
{

	glBindTexture(GL_TEXTURE_2D, texture->GetTid());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	bool alpha = texture->IsAlpha();
	if (!alpha)
	{
		// rgb (with no alpha)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->GetWidth(), texture->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE,pixels);
	}
	else
	{
		//rgba - with alpha
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->GetWidth(), texture->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	}
}

