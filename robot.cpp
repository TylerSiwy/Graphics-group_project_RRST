//This is the level design
#include <stdlib.h>
#include <stdio.h>    
#include <string.h>
#include <string>
#include <GL/gl.h>   // OpenGL itself.
#include <GL/glu.h>  // GLU support library.
#include <GL/glut.h> // GLUT support library.
#include <iostream>
#include "project_helpers.cpp"

using namespace std;

//System Vars
int Window_ID;
int Window_Width = 900;
int Window_Height = 900;
#define PROGRAM_TITLE "ROBOT RAMPAGE"

//Lookat Vars
float eyeX = 0;
float eyeY = 0;
float eyeZ = 15;
float lookAtX = 0;
float lookAtY = 0;
float lookAtZ = 0;
GLUquadric *eyeQuad = gluNewQuadric();

//Robot Vars
float hScale = 2.0;
float antX = 0;
float antY = 0;
float antZ = 0;
float antAngle = 0;
GLUquadric *antQuad = gluNewQuadric();
float rotate_cube = 0;
GLUquadric *neckQuad = gluNewQuadric();

static bool paused=false;

void Display(void);
void MyInit();
void myKeyboardKey(unsigned char key, int x, int y);
void myMouse(int button, int state, int x, int y);
void drawHead();
void specialKeys( int key, int x, int y );
void specialKeysUp( int key, int x, int y );
void rotateObjects();
void drawEyes();
void drawAntenna();
void rotateAntena();

int main (int argc, char **argv){
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

   // Set Window size
   glutInitWindowSize(Window_Width, Window_Height);

   // Create and Open a window with its title.
   Window_ID = glutCreateWindow(PROGRAM_TITLE);
   if(!paused){
   // Register and install the callback function to do the drawing.
   glutDisplayFunc(&Display);

   // If there's nothing to do, draw.
   glutIdleFunc(&Display);
   }
   glEnable(GL_DEPTH_TEST);
   MyInit();

   // Input functions
   glutSpecialFunc(&specialKeys);/////////////////////
   glutSpecialUpFunc(&specialKeysUp);///////////////////
   glutKeyboardFunc(&myKeyboardKey);
   glutMouseFunc(myMouse);

   glutMainLoop(); 
   return 0;
}

void Display(void){
   //testerino
   glLoadIdentity();
   //glOrtho(-10.0, 10.0, -10.0, 10.0, 200.0, -200.0);
   gluPerspective(90, 1.0, 20.0, 2.0);
   gluLookAt(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, 0.0, 1.0, 0.0); 
   // Clear the color and depth
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   drawHead();
   glutSwapBuffers();
}

///////////////////////////
//The special keys currently only F1-F12
//the only purpose of these is to change
//the view of the camera around the robot
//as well F1-F3 changes the angle of the robots head
///////////////////////////
void specialKeys( int key, int x, int y ){
   switch(key){
      case GLUT_KEY_F1: 
	 cout << "F1";
	 //turn head to face forwards (the default)
	 break;
      case GLUT_KEY_F2:
	 cout << "F2";
	 eyeX = -5.0;
	 eyeY = -10.0;
	 eyeZ = 5.0;
	 //turn robot head to the right
	 //when unpressed turn head forward(the default)
	 break;
      case GLUT_KEY_F3:
	 cout << "F3";
	 //turn robot head to the left
	 //when unpressed turn head forward(the default)
	 break;
      case GLUT_KEY_F4:
	 cout << "F4";
	 //makes the view go back to the regular view
	 break;
      case GLUT_KEY_F5:
	 cout << "F5";
	 //looks at robot from the BACK LEFT
	 break;
      case GLUT_KEY_F6:
	 cout << "F6";
	 //looks at robot from the BACK RIGHT
	 break;
      case GLUT_KEY_F7:
	 cout << "F7";
	 //looks at robot from the FRONT RIGHT
	 break;
      case GLUT_KEY_F8:
	 cout << "F8";
	 //looks at robot from the FRONT LEFT
	 break;
      case GLUT_KEY_F9:
	 cout << "F9";
	 //looks at robot from the BACK LEFT at GREATER distance
	 break;
      case GLUT_KEY_F10:
	 cout << "F10";
	 //looks at robot from the BACK RIGHT at GREATER distance
	 break;
      case GLUT_KEY_F11:
	 cout << "F11";
	 //looks at robot from the FRONT RIGHT at GREATER distance
	 break;
      case GLUT_KEY_F12:
	 cout << "F12";
	 //looks at robot from the FRONT LEFT at GREATER distance
	 break;

      default:
	 printf ("KP: No action for %d.\n", key);
	 break;
   }
}

