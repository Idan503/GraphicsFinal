#include "glut.h"
#include "globals.h"
#include <math.h>
#include "material_manager.h"
#include "texture_manager.h"
#include "ground_builder.h"


double flat_height = 3;

void SetNormal(int i, int j)
{
	if (i >= ground_size-1 || j >= ground_size - 1)
		return; // out of array

	double n[3];

	n[0] = ground[i][j] - ground[i][j + 1];
	n[1] = 1;
	n[2] = ground[i][j] - ground[i + 1][j];
	glNormal3d(n[0], n[1], n[2]);

}

// I should add here another color of between ground and high ground
void SetHeightMaterial(int h)
{
	if (h > 4.5)
	{
		SetSnowMaterial();
		return;
	}
	else if (h > 3)
	{
		SetHighGroundMaterial();
		return;
	}
	else if (h > 0.12)
	{
		SetGroundMaterial();
		return;
	}
	else if (h > 0.06)
	{
		SetLowGroundMaterial();
		return;
	}
	else if (h < -0.05)
	{
		SetUnderGroundMaterial();
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

	// The ground model I created here contains both material with lightning and overlayed texture
	// for improving the details
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD); // using GL_ADD to "add" the lines texture 'above' the material

	// Using lines texutre that is added to materialed ground

	for (i = 0; i <= ground_size-2; i++) 
		for (j = 0; j <= ground_size-2; j++)
		{
			glBegin(GL_POLYGON);
				SetNormal(i, j);
				glTexCoord2d(0, 0);
				SetHeightMaterial(ground[i][j]);
				glVertex3d(j - (ground_size / 2.0), ground[i][j], i - (ground_size) / 2.0);
				SetNormal(i, j+1);
				glTexCoord2d(0, 1);
				SetHeightMaterial(ground[i][j+1]);
				glVertex3d(j+1.0 - (ground_size / 2.0), ground[i][j+1], i - (ground_size) / 2.0);
				SetNormal(i+1, j+1);
				glTexCoord2d(1, 1);
				SetHeightMaterial(ground[i+1][j+1]);
				glVertex3d(j + 1.0 - (ground_size / 2.0), ground[i+1][j + 1], i+1.0 - (ground_size) / 2.0);
				SetNormal(i+1, j);
				glTexCoord2d(1, 0);
				SetHeightMaterial(ground[i+1][j]);
				glVertex3d(j - (ground_size / 2.0), ground[i + 1][j], i + 1.0 - (ground_size) / 2.0);

			glEnd();


		}


	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);


	DrawWater(); // We draw water before rail because rail is half transparent
	
	DrawRail();
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
void BuildGroundTerrain()
{
	int i;
	BuildFlatGround();

	
	for (i = 0; i <100; i++)
	{
		BuildRandomWalk();
	}
	
	for (i = 0; i < 250; i++)
	{
		BuildSeismologic();
	}
	
	BuildRiverPath();
	
	if (ValidateGroundBuild()) {
		SmoothTerrain();
		SmoothTerrain();
		SmoothTerrain();

		PrepareRailRoad();
	}
}

// This algorithm makes mountain peeks with delta random changes
void BuildFlatGround()
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
bool ValidateGroundBuild()
{

	double max_height = GetMaxBridgeGroundHeight();
	if (max_height < 0.15 || max_height > 4.5)
	{
		BuildGroundTerrain(); // Bridge will be too low/to high
		return false;
	}


	int too_low = 0;
	int too_high = 0;
	int i, j;
	for (i = 0; i < ground_size - 1; i++) {
		for (j = 0; j < ground_size; j++)
		{
			if (ground[i][j] < 0)
				too_low++;

			if (ground[i][j] > 5.5 * (ground_size / 100))
				too_high++;
		}
	}


	if (too_low >= 2200 * (ground_size/100)) {
		BuildGroundTerrain(); // Too many points under the sea..
		return false;
	}
	else if (too_high > 600 * (ground_size / 100) || too_high < 15 * (ground_size / 100)) {
		BuildGroundTerrain(); // Too many / too few higher points
		return false;
	}
		

	return true;
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
	int x,z,i;

	// Flats on x axis (for flat rail)
	for (x = 0; x < ground_size; x++) {
		if(ground[x][ground_size/2] > 0)
			ground[x][ground_size / 2 + 1] = ground[x][ground_size / 2 - 1] = ground[x][ground_size /2];
	}


	const double max_ground_height = GetMaxBridgeGroundHeight();

	int offset_x, offset_z;


	for (offset_z = -2; offset_z < 5; offset_z++) {
		for (offset_x = -1; offset_x < 2; offset_x++) {
			ground[ground_size / 2 + river_size + offset_z][ground_size / 2 + offset_x] = max_ground_height;
			ground[ground_size / 2 - river_size - offset_z][ground_size / 2 + offset_x] = max_ground_height;
		}
	}


	for (i = 0; i < 40; i++) {
		for (offset_x = -1; offset_x < 2; offset_x++) {
			for (z = 1; z < ground_size - 1; z++) {
				if (z <= ground_size / 2 - river_size - 1 || z >= ground_size / 2 + river_size + 1) {
					ground[z][ground_size / 2 + offset_x] = (0.4 * ground[z - 1][ground_size / 2 + offset_x]) +
						(0.2 * ground[z][ground_size / 2 + offset_x]) + (0.4 * ground[z + 1][ground_size / 2 + offset_x]);
				}
			}
		}
	}




	

}


void DrawRail()
{
	
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 10);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	int i;
	const double min_height = 0.1;
	const double max_ground_height = GetMaxBridgeGroundHeight();

	for (i = 0; i < ground_size - 1; i++) {
		if (rail[i] == NULL) {
			double start_height = 0, end_height = 0;

			if (i >= (ground_size / 2 - river_size) && i < (ground_size / 2 + river_size))
				end_height = max_ground_height + bridge_height;
			else
				end_height = ground[i + 1][ground_size / 2];

			if (i > (ground_size / 2 - river_size) && i <= (ground_size / 2 + river_size))
				start_height = max_ground_height + bridge_height;
			else
				start_height = ground[i][ground_size / 2];


			start_height += min_height;
			end_height += min_height;

			// init the array, rail height is constant
			rail[i] = start_height;
			rail[i + 1] = end_height;

		}

		



		glBegin(GL_POLYGON);
		glTexCoord2d(0, 0);
		glVertex3d(-rail_width, rail[i], i - ground_size / 2.0);

		glTexCoord2d(0, 1);
		glVertex3d(-rail_width, rail[i + 1], i + 1.0 - ground_size / 2.0);

		glTexCoord2d(1, 1);
		glVertex3d(rail_width, rail[i + 1], i + 1.0 - ground_size / 2.0);

		glTexCoord2d(1, 0);
		glVertex3d(rail_width, rail[i], i - ground_size / 2.0);

		glEnd();

	}


	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	
}

//returns the highest height of ground touching the bridge - to set bridge height
double GetMaxBridgeGroundHeight()
{

	return fmax(fmax(ground[ground_size / 2 - river_size + 1][ground_size / 2], ground[ground_size / 2 - river_size][ground_size / 2]),
		fmax(ground[ground_size / 2 + river_size - 1][ground_size / 2], ground[ground_size / 2 + river_size][ground_size / 2]));
}