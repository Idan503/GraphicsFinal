#include "glut.h"
#include "globals.h"
#include <math.h>
#include "material.h"
#include "texture.h"
#include "ground_builder.h"


int flat_height = 2.25;

void SetNormal(int i, int j)
{
	double n[3];

	n[0] = ground[i][j] - ground[i][j + 1];
	n[1] = 1;
	n[2] = ground[i][j] - ground[i + 1][j];
	glNormal3d(n[0], n[1], n[2]);

}

// I should add here another color of between ground and high ground
void SetHeightMaterial(int h)
{
	if (h > 3)
	{
		SetHighGroundMaterial();
		return;
	}
	else if (h < 0)
	{
		SetLowGroundMaterial();
		return;
	}
	else if (h > 0.1)
	{
		SetGroundMaterial();
		return;
	}
	else
	{
		SetSandMaterial();
		return;
	}


}

void DrawGround()
{
	int i, j;
	glColor3d(0, 0, 0.3);

	for (i = 0; i < ground_size-2; i++) 
		for (j = 0; j < ground_size-2; j++)
		{
			glBegin(GL_POLYGON);
				SetNormal(i, j);
				SetHeightMaterial(ground[i][j]);
				glVertex3d(j - (ground_size / 2.0), ground[i][j], i - (ground_size) / 2.0);
				SetNormal(i, j+1);
				SetHeightMaterial(ground[i][j+1]);
				glVertex3d(j+1.0 - (ground_size / 2.0), ground[i][j+1], i - (ground_size) / 2.0);
				SetNormal(i+1, j+1);
				SetHeightMaterial(ground[i+1][j+1]);
				glVertex3d(j + 1.0 - (ground_size / 2.0), ground[i+1][j + 1], i+1.0 - (ground_size) / 2.0);
				SetNormal(i+1, j);
				SetHeightMaterial(ground[i+1][j]);
				glVertex3d(j - (ground_size / 2.0), ground[i + 1][j], i + 1.0 - (ground_size) / 2.0);

			glEnd();
		}

	DrawRail();
	DrawWater();
	
}

void DrawWater()
{
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4d(0, 0.2, 0.6, 0.8);
	glBegin(GL_POLYGON);
	glVertex3d(-ground_size / 2, 0, -ground_size / 2);
	glVertex3d(-ground_size / 2, 0, ground_size / 2);
	glVertex3d(ground_size / 2, 0, ground_size / 2);
	glVertex3d(ground_size / 2, 0, -ground_size / 2);
	glEnd();
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
}


// Mix of algorithms that learn in class + river in the middle
void BuildGroundTerrain()
{
	int i;
	BuildFlatMount();

	
	for (i = 0; i < 100; i++)
	{
		BuildRandomWalk();
	}
	
	for (i = 0; i < 220; i++)
	{
		BuildSeismologic();
	}
	
	BuildRiverPath();
	
	ValidateBuild();
	
	SmoothTerrain();

	PrepareRailRoad();
}

// This algorithm makes mountain peeks with delta random changes
void BuildFlatMount()
{
	int i, j;

	for (i = 0; i < ground_size; i++)
		for (j = 0; j < ground_size; j++)
		{
			ground[i][j] = flat_height;
		}


}

void BuildRandomWalk()
{
	int counter = 1200;
	int i, j;
	double delta = 0.12;

	if (rand() % 2 == 0)
		delta = -delta;

	// initial point
	i = rand() % ground_size;
	j = rand() % ground_size;
	while (counter > 0)
	{
		counter--;
		ground[i][j] += delta;
		// choose direction
		switch (rand() % 4)
		{
		case 0: // up
			i++;
			break;
		case 1: // right
			j++;
			break;
		case 2: // down
			i--;
			break;
		case 3: // left
			j--;
			break;
		}

		i = (i + ground_size) % ground_size;
		j = (j + ground_size) % ground_size;
	}
}

