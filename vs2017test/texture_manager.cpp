#include "texture_manager.h"
#include "glut.h"
#include "globals.h"
#include "Texture.h"
#include <math.h>
#include <stdio.h>

//Texture Declaration

//Terrain 0-9
Texture* terrain_tex = new Texture(0, 256, 256, false);
unsigned char terrain_data[256][256][3]; // 3 stands for rgb

//Rail 10-19
Texture* rail_tex = new Texture(10, 256, 256, true);
unsigned char rail_data[256][256][4]; // 4 stands for rgba

//Bridge 20-29
Texture* bridge_road_tex = new Texture(20, 1024, 512, false);
unsigned char bridge_road_data[1024][512][3];

//Train 30-49
Texture* train_pipe_tex = new Texture(30, 1024, 512, false);
unsigned char train_pipe_data[1024][512][3];



unsigned char* bmp;

void InitAllTextures()
{
	InitRailTexture();
	InitTerrainTexture();
	InitBridgeRoadTexture();

	//Texture properties

}

// support rgb bitmaps only 
void ReadBitmap(const char* fname)
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

	int size = bi.biHeight * bi.biWidth * 3;
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

void InitBridgeRoadTexture() {
	
	ReadBitmap("bridge_road.bmp");
	
	/*
	vector<vector<vector<unsigned char>>> bridge_road_data = bridge_road_tex->GetData();

	int width = bridge_road_data.size();
	int height = bridge_road_data[0].size();

	int i, j, k;
	for(i=0,k=0;i< width;i++)
		for (j = 0; j < height; j++, k+=3)
		{
			bridge_road_data[i][j][0] = bmp[k + 2];
			bridge_road_data[i][j][1] = bmp[k + 1];
			bridge_road_data[i][j][2] = bmp[k]; //in the file(bmp): bgrbgrbgr...
		}

	bridge_road_tex->SetData(bridge_road_data);
	bridge_road_tex->Bind(tex_arr_data);

	free(bmp);
	*/
}

void InitTrainPipeTexture()
{




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

