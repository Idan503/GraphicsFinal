#include "glut.h"
#include "material.h"
#include <math.h>
#include "globals.h"


//region Light Definitions

float light_0_ambient[4] = { 0.2,0.2,0.2,0 };
float light_0_diffuse[4] = { 0.8,0.5,0.2,0 };
float light_0_specular[4] = { 0.5,0.5,0.5,0 };
float light_0_position[4] = { 0,10,0,1 }; // Last parameter is type (0=directional, 1=point)

float light_1_ambient[4] = { 0.2,0.2,0.2,0 };
float light_1_diffuse[4] = { 0.8,0.8,0.8,0 };
float light_1_specular[4] = { 0.7,0.7,0.7,0 };
float light_1_position[4] = { 1,1,1,0 }; // directional

//endregion

//region Material Definition


//Tin
float tin_ambient[4] = { 0.105882f, 0.058824f, 0.113725f, 1.0f };
float tin_diffuse[4] = { 0.427451f, 0.470588f, 0.541176f, 1.0f };
float tin_specular[4] = { 0.333333f, 0.333333f, 0.521569f, 1.0f };
float tin_shine = 9.84615f;

//Red Plastic
float red_plastic_ambient[4] = { 0.4,0.2,0.2,0 };
float red_plastic_diffuse[4] = { 0.9,0.0,0.0,0 };
float red_plastic_specular[4] = { 0.9,0.7,0.7,0 };
float red_plastic_shine = 32.0f;


//endregion

void InitLight()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_0_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_0_position);

	glLightfv(GL_LIGHT1, GL_AMBIENT, light_1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_1_diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, light_1_diffuse);

	glEnable(GL_NORMALIZE);

}

void SetTinMaterial()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, tin_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tin_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, tin_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, tin_shine);
}

void SetRedPlasticMaterial()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, red_plastic_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, red_plastic_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, red_plastic_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, red_plastic_shine);
}