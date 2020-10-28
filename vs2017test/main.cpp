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


void Init()
{
	srand(time(0)); // seed or init random numbers generator
	
	glClearColor(0.0, 0.6, 0.8, 0);// color of window background
	glEnable(GL_DEPTH_TEST); // allow to show the nearest object

	BuildGroundTerrain();

	InitAllTextures();
	InitTrain();
	InitTrees();
	InitSmoke();

	glEnable(GL_NORMALIZE);


}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // clean frame buffer and depth buffer

	CameraDisplay();

	InitLight();
	DrawSky();
	
	DrawBridge();
	DrawGround();

	DrawTrain();
	DrawTrees();
	DrawSmoke();

	if (selected_view == 3) // window view
		DrawWindowFilter();

	glutSwapBuffers(); // show all
}

void Idle()
{

	current_time += 0.01;
	CameraIdle();
	MoveTrain();
	MoveSmoke();

	glutPostRedisplay(); // posts message (with request to show the frame ) to main window
}




void Menu(int choise)
{
	selected_view = choise;
	// 0 = regular view, 1 = side view, 2 = train driver view, 3 = window view
}

void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	// defines BUFFERS: Color buffer (frame buffer) and Depth buffer
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); 
	glutInitWindowSize(W, H);
	glutInitWindowPosition(2050, 100);
	glutCreateWindow("Final Graphics Project ID 211546288");

	glutDisplayFunc(Display); // refresh window function
	glutIdleFunc(Idle); // kind of timer function

	glutSpecialFunc(SpecialKey);
	
	//menu
	glutCreateMenu(Menu);
	glutAddMenuEntry("Free View",0);
	glutAddMenuEntry("Side View", 1);
	glutAddMenuEntry("Driver View", 2);
	glutAddMenuEntry("Window View", 3);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	Init();

	glutMainLoop();
}