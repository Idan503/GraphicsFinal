#include "glut.h"
#include "globals.h"
#include "entity_builder.h"
#include "material_manager.h"
#include "texture_manager.h"
#include "TrainWagon.h"
#include <math.h>
#include <stdio.h>

int train_z = -ground_size / 2;
int train_x = ground_size/2;
double max_ground_height;
double bridge_width;
double bridge_final_height;
double bridge_curve_length;

const int WAGON_COUNT = 1; //excluding head

TrainWagon* train[WAGON_COUNT+1];


void InitTrain()  {
	int i;
	// define a car
	// we still have to compute diry
	/*
	for (i = 0; i < WAGON_COUNT+ 1; i++)
	{
		// First wagon is head, others are regular wagons
		train[i] = new TrainWagon(1, 0, 0, vector<double> {0, 0, -(double)ground_size / 2 + ((WAGON_COUNT+1-i) * 4)}, vector<double>{0,0,1}, 0,(i==0));
		train[i]->Move();
		train[i]->SetSpeed(train_speed);

	}
	*/

	//TESTING
	train[0] = new TrainWagon(1, 0, 0, vector<double> {0, 0, 0}, vector<double>{0, 0, 1}, 0, false);

}


void DrawTrain() {

	//for (int i = 0; i < WAGON_COUNT + 1; i++)
	//	train[i]->Draw();

	
	//TESTING
	glPushMatrix();

	glTranslated(0, 25, 0);
	glRotated(current_time * 140, 0, 1, 0);
	
	train[0]->Draw();

	glPopMatrix();
	
	
}

void MoveTrain() {
	//for (int i = 0; i < WAGON_COUNT + 1; i++)
	//	train[i]->Move();

}


void DrawBridge()
{
		
	bridge_width = rail_width + 0.6;
	
	DrawBridgeRoad();

	DrawBridgePoles(0.25);

	DrawBridgeArch();

	DrawBridgeInnerPoles();
	
}

void DrawBridgeArch()
{
	//curves z-
	glPushMatrix();
	glTranslated(bridge_width, bridge_final_height, -river_size + 1.5);
	glScaled(0.3, 0.3, 0.3);
	DrawBridgeCurve();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-bridge_width, bridge_final_height, -river_size + 1.5);
	glScaled(0.3, 0.3, 0.3);
	DrawBridgeCurve();
	glPopMatrix();

	//curves z+
	glPushMatrix();
	glTranslated(bridge_width, bridge_final_height, river_size - 1.5);
	glScaled(0.3, 0.3, -0.3);
	DrawBridgeCurve();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-bridge_width, bridge_final_height, river_size - 1.5);
	glScaled(0.3, 0.3, -0.3);
	DrawBridgeCurve();
	glPopMatrix();

	// main pole x-
	glPushMatrix();
	glTranslated(-bridge_width, bridge_final_height,0);
	glScaled(0.3, (CalcBridgeCurveHeight(bridge_curve_length) * 0.3) - bridge_height + 0.35, 0.5);
	DrawTexCube(34);
	glPopMatrix();

	// main pole x+
	glPushMatrix();
	glTranslated(bridge_width, bridge_final_height, 0);
	glScaled(0.3, (CalcBridgeCurveHeight(bridge_curve_length) * 0.3) - bridge_height + 0.35, 0.5);
	DrawTexCube(34);
	glPopMatrix();

	// road handle x+
	glPushMatrix();
	glTranslated(bridge_width, bridge_final_height, -river_size);
	glScaled(0.3, 0.3, river_size * 2.0);
	glRotated(90, 1, 0, 0);
	DrawTexCylinder(6,34,1);
	glPopMatrix();

	// road handle x-
	glPushMatrix();
	glTranslated(-bridge_width, bridge_final_height, -river_size);
	glScaled(0.3, 0.3, river_size * 2.0);
	glRotated(90, 1, 0, 0);
	DrawTexCylinder(6, 34, 1);
	glPopMatrix();


}

