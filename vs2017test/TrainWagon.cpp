#include "TrainWagon.h"
#include "glut.h"
#include "material_manager.h"
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
	// Drawing the train relative to rail's path
	double beta;
	glPushMatrix();
	glTranslated(position[0], position[1] + 1, position[2]);
	glScaled(0.65, 0.65, 0.65);
	// only when the motion is along X axis
	beta = -atan(direction[1]); // in rad
	glRotated(beta * 180 / PI, 1, 0, 0);

	if (head)
		DrawHeadWagon();
	else
		DrawRegularWagon();

	glPopMatrix();
}

	vector<double> color_red = { 0.65,0.3,0.3 };
	vector<double> color_grey = { 0.25,0.25,0.25 };
	vector<double> color_black = { 0,0,0};
	vector<double> color_white = { 1,1,1 };

void TrainWagon::DrawWheel() {


	// inside inner shpere
	glPushMatrix();
	glTranslated(-0.5, 0, 0);
	glScaled(0.55, 0.35, 0.35);
	glRotated(current_time * 330, 1, 0, 0);
	glRotated(90, 0, 0, 1);
	DrawColorSphere(color_black,16,16);
	glPopMatrix();

	// inside ring
	glPushMatrix();
	glRotated(current_time * 330, 1, 0, 0);
	glRotated(90, 0, 0, 1);
	DrawColorCylinder(color_red, 16);
	glPopMatrix();

	// inside tire 1
	glPushMatrix();
	glRotated(current_time * 330, 1, 0, 0);
	glRotated(90, 0,0, 1);
	DrawColorTire(12, 0.9,0.35,color_grey, 2);
	glPopMatrix();

	// inside tire 2
	glPushMatrix();
	glTranslated(-1, 0, 0);
	glRotated(current_time * 330, 1, 0, 0);
	glRotated(90, 0, 0, 1);
	DrawColorTire(12, 0.9, 0.35, color_grey,2);
	glPopMatrix();

	// outer ring
	glPushMatrix();
	glRotated(current_time * 330, 1, 0, 0);
	glRotated(90, 0, 0, 1);
	DrawColorCylinder(color_red, 16);
	glPopMatrix();

	//inner flat 1
	glPushMatrix();
	glTranslated(-0.1, 0, 0);
	glScaled(0.1, 1, 1);
	glRotated(current_time * 330, 1, 0, 0);
	glRotated(90, 0, 0, 1);
	DrawColorSphere(color_white, 16, 16);
	glPopMatrix();


	//inner flat 2
	glPushMatrix();
	glTranslated(-0.9, 0, 0);
	glScaled(0.1, 1, 1);
	glRotated(current_time * 330, 1, 0, 0);
	glRotated(90, 0, 0, 1);
	DrawColorSphere(color_white, 16, 16);
	glPopMatrix();

}

