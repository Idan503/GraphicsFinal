#include "glut.h"
#include <stdio.h>
#include "material_manager.h"
#include "bridge.h"
#include "globals.h"


int train_z = -ground_size / 2;
int train_x = ground_size / 2;
double max_ground_height;
double bridge_width;
double bridge_final_height;
double bridge_curve_length;


void DrawBridgeArch()
{

	SetBridgeMaterial();
	//curves z-
	glPushMatrix();
	glTranslated(bridge_width, bridge_final_height, -river_size + 1.5);
	glScaled(0.3, 0.3, 0.3);
	DrawBridgeCurve();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-bridge_width, bridge_final_height, -river_size + 1.5);
	glScaled(0.3, 0.3, 0.3);
	DrawBridgeCurve();
	glPopMatrix();

	//curves z+
	glPushMatrix();
	glTranslated(bridge_width, bridge_final_height, river_size - 1.5);
	glScaled(0.3, 0.3, -0.3);
	DrawBridgeCurve();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-bridge_width, bridge_final_height, river_size - 1.5);
	glScaled(0.3, 0.3, -0.3);
	DrawBridgeCurve();
	glPopMatrix();

	SetBridgeAccentMaterial();
	// main pole x-
	glPushMatrix();
	glTranslated(-bridge_width, 0, 0);
	glScaled(0.3, bridge_final_height + 0.25 + CalcBridgeCurveHeight(bridge_curve_length) * 0.3, 0.5);
	DrawTexCube(21,6,false);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-bridge_width, bridge_final_height + CalcBridgeCurveHeight(bridge_curve_length) * 0.3 - 0.4, 0);
	glScaled(0.4, 0.5, 0.4);
	DrawTexSphere(16, 16, 22, 1, 1, true);
	glPopMatrix();


	//pole lines x-
	glPushMatrix();
	glTranslated(-bridge_width, -2, 0.25);
	glScaled(-0.35, bridge_final_height + 0.25 + CalcBridgeCurveHeight(bridge_curve_length) * 0.3, 0.02);
	DrawTexCube(22, 8, true);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-bridge_width, -2, -0.25);
	glScaled(-0.35, bridge_final_height + 0.25 + CalcBridgeCurveHeight(bridge_curve_length) * 0.3, 0.02);
	DrawTexCube(22, 8, true);
	glPopMatrix();


	glPushMatrix();
	glTranslated(-bridge_width, -1.75, 0);
	glScaled(-0.35, bridge_final_height + 0.25 + CalcBridgeCurveHeight(bridge_curve_length) * 0.3, 0.05);
	DrawTexCube(22, 8, true);
	glPopMatrix();


	// main pole x+
	glPushMatrix();
	glTranslated(bridge_width, 0, 0);
	glScaled(0.3, bridge_final_height + 0.25 + CalcBridgeCurveHeight(bridge_curve_length) * 0.3, 0.5);
	DrawTexCube(21,6,false);
	glPopMatrix();

	glPushMatrix();
	glTranslated(bridge_width, bridge_final_height + CalcBridgeCurveHeight(bridge_curve_length) * 0.3 - 0.4, 0);
	glScaled(0.4, 0.5, 0.4);
	DrawTexSphere(16, 16, 22, 1, 1,true);
	glPopMatrix();


	//pole lines x+
	glPushMatrix();
	glTranslated(bridge_width, -2, 0.25);
	glScaled(0.35, bridge_final_height + 0.25 + CalcBridgeCurveHeight(bridge_curve_length) * 0.3, 0.02);
	DrawTexCube(22, 8, true);
	glPopMatrix();

	glPushMatrix();
	glTranslated(bridge_width, -2, -0.25);
	glScaled(0.35, bridge_final_height + 0.25 + CalcBridgeCurveHeight(bridge_curve_length) * 0.3, 0.02);
	DrawTexCube(22, 8, true);
	glPopMatrix();


	glPushMatrix();
	glTranslated(bridge_width, -1.75, 0);
	glScaled(0.35, bridge_final_height + 0.25 + CalcBridgeCurveHeight(bridge_curve_length) * 0.3, 0.05);
	DrawTexCube(22,8,true);
	glPopMatrix();

	SetBridgeMaterial();
	// road handle x+
	glPushMatrix();
	glTranslated(bridge_width, bridge_final_height, -river_size);
	glScaled(0.3, 0.3, river_size * 2.0);
	glRotated(90, 1, 0, 0);
	DrawTexCylinder(6, 21,5, true);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-bridge_width, bridge_final_height, -river_size);
	glScaled(0.3, 0.3, 0.3);
	glRotated(90, 1, 0, 0);
	DrawTexSphere(16, 16, 21, 1,1, true);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-bridge_width, bridge_final_height, river_size);
	glScaled(0.3, 0.3, 0.3);
	glRotated(90, 1, 0, 0);
	DrawTexSphere(16, 16, 21, 1, 1, true);
	glPopMatrix();

	// road handle x-
	glPushMatrix();
	glTranslated(-bridge_width, bridge_final_height, -river_size);
	glScaled(0.3, 0.3, river_size * 2.0);
	glRotated(90, 1, 0, 0);
	DrawTexCylinder(6, 21, 5,true);
	glPopMatrix();

	glPushMatrix();
	glTranslated(bridge_width, bridge_final_height, -river_size);
	glScaled(0.3, 0.3, 0.3);
	glRotated(90, 1, 0, 0);
	DrawTexSphere(16, 16, 21, 1, 1, true);
	glPopMatrix();

	glPushMatrix();
	glTranslated(bridge_width, bridge_final_height, river_size);
	glScaled(0.3, 0.3, 0.3);
	glRotated(90, 1, 0, 0);
	DrawTexSphere(16, 16, 21, 1, 1, true);
	glPopMatrix();


}

