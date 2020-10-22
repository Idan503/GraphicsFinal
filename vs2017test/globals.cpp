#include "globals.h"
#include "glut.h"


// Global variables/functions that will be used in various files in the project

const double PI = 3.1415;
const double E = 2.71828;
const int ground_size = 100;
double current_time = 0;
const int river_size = 10;
const double rail_width = 0.75;
const double bridge_height = 0.25;
const double train_speed = 0.03;
vector<vector<double> > ground(ground_size,vector<double>(ground_size,0));
vector<double> rail(ground_size);


void DrawColorCube(vector<double> color)
{
	glColor3d(color[0], color[1], color[2]);
	// top side
	glBegin(GL_POLYGON);
	glVertex3d(1, 1, 1);
	glVertex3d(1, 1, -1);
	glVertex3d(-1, 1, -1);
	glVertex3d(-1, 1, 1);
	glEnd();

	// bottom side
	glBegin(GL_POLYGON);
	glVertex3d(1, -1, 1);
	glVertex3d(1, -1, -1);
	glVertex3d(-1, -1, -1);
	glVertex3d(-1, -1, 1);
	glEnd();

	// front side
	glBegin(GL_POLYGON);
	glVertex3d(1, 1, 1);
	glVertex3d(-1, 1, 1);
	glVertex3d(-1, -1, 1);
	glVertex3d(1, -1, 1);
	glEnd();

	// rear side
	glBegin(GL_POLYGON);
	glVertex3d(1, 1, -1);
	glVertex3d(-1, 1, -1);
	glVertex3d(-1, -1, -1);
	glVertex3d(1, -1, -1);
	glEnd();

	// left side
	glBegin(GL_POLYGON);
	glVertex3d(-1, 1, 1);
	glVertex3d(-1, 1, -1);
	glVertex3d(-1, -1, -1);
	glVertex3d(-1, -1, 1);
	glEnd();

	// right side
	glBegin(GL_POLYGON);
	glVertex3d(1, 1, 1);
	glVertex3d(1, 1, -1);
	glVertex3d(1, -1, -1);
	glVertex3d(1, -1, 1);
	glEnd();
}


void DrawColorTire(int sides, double outer, double inner, vector<double> color, int step)
{
	double alpha, teta = 2 * PI / sides;
	double x, z;
	glColor3d(color[0], color[1], color[2]);
	for (alpha = 0; alpha < 2 * PI; alpha += step * teta)
	{
		glBegin(GL_POLYGON);
		x = outer * sin(alpha);
		z = outer * cos(alpha);
		glVertex3d(x, 0, z); // 1
		x = inner * sin(alpha);
		z = inner * cos(alpha);
		glVertex3d(x, 0, z); // 2
		x = inner * sin(alpha + teta);
		z = inner * cos(alpha + teta);
		glVertex3d(x, 0, z); // 3
		x = outer * sin(alpha + teta);
		z = outer * cos(alpha + teta);
		glVertex3d(x, 0, z); // 4
		glEnd();
	}
}

void DrawTexTire(int sides, double outer, double inner, int texture_id, bool replace, int step)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_id); // wall with window texture
	if (replace)
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	else
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	double alpha, teta = 2 * PI / sides;
	double x, z;
	for (alpha = 0; alpha < 2 * PI; alpha += step * teta)
	{
		glBegin(GL_POLYGON);
		x = outer * sin(alpha);
		z = outer * cos(alpha);
		glTexCoord2d(1, 1); glVertex3d(x, 0, z); // 1
		x = inner * sin(alpha);
		z = inner * cos(alpha);
		glTexCoord2d(1, 0); glVertex3d(x, 0, z); // 2
		x = inner * sin(alpha + teta);
		z = inner * cos(alpha + teta);
		glTexCoord2d(0, 0); glVertex3d(x, 0, z); // 3
		x = outer * sin(alpha + teta);
		z = outer * cos(alpha + teta);
		glTexCoord2d(0, 1); glVertex3d(x, 0, z); // 4
		glEnd();
	}
}

void DrawTexCube(int texture_id, bool replace) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_id); // wall with window texture
	if (replace)
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	else
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


	// top side
	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1); glVertex3d(1, 1, 1);
	glTexCoord2d(1, 0); glVertex3d(1, 1, -1);
	glTexCoord2d(0, 0); glVertex3d(-1, 1, -1);
	glTexCoord2d(0, 1); glVertex3d(-1, 1, 1);
	glEnd();

	// bottom side
	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1); glVertex3d(1, -1, 1);
	glTexCoord2d(1, 0); glVertex3d(1, -1, -1);
	glTexCoord2d(0, 0); glVertex3d(-1, -1, -1);
	glTexCoord2d(1, 0); glVertex3d(-1, -1, 1);
	glEnd();

	// front side
	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1); glVertex3d(1, 1, 1);
	glTexCoord2d(1, 0); glVertex3d(-1, 1, 1);
	glTexCoord2d(0,0); glVertex3d(-1, -1, 1);
	glTexCoord2d(1, 0); glVertex3d(1, -1, 1);
	glEnd();

	// rear side
	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1); glVertex3d(1, 1, -1);
	glTexCoord2d(1, 0); glVertex3d(-1, 1, -1);
	glTexCoord2d(0,0); glVertex3d(-1, -1, -1);
	glTexCoord2d(1, 0); glVertex3d(1, -1, -1);
	glEnd();

	// left side
	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1); glVertex3d(-1, 1, 1);
	glTexCoord2d(1, 0); glVertex3d(-1, 1, -1);
	glTexCoord2d(0,0); glVertex3d(-1, -1, -1);
	glTexCoord2d(1, 0); glVertex3d(-1, -1, 1);
	glEnd();

	// right side
	glBegin(GL_POLYGON);
	glTexCoord2d(1, 1); glVertex3d(1, 1, 1);
	glTexCoord2d(1, 0); glVertex3d(1, 1, -1);
	glTexCoord2d(0, 0); glVertex3d(1, -1, -1);
	glTexCoord2d(1, 0); glVertex3d(1, -1, 1);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void DrawColorCylinder(vector<double> color, int sides)
{
	double alpha, teta = 2 * PI / sides;

	glColor3d(color[0], color[1], color[2]);
	for (alpha = 0; alpha <= 2 * PI; alpha += teta)
	{
		// defines one side

		glBegin(GL_POLYGON);
		glVertex3d(sin(alpha), 1, cos(alpha)); // vertex 1
		glVertex3d(sin(alpha + teta), 1, cos(alpha + teta)); // vertex 2
		glVertex3d(sin(alpha + teta), 0, cos(alpha + teta)); // vertex 3
		glVertex3d(sin(alpha), 0, cos(alpha)); // vertex 4
		glEnd();
	}
}

