#include <math.h>
#include <time.h>
#include "glut.h"
#include "material_manager.h"
#include "globals.h"
#include "texture_manager.h"
#include "camera.h"
#include "ground_builder.h"
#include "entity_builder.h"

const int W = 600;
const int H = 600;


void init()
{
	srand(time(0)); // seed or init random numbers generator
	
	glClearColor(0.0, 0.6, 0.8, 0);// color of window background
	glEnable(GL_DEPTH_TEST); // allow to show the nearest object

	BuildGroundTerrain();

	InitAllTextures();
	InitTrain();

	glEnable(GL_NORMALIZE);


}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // clean frame buffer and depth buffer

	CameraDisplay();

	InitLight();
	
	DrawBridge();
	DrawGround();

	DrawTrain();

	DrawTrain();
	DrawTrees();

	glutSwapBuffers(); // show all
}

void idle()
{

	current_time += 0.01;
	CameraIdle();
	MoveTrain();

	glutPostRedisplay(); // posts message (with request to show the frame ) to main window
}



void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	// defines BUFFERS: Color buffer (frame buffer) and Depth buffer
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); 
	glutInitWindowSize(W, H);
	glutInitWindowPosition(2050, 100);
	glutCreateWindow("Final Graphics Project ID 211546288");

	glutDisplayFunc(display); // refresh window function
	glutIdleFunc(idle); // kind of timer function

	glutSpecialFunc(SpecialKey);

	init();

	glutMainLoop();
}