void specialKeysUp( int key, int x, int y ){
   switch(key){
      case GLUT_KEY_F2:
	 case GLUT_KEY_F3:
	 cout << "F2UP ";
	 break;
      default:
	 printf ("KP: No action for %d.\n", key);
	 break;
   }
}





void MyInit(){
   // Color to clear color buffer to.
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glEnable(GL_CULL_FACE);
   glCullFace(GL_BACK);
}

void myKeyboardKey(unsigned char key, int x, int y){
   switch(key){
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
	 case 'p':
	    //pauses the game, press again to unpause
	    paused = !paused;
	    break;
      case 'r':
	 //return the robot to the origin if the robot is on the boundary
	 //do nothing if not on boundary
	 break;
      default:
	 printf ("KP: No action for %d.\n", key);
	 break;
   }
}

void myMouse(int button, int state, int x, int y){
   switch(button){
      case GLUT_LEFT_BUTTON:
	 if(state == GLUT_DOWN ){
	    
	        eyeX = 0.0;
	        eyeY = 0.0;
	        eyeZ = 15.0;
	 }else{
	        eyeX = eyeY = 0;
	        eyeZ = -15;
	 }
	 break;
      case GLUT_RIGHT_BUTTON:
	 if(state == GLUT_DOWN ){
	    eyeX = eyeY = eyeZ = -5.0;
	 }else{
	    eyeX = eyeY =0;
	    eyeZ = 5;
	 }
	 break;	 
   }
}

void drawEyes(){
   float eyeRadius = 0.5;
   float resolution = 10;
   float headCenterOffset = hScale + 0.01;
   //Right EyebackHeadScale
   glPushMatrix();   
   glTranslatef(hScale/2, hScale/3, headCenterOffset);
   glRotatef(180, 0, 1, 0);
   glColor3f(1.0,1.0, 1.0);
   gluDisk(eyeQuad, 0, eyeRadius, resolution, 1);
   glPopMatrix();
   //Left Eye
   glPushMatrix();
   glTranslatef(-hScale/2, hScale/3, headCenterOffset);
      glRotatef(180, 0, 1, 0);
   glColor3f(1.0, 1.0, 1.0);
   gluDisk(eyeQuad, 0, eyeRadius, resolution, 1);
   glPopMatrix();
}
void rotateAntena(){
   antAngle += 10;
   glTranslatef(antX, antY, antZ);
   glRotatef(antAngle, 0, 1, 0);
   glTranslatef(-antX, -antY, -antZ);
}

void drawAntenna(){
   antY=hScale;
   float antRadius = 0.15;
   float antHeight = 1.35;
   float antRotation = 270;
   glPushMatrix();
   rotateAntena();
   glTranslatef(antX, antY, antZ);
   glRotatef(antRotation, 1.0, 0 ,0.0);
   glColor3f(0.6,0.1,0.3); //Purple
   gluCylinder(antQuad, antRadius, 0.05, antHeight, 10, 10); //Cone Shaped
   drawCube(0.8, 0.3, 0.1, 0, 0, antHeight);
   glPopMatrix();
   
}

void drawNeck(){
   float neckRadius = hScale * 0.80;
   gluCylinder(neckQuad, neckRadius, neckRadius, 1, 10, 10);
}

void drawBody(){

}

void drawHead(){  
   float backHeadScale = hScale * 0.55;
   glPushMatrix();
   glRotatef(rotate_cube, 0.0, 0.0, 1.0);
   drawCube(hScale, hScale, hScale, 0, 0, 0);
   
   drawEyes();
   drawAntenna();
   // square on back of head for identification
   glBegin(GL_POLYGON);
   glColor3f(0.5, 0.5, 1.0);
   glVertex3f(backHeadScale, -backHeadScale, -hScale-0.1);
   glVertex3f(backHeadScale, backHeadScale, -hScale-0.1);
   glVertex3f(-backHeadScale, backHeadScale,-hScale-0.1);
   glVertex3f(-backHeadScale, -backHeadScale, -hScale-0.1);
   glEnd();
   glPopMatrix();
}