void DrawBridgeRoad()
{
	bridge_width = rail_width + 0.6;

	max_ground_height =
		fmax(fmax(ground[ground_size / 2 - river_size + 1][ground_size / 2], ground[ground_size / 2 - river_size][ground_size / 2]),
			fmax(ground[ground_size / 2 + river_size - 1][ground_size / 2], ground[ground_size / 2 + river_size][ground_size / 2]));
	bridge_final_height = max_ground_height + bridge_height;


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 20);

	glBegin(GL_POLYGON);
	// Road Texture under the rail
	glTexCoord2d(0, 1); glVertex3d(bridge_width, bridge_final_height, -river_size + 1.0);
	glTexCoord2d(bridge_width, 1); glVertex3d(bridge_width, bridge_final_height, river_size - 1.0);
	glTexCoord2d(bridge_width, 0); glVertex3d(-bridge_width, bridge_final_height, river_size - 1.0);
	glTexCoord2d(0, 0); glVertex3d(-bridge_width, bridge_final_height, -river_size + 1.0);


	glEnd();


	glDisable(GL_TEXTURE_2D);


}

void DrawBridgePoles(double thinkness)
{
	SetSilverMaterial();
	const double pole_line_margin = 0.5, pole_row_step = 3.5;
	// poles of the bridge

	SetSilverMaterial();
	double z;
	for (z = -river_size + pole_row_step; z <= river_size - 1.0; z += pole_row_step) {
		if (fabs(z) > 0.25) { //no need for pole in center (there is main pole)
			glPushMatrix();
			glTranslated(bridge_width - pole_line_margin, bridge_final_height, z);
			DrawBridgeSinglePole();
			glPopMatrix();
			glPushMatrix();
			glTranslated(-bridge_width + pole_line_margin, bridge_final_height, z);
			DrawBridgeSinglePole();
			glPopMatrix();
		}
	}
}

void DrawBridgeSinglePole()
{
	glPushMatrix();
	glTranslated(0, -bridge_final_height + ground[ground_size / 2][ground_size / 2], 0);
	glScaled(0.15, bridge_final_height - ground[ground_size / 2][ground_size / 2], 0.15);
	DrawTexCylinder(12, 21, 1);

	glPopMatrix();

}

void DrawBridgeCurve()
{
	bridge_curve_length = 27.5;
	double step = 0.15;
	double z;

	//bridge curve function: f(x) = \frac{1}{20}e^{0.235x^{1.1}}\cdot e^{1.25}

	double beta, gamma = PI / 16;
	int counter;

	for (z = 0.0; z < bridge_curve_length; z += step)
	{
		double y = CalcBridgeCurveHeight(z);

		glPushMatrix();
		glTranslated(0, y, z);
		glRotated(z * 3.5, 0, 1, 0);
		glScaled(0.75, 0.75, 0.75);
		DrawTexSphere(6, 6, 21, 1, 1,true);
		glPopMatrix();
	}
}

//returns the y of the f(x) curve:
//which is: f(x) = \frac{1}{20}e^{0.235x^{1.1}}\cdot e^{1.25}
double CalcBridgeCurveHeight(double x)
{
	return pow(E, 0.235 * pow(x, 0.78));
}

void DrawBridgeInnerPoles()
{
	const double inner_pole_size = 0.13;
	double x_mult, z_mult;

	for (x_mult = -1, 0; x_mult <= 1; x_mult += 2.0)
	{
		for (z_mult = -1, 0; z_mult <= 1; z_mult += 2.0)
		{
			glPushMatrix();
			glTranslated(x_mult * bridge_width, bridge_final_height, z_mult * river_size * 0.55);
			glScaled(inner_pole_size, 1.25, inner_pole_size);
			DrawTexCylinder(16, 21, 1);
			glPopMatrix();

			glPushMatrix();
			glTranslated(x_mult * bridge_width, bridge_final_height, z_mult * river_size * 0.35);
			glScaled(inner_pole_size, 2.5, inner_pole_size);
			DrawTexCylinder(16, 21, 1);
			glPopMatrix();

			glPushMatrix();
			glTranslated(x_mult * bridge_width, bridge_final_height, z_mult * river_size * 0.2);
			glScaled(inner_pole_size, 3.85, inner_pole_size);
			DrawTexCylinder(16, 21, 1);
			glPopMatrix();
		}
	}


}