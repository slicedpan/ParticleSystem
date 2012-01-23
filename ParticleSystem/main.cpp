// Skeleton program for GLUT applications.

// Link with: opengl32.lib, glu32.lib, glut32.lib.

#include <math.h>
#include <iostream>
#include <strstream>
#include <iomanip>
#include <glut.h>
#include "../FPSCamera/FPSCamera.h"
#include "../FPSCamera/CameraController.h"
#include "Plane.h"
#include "ParticleSystem.h"
#include "PhysicsSystem.h"
#include "GravitationalForce.h"
#include "CentralForce.h"
#include "Box.h"

using namespace std;

// Initial size of graphics window.
const int WIDTH  = 1200;
const int HEIGHT = 800;

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

int fps = 60;

Plane * groundPlane;
ColouredParticleSystem* particleSystem;
Box * box;
Box * box2;

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
	groundPlane = new Plane(Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 0.0));
	PhysicsSystem::GetCurrentInstance()->AddCollidable(groundPlane);
	box = new Box(Vec3(16.0, 2.0, 0.0), Vec3(10.0, 4.0, 10.0));
	box2 = new Box(Vec3(20.0, 6.0, 0.0), Vec3(1.0, 5.0, 5.0));
	box2->Colour = Vec3(0.0, 0.2, 0.8);
	PhysicsSystem::GetCurrentInstance()->AddCollidable(box);
	PhysicsSystem::GetCurrentInstance()->AddCollidable(box2);
	particleSystem = new ColouredParticleSystem(Vec3(0.0, 15.0, 0.0), Vec3(0.25f, 0.0, 0.0), Vec3(0.0, 0.2, 1.0), 1000, 35);
	particleSystem->AddForce(new GravitationalForce(Vec3(0.0f, -10.0f, 0.0f)));
	//particleSystem->AddForce(new CentralForce(Vec3(0.0, 5.0, 10.0), 3.0f));	
}

int lastTime = 0;
int frameCounter = 0;
int frameTimeCount = 0;

void display ()
{
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	int elapsedTime = (currentTime - lastTime);
	lastTime = currentTime;

	++frameCounter;
	frameTimeCount += elapsedTime;

	if (frameTimeCount > 1000)
	{
		frameTimeCount = 0;
		fps = frameCounter;
		frameCounter = 0;
	}

	cameraController->Update((float)elapsedTime);	
	particleSystem->Update((float)elapsedTime);

 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glMultMatrixf(camera->GetViewTransform().Ref()); //apply camera transform

	groundPlane->Draw();
	particleSystem->Draw();
	box->Draw();
	box2->Draw();
	/*
	//Draw model axes.
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
	*/

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
	if (keystate['h'])
		int i = 0;
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
		setprecision(3) << "Camera pitch, yaw: " << camera->Pitch << ", " << camera->Yaw << 
		setprecision(0) << ").  Position=" << setw(3) << camera->Position[0] << ", " << camera->Position[1] << ", " << camera->Position[2] <<
		".  Beta=" << setw(3) << beta <<
		setprecision(2) << ".  fps=" << fps <<
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
