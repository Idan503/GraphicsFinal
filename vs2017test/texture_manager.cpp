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

Texture* rock_tex = new Texture(1, 512, 512);
unsigned char rock_data[512][512][3];

//Rail 10-19
Texture* rail_tex = new Texture(10, 256, 256, true);
unsigned char rail_data[256][256][4]; // 4 stands for rgba

//Bridge 20-29
Texture* bridge_road_tex = new Texture(20, 1024, 512);
unsigned char bridge_road_data[1024][512][3];

Texture* metal_white_tex = new Texture(21, 512, 512);
unsigned char metal_white_data[512][512][3];

Texture* metal_white_dark_tex = new Texture(22, 512, 512);
unsigned char metal_white_dark_data[512][512][3];

//Train 30-49
Texture* train_tube_tex = new Texture(30, 1024, 512);
unsigned char train_tube_data[1024][512][3];

Texture* train_tube_lines_tex = new Texture(31, 128, 512);
unsigned char train_tube_lines_data[128][512][3];

Texture* train_nose_tex = new Texture(32, 256, 256);
unsigned char train_nose_data[256][256][3];

Texture* metal_accent_tex= new Texture(33, 512, 256);
unsigned char metal_accent_data[512][256][3];

Texture* metal_grey_tex = new Texture(34, 512, 512);
unsigned char metal_grey_data[512][512][3];


Texture* metal_dark_grey_tex = new Texture(37, 512, 512);
unsigned char metal_dark_grey_data[512][512][3];

Texture* metal_red_tex = new Texture(35, 512, 512);
unsigned char metal_red_data[512][512][3];

Texture* metal_yellow_tex = new Texture(36, 512, 512);
unsigned char metal_yellow_data[512][512][3];

Texture* train_half_tube_tex = new Texture(38, 512, 512);
unsigned char train_half_tube_data[512][512][3];

Texture* train_patch_tube_front_tex = new Texture(39, 512, 248);
unsigned char train_patch_tube_front_data[512][248][3];

Texture* train_patch_tube_back_tex = new Texture(40, 512, 248);
unsigned char train_patch_tube_back_data[512][248][3];

//Tree 50-59
Texture* tree_log_tex = new Texture(50, 512, 512);
unsigned char tree_log_data[512][512][3];

Texture* tree_leaves_tex = new Texture(51, 512, 512,true);
unsigned char tree_leaves_data[512][512][4];

//Ambient 60-69
Texture* sky_tex = new Texture(60, 2048, 1024, false);
unsigned char sky_data[2048][1024][3];

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
	InitMetalGreyTexture();
	InitTreeLeavesTexture();
	InitTreeLogTexture();
	InitRedMetalTexture();
	InitMetalDarkGreyTexture();
	InitYellowMetalTexture();
	InitTrainHalfTubeTexture();
	InitTrainPatchTubeFrontTexture();
	InitTrainPatchTubeBackTexture();
	InitSkyTexture();
	InitMetalWhiteTexture();
	InitMetalWhiteDarkTexture();
	InitRockTexture();
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


