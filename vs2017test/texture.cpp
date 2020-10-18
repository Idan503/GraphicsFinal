#include "texture.h"
#include "glut.h"
#include "globals.h"
#include <math.h>
#include <stdio.h>

const int rail_size = 256;
const int grass_size = 256;

const int bridge_road_width = 1024;
const int bridge_road_height= 512;

// Texture definitions
unsigned char rail[rail_size][rail_size][4]; //rgb with alpha
unsigned char grass[grass_size][grass_size][3]; //rgb
unsigned char fence[bridge_road_width][bridge_road_height][3];

unsigned char* bmp;


// 0 = rail, 1 = ground...
void InitAllTextures()
{
	InitRailTexture();
	InitTerrainTexture();
	InitBridgeRoadTexture();

	//Texture properties

}

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

// ID = 0
void InitRailTexture()
{
	int i, j, noise, side_noise; // noise change color a bit to make it more realistic

	for (j = 0; j < rail_size; j++){
		side_noise = 5 - rand() % 10;
		for (i = 0; i < rail_size; i++) {
			noise = 10 - rand() % 20;
			if ((j > rail_size * 0.75 && j < rail_size * 0.85) ||
				(j < rail_size * 0.25 && j >rail_size * 0.15))
			{
				// Continues lines on sides
				rail[i][j][0] = 50 + side_noise + (noise * 0.5);
				rail[i][j][1] = 45 + side_noise + (noise * 0.5);
				rail[i][j][2] = 46 + side_noise + (noise * 0.5);
				rail[i][j][3] = 255;
			}
			else if (i % (rail_size / 4) > 10 && i % (rail_size / 4) < 42) {
				// Striped  lines of rails
				rail[i][j][0] = 38 + noise;
				rail[i][j][1] = 38 + noise;
				rail[i][j][2] = 39 + noise;
				rail[i][j][3] = 255;
			}
			else {
				rail[i][j][0] = 255;
				rail[i][j][1] = 255;
				rail[i][j][2] = 255;
				rail[i][j][3] = 0;
			}
		}
	}


	glBindTexture(GL_TEXTURE_2D, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, grass_size, grass_size, 0, GL_RGBA, GL_UNSIGNED_BYTE, rail);
}

// ID = 1
void InitTerrainTexture() {
	int i, j, noise;
	for(i=0;i<grass_size;i++)
		for (j = 0; j < grass_size; j++)
		{
			noise = 5 - rand() % 10;
			grass[i][j][0] = 15 + noise;
			grass[i][j][1] = 65 + noise;
			grass[i][j][2] = 25+ noise;

			if (rand() % 4 == 0)
				grass[i][j][1] -= 10;

			if ((i+j) % (grass_size / 4) > 10 && (i+j) % (grass_size / 4) < 35)
			{
				grass[i][j][0] = 30;
				grass[i][j][1] = 70;
				grass[i][j][2] = 20;
			}
		}

	glBindTexture(GL_TEXTURE_2D, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, grass_size, grass_size, 0, GL_RGB, GL_UNSIGNED_BYTE, grass);
}

// ID = 2
void InitBridgeRoadTexture() {
	ReadBitmap("bridge_road.bmp");
	
	int i, j, k;
	for(i=0,k=0;i< bridge_road_width;i++)
		for (j = 0; j < bridge_road_height; j++, k+=3)
		{
			fence[i][j][0] = bmp[k + 2];
			fence[i][j][1] = bmp[k + 1];
			fence[i][j][2] = bmp[k]; //in the file(bmp): bgrbgrbgr...
		}

	glBindTexture(GL_TEXTURE_2D, 2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,0, GL_RGB, bridge_road_width, bridge_road_height, 0, GL_RGB, GL_UNSIGNED_BYTE, fence);

	free(bmp);
}
