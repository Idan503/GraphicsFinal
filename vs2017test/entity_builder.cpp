#include "glut.h"
#include "globals.h"
#include "entity_builder.h"
#include "material.h"
#include "texture.h"

void DrawTrain() {

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
