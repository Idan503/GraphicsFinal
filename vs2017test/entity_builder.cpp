#include "glut.h"
#include "globals.h"
#include "entity_builder.h"
#include "material_manager.h"
#include "texture_manager.h"
#include "bridge.h"
#include "tree.h"
#include "TrainWagon.h"
#include <math.h>

const int WAGON_COUNT = 1; //excluding head

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
