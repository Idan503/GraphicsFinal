#include "camera.h"
#include "glut.h"
#include "globals.h"
#include <math.h>


// position is defined in globals.h

double yaw = -PI * 0.5, pitch = -0.2, roll;
double speed = 0, angularSpeed = 0;
double dir[3] = { sin(yaw),sin(pitch),cos(yaw) };


void CameraDisplay() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // loads the Identity matrix to the Projection Matrix
	// define the camera model
	glFrustum(-1, 1, -1, 1, 1, 300);
	// define the viewing parameters

	SetLookAt(selected_view);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // loads the Identity matrix to the TRASFORMATION Matrix

}

void SetLookAt(int view_choise)
{
	// 0 = regular view, 1 = side view, 2 = train driver view, 3 = window view
	switch (view_choise)
	{
	case 0:
		// Regular View
		gluLookAt(eyex, eyey, eyez, // eye coordinates
			eyex + dir[0], eyey + dir[1], eyez + dir[2], // point of interest coordinates
			0, 1, 0); // vector UP reflects roll
		break;
	case 1:
		// Side View - looking at train from the side
		gluLookAt(train_head_position[0] + 10, train_head_position[1] + 5, train_head_position[2] - 6.5,
			train_head_position[0], train_head_position[1] + 1, train_head_position[2] - 6.5,
			0, 1, 0);
		break;
	case 2:
		// Driver View
		gluLookAt(train_head_position[0], train_head_position[1] + 2, train_head_position[2] + 0.5,
			0, 2 , ground_size, // looking at the front
			0, 1, 0);
		break;
	case 3:
		// Window View
		gluLookAt(train_head_position[0], train_head_position[1] + 1.75 , train_head_position[2] - 2,
			ground_size, train_head_position[1] + 2, train_head_position[2], // looking to the side (from window)
			0, 1, 0);
		break;
	}
}


void CameraIdle() {
	if (selected_view == 0) {
		//moving on regular view
		yaw += angularSpeed;
		// setup the sight direction
		dir[0] = sin(yaw);
		dir[1] = sin(pitch);
		dir[2] = cos(yaw);
		// setup the motion
		eyex += speed * dir[0];
		eyey += speed * dir[1];
		eyez += speed * dir[2];

		ValidateCameraPosition();


	}
}

//Prevent free camera to go out of scene
void ValidateCameraPosition()
{
	if (eyex > ground_size/2)
	{
		eyex = ground_size/2;
		speed = 0;
	}

	if (eyex < -ground_size/2)
	{
		eyex = -ground_size/2;
		speed = 0;
	}


	if (eyey > ground_size / 2)
	{
		eyey = ground_size / 2;
		speed = 0;
	}

	if (eyey < -10)
	{
		eyey = -10;
		speed = 0;
	}


	if (eyez > ground_size / 2)
	{
		eyez = ground_size / 2;
		speed = 0;
	}

	if (eyez < -ground_size / 2)
	{
		eyez = -ground_size / 2;
		speed = 0;
	}
}


void SpecialKey(int key, int x, int y)
{
	if (selected_view == 0) { //only when on regular view
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
}
