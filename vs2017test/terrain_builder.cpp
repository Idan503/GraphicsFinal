#include "glut.h"
#include "globals.h"
#include <math.h>
#include "material.h"
#include "terrain_builder.h"


int flat_height = 2.25;

void SetColor(double h) {
	if (fabs(h) <1.2) // sand
		glColor3d(0.8, 0.7, 0.5);
	else
		if (fabs(h) <7) // green fields
			glColor3d(0.2 + h / 30, 0.6 - fabs(h) / 15, 0);
		else // rocks and snow
			glColor3d(sqrt(h) / 5, sqrt(h) / 5, sqrt(h) / 4.0);
}

void DrawGround()
{
	int i, j;
	glColor3d(0, 0, 0.3);

	SetRedPlasticMaterial();
	
	for (i = 0; i < ground_size-1; i++) 
		for (j = 0; j < ground_size-1; j++)
		{
			glBegin(GL_POLYGON);
				SetColor(ground[i][j]);
				glVertex3d(j - (ground_size / 2.0), ground[i][j], i - (ground_size) / 2.0);
				SetColor(ground[i][j+1]);
				glVertex3d(j+1.0 - (ground_size / 2.0), ground[i][j+1], i - (ground_size) / 2.0);
				SetColor(ground[i+1][j+1]);
				glVertex3d(j + 1.0 - (ground_size / 2.0), ground[i+1][j + 1], i+1.0 - (ground_size) / 2.0);
				SetColor(ground[i+1][j]);
				glVertex3d(j - (ground_size / 2.0), ground[i + 1][j], i + 1.0 - (ground_size) / 2.0);

			glEnd();
		}
	DrawWater();
	
}

void DrawWater()
{
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
}


// Mix of algorithms that learn in class + river in the middle
void BuildTerrain()
{
	int i;
	BuildFlatMount();

	
	for (i = 0; i < 250; i++)
	{
		BuildRandomWalk();
	}
	
	for (i = 0; i < 250; i++)
	{
		BuildSeismologic();
	}
	
	BuildRiverPath();
	
	ValidateBuild();

	SmoothTerrain();
	
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
	double delta = 0.08;

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
	double delta = 0.1;

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
		a = ((double)i2 - i1) / (j2 - j1);
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

			if (ground[i][j] > 5)
				tooHigh++;
		}

	if (tooLow >= 3500 * (ground_size/100)) {
		BuildTerrain(); // Too many points under the sea..
	}
	else if (tooHigh > 600 * (ground_size / 100) || tooHigh < 15 * (ground_size / 100))
		BuildTerrain(); // Too many / too few higher points

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