void TrainWagon::DrawHeadBase()
{
	//lower grey flat upper
	glPushMatrix();
	glScaled(1, 0.1, 2.5);
	DrawColorCube(color_grey);
	glPopMatrix();


	//lower flat 
	glPushMatrix();
	glTranslated(0, -0.2, 0.5);
	glScaled(1, 0.1, 2);
	DrawColorCube(color_grey);
	glPopMatrix();


	//back wheel holder
	glPushMatrix();
	glTranslated(0, -0.4, -0.75);
	glScaled(1, 0.1, 0.75);
	DrawColorCube(color_grey);
	glPopMatrix();


	//lower red flat
	glPushMatrix();
	glTranslated(0, 0.2, 0);
	glScaled(1, 0.1, 2.75);
	DrawColorCube(color_red);
	glPopMatrix();

	//tail holder x+
	glPushMatrix();
	glTranslated(0.75, -0.25, -2.25);
	glScaled(0.12, 0.15, 0.12);
	DrawColorCube(color_grey);
	glPopMatrix();

	//tail holder x-
	glPushMatrix();
	glTranslated(-0.75, -0.25, -2.25);
	glScaled(0.12, 0.15, 0.12);
	DrawColorCube(color_grey);
	glPopMatrix();

	// tail x+
	glPushMatrix();
	glTranslated(0.75, -0.25, -3);
	glScaled(0.1, 0.1, 0.65);
	glRotated(90, 1, 0, 0);
	DrawColorCylinder(color_grey, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.75, -0.25, -2.9);
	glScaled(0.15, 0.15, 0.15);
	DrawColorSphere(color_grey, 16, 16);
	glPopMatrix();

	// tail x-
	glPushMatrix();
	glTranslated(-0.75, -0.25, -3);
	glScaled(0.1, 0.1, 0.65);
	glRotated(90, 1, 0, 0);
	DrawColorCylinder(color_grey, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.75, -0.25, -2.9);
	glScaled(0.15, 0.15, 0.15);
	DrawColorSphere(color_grey, 16, 16);
	glPopMatrix();


	//front wheel grey holder
	glPushMatrix();
	glTranslated(0, -0.4, 2.1);
	glScaled(1, 0.1, 0.4);
	DrawColorCube(color_grey);
	glPopMatrix();


	//shock absorber
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glColor3d(0, 0, 0);
	glTranslated(0, 0.1, 2.5);
	glScaled(1, 0.7, 0.45);
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


	//tube x-
	glPushMatrix();
	glTranslated(-1, -0.35, 0.8);
	glScaled(0.2, 0.2, 0.75);
	glRotated(90, 1, 0, 0);
	DrawColorCylinder(color_black,16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-1, -0.35, 0.8);
	glScaled(0.2, 0.2, 0.05);
	DrawColorSphere(color_black, 16,16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-1, -0.35, 1.55);
	glScaled(0.2, 0.2, 0.05);
	DrawColorSphere(color_black, 16, 16);
	glPopMatrix();

	//tube x+
	glPushMatrix();
	glTranslated(1, -0.35, 0.8);
	glScaled(0.2, 0.2, 0.75);
	glRotated(90, 1, 0, 0);
	DrawColorCylinder(color_black, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(1, -0.35, 0.8);
	glScaled(0.2, 0.2, 0.05);
	DrawColorSphere(color_black, 16, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(1, -0.35, 1.55);
	glScaled(0.2, 0.2, 0.05);
	DrawColorSphere(color_black, 16, 16);
	glPopMatrix();


	//back wheels x+
	glPushMatrix();
	glTranslated(1.15, -0.45, -0.9);
	glScaled(0.475, 0.475, 0.475);
	DrawWheel();
	glPopMatrix();
	
	glPushMatrix();
	glTranslated(1.15, -0.45, 0.2);
	glScaled(0.475, 0.475, 0.475);
	DrawWheel();
	glPopMatrix();

	//front wheel x+
	glPushMatrix();
	glTranslated(1.15, -0.55, 2.1);
	glScaled(0.35, 0.35, 0.35);
	DrawWheel();
	glPopMatrix();



	//back wheels x-
	glPushMatrix();
	glTranslated(-1.15, -0.45, -0.9);
	glScaled(0.475, 0.475, 0.475);
	DrawWheel();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-1.15, -0.45, 0.2);
	glScaled(0.475, 0.475, 0.475);
	DrawWheel();
	glPopMatrix();

	//front wheel x-
	glPushMatrix();
	glTranslated(-1.15, -0.55, 2.1);
	glScaled(0.35, 0.35, 0.35);
	DrawWheel();
	glPopMatrix();

}

void TrainWagon::DrawHeadBody() {

	//tube
	glPushMatrix();
	glTranslated(0, 1, -0.75);
	glScaled(0.75, 0.75, 3.25);
	glRotated(90, 1, 0, 0);
	DrawColorCylinder(color_grey, 16);
	glPopMatrix();

	//tube lines
	glPushMatrix();
	glTranslated(0, 1, -0.2);
	glScaled(0.76, 0.76, 0.1);
	glRotated(90, 1, 0, 0);
	DrawColorCylinder(color_black, 16);
	glPopMatrix();

	//inner tubes
	glPushMatrix();
	glTranslated(0, 1, 0.75);
	glScaled(0.76, 0.76, 0.1);
	glRotated(90, 1, 0, 0);
	DrawColorCylinder(color_black, 16);
	glPopMatrix();

	//inner tubes
	glPushMatrix();
	glTranslated(0, 1, 2);
	glScaled(0.76, 0.76, 0.1);
	glRotated(90, 1, 0, 0);
	DrawColorCylinder(color_black, 16);
	glPopMatrix();

	//nose
	glPushMatrix();
	glTranslated(0, 1, 2.5);
	glScaled(0.75, 0.75, 0.3);
	glRotated(90, 1, 0, 0);
	DrawColorSphere(color_black, 16, 16);
	glPopMatrix();

	//red flat
	glPushMatrix();
	glTranslated(0, 0.5, 0.5);
	glScaled(1, 0.2, 1.25);
	glRotated(90, 1, 0, 0);
	DrawColorCube(color_black);
	glPopMatrix();

	//grey front flat
	glPushMatrix();
	glTranslated(0, 0.5, 2.1);
	glScaled(1, 0.2, 0.35);
	glRotated(90, 1, 0, 0);
	DrawColorCube(color_grey);
	glPopMatrix();

	//tank
	glPushMatrix();
	glTranslated(0, 1.5, -1.6);
	glScaled(1, 1.25, 0.85);
	glRotated(90, 1, 0, 0);
	DrawColorCube(color_red);
	glPopMatrix();

	//chimney
	glPushMatrix();
	glTranslated(0, 1.65, 1.65);
	glScaled(0.2, 1.25, 0.2);
	DrawColorCylinder(color_red,16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 1.7, 1.65);
	glScaled(0.3, 0.25, 0.23);
	DrawColorCylinder(color_red, 16);
	glPopMatrix();


	glPushMatrix();
	glTranslated(0, 2.85, 1.65);
	glScaled(0.25, 0.25, 0.25);
	DrawColorCylinder(color_red, 16, 1.65,1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 3.1, 1.65);
	glScaled(0.25, 0.25, 0.25);
	DrawColorCylinder(color_red, 16, 1.25, 1.65);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 3.15, 1.65);
	glScaled(0.25, 0.1, 0.25);
	DrawColorSphere(color_black, 16, 16);
	glPopMatrix();

	
	//bell
	glPushMatrix();
	glTranslated(0, 1.65, 0.35);
	glScaled(0.2, 0.55, 0.2);
	DrawColorCylinder(color_red, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 1.7, 0.35);
	glScaled(0.225, 0.2, 0.225);
	DrawColorCylinder(color_red, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 2.15, 0.35);
	glScaled(0.2, 0.2, 0.2);
	DrawColorSphere(color_black, 16,16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 2.35, 0.35);
	glScaled(0.05, 0.2, 0.05);
	DrawColorCylinder(color_red, 16);
	glPopMatrix();


	//light
	glPushMatrix();
	glTranslated(0, 2, 2.5);
	glScaled(0.3 , 0.3, 0.15);
	glRotated(90, 1, 0, 0);
	DrawColorCube(color_red);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 2, 2.65);
	glScaled(0.2, 0.2, 0.075);
	glRotated(90, 1, 0, 0);
	DrawColorSphere(color_black,16,16);
	glPopMatrix();

}


