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

const int WAGON_COUNT = 6; //excluding head
const int SMOKE_PARTICLES_COUNT = 10;
const float tree_rate = 0.0045; // % rate of a tree in a ground cell

TrainWagon* train[WAGON_COUNT+1];

SmokeParticle* smoke[SMOKE_PARTICLES_COUNT];
int next_to_emit = 0;

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
	vector<double> origin = { head_pos[0],head_pos[1] + 2, head_pos[2] + 0.7 };
	// Origin is the top of train head's chimney
	smoke[emit_index]->RandomizeAttrs(4.5);
	smoke[emit_index]->Emit(origin);
}

void InitSmoke()
{
	int i;
	for (i = 0; i < SMOKE_PARTICLES_COUNT; i++)
	{
		smoke[i] = new SmokeParticle(vector<double>{0, 1, 0.55},0.03,0.005,0.2,0.45,225);
	}

	for (i = 0; i < 1000; i++) {
		glutTimerFunc(i*750 + (rand()%2500), EmitSingleSmoke, next_to_emit);

		next_to_emit++;
		if (next_to_emit == SMOKE_PARTICLES_COUNT)
			next_to_emit = 0;
	}
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

void MoveTrain() {
	//Disable for testing
	for (int i = 0; i < WAGON_COUNT + 1; i++)
		train[i]->Move();
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

void DrawBridge()
{
	DrawBridgeRoad();

	DrawBridgePoles(0.25);

	DrawBridgeArch();

	DrawBridgeInnerPoles();
}

void DrawTrees()
{
	
	double x, z;
	for(z=-ground_size/2;z<ground_size/2;z++)
		for (x = -ground_size / 2; x < ground_size / 2; x++)
		{
			int j = x + ground_size / 2;
			int i = z + ground_size / 2;


			bool draw_here = tree_chance[i][j] < tree_rate;

			if (ground[i][j]>0 && draw_here && fabs(x) > 3 && fabs(z) > river_size + 3.0) {
				// we should draw a tree here, it is not under the sea and not close to rail/river
				glPushMatrix();
				glTranslated(x, ground[i][j] - 0.2, z);
				glRotated((int)(360* (float)(tree_chance[i][j]) / tree_rate), 0, 1,0);
				DrawTree();
				glPopMatrix();
			}

		}




	//Testing
	/*
	glPushMatrix();

	glTranslated(0, 25, 0);
	glRotated(current_time * 140, 0, 1, 0);

	DrawTree();

	glPopMatrix();
	*/
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