void DrawColorCylinder(vector<double> color, int sides, double tr, double br)
{
	glColor3d(color[0], color[1], color[2]);
	double alpha, teta = 2 * PI / sides;

	for (alpha = 0; alpha <= 2 * PI; alpha += teta)
	{
		// defines one side
		glBegin(GL_POLYGON);
		glVertex3d(tr * sin(alpha), 1, tr * cos(alpha)); // vertex 1
		glVertex3d(tr * sin(alpha + teta), 1, tr * cos(alpha + teta)); // vertex 2
		glVertex3d(br * sin(alpha + teta), 0, br * cos(alpha + teta)); // vertex 3
		glVertex3d(br * sin(alpha), 0, br * cos(alpha)); // vertex 4
		glEnd();
	}
}



// overloading - radius as 1
void DrawTexCylinder(int sides, int texture_id, int num_rep, bool replace)
{
	DrawTexCylinder(sides, texture_id, num_rep, 1, 1, replace);

}


// texture_id is texture id number
void DrawTexCylinder(int sides, int texture_id, int num_rep, double tr, double br, bool replace)
{
	double alpha, teta = 2 * PI / sides;
	double part = num_rep / (double)sides;
	int counter;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_id); // wall with window texture
	if(replace)
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	else
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


	for (alpha = 0, counter = 0; alpha <= 2 * PI; alpha += teta, counter++)
	{
		// defines one side
		glBegin(GL_POLYGON);
		glTexCoord2d(counter * part, 1);    glVertex3d(tr * sin(alpha), 1, tr * cos(alpha)); // vertex 1
		glTexCoord2d((counter + 1.0) * part, 1);    		glVertex3d(tr * sin(alpha + teta), 1, tr * cos(alpha + teta)); // vertex 2
		glTexCoord2d((counter + 1.0) * part, 0);    		glVertex3d(br * sin(alpha + teta), 0, br * cos(alpha + teta)); // vertex 3
		glTexCoord2d(counter * part, 0);    		glVertex3d(br * sin(alpha), 0, br * cos(alpha)); // vertex 4
		glEnd();
	}

	glDisable(GL_TEXTURE_2D);

}

void DrawColorSphere(vector<double> color, int sides, int slices)
{
	double beta, gamma = PI / slices;
	int counter;

	for (beta = -PI / 2, counter = 0; beta <= PI / 2; beta += gamma, counter++)
	{
		glPushMatrix();
		glTranslated(0, sin(beta), 0);
		glScaled(1, sin(beta + gamma) - sin(beta), 1);
		DrawColorCylinder(color, sides, cos(beta+gamma), cos(beta));
		glPopMatrix();
	}
}



void DrawTexSphere(int sides, int slices, int texutre_id, int num_rep, int vert_rep, bool replace)
{
	double beta, gamma = PI / slices;
	int counter;
	double part = vert_rep / (double)slices;

	for (beta = -PI / 2, counter = 0; beta <= PI / 2; beta += gamma, counter++)
	{
		glPushMatrix();
		glTranslated(0, sin(beta), 0);
		glScaled(1, sin(beta + gamma) - sin(beta), 1);
		DrawTexCylinder2(sides, texutre_id, num_rep, cos(beta + gamma), cos(beta), (counter + 1.0) * part, counter * part, replace);
		glPopMatrix();
	}
}


void DrawTexCylinder2(int n, int tnum, int num_repeat, double tr, double br, double tpart, double bpart, bool replace)
{
	double alpha, teta = 2 * PI / n;
	double part = num_repeat / (double)n;
	int counter;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tnum); // wall with window texture
	if(replace)
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	else
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


	for (alpha = 0, counter = 0; alpha <= 2 * PI; alpha += teta, counter++)
	{
		// defines one side

		glBegin(GL_POLYGON);
		//		glColor3d(0.3 + 0.7 * fabs(sin(alpha)), 0.3 + 0.7 * fabs(sin(alpha)), 0.3 + 0.7 * fabs(sin(alpha)));
		glTexCoord2d(counter * part, tpart);    glVertex3d(tr * sin(alpha), 1, tr * cos(alpha)); // vertex 1
		glTexCoord2d((counter + 1.0) * part, tpart);    		glVertex3d(tr * sin(alpha + teta), 1, tr * cos(alpha + teta)); // vertex 2
		glTexCoord2d((counter + 1.0) * part, bpart);    		glVertex3d(br * sin(alpha + teta), 0, br * cos(alpha + teta)); // vertex 3
		glTexCoord2d(counter * part, bpart);    		glVertex3d(br * sin(alpha), 0, br * cos(alpha)); // vertex 4
		glEnd();
	}

	glDisable(GL_TEXTURE_2D);

}
