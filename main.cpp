#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "city.h"
#include "robotC.h"
using namespace std;
#define SIZE 512
// Window Options
int WindowWidth = 700;
int WindowHeight = 700;
const char* WindowName = "Rylan Bueckert";

int WindowID;

// LookAt
double eyex = 0.0;
double eyey = 50.0;
double eyez = 50.0;
double atx = 0.0;
double aty = 0.0;
double atz = 0.0;
double upx = 0.0;
double upy = 1.0;
double upz = -10.0;

// Objects
City myCity(20, 20);
Robot t1000;

// Callback Functions
void Display();
//void Reshape(int width, int height);
void Mouse(int button, int state, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Idle();
void Special(int key, int x, int y);
void init(int &argc, char ** argv);
//////////Rchanges
void drawBuildings(GLenum mode);
void processHits (GLint hits, GLuint buffer[]);
//////////Rchanges
int main(int argc, char ** argv) {
   //myCity.printLayout();
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowSize(WindowWidth, WindowHeight);
   glutInitWindowPosition (200, 100);
   WindowID = glutCreateWindow(WindowName);
   glutDisplayFunc(&Display);
   glutIdleFunc(&Idle);
//   glutReshapeFunc(&Reshape);
   glutMouseFunc(&Mouse);
   glutKeyboardFunc(&Keyboard);
   glutSpecialFunc(&Special);
   init(argc, argv);
   glutMainLoop();
   return 0;
}

void init(int &argc, char ** argv) {
	glClearColor(0.52, 0.80, 0.92, 0.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);	
}

void Idle() {
	glutPostRedisplay();
}

void Special(int key, int x, int y) {
	switch(key) {
	case GLUT_KEY_DOWN:
		eyez += 1;
		atz += 1;
		break;
	case GLUT_KEY_LEFT:
		eyex -= 1;
		atx -= 1;
		break;
	case GLUT_KEY_UP:
		eyez -= 1;
		atz -= 1;
		break;
	case GLUT_KEY_RIGHT:
		eyex += 1;
		atx += 1;
		break;
		}
   
}

void Keyboard(unsigned char key, int x, int y) {
	switch(key) {
	case 'w':
		break;

	case 'a':
		break;

	case 's':
		break;

	case 'd':

		break;

	default:
		break;
	}
}

void Mouse(int button, int state, int x, int y) {
	switch(button) {
	case GLUT_RIGHT_BUTTON:
		if(state == GLUT_DOWN) {

		}
		if(state == GLUT_UP) {

		}
		break;

	case GLUT_LEFT_BUTTON:
		if(state == GLUT_DOWN) {

		}
		if(state == GLUT_UP) {

		}
		break;
	default:
		break;
	}
}

void Display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluPerspective(50, 1, 5, 1000);
	gluLookAt(eyex, eyey, eyez, atx, aty, atz, upx, upy, upz);
	myCity.drawCity(10);
	drawBuildings(GL_RENDER);
	t1000.draw(1);
	glutSwapBuffers();
	/////////R changes
	glFlush();
	/////////R changes
}

void drawBuildings(GLenum mode)
{
   //This will eventually be the total number of buildings
   int numBuilding=10;
   //This i needs to start at 1, as 0 on the stack is already defined
   //This will protect the stack from underflow dumps
   for(int i=1; i<numBuilding; i++)
   {
      if(mode == GL_SELECT)
	 glLoadName(i);
      //  the building are created here
   }
}

void processHits (GLint hits, GLuint buffer[])
{
   int names, *ptr;
   printf ("hits = %d\n", hits);
   ptr = (GLint *) buffer; 
   for (int i = 0; i < hits; i++) {	/*  for each hit  */
      names = *ptr;
      ptr+=3;
      for (int j = 0; j < names; j++) { /*  for each name */
	 //Here we need to send a message with the
	 //*ptr value to destroy the correct building  
         if(*ptr==1) printf ("red rectangle\n");
         else printf ("blue rectangle\n");
         ptr++;
      }
      printf ("\n");
   }
}
