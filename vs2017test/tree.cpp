#include "tree.h"
#include <float.h>
#include <math.h>
#include "glut.h"
#include "globals.h"


float height = 3;

vector<double> brown = { 0.25,0.25,0.2 };
vector<double> green = { 0.25,0.8,0.2 };

void DrawTree() {
	DrawLog();
	DrawBranches();
	DrawRoots();
}


void DrawLog()
{
	glPushMatrix();
	
	glScaled(0.3, height, 0.3);
	DrawColorCylinder(brown, 16, 0.5, 1);

	glPopMatrix();
}

void DrawRoots()
{


	int i;
	for (i = 0; i <= 3; i++) {
		glPushMatrix();
		glRotated(90.0 * i, 0, 1, 0);
		glRotated(10, 1, 0, 0);
		glRotated(90, 1, 0, 0);
		glScaled(0.3, height / 4.5, 0.3);
		DrawColorCylinder(brown, 16, 0.15, 0.2);
		glPopMatrix();
	}
}


void DrawBranches()
{
	int i;

	glPushMatrix();
	glTranslated(0, 3*height/5, -1.5);
	glScaled(0.2, 0.2, 3);
	glRotated(90, 1, 0, 0);
	DrawColorCylinder(green, 16);
	glPopMatrix();


	glPushMatrix();
	glTranslated(-1.5, 3 * height / 5, 0);
	glRotated(90, 0, 1, 0);
	glScaled(0.2, 0.2, 3);
	glRotated(90, 1, 0, 0);
	DrawColorCylinder(green, 16);
	glPopMatrix();

	
}

