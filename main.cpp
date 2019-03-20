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


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ For special keys ~~~~~~~~~~~~
float angleViewDist=30;
//Determines if game is paused or not
static bool paused=false;

//Lookat Vars
//float eyeX = 0;
//float eyeY = 0;
//float eyeZ = 15;

//Angle of head for rotation on button presses
float headRotationAngle = 0;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ For special keys (ryan is speical) ~~~~~~~~~~~~

// LookAt
double eyeX = 0.0;
double eyeY = 50.0;
double eyeZ = 50.0;
double atX = 0.0;
double atY = 0.0;
double atZ = 0.0;
double upX = 0.0;
double upY = 1.0;
double upZ = 0.0;

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
   cout << myCity.countBuildings();
   glClearColor(0.52, 0.80, 0.92, 0.0);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_CULL_FACE);
   glCullFace(GL_BACK);	
}

void Idle() {
   glutPostRedisplay();
}

void Special(int key, int x, int y) {
/*	switch(key) {
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
		}*/

// New special keys
   if(paused==false){
      switch(key){
	 case GLUT_KEY_F1://turn head to face forwards (the default)
	    t1000.setHeadRotationAngle(0);
	    //t1000.smoothRotate(0); 
	    break;
	 case GLUT_KEY_F2://turn robot head to the right
	    t1000.setHeadRotationAngle(90);
	    //t1000.smoothRotate(90);
	    break;
	 case GLUT_KEY_F3://turn robot head to the left
	    t1000.setHeadRotationAngle(-90);
	    //t1000.smoothRotate(-90);
	    break;
	 case GLUT_KEY_F4://makes the view go back to the regular view
	    eyeX = 0;
	    eyeY = 0;
	    eyeZ = angleViewDist;
	    break;
	 case GLUT_KEY_F5://looks at robot from the BACK LEFT
	    eyeX = angleViewDist;
	    eyeY = angleViewDist;
	    eyeZ = angleViewDist;
	    break;
	 case GLUT_KEY_F6://looks at robot from the BACK RIGHT
	    eyeX = -angleViewDist;
	    eyeY =  angleViewDist;
	    eyeZ =  angleViewDist;
	    break;
	 case GLUT_KEY_F7://looks at robot from the FRONT RIGHT
	    eyeX = -angleViewDist;
	    eyeY =  angleViewDist;
	    eyeZ = -angleViewDist;
	    break;
	 case GLUT_KEY_F8://looks at robot from the FRONT LEFT
	    eyeX =  angleViewDist;
	    eyeY =  angleViewDist;
	    eyeZ = -angleViewDist;
	    break;
	 case GLUT_KEY_F9://looks at robot from the BACK LEFT at GREATER dist
	    eyeX = angleViewDist*2;
	    eyeY = angleViewDist*2;
	    eyeZ = angleViewDist*2;
	    break;
	 case GLUT_KEY_F10://looks at robot from the BACK RIGHT at GREATER dist
	    eyeX = -angleViewDist*2;
	    eyeY =  angleViewDist*2;
	    eyeZ =  angleViewDist*2;
	    break;
	 case GLUT_KEY_F11://looks at robot from the FRONT RIGHT at GREATER dist
	    eyeX = -angleViewDist*2;
	    eyeY =  angleViewDist*2;
	    eyeZ = -angleViewDist*2;
	    break;
	 case GLUT_KEY_F12://looks at robot from the FRONT LEFT at GREATER dist
	    eyeX =  angleViewDist*2;
	    eyeY =  angleViewDist*2;
	    eyeZ = -angleViewDist*2;
	    break;

	 default:
	    printf ("KP: No action for %d.\n", key);
	    break;
      }
   }
// New special keys

}

void Keyboard(unsigned char key, int x, int y) {
   if(paused==false){ 
      switch(key){
	 // if(paused==false){
	 cout << key;
	 case 'z': // z
	    //This will now move the robot forward
	    break;
	 case 'a':
	    //turn robot right
	    break;
	 case 'q':
	    //turn robot left
	    break;
	 case 'r':
	    //return the robot to the origin if the robot is on the boundary
	    //do nothing if not on boundary
	    break;
	 case 27:
	    // This closes the program.
	    exit(0);
	 default:
	    printf ("KP: No action for %d.\n", key);
	    break;
      }
   }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ New special keys
void myKeyboardUpKey(unsigned char key, int x, int y){
   switch(key){
      case 'p'://pauses the game, press again to unpause
	 paused = !paused;
	 cout << paused;
	 break;
      default:
	 printf ("KP: No action for %d.\n", key);
	 break;
   }
}

void specialKeysUp( int key, int x, int y ){
   if(paused==false){
      switch(key){
	 case GLUT_KEY_F2:
	 case GLUT_KEY_F3:
	    //robot.setHeadRotationAngle(0);
	    break;
	 default:
	    break;
      }
   }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ New special keys

void Mouse(int button, int state, int x, int y) {
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
   {
      printf ("mouseX %d mouseY %d\n",x,y);
   }
}

void Display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluPerspective(50, 1, 5, 1000);
	gluLookAt(eyeX, eyeY, eyeZ, atX, atY, atZ, upX, upY, upZ);
	myCity.drawCity(10, GL_RENDER);
	//drawBuildings(GL_RENDER);
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