void BuildSeismologic()
{
	int i1, j1, i2, j2, i, j;
	double a, b;
	double delta = 0.2;

	int times;
	if (rand() % 2 == 0)
		delta = -delta;

	// Totally random point
	i1 = rand() % ground_size;
	j1 = rand() % ground_size;
	i2 = rand() % ground_size;
	j2 = rand() % ground_size;


	if (j1 != j2)
	{
		a = ((double)i2 - i1) / ((double)j2 - j1);
		b = i1 - a * j1;

		for (i = 0; i < ground_size; i++)
			for (j = 0; j < ground_size; j++)
			{
				if (i < a * (j + b))
					ground[i][j] += delta;
				else
					ground[i][j] -= delta;
			}
	}
}

void BuildRiverPath()
{
	int i, j;
	for(i=0;i<ground_size;i++)
		for (j = 0; j < ground_size; j++)
		{
			if (i < (ground_size/2) + river_size && i>(ground_size / 2) - river_size)
				ground[i][j] -= 8.0 * ((river_size - fabs(i - ground_size/2.0)) / river_size);
		}
}


// This method will check if there are not too many points under the water
// If there are too many low points, build will restart
void ValidateBuild()
{
	int tooLow = 0;
	int tooHigh = 0;
	int i, j;
	for(i=0;i<ground_size;i++)
		for (j = 0; j < ground_size; j++)
		{
			if (ground[i][j] < 0)
				tooLow++;

			if (ground[i][j] > 5.0 * (ground_size / 100))
				tooHigh++;
		}

	if (tooLow >= 2500 * (ground_size/100)) {
		BuildGroundTerrain(); // Too many points under the sea..
	}
	else if (tooHigh > 600 * (ground_size / 100) || tooHigh < 15 * (ground_size / 100))
		BuildGroundTerrain(); // Too many / too few higher points

	// This way we prevent a terrian which is too low or too high
}

void SmoothTerrain()
{
	// Using a mask with low pass filter
	vector<vector<double> > tmp(ground_size, vector<double>(ground_size, 0));
	int i, j;

	// compute smoothing signal
	for (i = 1; i < ground_size - 1; i++)
		for (j = 1; j < ground_size - 1; j++)
			tmp[i][j] = (0.25 * ground[i - 1][j - 1] + ground[i - 1][j] + 0.25 * ground[i - 1][j + 1] +
				ground[i][j - 1] + 4 * ground[i][j] + ground[i][j + 1] +
				0.25 * ground[i + 1][j - 1] + ground[i + 1][j] + 0.25 * ground[i + 1][j + 1]) / 9.0;

	// copy the new signal
	for (i = 1; i < ground_size - 1; i++)
		for (j = 1; j < ground_size - 1; j++)
			ground[i][j] = tmp[i][j];

}


void PrepareRailRoad() {
	int i;

	for (i = 0; i < ground_size; i++) {
		if(ground[i][ground_size/2] > 0)
			ground[i][ground_size / 2 + 1] = ground[i][ground_size / 2 - 1] = ground[i][ground_size /2];
	}
}


void DrawRail()
{
	SetTexture(0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // Might be changed to moduoate
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	int i;


	for (i = 0; i < ground_size - 1; i++) {


		glBegin(GL_POLYGON);
		glTexCoord2d(0, 0);
		glVertex3d(-1, ground[i][ground_size / 2] + 0.1, i - ground_size / 2);

		glTexCoord2d(0, 1);
		glVertex3d(-1, ground[i+1][ground_size / 2] + 0.1, i+1 - ground_size / 2);

		glTexCoord2d(1, 1);
		glVertex3d(1, ground[i + 1][ground_size / 2] +0.1, i + 1 - ground_size / 2);

		glTexCoord2d(1, 0);
		glVertex3d(1, ground[i][ground_size / 2] + 0.1, i - ground_size / 2);

		glEnd();

	}


	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}