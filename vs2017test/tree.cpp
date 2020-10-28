#include "tree.h"
#include <float.h>
#include <math.h>
#include "glut.h"
#include "globals.h"

float small_tree_height = 3;
float tree_height = 4;

int type_count = 4;

vector<double> brown = { 0.25,0.25,0.2 };
vector<double> green = { 0.25,0.8,0.2 };

void DrawTree(int type) {
	// Setting to regular tree if recieved unexpeted input
	int regular_tree_type = 1;
	if (type > type_count-1)
		type = regular_tree_type;
	if (type < 0)
		type = regular_tree_type;


	DrawLog(type);
	DrawBranches(type);
	DrawLeaves(type);
}


void DrawLog(int type)
{
	switch (type)
	{
	case 0:
		glPushMatrix();
		glScaled(0.125, small_tree_height, 0.125);
		DrawTexCylinder(14, 50, 1, 0.8, 1);

		glPopMatrix();

		break;
	case 1:
		glPushMatrix();

		glScaled(0.3, tree_height, 0.3);
		DrawTexCylinder(14, 50, 1, 0.3, 1);

		glPopMatrix();
		break;
	case 2:
		glPushMatrix();

		glScaled(0.5, tree_height, 0.5);
		DrawTexCylinder(14, 50, 1, 0.4, 1);

		glPopMatrix();
		break;
	default:
		//tree with no leaves
		glPushMatrix();
		glScaled(0.125, tree_height-0.5, 0.125);
		DrawTexCylinder(14, 50, 1, 0.2, 1);

		glPopMatrix();
		break;
	}

}


void DrawLeaves(int type)
{
	glEnable(GL_BLEND);
	switch (type)
	{
	case 0:
		glPushMatrix();
		glTranslated(0, 2.5, 0);
		glScaled(0.8, 1.55, 0.8);

		glPushMatrix();
		glTranslated(0, -0.35, 0);
		glScaled(0.6, 0.5, 0.6);
		DrawTexSphere(16, 16, 51, 6, 3);
		glPopMatrix();

		glPushMatrix();
		glTranslated(0, -0.125, 0);
		glScaled(0.75, 0.5, 0.75);
		DrawTexSphere(16, 16, 51, 4, 4);
		glPopMatrix();


		glPopMatrix();


		break;
	case 1:
		glPushMatrix();
		glTranslated(0, 3, 0);
		glScaled(0.8, 1.15, 0.8);

		//Inner leavves
		glPushMatrix();
		glScaled(0.75, 1, 0.75);
		DrawTexSphere(16, 16, 51, 4, 4);
		glPopMatrix();

		//Outer leavves
		glPushMatrix();
		DrawTexSphere(16, 16, 51, 4, 4);
		glPopMatrix();

		glPushMatrix();
		glTranslated(0, -0.65, 0);
		glScaled(1.45, 0.65, 1.45);
		DrawTexSphere(16, 16, 51, 6, 3);
		glPopMatrix();

		glPopMatrix();

	
		break;
	case 2:
		glPushMatrix();
		glTranslated(0, 3, 0);
		glScaled(0.8, 1.35, 0.8);

		//Inner leavves
		glPushMatrix();
		glTranslated(0, -0.25, 0);
		glScaled(0.95, 1.05, 0.95);
		DrawTexSphere(16, 16, 51, 4, 4);
		glPopMatrix();

		//Outer leavves
		glPushMatrix();
		glTranslated(0, 0.8, 0);
		glScaled(1, 0.6, 1);
		DrawTexSphere(16, 16, 51, 4, 4);
		glPopMatrix();

		glPushMatrix();
		glScaled(2.05, 1, 2.05);
		DrawTexSphere(16, 16, 51, 6, 3);
		glPopMatrix();

		glPopMatrix();

		break;
	default:
		break;
	}

	glDisable(GL_BLEND);
}


void DrawRoots(int type)
{
	glPushMatrix();
	glTranslated(0, -0.05, 0);

	int i;
	for (i = 0; i <= 3; i++) {
		glPushMatrix();
		glRotated(90.0 * i, 0, 1, 0);
		glRotated(10, 1, 0, 0);
		glRotated(90, 1, 0, 0);
		glScaled(0.2, tree_height / 4.5, 0.2);
		DrawColorCylinder(brown, 6, 0.15, 0.2);
		glPopMatrix();

		glPushMatrix();
		glRotated(20, 0, 1, 0);
		glRotated(90.0 * i, 0, 1, 0);
		glRotated(20, 1, 0, 0);
		glRotated(90, 1, 0, 0);
		glScaled(0.1, tree_height / 8, 0.1);
		DrawColorCylinder(brown, 6, 0.15, 0.2);
		glPopMatrix();

	}

	glPopMatrix();
}


void DrawBranches(int type)
{
	double current_tree_height = tree_height;
	if (type == 0)
		current_tree_height = small_tree_height;
	
	double y;
	double branch_step = 0.075 * current_tree_height;

	for (y = current_tree_height * 0.45; y <= current_tree_height - 2 * branch_step; y += branch_step) {

		if (type==0 && y <= current_tree_height * 0.65) {
			//edge case prevent small tree outer brench
			glPushMatrix();
			glTranslated(0, y, 0);
			glScaled(0.15, 0.15, 0.15);
			glRotated(5 * (y * 1), 1, 0, 0);
			glRotated(41 * (y * 7.5), 0, 1, 0);
			DrawSignleBranch(y);
			glPopMatrix();
		}
		else {
			glPushMatrix();
			glTranslated(0, y, 0);
			if (type == 0) // smaller branches for small tree
				glScaled(0.6, 0.6, 0.6);

			glRotated(5 * (y * 1), 1, 0, 0);
			glRotated(41 * (y * 7.5), 0, 1, 0);
			DrawSignleBranch(y);
			glPopMatrix();
		}
	}

}

void DrawSignleBranch(double y, int level)
{
	if (level <= 0)
		return;

	glPushMatrix();

	if (level != 3)
	{
		//sub-branch
		glTranslated(0, (1 - (y/tree_height)) * 0.1, 0);
		glTranslated(0, 0, (1 - (y/tree_height)) *(fabs(level - 1.0)/5.0) + 0.15);
		glRotated(-35 * (0.5 - level), 0, 1, 0);
		glRotated(55 * (1.0-level + (y / tree_height)), 1, 0, 0);
		glScaled((double) level / 4.0 , (double)level / 4.0, (double)level /4.0);
	}


	glScaled(0.05, 0.05, (tree_height-y) * 2 / tree_height);
	glRotated(90, 1, 0, 0);
	DrawTexCylinder(5,50,1,true);
	glPopMatrix();

	DrawSignleBranch(y, level-1);
	DrawSignleBranch(y+1.5, level - 2);

}

