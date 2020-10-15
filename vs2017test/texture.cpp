#include "texture.h"
#include "glut.h"
#include "globals.h"

const int rail_size = 256;
const int grass_size = 256;

// Texture definitions
unsigned char rail[rail_size][rail_size][4]; //rgb with alpha
unsigned char grass[grass_size][grass_size][3]; //rgb


void InitTextures()
{
	InitRailTexture();
	InitGrassTexture();

	//Texture properties
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	SetTexture(0);

}


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


}


void InitGrassTexture() {
	int i, j, noise;

	for(i=0;i<grass_size;i++)
		for (j = 0; j < grass_size; j++)
		{
			noise = 10 - rand() % 20;
			grass[i][j][0] = 35 + noise;
			grass[i][j][1] = 190 + noise;
			grass[i][j][2] = 20 + noise;
		}
}

// 0 = Rail , 1 = grass
void SetTexture(int textureId)
{
	if (textureId == current_texture_id)
		return; // For better performance - function doesn't need to work

	switch (textureId)
	{
	case 0: // RAIL
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, rail_size, rail_size, 0, GL_RGBA, GL_UNSIGNED_BYTE, rail);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // Might be changed to moduoate
		break;
	case 1: // GRASS
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, grass_size, grass_size, 0, GL_RGB, GL_UNSIGNED_BYTE, grass);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // Might be changed to moduoate
		break;
	}

	glBindTexture(GL_TEXTURE_2D, textureId);
	current_texture_id = textureId;
	
}
