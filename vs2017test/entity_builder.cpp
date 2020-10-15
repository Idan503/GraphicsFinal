#include "glut.h"
#include "globals.h"
#include "entity_builder.h"
#include "material.h"
#include "texture.h"

void BuildTrain() {

	SetRedPlasticMaterial();

	glPushMatrix();
	glTranslated(6, 12, 0);
	glRotated(current_time * 100,1, 1,0);

	glutSolidCube(4);

	glPopMatrix();

	glPushMatrix();
	glTranslated(-6, 12, 0);
	glRotated(current_time * 100, 1, 1, 0);

	glutSolidSphere(4,20,20);

	glPopMatrix();
}
