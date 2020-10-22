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
	train[0] = new TrainWagon(1, 0, 0, vector<double> {0, 0, 0}, vector<double>{0, 0, 1}, 0, true);

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

	// upper arch
	glPushMatrix();
	glScaled(1, 1, 1);
	DrawBridgeCurve();
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
	int curve_width = 25;
	double step = 0.02;
	double x;


	//f(x) of the bridge curve: f(x) = 0.00001x^{1.7e}

	double beta, gamma = PI / 16;
	int counter;

	for (x = 0.0; x < curve_width; x += step)
	{
		double y = pow(10, -5) * pow(x, 1.7 * E);

		glPushMatrix();
		glTranslated(0, y,x);
		glRotated(x*3.5, 0, 1, 0);
		glScaled(1, 1, 1);
		DrawColorCylinder(vector<double>{1, 1, 1}, 16);
		glPopMatrix();
	}

}