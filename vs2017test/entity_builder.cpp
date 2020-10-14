#include "glut.h"
#include "globals.h"
#include "entity_builder.h"
#include "material.h"

void BuildTrain() {

	SetRedPlasticMaterial();

	glPushMatrix();
	glColor3d(0.2, 0.7, 0.1);
	glTranslated(6, 12, 0);
	glRotated(current_time * 100,1, 1,0);

	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();
	glColor3d(0.2, 0.4, 0.1);
	glTranslated(-6, 12, 0);
	glRotated(current_time * 100, 1, 1, 0);

	glutSolidSphere(4,20,20);

	glPopMatrix();
}
