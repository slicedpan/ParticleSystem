// Skeleton program for GLUT applications.

// Link with: opengl32.lib, glu32.lib, glut32.lib.

#include <math.h>
#include <iostream>
#include <strstream>
#include <iomanip>
#include <glut.h>
#include "../FPSCamera/FPSCamera.h"
#include "../FPSCamera/CameraController.h"

using namespace std;

// Initial size of graphics window.
const int WIDTH  = 600;
const int HEIGHT = 400;

// Current size of window.
int width  = WIDTH;
int height = HEIGHT;

float xMouse = (float)width / 2.0f;
float yMouse = (float)height / 2.0f;

float dMouseX = 0.0f;
float dMouseY = 0.0f;

bool keystate[255];

// Bounds of viewing frustum.
double nearPlane =  0.1f;
double farPlane  = 1000.0f;

// Viewing angle.
double fovy = 40.0;

// Variables.
double alpha = 0;                                  // Set by idle function.
double beta = 0;                                   // Set by mouse X.
double dist = - (farPlane - nearPlane) / 2;    // Set by mouse Y.

CameraController* cameraController;
FPSCamera* camera;

// This function is called to display the scene.

void setup()
{
	camera = new FPSCamera();
	cameraController = new CameraController();
	cameraController->SetCamera(camera);
	camera->Position = Vec3(0.0, 0.0, -5.0f);
	cameraController->HasMomentum = true;
	glutWarpPointer(width / 2, height/ 2);
	cameraController->HasAngularMomentum = true;
	cameraController->MaxSpeed = 0.25f;
	for (int i = 0; i < 255; ++i)
	{
		keystate[i] = false;
	}
	glutSetCursor(GLUT_CURSOR_NONE);
}

void display ()
{

	cameraController->Update(16);	

 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

   /*
   dist = - (yMouse * (farPlane - nearPlane) + nearPlane);
   glTranslatef(0, 0, dist);

   // Rotation from idle function.
   glRotatef(alpha, 0, 1, 0);
   
   // Rotation using X mouse.
   beta = 180.0 * xMouse;
   glRotatef(beta, 1, 0, 0);

   */

	glMultMatrixf(camera->GetViewTransform().Ref());
	//glTranslatef(-camera->Position[0], -camera->Position[1], -camera->Position[2]);
	if (camera->Position[2] > 0.0f)
	{
		int i = 0;
	}

   // Draw model axes.
	glBegin(GL_LINES);
		// X axis
		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(2, 0, 0);
		// Y axis
		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 2, 0);
		// Z axis
		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 2);
	glEnd();

   // Draw an object.
	glColor3f(0, 1, 1);
	glutWireSphere(1, 20, 20);

	glutSwapBuffers();
}

void HandleInput()
{
	if (keystate['w'])
	{
		cameraController->MoveForward();
	}
	else if (keystate['s'])
	{
		cameraController->MoveBackward();
	}

	if (keystate['a'])
	{
		cameraController->MoveLeft();
	}
	else if (keystate['d'])
	{
		cameraController->MoveRight();
	}

	if (keystate[' '])
	{
		cameraController->MoveUp();
	}
	else if (keystate['c'])
	{
		cameraController->MoveDown();
	}

	if (keystate[27])
		exit(0);
}

// This function is called when there is nothing else to do.
void idle ()
{

	HandleInput();

	const double STEP = 0.1;
	const double ALL_ROUND = 360;
	alpha += STEP;
	if (alpha > ALL_ROUND)
		alpha -= ALL_ROUND;

	// Display normalized coordinates in title bar.
	const int BUFSIZE = 200;
	static char buffer[BUFSIZE];
	ostrstream s(buffer, BUFSIZE);
	s << 
		resetiosflags(ios::floatfield) << setiosflags(ios::fixed) << 
		setprecision(3) << "Mouse at (" << xMouse << ", " << yMouse << 
		setprecision(0) << ").  Alpha=" << setw(3) << alpha << 
		".  Beta=" << setw(3) << beta <<
		setprecision(2) << ".  dist=" << dist <<
		"." << ends;
	glutSetWindowTitle(buffer);

	dMouseX = (xMouse - width / 2.0f);
	dMouseY = (yMouse - height / 2.0f);

	cameraController->ChangePitch(-dMouseY);
	cameraController->ChangeYaw(-dMouseX);

	glutWarpPointer(width / 2, height / 2);

	glutPostRedisplay();
}

void mouseMovement (int mx, int my)
{
   // Normalize mouse coordinates.
   xMouse = float(mx);
   yMouse = float(my);

   // Redisplay image.
   glutPostRedisplay();
}

// Respond to window resizing, preserving proportions.
// Parameters give new window size in pixels.
void reshapeMainWindow (int newWidth, int newHeight)
{
   width = newWidth;
   height = newHeight;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
   gluPerspective(fovy, GLfloat(width) / GLfloat(height), nearPlane, farPlane);
}

// Display help.
void help()
{
   cout << 
      "'h'   display help" << endl <<
      endl;
}

// Respond to graphic character keys.
// Parameters give key code and mouse coordinates.
void KeyDown (unsigned char key, int x, int y)
{
	keystate[key] = true;
}

void KeyUp (unsigned char key, int x, int y)
{
	keystate[key] = false;
}

// Respond to function keys.
// Parameters give key code and mouse coordinates.
void functionKeys (int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_F1:
		cout << "F1" << endl;
		break;
	case GLUT_KEY_UP:
		cout << "Up" << endl;
		break;	  
	}
}


void main (int argc, char **argv)
{
	// GLUT initialization.
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutCreateWindow("GLUT Skeleton Program");
	setup();
	// Register call backs.
	glutDisplayFunc(display);
	glutReshapeFunc(reshapeMainWindow);
	glutKeyboardFunc(KeyDown);
	glutKeyboardUpFunc(KeyUp);
	glutSpecialFunc(functionKeys);
	glutMotionFunc(mouseMovement);
	glutPassiveMotionFunc(mouseMovement);
	glutIdleFunc(idle);

	// OpenGL initialization
	glEnable(GL_DEPTH_TEST);

	// Display help.
	help();

	// Enter GLUT loop.
	glutMainLoop();
}
