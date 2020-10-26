#include "tree.h"
#include <float.h>
#include <math.h>
#include "glut.h"
#include "globals.h"


float tree_height = 4;

vector<double> brown = { 0.25,0.25,0.2 };
vector<double> green = { 0.25,0.8,0.2 };

void DrawTree() {
	DrawLog();
	DrawBranches();
	//DrawRoots();
	//DrawLeaves();
}


void DrawLog()
{
	glPushMatrix();
	
	glScaled(0.3, tree_height, 0.3);
	DrawColorCylinder(brown, 16, 0.5, 0.8);

	glPopMatrix();
}

void DrawLeaves()
{
	glEnable(GL_BLEND);
	glPushMatrix();
	

	glTranslated(0, 3, 0);
	glScaled(0.8, 1.35, 0.8);
	//Inner leaves
	glPushMatrix();
	glRotated(75, 1, 1, 1);
	glScaled(0.8, 0.8, 0.8);
	DrawTexSphere(32, 32, 51, 4, 4);
	glPopMatrix();

	//Outer leavves
	glPushMatrix();
	DrawTexSphere(32, 32, 51, 4, 4);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -0.5, 0);
	glScaled(1.45, 0.5, 1.45);
	DrawTexSphere(32, 32, 51, 6, 2);
	glPopMatrix();

	glPopMatrix();

	glDisable(GL_BLEND);
}

void DrawRoots()
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
		DrawColorCylinder(brown, 16, 0.15, 0.2);
		glPopMatrix();

		glPushMatrix();
		glRotated(20, 0, 1, 0);
		glRotated(90.0 * i, 0, 1, 0);
		glRotated(20, 1, 0, 0);
		glRotated(90, 1, 0, 0);
		glScaled(0.1, tree_height / 8, 0.1);
		DrawColorCylinder(brown, 16, 0.15, 0.2);
		glPopMatrix();

	}

	glPopMatrix();
}


void DrawBranches()
{
	double y;
	double branch_step = 0.075 * tree_height;

	for (y = tree_height * 0.45; y <= tree_height - 2 * branch_step; y += branch_step) {

		glPushMatrix();
		glTranslated(0, y, 0);
		glRotated(5 * (y * 1), 1, 0, 0);
		glRotated(128 * (y * 10), 0, 1, 0);
		DrawSignleBranch(y);
		glPopMatrix();
	}

}

void DrawSignleBranch(double y, int level)
{
	if (level == 0)
		return;

	glPushMatrix();

	if (level != 3)
	{
		//sub-branch
		glTranslated(0, (1 - (y/tree_height)) * 0.1, 0);
		glTranslated(0, 0, (1 - (y/tree_height)) *(fabs(level - 1.0)/5.0) + 0.5);
		glRotated(-35 * (0.5 - level), 0, 1, 0);
		glRotated(55 * (1.0-level + (y / tree_height)), 1, 0, 0);
		glScaled((double) level / 4.0 , (double)level / 4.0, (double)level /4.0);
	}


	glScaled(0.05, 0.05, (tree_height-y) * 2 / tree_height);
	glRotated(90, 1, 0, 0);
	DrawColorCylinder(brown, 16);
	glPopMatrix();

	DrawSignleBranch(y, level-1);
	DrawSignleBranch(y+1.5, level - 1);

}

