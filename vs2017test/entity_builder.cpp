#include "glut.h"
#include "globals.h"
#include "entity_builder.h"
#include "material_manager.h"
#include "texture_manager.h"
#include "bridge.h"
#include "tree.h"
#include "TrainWagon.h"
#include <math.h>

const int WAGON_COUNT = 6; //excluding head

TrainWagon* train[WAGON_COUNT+1];

void InitTrain()  {
	int i;
	// define a car
	// we still have to compute diry
	
	
	for (i = 0; i < WAGON_COUNT+ 1; i++)
	{
		// First wagon is head, others are regular wagons
		train[i] = new TrainWagon(1, 0, 0, vector<double> {0, 0, -(double)ground_size / 2 + ((WAGON_COUNT+1.0-i) * 2.55)}, vector<double>{0,0,1}, 0,(i==0));
		train[i]->Move();
		train[i]->SetSpeed(train_speed);
	}
	
	//TESTING
	//train[0] = new TrainWagon(1, 0, 0, vector<double> {0, 0, 0}, vector<double>{0, 0, 1}, 0, true);
}


void DrawTrain() {

	for (int i = 0; i < WAGON_COUNT + 1; i++)
		train[i]->Draw();

	
	//TESTING
	/*
	glPushMatrix();

	glTranslated(0, 25, 0);
	glRotated(current_time * 140, 0, 1, 0);
	
	train[0]->Draw();

	glPopMatrix();
	*/
	
	
}

void MoveTrain() {
	//Disable for testing
	for (int i = 0; i < WAGON_COUNT + 1; i++)
		train[i]->Move();
}


void DrawBridge()
{
	DrawBridgeRoad();

	DrawBridgePoles(0.25);

	DrawBridgeArch();

	DrawBridgeInnerPoles();
}

void DrawTrees()
{
	//DrawTree();


	//Testing
	glPushMatrix();

	glTranslated(0, 25, 0);
	glRotated(current_time * 140, 0, 1, 0);

	DrawTree();

	glPopMatrix();
}


// A cam- filter for window - only used when viewing from window
// Creating the illusion that the viewer is inside the train
void DrawWindowFilter()
{
	glEnable(GL_BLEND);
	glPushMatrix();
	glTranslated(1.0225, 0, 0);
	glScaled(1, 50, ground_size * 2); // straching to all view
	glBegin(GL_POLYGON);

	glColor4d(train_window_color[0], train_window_color[1], train_window_color[2], train_window_color[3] - 0.125);
	glVertex3d(0, -1, -1);
	glVertex3d(0, -1, 1);
	glVertex3d(0, 1, 1);
	glVertex3d(0, 1, -1);

	glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);
}