void InitRockTexture()
{
	ReadBitmap("rock.bmp",false);

	int i, j, k;
	for (i = 0, k = 0; i < rock_tex->GetWidth(); i++)
		for (j = 0; j < rock_tex->GetHeight(); j++, k += 3)
		{
			rock_data[i][j][0] = bmp[k + 2];
			rock_data[i][j][1] = bmp[k + 1];
			rock_data[i][j][2] = bmp[k]; //in the file(bmp): bgrbgrbgr...
		}

	BindTexture(rock_tex, rock_data);

	free(bmp);

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


void InitTrainHalfTubeTexture()
{
	ReadBitmap("half_tube.bmp");

	int i, j, k;
	for (i = 0, k = 0; i < train_half_tube_tex->GetWidth(); i++)
		for (j = 0; j < train_half_tube_tex->GetHeight(); j++, k += 3)
		{
			train_half_tube_data[i][j][0] = bmp[k + 2];
			train_half_tube_data[i][j][1] = bmp[k + 1];
			train_half_tube_data[i][j][2] = bmp[k]; //in the file(bmp): bgrbgrbgr...
		}

	BindTexture(train_half_tube_tex, train_half_tube_data);

	free(bmp);
}


void InitTrainPatchTubeFrontTexture()
{
	ReadBitmap("patch_tube_front.bmp");

	int i, j, k;
	for (i = 0, k = 0; i < train_patch_tube_front_tex->GetWidth(); i++)
		for (j = 0; j < train_patch_tube_front_tex->GetHeight(); j++, k += 3)
		{
			train_patch_tube_front_data[i][j][0] = bmp[k + 2];
			train_patch_tube_front_data[i][j][1] = bmp[k + 1];
			train_patch_tube_front_data[i][j][2] = bmp[k]; //in the file(bmp): bgrbgrbgr...
		}

	BindTexture(train_patch_tube_front_tex, train_patch_tube_front_data);

	free(bmp);
}


void InitTrainPatchTubeBackTexture()
{
	ReadBitmap("patch_tube_back.bmp");

	int i, j, k;
	for (i = 0, k = 0; i < train_patch_tube_back_tex->GetWidth(); i++)
		for (j = 0; j < train_patch_tube_back_tex->GetHeight(); j++, k += 3)
		{
			train_patch_tube_back_data[i][j][0] = bmp[k + 2];
			train_patch_tube_back_data[i][j][1] = bmp[k + 1];
			train_patch_tube_back_data[i][j][2] = bmp[k]; //in the file(bmp): bgrbgrbgr...
		}

	BindTexture(train_patch_tube_back_tex, train_patch_tube_back_data);

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

void InitRedMetalTexture()
{
	ReadBitmap("metal_red.bmp");

	int i, j, k;
	for (i = 0, k = 0; i < metal_red_tex->GetWidth(); i++)
		for (j = 0; j < metal_red_tex->GetHeight(); j++, k += 3)
		{
			metal_red_data[i][j][0] = bmp[k + 2];
			metal_red_data[i][j][1] = bmp[k + 1];
			metal_red_data[i][j][2] = bmp[k]; //in the file(bmp): bgrbgrbgr...
		}

	BindTexture(metal_red_tex, metal_red_data);

	free(bmp);
}

void InitYellowMetalTexture()
{
	ReadBitmap("metal_yellow.bmp");

	int i, j, k;
	for (i = 0, k = 0; i < metal_yellow_tex->GetWidth(); i++)
		for (j = 0; j < metal_yellow_tex->GetHeight(); j++, k += 3)
		{
			metal_yellow_data[i][j][0] = bmp[k + 2];
			metal_yellow_data[i][j][1] = bmp[k + 1];
			metal_yellow_data[i][j][2] = bmp[k]; //in the file(bmp): bgrbgrbgr...
		}

	BindTexture(metal_yellow_tex, metal_yellow_data);

	free(bmp);
}


void InitMetalGreyTexture()
{
	ReadBitmap("metal_grey.bmp");

	int i, j, k;
	for (i = 0, k = 0; i < metal_grey_tex->GetWidth(); i++)
		for (j = 0; j < metal_grey_tex->GetHeight(); j++, k += 3)
		{
			metal_grey_data[i][j][0] = bmp[k + 2];
			metal_grey_data[i][j][1] = bmp[k + 1];
			metal_grey_data[i][j][2] = bmp[k]; //in the file(bmp): bgrbgrbgr...
		}

	BindTexture(metal_grey_tex, metal_grey_data);

	free(bmp);
}



void InitMetalWhiteTexture()
{
	ReadBitmap("metal_white.bmp");

	int i, j, k;
	for (i = 0, k = 0; i < metal_white_tex->GetWidth(); i++)
		for (j = 0; j < metal_white_tex->GetHeight(); j++, k += 3)
		{
			metal_white_data[i][j][0] = bmp[k + 2];
			metal_white_data[i][j][1] = bmp[k + 1];
			metal_white_data[i][j][2] = bmp[k]; //in the file(bmp): bgrbgrbgr...
		}

	BindTexture(metal_white_tex, metal_white_data);

	free(bmp);
}

void InitMetalWhiteDarkTexture()
{
	ReadBitmap("metal_white_dark.bmp");

	int i, j, k;
	for (i = 0, k = 0; i < metal_white_dark_tex->GetWidth(); i++)
		for (j = 0; j < metal_white_dark_tex->GetHeight(); j++, k += 3)
		{
			metal_white_dark_data[i][j][0] = bmp[k + 2];
			metal_white_dark_data[i][j][1] = bmp[k + 1];
			metal_white_dark_data[i][j][2] = bmp[k]; //in the file(bmp): bgrbgrbgr...
		}

	BindTexture(metal_white_dark_tex, metal_white_dark_data);
}


void InitMetalDarkGreyTexture()
{
	ReadBitmap("metal_dark_grey.bmp");

	int i, j, k;
	for (i = 0, k = 0; i < metal_dark_grey_tex->GetWidth(); i++)
		for (j = 0; j < metal_dark_grey_tex->GetHeight(); j++, k += 3)
		{
			metal_dark_grey_data[i][j][0] = bmp[k + 2];
			metal_dark_grey_data[i][j][1] = bmp[k + 1];
			metal_dark_grey_data[i][j][2] = bmp[k]; //in the file(bmp): bgrbgrbgr...
		}

	BindTexture(metal_dark_grey_tex, metal_dark_grey_data);

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
	ReadBitmap("wood.bmp");

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


void InitSkyTexture()
{
	ReadBitmap("sky.bmp");

	int i, j, k;
	for (i = 0, k = 0; i < sky_tex->GetWidth(); i++)
		for (j = 0; j < sky_tex->GetHeight(); j++, k += 3)
		{
			sky_data[i][j][0] = bmp[k + 2];
			sky_data[i][j][1] = bmp[k + 1];
			sky_data[i][j][2] = bmp[k];
		}

	BindTexture(sky_tex, sky_data);

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

