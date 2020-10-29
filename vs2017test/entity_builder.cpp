#include "glut.h"
#include "globals.h"
#include "entity_builder.h"
#include "material_manager.h"
#include "texture_manager.h"
#include "bridge.h"
#include "tree.h"
#include <time.h>
#include "TrainWagon.h"
#include <math.h>
#include "SmokeParticle.h"
#include "sound_manager.h"


const int WAGON_COUNT = 6; //excluding head
const int SMOKE_PARTICLES_COUNT = 10;
const float tree_rate = 0.0045; // % rate of a tree in a ground cell

TrainWagon* train[WAGON_COUNT+1];

SmokeParticle* smoke[SMOKE_PARTICLES_COUNT];
double smoke_random_strength = 4.5;
int next_to_emit = 0;
double TRAIN_SOUND_CAMERA_MAX_RANGE = 27.5; // The max range from train center that would trigger sound of train

vector < vector < float >> tree_chance;

void InitTrain()  {
	int i;
	// define a car
	// we still have to compute diry
	
	for (i = 0; i < WAGON_COUNT+ 1; i++)
	{
		// First wagon is head, others are regular wagons
		train[i] = new TrainWagon(vector<double> {0, 0, -(double)ground_size / 2 + ((WAGON_COUNT+1.0-i) * 2.55)}, vector<double>{0,0,1}, 0,(i==0));
		train[i]->Move();
		train[i]->SetSpeed(train_speed);
	}
	
	
	//TESTING
	//train[0] = new TrainWagon(1, 0, 0, vector<double> {0, 0, 0}, vector<double>{0, 0, 1}, 0, false);
}

void EmitSingleSmoke(int emit_index)
{

	vector<double> head_pos = train[0]->GetPosition();
	vector<double> head_dir = train[0]->GetDirection();
	vector<double> origin = { head_pos[0],head_pos[1] + 2 + 0.5*sin(head_dir[1]), head_pos[2] + 0.735 - 2* 0.735 *sin(head_dir[1])};
	// Origin is the top of train head's chimney
	if(smoke_random_strength!=0){
		// not all smoke particles are randomized
		smoke[emit_index]->RandomizeAttrs(smoke_random_strength);
	}
	
	smoke[emit_index]->Emit(origin);

	if (emit_index == SMOKE_PARTICLES_COUNT - 1) {
		smoke_random_strength = 0; // all have been randomized
	}

}

void InitSmoke()
{
	int i;
	for (i = 0; i < SMOKE_PARTICLES_COUNT; i++)
	{
		smoke[i] = new SmokeParticle(vector<double>{0, 1, 0.55},0.03,0.005,0.2,0.45,225);
	}

	InitSmokeEmitTimer(0);

}

void InitSmokeEmitTimer(int i)
{
	int final_time;
	for (i = 0; i < 1500; i++) {

		int delay = i * 500 + (rand() % 2000);
		glutTimerFunc(delay, EmitSingleSmoke, next_to_emit);

		if (i == 1499)
			final_time = delay; // last iteration

		next_to_emit++;
		if (next_to_emit == SMOKE_PARTICLES_COUNT) {
			next_to_emit = 0;
		}
	}

	glutTimerFunc(final_time, InitSmokeEmitTimer, 0); //infinite smoke
}

bool IsCameraCloseToTrain()
{
	vector<double> train_center = train[WAGON_COUNT / 2]->GetPosition();

	double distance = pow((pow(eyex - train_center[0], 2)) + (pow(eyey - train_center[1], 2)) + (pow(eyez - train_center[2], 2)), 0.5);
	return distance < TRAIN_SOUND_CAMERA_MAX_RANGE;
}


