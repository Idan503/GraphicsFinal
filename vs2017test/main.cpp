#include "glut.h"
#include <math.h>
#include <time.h>
#include "view_manager.h"

const int W = 600;
const int H = 600;




void init()
{

	srand(time(0)); // seed or init random numbers generator
	
	glClearColor(0.0, 0.6, 0.8, 0);// color of window background
	glEnable(GL_DEPTH_TEST); // allow to show the nearest object

}

void DrawFloor()
{
	int i;

	glColor3d(0, 0, 0.3);
	// lines that are parallel to X
	glBegin(GL_LINES);
	for (i = -10; i <= 10; i++)
	{
		glVertex3d(-10, 0, i);
		glVertex3d(10, 0, i);
	}
	glEnd();
	// lines that are parallel to Z
	glBegin(GL_LINES);
	for (i = -10; i <= 10; i++)
	{
		glVertex3d(i, 0, -10);
		glVertex3d(i, 0, 10);
	}
	glEnd();

}


void DrawAxes()
{
	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3d(1, 0, 0); // x
	glVertex3d(0, 0, 0);
	glVertex3d(15, 0, 0);
	glColor3d(0, 1, 0); // y
	glVertex3d(0, 0, 0);
	glVertex3d(0, 5, 0);
	glColor3d(0, 0, 1); // z
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, 15);

	glEnd();
	glLineWidth(1);

}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // clean frame buffer and depth buffer

	viewDisplay();

	DrawFloor();
	DrawAxes();

	glutSwapBuffers(); // show all
}

void idle()
{

	viewIdle();

	glutPostRedisplay(); // posts message (with request to show the frame ) to main window
}



void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	// defines BUFFERS: Color buffer (frame buffer) and Depth buffer
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); 
	glutInitWindowSize(W, H);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("Final Graphics Project ID 211546288");

	glutDisplayFunc(display); // refresh window function
	glutIdleFunc(idle); // kind of timer function

	glutSpecialFunc(specialKey);

	init();

	glutMainLoop();
}