#include "TrainWagon.h"
#include "glut.h"
#include "material.h"
#include "globals.h"
#include <math.h>

TrainWagon::TrainWagon(double r, double g, double b, vector<double> pos, vector<double> dir, double speed)
{
	red = r;
	green = g;
	blue = b;
	this->position = pos;
	this->direction = dir;
	this->speed = speed;
}



void TrainWagon::SetSpeed(double s)
{
	speed = s;
}

vector<double> TrainWagon::GetPosition()
{
	return position;
}


vector<double> TrainWagon::GetDirection()
{
	return direction;
}

bool TrainWagon::IsHead() {
	return head;
}


void TrainWagon::Draw()
{
	double beta;
	glPushMatrix();
	glTranslated(position[0], position[1] + 1, position[2]);
	// only when the motion is along X axis
	beta = -atan(direction[1]); // in rad
	glRotated(beta * 180 / PI, 1, 0, 0);
	
	SetRedPlasticMaterial();
	glutSolidCube(2);

	glPopMatrix();
}

// compute the direction and update car center
void TrainWagon::Move()
{
	int rail_index;
	if (fabs(direction[0]) < 0.01 && fabs(direction[2]) > 0.99) {
		// Direction is along z (Rail axis)
		rail_index = (int)(position[2] + ground_size / 2);
		if (direction[2] > 0)
		{
			// Moving to z+
			if (rail_index > ground_size - 1)
			{
				rail_index = 0;
				position[2] = -ground_size / 2;
				if (rail[rail_index] > 0)
					position[1] = rail[rail_index];
				else
					position[1] = 1;
			}
			

			if (rail[rail_index] > 0) {
				direction[1] = rail[rail_index + 1] - rail[rail_index];
			}
			else {
				direction[1] = 0;
			}

		}
		else 
		{
			// Moving to z-
			if (rail_index < 0)
			{
				rail_index = ground_size - 2;
				position[2] = ground_size/2;

				if (ground[ground_size / 2][rail_index + 1] > 0)
					position[1] = ground[ground_size / 2][rail_index + 1];
				else
					position[1] = 1;
			}

			if (ground[ground_size / 2][rail_index + 1] > 0)
				direction[1] = ground[ground_size / 2][rail_index] - ground[ground_size / 2][rail_index + 1];
			else {
				position[1] = 1;
				direction[1] = 0;
			}
		}

		int i;
		for (i = 0; i < 3; i++)
		{
			position[i] += direction[i] * speed;
			
			// updating position of train
		}

		int tmp_col;
		tmp_col = (int)(position[2] + ground_size / 2);
		if (tmp_col != rail_index&& tmp_col < ground_size) // update cy
		{
			if (rail[tmp_col] > 0)
				position[1] = rail[tmp_col];
			else position[1] = 1;

		}


		//printf("Dir: %lf %lf %lf\n", direction[0], direction[1], direction[2]);

	}


}
