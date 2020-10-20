#include "globals.h"
#include "glut.h"


// Global variables/functions that will be used in various files in the project

const double PI = 3.1415;
const int ground_size = 100;
double current_time = 0;
const int river_size = 10;
const double rail_width = 0.75;
const double bridge_height = 0.25;
const double train_speed = 0.03;
vector<vector<double> > ground(ground_size,vector<double>(ground_size,0));
vector<double> rail(ground_size);


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
