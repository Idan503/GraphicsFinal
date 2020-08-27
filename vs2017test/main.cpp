#include "glut.h"
#include <math.h>
#include <time.h>

const double PI = 3.1415;
const int WIN_W= 600;
const int WIN_H = 600;


double eyex=0, eyey=30, eyez = 75;


double yaw=PI, pitch = -0.5, roll;
double speed = 0, angularSpeed = 0;
double dir[3] = {sin(yaw),sin(pitch),cos(yaw)};


void init()
{

	srand(time(0)); // seed or init random numbers generator
	
	glClearColor(0.0, 0.6, 0.8, 0);// color of window background
	glEnable(GL_DEPTH_TEST); // allow to show the nearest object

}

void DrawGround()
{
	int i;

	glColor3d(0, 0, 0.3);
	// lines that are parallel to X
	glBegin(GL_LINES);
	for (i = -50; i <= 50; i++)
	{
		glVertex3d(-50, 0, i);
		glVertex3d(50, 0, i);
	}
	glEnd();
	// lines that are parallel to Z
	glBegin(GL_LINES);
	for (i = -50; i <= 50; i++)
	{
		glVertex3d(i, 0, -50);
		glVertex3d(i, 0, 50);
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

void setProjection() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // loads the Identity matrix to the Projection Matrix
	// define the camera model
	glFrustum(-1, 1, -1, 1, 1, 300);
	// define the viewing parameters
	gluLookAt(eyex, eyey, eyez, // eye coordinates
		eyex + dir[0], eyey + dir[1], eyez + dir[2], // point of interest coordinates
		0, 1, 0); // vector UP reflects roll

}


void display()
{
	double x, y,beta;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // clean frame buffer and depth buffer

	setProjection();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // loads the Identity matrix to the TRASFORMATION Matrix

	DrawGround();
	DrawAxes();

	glutSwapBuffers(); // show all
}

void idle()
{

	yaw += angularSpeed;
	// setup the sight direction
	dir[0] = sin(yaw);
	dir[1] = sin(pitch);
	dir[2] = cos(yaw);
	// setup the motion
	eyex += speed * dir[0];
	eyey += speed * dir[1];
	eyez += speed * dir[2];

	glutPostRedisplay(); // posts message (with request to show the frame ) to main window
}


void special_key(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		angularSpeed += 0.001;
		break;
	case GLUT_KEY_RIGHT:
		angularSpeed -= 0.001;
		break;
	case GLUT_KEY_UP: 
		speed += 0.01;
		break;
	case GLUT_KEY_DOWN:
		speed -= 0.01;
		break;
	case GLUT_KEY_PAGE_UP:
		pitch+= 0.1;
		break;
	case GLUT_KEY_PAGE_DOWN:
		pitch -= 0.1;
		break;


	}
}

void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	// defines BUFFERS: Color buffer (frame buffer) and Depth buffer
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); 
	glutInitWindowSize(WIN_W, WIN_H);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("3D Example");

	glutDisplayFunc(display); // refresh window function
	glutIdleFunc(idle); // kind of timer function

	glutSpecialFunc(special_key);

	init();

	glutMainLoop();
}