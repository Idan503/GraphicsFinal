#include "texture.h"
#include "glut.h"
#include "globals.h"

const int rail_size = 256;

// Texture definitions
unsigned char rail[rail_size][rail_size][4]; //3 stands for rgb, 4 for alpha


void InitTextures()
{
	InitRailTexture();

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
			noise = 15 - rand() % 30;
			if (i % (rail_size / 4) > 10 && i % (rail_size / 4) < 42) {
				// Striped  lines of rails
				rail[i][j][0] = 55 + noise;
				rail[i][j][1] = 55 + noise;
				rail[i][j][2] = 55 + noise;
				rail[i][j][3] = 255;
			}
			else if ((j > rail_size * 0.75 && j < rail_size * 0.85) ||
				(j < rail_size * 0.25 && j >rail_size * 0.15 ))
			{
				// Continues lines on sides
				rail[i][j][0] = 55 + side_noise + (noise * 0.5);
				rail[i][j][1] = 55 + side_noise+ (noise * 0.5 );
				rail[i][j][2] = 55 + side_noise + (noise * 0.5);
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


// 0 = Rail , 1 = ..
void SetTexture(int textureId)
{
	if (textureId == current_texture_id)
		return; // For better performance - function doesn't need to work

	switch (textureId)
	{
	case 0:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, rail_size, rail_size, 0, GL_RGBA, GL_UNSIGNED_BYTE, rail);
		glBindTexture(GL_TEXTURE_2D, textureId);
		current_texture_id = textureId;
		break;
	}
}
