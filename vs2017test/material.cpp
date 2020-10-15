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

// Low Ground
float low_ground_ambient[4] = { 0.29125f, 0.3735f, 0.0225f, 1.0f };
float low_ground_diffuse[4] = { 0.3038f, 0.17048f, 0.0828f, 1.0f };
float low_ground_specular[4] = { 0.256777f, 0.137622f, 0.086014f, 1.0f };
float low_ground_shine = 1.8f;

// Ground
float ground_ambient[4] = { 0.09125f, 0.0935f, 0.0325f, 1.0f };
float ground_diffuse[4] = { 0.07038f, 0.28048f, 0.188f, 1.0f };
float ground_specular[4] = { 0.056777f, 0.037622f, 0.006014f, 1.0f };
float ground_shine = 0.8f;

// Sand
float sand_ambient[4] = { 0.44725f, 0.3895f, 0.2245f, 1.0f };
float sand_diffuse[4] = { 0.59164f, 0.37048f, 0.11648f, 1.0f };
float sand_specular[4] = { 0.828281f, 0.855802f, 0.766065f, 1.0f };
float sand_shine = 80.2f;

// High Ground
float high_ground_ambient[4] = { 0.16125f, 0.1535f, 0.1525f, 1.0f };
float high_ground_diffuse[4] = { 0.1338f, 0.46048f, 0.228f, 1.0f };
float high_ground_specular[4] = { 0.156777f, 0.137622f, 0.056014f, 1.0f };
float high_ground_shine = 12.8f;


// Snow
float snow_ambient[4] = { 0.7125f, 0.6735f, 0.9225f, 1.0f };
float snow_diffuse[4] = { 0.6038f, 0.67048f, 0.6828f, 1.0f };
float snow_specular[4] = { 0.956777f, 0.937622f, 0.66014f, 1.0f };
float snow_shine = 68.8f;

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

void SetLowGroundMaterial()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, low_ground_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, low_ground_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, low_ground_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, low_ground_shine);
}

void SetGroundMaterial()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ground_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ground_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ground_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, ground_shine);
}

void SetHighGroundMaterial()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, high_ground_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, high_ground_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, high_ground_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, high_ground_shine);
}

void SetSnowMaterial()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, snow_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, snow_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, snow_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, snow_shine);
}

void SetSandMaterial()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, sand_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, sand_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, sand_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, sand_shine);
}

