#include "texture_manager.h"
#include "glut.h"
#include "globals.h"
#include "Texture.h"
#include <math.h>
#include <stdio.h>

Texture* rail_tex = new Texture(0, 256, 256, true);
Texture* grass_tex = new Texture(0, 256, 256, false);
Texture* train_pipe_tex = new Texture(0, 1024, 512, false);

unsigned char* bmp;

// 0 = rail, 1x = ground, 2x = bridge, 3x = train
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

	vector<vector<vector<unsigned char>>> rail_tex_data = rail_tex->GetData();

	for (j = 0; j < rail_tex_data.size(); j++){
		side_noise = 5 - rand() % 10;
		for (i = 0; i < rail_tex_data[0].size(); i++) {
			noise = 10 - rand() % 20;
			if ((j > rail_tex_data.size() * 0.75 && j < rail_tex_data.size() * 0.85) ||
				(j < rail_tex_data.size() * 0.25 && j >rail_tex_data.size() * 0.15))
			{
				// Continues lines on sides
				rail_tex_data[i][j][0] = 50 + side_noise + (noise * 0.5);
				rail_tex_data[i][j][1] = 45 + side_noise + (noise * 0.5);
				rail_tex_data[i][j][2] = 46 + side_noise + (noise * 0.5);
				rail_tex_data[i][j][3] = 255;
			}
			else if (i % (rail_tex_data.size() / 4) > 10 && i % (rail_tex_data.size() / 4) < 42) {
				// Striped  lines of rails
				rail_tex_data[i][j][0] = 38 + noise;
				rail_tex_data[i][j][1] = 38 + noise;
				rail_tex_data[i][j][2] = 39 + noise;
				rail_tex_data[i][j][3] = 255;
			}
			else {
				rail_tex_data[i][j][0] = 255;
				rail_tex_data[i][j][1] = 255;
				rail_tex_data[i][j][2] = 255;
				rail_tex_data[i][j][3] = 0;
			}
		}
	}

	rail_tex->SetData(rail_tex_data);
	rail_tex->Bind();

}

// ID = 1
void InitTerrainTexture() {
	int i, j, noise;

	vector<vector<vector<unsigned char>>> terrain = rail_tex->GetData();

	for(i=0;i<grass_size;i++)
		for (j = 0; j < grass_size; j++)
		{
			noise = 5 - rand() % 10;
			grass_tex[i][j][0] = 15 + noise;
			grass_tex[i][j][1] = 65 + noise;
			grass_tex[i][j][2] = 25+ noise;

			if (rand() % 4 == 0)
				grass_tex[i][j][1] -= 10;

			if ((i+j) % (grass_size / 4) > 10 && (i+j) % (grass_size / 4) < 35)
			{
				grass_tex[i][j][0] = 30;
				grass_tex[i][j][1] = 70;
				grass_tex[i][j][2] = 20;
			}
		}

	glBindTexture(GL_TEXTURE_2D, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, grass_size, grass_size, 0, GL_RGB, GL_UNSIGNED_BYTE, grass_tex);
}

// ID = 2
void InitBridgeRoadTexture() {
	/*
	ReadBitmap("bridge_road.bmp");
	
	int i, j, k;
	for(i=0,k=0;i< bridge_road_width;i++)
		for (j = 0; j < bridge_road_height; j++, k+=3)
		{
			fence_tex[i][j][0] = bmp[k + 2];
			fence_tex[i][j][1] = bmp[k + 1];
			fence_tex[i][j][2] = bmp[k]; //in the file(bmp): bgrbgrbgr...
		}

	glBindTexture(GL_TEXTURE_2D, 2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,0, GL_RGB, bridge_road_width, bridge_road_height, 0, GL_RGB, GL_UNSIGNED_BYTE, fence_tex);

	free(bmp);
	*/
}

// ID = 3
void InitTrainPipeTexture()
{




	free(bmp);
}