void DrawBridgeRoad()
{
	max_ground_height =
		fmax(fmax(ground[ground_size / 2 - river_size + 1][ground_size / 2], ground[ground_size / 2 - river_size][ground_size / 2]),
			fmax(ground[ground_size / 2 + river_size - 1][ground_size / 2], ground[ground_size / 2 + river_size][ground_size / 2]));
	bridge_final_height = max_ground_height + bridge_height;


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 20);

	glBegin(GL_POLYGON);
	// Road Texture under the rail
	glTexCoord2d(0, 1); glVertex3d(bridge_width, bridge_final_height, -river_size + 1.0);
	glTexCoord2d(bridge_width, 1); glVertex3d(bridge_width, bridge_final_height, river_size - 1.0);
	glTexCoord2d(bridge_width, 0); glVertex3d(-bridge_width, bridge_final_height, river_size - 1.0);
	glTexCoord2d(0, 0); glVertex3d(-bridge_width, bridge_final_height, -river_size + 1.0);


	glEnd();


	glDisable(GL_TEXTURE_2D);


}

void DrawBridgePoles(double thinkness)
{
	SetSilverMaterial();
	const double pole_line_margin = 0.5, pole_row_step = 3.5;
	// poles of the bridge

	SetSilverMaterial();
	double i;
	for (i = -river_size + pole_row_step; i <= river_size - 1.0; i += pole_row_step) {
		glPushMatrix();
		glTranslated(bridge_width - pole_line_margin, bridge_final_height, i);
		DrawBridgeSinglePole();
		glPopMatrix();
		glPushMatrix();
		glTranslated(-bridge_width + pole_line_margin, bridge_final_height, i);
		DrawBridgeSinglePole();
		glPopMatrix();
	}
}

void DrawBridgeSinglePole()
{
	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, 10);

	glPushMatrix();
	glRotated(90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 0.15, 0.15, 5, 20, 4);

	glPopMatrix();

	//glDisable(GL_TEXTURE_2D);

}

void DrawBridgeCurve()
{
	bridge_curve_length = 27.5;
	double step = 0.15;
	double z;

	//bridge curve function: f(x) = \frac{1}{20}e^{0.235x^{1.1}}\cdot e^{1.25}

	double beta, gamma = PI / 16;
	int counter;

	for (z = 0.0; z < bridge_curve_length; z += step)
	{
		double y = CalcBridgeCurveHeight(z);

		glPushMatrix();
		glTranslated(0, y,z);
		glRotated(z*3.5, 0, 1, 0);
		glScaled(0.75, 0.75, 0.75);
		DrawTexSphere(6,6,34,1,1);
		glPopMatrix();
	}
}

//returns the y of the f(x) curve:
//which is: f(x) = \frac{1}{20}e^{0.235x^{1.1}}\cdot e^{1.25}
double CalcBridgeCurveHeight(double x)
{
	return pow(E, 0.235 * pow(x, 0.78));
}

void DrawBridgeInnerPoles()
{
	const double inner_pole_size = 0.13;
	double x_mult, z_mult;

	for (x_mult = -1,0; x_mult <= 1; x_mult += 2.0)
	{
		for (z_mult = -1,0; z_mult <= 1; z_mult += 2.0)
		{
			glPushMatrix();
			glTranslated(x_mult * bridge_width, bridge_final_height, z_mult * river_size * 0.35);
			glScaled(inner_pole_size, 1, inner_pole_size);
			DrawTexCylinder(16, 34, 1);
			glPopMatrix();

			glPushMatrix();
			glTranslated(x_mult * bridge_width, bridge_final_height, z_mult * river_size * 0.225);
			glScaled(inner_pole_size, 2, inner_pole_size);
			DrawTexCylinder(16, 34, 1);
			glPopMatrix();

			glPushMatrix();
			glTranslated(x_mult * bridge_width, bridge_final_height, z_mult * river_size * 0.125);
			glScaled(inner_pole_size, 3, inner_pole_size);
			DrawTexCylinder(16, 34, 1);
			glPopMatrix();
		}
	}



}