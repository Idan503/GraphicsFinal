#include "camera.h"
#include "glut.h"
#include "globals.h"
#include <math.h>


double eyex = -14, eyey = 5 , eyez = 0;

double yaw = PI * 0.5, pitch = 0, roll;
double speed = 0, angularSpeed = 0;
double dir[3] = { sin(yaw),sin(pitch),cos(yaw) };


void CameraDisplay() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // loads the Identity matrix to the Projection Matrix
	// define the camera model
	glFrustum(-1, 1, -1, 1, 1, 300);
	// define the viewing parameters
	gluLookAt(eyex, eyey, eyez, // eye coordinates
		eyex + dir[0], eyey + dir[1], eyez + dir[2], // point of interest coordinates
		0, 1, 0); // vector UP reflects roll

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // loads the Identity matrix to the TRASFORMATION Matrix

}


void CameraIdle() {
	yaw += angularSpeed;
	// setup the sight direction
	dir[0] = sin(yaw);
	dir[1] = sin(pitch);
	dir[2] = cos(yaw);
	// setup the motion
	eyex += speed * dir[0];
	eyey += speed * dir[1];
	eyez += speed * dir[2];
}


void SpecialKey(int key, int x, int y)
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
		pitch += 0.1;
		break;
	case GLUT_KEY_PAGE_DOWN:
		pitch -= 0.1;
		break;
	}
}