void InitTrees()
{
	// a random matrix for chance between 0 and 1 for each ground cell
	tree_chance.resize(ground_size);
	int j;
	for (j = 0; j < ground_size; j++)
	{
		tree_chance[j].resize(ground_size);
	}

	int i;
	for(i = 0; i < ground_size; i++)
	{
		for (j = 0; j < ground_size; j++) {
			float rnd_num = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			tree_chance[i][j] = rnd_num;

		}
	}

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

void CheckAndPlayTrainSound(int i)
{
	bool should_play = IsCameraCloseToTrain();
	if (should_play) {
		if (!train_sound_playing)
			PlayTrainSound(0);
	}
	else {
		StopSound(0);
	}
	
}

void MoveTrain() {
	//Disable for testing
	for (int i = 0; i < WAGON_COUNT + 1; i++)
		train[i]->Move();


	CheckAndPlayTrainSound(0);
}


void DrawSmoke()
{
	for (int i = 0; i < SMOKE_PARTICLES_COUNT; i++)
		smoke[i]->Draw();
}

void MoveSmoke()
{
	for (int i = 0; i < SMOKE_PARTICLES_COUNT; i++)
		smoke[i]->Move();
}

void DrawSky()
{
	glPushMatrix();
	glRotated(current_time * -5, 0, 1, 0);
	glScaled(150, 150, 150);
	DrawTexSphere(32, 32, 60, 1, 1, true);

	glPopMatrix();
}

void DrawSingleRock()
{


	glPushMatrix();
	glTranslated(0, -0.2, 0);
	glScaled(1.25, 0.5, 0.7);
	DrawTexSphere(16, 16, 1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -0.15, 0);
	glScaled(1.35, 0.6, 0.85);
	DrawTexSphere(16, 16, 1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.7, -0.71, 1);
	glScaled(1.4, 0.7, 0.6);
	DrawTexSphere(16, 16, 1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.4, -0.95, -1.4);
	glScaled(1, 0.25, 0.33);
	DrawTexSphere(16, 16, 1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.2, -0.5, -0.9);
	glScaled(0.2, 0.3, 0.33);
	DrawTexSphere(16, 16, 1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-2.2, -1.25, 0.2);
	glScaled(0.55, 0.3, 0.4);
	DrawTexSphere(16, 16, 1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-1.2, -0.81, 1.2);
	glScaled(0.3, 0.005, 0.305);
	DrawTexSphere(8, 8, 1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.3, -0.91, 0.8);
	glScaled(0.3, 0.015, 0.4);
	DrawTexSphere(8, 12, 1, 1, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.7, -0.41, +1.1);
	glScaled(0.2, 0.5, 0.65);
	DrawTexSphere(8, 12, 1, 1, 1);
	glPopMatrix();
}

void DrawRocks()
{

	double x, z;
	for (z = -ground_size / 2 + 1.0; z < ground_size / 2 - 1.0; z++)
		for (x = -ground_size / 2 + 1.0; x < ground_size / 2 - 1.0; x++)
		{
			int j = x + ground_size / 2;
			int i = z + ground_size / 2;


			bool draw_here = tree_chance[i][j] > tree_rate && tree_chance[i][j] < tree_rate * 1.25;
			//less rocks then trees, not in the same place

			if (ground[i][j] > 0 && draw_here && fabs(x) > 3 && fabs(z) > river_size + 3.0) {
				// we should draw a rock here, it is not under the sea and not close to rail/river
				glPushMatrix();
				glTranslated(x, ground[i][j], z);
				glRotated((int)(360 * (float)(tree_chance[i][j]) / tree_rate), 0, 1, 0);

				DrawSingleRock();
				glPopMatrix();
			}

		}
}

void DrawBridge()
{
	DrawBridgeRoad();

	DrawBridgePoles(0.25);

	DrawBridgeArch();

	DrawBridgeInnerPoles();
}

// creating type id base on terrain cordinates
int GenerateTreeType(int i, int j)
{
	int type;
	type = (int)(1.0 / tree_chance[i][j]) % 4;
	if (ground[i][j] > snow_height && (type == 2 || type==1))
		type = 3; // more non-leaves trees on snow, no large trees on snow
	else
		if (type == 3)
			type = 2; // regular trees instead of non-leaves on regular terrain (no snow)
	return type;
}

void DrawTrees()
{
	
	double x, z;
	for(z=-ground_size/2 + 1.0;z<ground_size/2 -1.0;z++)
		for (x = -ground_size / 2 + 1.0; x < ground_size / 2 -1.0 ; x++)
		{
			int j = x + ground_size / 2;
			int i = z + ground_size / 2;


			bool draw_here = tree_chance[i][j] < tree_rate;

			if (ground[i][j]>0 && draw_here && fabs(x) > 3 && fabs(z) > river_size + 3.0) {
				// we should draw a tree here, it is not under the sea and not close to rail/river
				glPushMatrix();
				glTranslated(x, ground[i][j] - 0.2, z);
				glRotated((int)(360* (float)(tree_chance[i][j]) / tree_rate), 0, 1,0);

				int type = GenerateTreeType(i, j);

				DrawTree(type);
				glPopMatrix();
			}

		}

}


// A cam- filter for window - only used when viewing from window
// Creating the illusion that the viewer is inside the train
void DrawWindowFilter()
{
	glEnable(GL_BLEND);
	glPushMatrix();
	glTranslated(1.0225, 0, 0);
	glScaled(1, 50, ground_size * 2.0); // straching to all view
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
