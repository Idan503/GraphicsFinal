#include "glut.h"
#include "globals.h"
#include "entity_builder.h"
#include "material.h"
#include "texture.h"
#include "TrainWagon.h"
#include <stdio.h>

int train_z = -ground_size / 2;
int train_x = ground_size/2;
double max_ground_height;
double bridge_width;
double bridge_final_height;

const int WAGON_COUNT = 0; //excluding head

TrainWagon* train[WAGON_COUNT+1];


void InitTrain()  {
	int i;
	// define a car
	// we still have to compute diry
	for (i = 0; i < WAGON_COUNT+ 1; i++)
	{
		// First wagon is head, others are regular "wagons"
		//train[i] = new TrainWagon(1, 0, 0, vector<double> {0, 0, -(double)ground_size / 2 + ((WAGON_COUNT+1-i) * 4)}, vector<double>{0,0,1}, 0,(i==0));
		//train[i]->Move();
		//train[i]->SetSpeed(train_speed);

		train[i] = new TrainWagon(1, 0, 0, vector<double> {0, 0, 0}, vector<double>{0,0,1}, 0, false);
	}

}


void DrawTrain() {

	//for (int i = 0; i < WAGON_COUNT + 1; i++)
	//	train[i]->Draw();

	glPushMatrix();

	glTranslated(0, 25, 0);
	glRotated(current_time * 140, 0, 1, 0);
	
	for (int i = 0; i < WAGON_COUNT + 1; i++)
		train[i]->Draw();

	glPopMatrix();

	
}

void MoveTrain() {
	//for (int i = 0; i < WAGON_COUNT + 1; i++)
	//	train[i]->Move();

}


void DrawFence()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 2);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glPushMatrix();


	glTranslated(0, 15, 0);

	glBegin(GL_POLYGON);

	glTexCoord2d(0, 0); glVertex3d(-10, 0, 0);
	glTexCoord2d(0, 1); glVertex3d(-10, 10, 0);
	glTexCoord2d(1, 1); glVertex3d(10, 10, 0);
	glTexCoord2d(1, 0); glVertex3d(10, 0, 0);

	glEnd();

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);

}

void DrawBridge()
{
	bridge_width = rail_width + 0.6;
	
	 max_ground_height =
		fmax(fmax(ground[ground_size / 2 - river_size + 1][ground_size / 2], ground[ground_size / 2 - river_size][ground_size / 2]),
			fmax(ground[ground_size / 2 + river_size - 1][ground_size / 2], ground[ground_size / 2 + river_size][ground_size / 2]));
	bridge_final_height = max_ground_height + bridge_height;


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 2);

	glBegin(GL_POLYGON);
	// Road Texture under the rail
	glTexCoord2d(0,1); glVertex3d(bridge_width, bridge_final_height, -river_size+1.0);
	glTexCoord2d(bridge_width, 1); glVertex3d(bridge_width, bridge_final_height,river_size-1.0);
	glTexCoord2d(bridge_width, 0); glVertex3d(-bridge_width, bridge_final_height,river_size-1.0);
	glTexCoord2d(0, 0); glVertex3d(-bridge_width, bridge_final_height,-river_size+1.0);


	glEnd();


	glDisable(GL_TEXTURE_2D);

	DrawBridgePoles(0.25);
	

	// upper arch
	glPushMatrix();
	glTranslated(-bridge_width + 0.2, bridge_final_height, 0);
	glScaled(1.6, 1.6, 1.6);
	DrawBridgeArch(0.06);

	glPopMatrix();

	glPushMatrix();
	glTranslated(bridge_width - 0.2, bridge_final_height, 0);
	glScaled(1.6, 1.6, 1.6);
	DrawBridgeArch(0.06);

	glPopMatrix();



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
	//glBindTexture(GL_TEXTURE_2D, 1);

	glPushMatrix();
	glRotated(90, 1, 0, 0);
	gluCylinder(gluNewQuadric(), 0.15, 0.15, 5, 20, 4);

	glPopMatrix();

	//glDisable(GL_TEXTURE_2D);

}

void DrawBridgeArch(double thickness)
{
	DrawHalfBridgeArch(thickness);

	glPushMatrix();

	glScaled(1, 1, -1);
	DrawHalfBridgeArch(thickness);

	glPopMatrix();

}

// The bridge arc is symetric, so we draw each half seperatly
void DrawHalfBridgeArch(double thickness)
{

	//DrawTexSphere for connection spherres
	glPushMatrix();
	glTranslated(0, 1.5, -5.5);
	glRotated(90, 1, 0, 0);
	SetRubyMaterial();
	gluSphere(gluNewQuadric(), thickness * 1.6, 8, 8);
	SetSilverMaterial();
	gluCylinder(gluNewQuadric(), thickness, thickness, 1.5, 8, 4);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 2.4, 0.341 - 5.5);
	glRotated(110, 1, 0, 0);
	SetRubyMaterial();
	gluSphere(gluNewQuadric(), thickness * 1.6, 8, 8);
	SetSilverMaterial();
	gluCylinder(gluNewQuadric(), thickness, thickness, 1, 8, 4);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 3.1, 0.95 - 5.5);
	glRotated(130, 1, 0, 0);
	SetRubyMaterial();
	gluSphere(gluNewQuadric(), thickness * 1.6, 8, 8);
	SetSilverMaterial();
	gluCylinder(gluNewQuadric(), thickness, thickness, 1, 8, 4);
	glPopMatrix();


	glPushMatrix();
	glTranslated(0, 3.7, 2 - 5.5);
	glRotated(150, 1, 0, 0);
	SetRubyMaterial();
	gluSphere(gluNewQuadric(), thickness * 1.6, 8, 8);
	SetSilverMaterial();
	gluCylinder(gluNewQuadric(), thickness, thickness, 1.25, 8, 4);
	glPopMatrix();


	glPushMatrix();
	glTranslated(0, 3.97, 3.45 - 5.5);
	glRotated(170, 1, 0, 0);
	SetRubyMaterial();
	gluSphere(gluNewQuadric(), thickness * 1.6, 8, 8);
	SetSilverMaterial();
	gluCylinder(gluNewQuadric(), thickness, thickness, 1.5, 8, 4);
	glPopMatrix();


	glPushMatrix();
	glTranslated(0, 3.985, 0);
	glRotated(180, 1, 0, 0);
	SetSilverMaterial();
	gluCylinder(gluNewQuadric(), thickness, thickness, 2.1, 8, 4);
	glPopMatrix();

}
