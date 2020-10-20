#include "TrainWagon.h"
#include "glut.h"
#include "material.h"
#include "globals.h"
#include <math.h>

TrainWagon::TrainWagon(double r, double g, double b, vector<double> pos, vector<double> dir, double speed, bool head)
{
	red = r;
	green = g;
	blue = b;
	this->position = pos;
	this->direction = dir;
	this->speed = speed;
	this->head = head;
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
	

	if (head)
		DrawHeadWagon();
	else
		DrawWagon();

	glPopMatrix();
}

void TrainWagon::DrawHeadWagon()
{
	SetRedPlasticMaterial();

	// lower flat
	glPushMatrix();
	glTranslated(0, -0.5, 0);
	glScaled(1, 0.1, 3);
	glutSolidCube(1);
	glPopMatrix();

	//thicker flat
	glPushMatrix();
	glTranslated(0, -0.25, 0.35);
	glScaled(1, 0.35, 1.2);
	glutSolidCube(1);
	glPopMatrix();

	//tank
	glPushMatrix();
	glTranslated(0, 0.3, -0.8);
	glScaled(1, 1.5, 1.15);
	glutSolidCube(1);
	glPopMatrix();

	//front light placeholder
	glPushMatrix();
	glTranslated(0, 1, 1.35);
	glScaled(0.4, 0.45, 0.15);
	glutSolidCube(1);
	glPopMatrix();

	//front light
	glPushMatrix();
	glTranslated(0, 1, 1.45);
	glScaled(0.15, 0.15, 0.05);
	glutSolidSphere(1, 16, 16);
	glPopMatrix();


	


	SetSilverMaterial();

	//pipe
	glPushMatrix();
	glTranslated(0, 0.25, -0.25);
	glScaled(0.5, 0.55, 0.55);
	gluCylinder(gluNewQuadric(),1,1,3,16,8);
	glPopMatrix();

	//smll front iron flat
	glPushMatrix();
	glTranslated(0, -0.25, 1.15);
	glScaled(1, 0.35, 0.4);
	glutSolidCube(1);
	glPopMatrix();

	// under lower flat
	glPushMatrix();
	glTranslated(0, -0.65, 0);
	glScaled(1, 0.25, 2.8);
	glutSolidCube(1);
	glPopMatrix();

	//chimney (for emit smoke)

	// chimney long cylinder
	glPushMatrix();
	glTranslated(0, 1.55, 0.9);
	glScaled(0.125, 0.3, 0.125);
	glRotated(90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 1, 1, 2.5, 16, 8);
	glPopMatrix();

	// base
	glPushMatrix();
	glTranslated(0, 0.9, 0.9);
	glScaled(0.16, 0.25, 0.16);
	glRotated(90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 1, 1, 0.5, 16, 8);
	glPopMatrix();

	// topping low
	glPushMatrix();
	glTranslated(0, 1.55, 0.9);
	glScaled(0.125, 0.2, 0.125);
	glRotated(-90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 1, 1.4, 1, 16, 8);
	glPopMatrix();

	// topping high
	glPushMatrix();
	glTranslated(0, 1.95, 0.9);
	glScaled(0.125, 0.2, 0.125);
	glRotated(90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 1.2,1.4,1,16,8);
	glPopMatrix();

	//nose
	glPushMatrix();
	glTranslated(0, 0.175, 1.35);
	glScaled(0.5, 0.62, 0.25);
	glutSolidSphere(1, 32, 32);
	glPopMatrix();

	//shock absorber
	glDisable(GL_LIGHTING);
	glColor3d(0.15, 0.15, 0.15);
	glPushMatrix();
	glTranslated(0,-0.55,1.4);
	glScaled(0.5,0.5,0.4);
	glBegin(GL_POLYGON);
	glVertex3d(-1, 0, 0);
	glVertex3d(-1, -1, 0);
	glVertex3d(-1, -1, 1);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(1, 0, 0);
	glVertex3d(1, -1, 0);
	glVertex3d(1, -1, 1);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3d(1, 0, 0);
	glVertex3d(1, -1, 1);
	glVertex3d(-1, -1, 1);
	glVertex3d(-1, 0, 0);
	glEnd();


	glBegin(GL_POLYGON);
	glVertex3d(1, -1, 0);
	glVertex3d(1, -1, 1);
	glVertex3d(-1, -1, 1);
	glVertex3d(-1, -1, 0);
	glEnd();
	
	glPopMatrix();

	glEnable(GL_LIGHTING);


	//front wheel holder
	glPushMatrix();
	glTranslated(0, -0.8, 1.2);
	glScaled(1, 0.2, 0.425);
	glutSolidCube(1);
	glPopMatrix();

	
	//wheel piston x+
	glPushMatrix();
	glTranslated(0.4, -0.75, 0.3);
	glScaled(0.15, 0.15, 0.5);
	gluCylinder(gluNewQuadric(), 1, 1, 1, 16, 4);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.4, -0.75, 0.75);
	glScaled(0.15, 0.15, 0.05);
	glutSolidSphere(1, 16, 16);
	glPopMatrix();
	
	glPushMatrix();
	glTranslated(0.4, -0.75, 0.3);
	glScaled(0.15, 0.15, 0.05);
	glutSolidSphere(1, 16, 16);
	glPopMatrix();

	//wheel piston x-
	glPushMatrix();
	glTranslated(-0.4, -0.75, 0.3);
	glScaled(0.15, 0.15, 0.5);
	gluCylinder(gluNewQuadric(), 1, 1, 1, 16, 4);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.4, -0.75, 0.75);
	glScaled(0.15, 0.15, 0.05);
	glutSolidSphere(1, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.4, -0.75, 0.3);
	glScaled(0.15, 0.15, 0.05);
	glutSolidSphere(1, 16, 16);
	glPopMatrix();


	//back whels holder
	glPushMatrix();
	glTranslated(0, -0.8, -0.6);
	glScaled(1, 0.2, 0.8);
	glutSolidCube(1);
	glPopMatrix();

	
	//back hook holder x-
	glPushMatrix();
	glTranslated(-0.4, -0.8, -1.3);
	glScaled(0.1, 0.15, 0.15);
	glutSolidCube(1);
	glPopMatrix();

	//back hook holder x+
	glPushMatrix();
	glTranslated(0.4, -0.8, -1.3);
	glScaled(0.1, 0.15, 0.15);
	glutSolidCube(1);
	glPopMatrix();

	//back hook x+
	glPushMatrix();
	glTranslated(0.4, -0.825, -1.65);
	glScaled(0.05, 0.05, 0.15);
	gluCylinder(gluNewQuadric(), 1, 1, 1.65, 16, 8);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.4, -0.825, -1.65);
	glScaled(0.075, 0.075, 0.05);
	glutSolidSphere(1,16,16);
	glPopMatrix();


	//back hook x-
	glPushMatrix();
	glTranslated(-0.4, -0.825, -1.65);
	glScaled(0.05, 0.05, 0.15);
	gluCylinder(gluNewQuadric(), 1, 1, 1.65, 16, 8);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.4, -0.825, -1.65);
	glScaled(0.075, 0.075, 0.05);
	glutSolidSphere(1, 16, 16);
	glPopMatrix();
	

}

void TrainWagon::DrawWagon()
{
	//glutSolidCube(2);
	DrawColorCylinder(vector<double>{0.3, 0.9, 0.3}, 8);
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
