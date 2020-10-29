#include "glut.h"
#include "material_manager.h"
#include <math.h>
#include "globals.h"


//region Light Definitions

float light_0_ambient[4] = { 0.2,0.2,0.2,0 };
float light_0_diffuse[4] = { 0.8,0.5,0.2,0 };
float light_0_specular[4] = { 0.5,0.5,0.5,0 };
float light_0_position[4] = { 0,30,0,1 }; // Last parameter is type (0=directional, 1=point)

float light_1_ambient[4] = { 0.2,0.2,0.2,0 };
float light_1_diffuse[4] = { 0.8,0.8,0.8,0 };
float light_1_specular[4] = { 0.7,0.7,0.7,0 };
float light_1_position[4] = { 0,1,0,0 }; // directional



//endregion

//region Material Definition


//Silver
float silver_ambient[4] = { 0.25225f, 0.25225f, 0.25225f, 1.0f };
float silver_diffuse[4] = { 0.60754f, 0.60754f, 0.60754f, 1.0f };
float silver_specular[4] = { 0.708273f, 0.708273f, 0.708273f, 1.0f };
float silver_shine = 180.84615f;

//Red Plastic
float red_plastic_ambient[4] = { 0.4,0.2,0.2,0 };
float red_plastic_diffuse[4] = { 0.9,0.0,0.0,0 };
float red_plastic_specular[4] = { 0.9,0.7,0.7,0 };
float red_plastic_shine = 32.0f;

//Ruby
float ruby_ambient[4] = { 0.1745f, 0.01175f, 0.01175f, 0.55f };
float ruby_diffuse[4] = { 0.41424f, 0.03136f, 0.01136f, 0.55f };
float ruby_specular[4] = { 0.627811f, 0.426959f, 0.426959f, 0.55f };
float ruby_shine = 89.8f;

// Under Ground (Under the water)
float under_ground_ambient[4] = { 0.29125f, 0.3735f, 0.0225f, 1.0f };
float under_ground_diffuse[4] = { 0.3038f, 0.17048f, 0.0828f, 1.0f };
float under_ground_specular[4] = { 0.256777f, 0.137622f, 0.086014f, 1.0f };
float under_ground_shine = 1.8f;

// Low Ground
float low_ground_ambient[4] = { 0.06125f, 0.04135f, 0.0525f, 1.0f };
float low_ground_diffuse[4] = { 0.07038f, 0.3048f, 0.0888f, 1.0f };
float low_ground_specular[4] = { 0.026777f, 0.037622f, 0.006014f, 1.0f };
float low_ground_shine = 1.0f;


// Half grass half sand
float grassand_ambient[4] = { 0.33725f, 0.4295f, 0.1745f, 1.0f };
float grassand_diffuse[4] = { 0.37164f, 0.32048f, 0.13648f, 1.0f };
float grassand_specular[4] = { 0.4728281f, 0.555802f, 0.426065f, 1.0f };
float grassand_shine = 30.0f;

// Ground
float ground_ambient[4] = { 0.09125f, 0.0935f, 0.0325f, 1.0f };
float ground_diffuse[4] = { 0.07038f, 0.28048f, 0.188f, 1.0f };
float ground_specular[4] = { 0.056777f, 0.037622f, 0.006014f, 1.0f };
float ground_shine = 0.8f;

// Sand
float sand_ambient[4] = { 0.44725f, 0.4195f, 0.2245f, 1.0f };
float sand_diffuse[4] = { 0.55164f, 0.33048f, 0.17648f, 1.0f };
float sand_specular[4] = { 0.628281f, 0.685802f, 0.466065f, 1.0f };
float sand_shine = 80.2f;

// High Ground
float high_ground_ambient[4] = { 0.3f,0.35f,0.3f, 1.0f };
float high_ground_diffuse[4] = { 0.15f,0.35f,0.15f, 1.0f };
float high_ground_specular[4] = { 0.15f,0.35f,0.15f, 1.0f };
float high_ground_shine = 12.8f;

// Snow
float snow_ambient[4] = { 0.7125f, 0.6735f, 0.9225f, 1.0f };
float snow_diffuse[4] = { 0.6038f, 0.67048f, 0.6828f, 1.0f };
float snow_specular[4] = { 0.956777f, 0.937622f, 0.66014f, 1.0f };
float snow_shine = 68.8f;

// Bridge
float bridge_ambient[4] = { 0.8125f, 0.7735f, 0.85225f, 1.0f };
float bridge_diffuse[4] = { 0.6538f, 0.66048f, 0.8828f, 1.0f };
float bridge_specular[4] = { 0.956777f, 0.937622f, 0.76014f, 1.0f };
float bridge_shine = 120.8f;

// Bridge accent
float bridge_accent_ambient[4] = { 0.9125f, 0.8735f, 0.85225f, 1.0f };
float bridge_accent_diffuse[4] = { 0.8538f, 0.86048f, 0.8828f, 1.0f };
float bridge_accent_specular[4] = { 0.956777f, 0.937622f, 0.76014f, 1.0f };
float bridge_accent_shine = 220.8f;

//endregion

void InitLight()
{
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

void SetSilverMaterial()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, silver_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, silver_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, silver_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, silver_shine);
}

void SetRedPlasticMaterial()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, red_plastic_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, red_plastic_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, red_plastic_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, red_plastic_shine);
}

void SetUnderGroundMaterial()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, under_ground_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, under_ground_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, under_ground_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, under_ground_shine);
}

void SetLowGroundMaterial()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, low_ground_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, low_ground_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, low_ground_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, low_ground_shine);
}



void SetBridgeMaterial()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, bridge_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, bridge_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, bridge_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, bridge_shine);
}

void SetBridgeAccentMaterial()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, bridge_accent_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, bridge_accent_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, bridge_accent_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, bridge_accent_shine);
}



void SetGrassandMaterial()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, grassand_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grassand_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, grassand_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, grassand_shine);
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


void SetRubyMaterial()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ruby_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ruby_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ruby_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, ruby_shine);
}