void TrainWagon::DrawRegularBase()
{
	//lower grey flat upper
	glPushMatrix();
	glScaled(1, 0.1, 2.5);
	DrawColorCube(color_grey);
	glPopMatrix();


	//lower flat 
	glPushMatrix();
	glTranslated(0, -0.2, 0.5);
	glScaled(1, 0.1, 2);
	DrawColorCube(color_grey);
	glPopMatrix();


	//back wheel holder
	glPushMatrix();
	glTranslated(0, -0.4, -0.95);
	glScaled(1, 0.1, 0.55);
	DrawColorCube(color_grey);
	glPopMatrix();


	//front wheel grey holder
	glPushMatrix();
	glTranslated(0, -0.4, 1.95);
	glScaled(1, 0.1, 0.55);
	DrawColorCube(color_grey);
	glPopMatrix();


	//lower red flat
	glPushMatrix();
	glTranslated(0, 0.2, 0);
	glScaled(1, 0.1, 2.75);
	DrawColorCube(color_red);
	glPopMatrix();

	//tail holder x+
	glPushMatrix();
	glTranslated(0.75, -0.25, -2.25);
	glScaled(0.12, 0.15, 0.12);
	DrawColorCube(color_grey);
	glPopMatrix();

	//tail holder x-
	glPushMatrix();
	glTranslated(-0.75, -0.25, -2.25);
	glScaled(0.12, 0.15, 0.12);
	DrawColorCube(color_grey);
	glPopMatrix();

	// tail x+
	glPushMatrix();
	glTranslated(0.75, -0.25, -3);
	glScaled(0.1, 0.1, 0.65);
	glRotated(90, 1, 0, 0);
	DrawColorCylinder(color_grey, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.75, -0.25, -2.9);
	glScaled(0.15, 0.15, 0.15);
	DrawColorSphere(color_grey, 16, 16);
	glPopMatrix();

	// tail x-
	glPushMatrix();
	glTranslated(-0.75, -0.25, -3);
	glScaled(0.1, 0.1, 0.65);
	glRotated(90, 1, 0, 0);
	DrawColorCylinder(color_grey, 16);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.75, -0.25, -2.9);
	glScaled(0.15, 0.15, 0.15);
	DrawColorSphere(color_grey, 16, 16);
	glPopMatrix();


	




	

}

void TrainWagon::DrawRegularBody() {

	//tank
	glPushMatrix();
	glTranslated(0, 1.45, 0);
	glScaled(1, 1.15, 2.5);
	glRotated(90, 1, 0, 0);
	DrawColorCube(color_red);
	glPopMatrix();

	//sing
	glPushMatrix();
	glTranslated(0, 0.85, 0);
	glScaled(1.05, 0.225, 1.4);
	glRotated(90, 1, 0, 0);
	DrawColorCube(color_black);
	glPopMatrix();

}


void TrainWagon::DrawHeadWagon()
{
	DrawHeadBase();
	DrawHeadBody();
}


void TrainWagon::DrawRegularWagon()
{
	DrawRegularBase();
	DrawRegularBody();
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
