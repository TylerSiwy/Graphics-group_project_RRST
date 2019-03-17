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
//-------------------------System Vars-------------------------
int Window_ID;
int Window_Width = 900;
int Window_Height = 900;
#define PROGRAM_TITLE "ROBOT RAMPAGE"
float angleViewDist=15;
//Determines if game is paused or not
static bool paused=false;

//Lookat Vars
float eyeX = 0;
float eyeY = 0;
float eyeZ = 15;
float lookAtX = 0;
float lookAtY = 0;
float lookAtZ = 0;
GLUquadric *eyeQuad = gluNewQuadric();
//--------------------------------------------------------------

//--------------------------Robot Vars--------------------------
//Scale for the size of the head cube
float headScale = 2.0;
//Head Centerpoint XYZ
float headX = 0;
float headY = 0;
float headZ = 0;
//Angle of head for rotation on button presses
float headRotationAngle = 0;
//Angle of head for rotation during initial setup
float rotate_cube = 0;

//Location of robot's Antenna
float antX = 0;
float antY = 0;
float antZ = 0;
//Angle of antenna used for it's constnat rotation
float antAngle = 0;
//Quadratic for creating the cone part of the antenna
GLUquadric *antQuad = gluNewQuadric();

//Neck coordinates
float neckX = 0;
float neckY = 0;
float neckZ = 0;
//Quadratic for creating the neck of the robot
GLUquadric *neckQuad = gluNewQuadric();
//--------------------------------------------------------------

void Display(void);
void MyInit();
void myKeyboardKey(unsigned char key, int x, int y);
void myMouse(int button, int state, int x, int y);
void drawHead();
void specialKeys( int key, int x, int y );
void specialKeysUp( int key, int x, int y );
void myKeyboardUpKey(unsigned char key, int x, int y);
void rotateObjects();
void drawEyes();
void drawAntenna();
void drawNeck();
void rotateAntena();
void drawBody();
void drawAndRotateHead();
void drawBackTriangles();

int main (int argc, char **argv){
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

   // Set Window size
   glutInitWindowSize(Window_Width, Window_Height);

   // Create and Open a window with its title.
   Window_ID = glutCreateWindow(PROGRAM_TITLE);
   // if(paused==false){
   // Register and install the callback function to do the drawing.
   glutDisplayFunc(&Display);
   
   // If there's nothing to do, draw.
   glutIdleFunc(&Display);
   // Input functions
   glutSpecialFunc(&specialKeys);
   glutSpecialUpFunc(&specialKeysUp);
   glutMouseFunc(myMouse);
   glutKeyboardFunc(&myKeyboardKey);
   glutKeyboardFunc(&myKeyboardUpKey);
   glEnable(GL_DEPTH_TEST);
   MyInit();
   glutMainLoop(); 
   return 0;
}

void Display(void){

   //testerino
   glLoadIdentity();
   glOrtho(-10.0, 10.0, -10.0, 10.0, 200.0, -200.0);
   //gluPerspective(45, 1.0, 80.0, 1.0);
   gluLookAt(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, 0.0, 1.0, 0.0); 
   // Clear the color and depth
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   drawAndRotateHead();
   drawBody();
   glutSwapBuffers();
}



void MyInit(){
   // Color to clear color buffer to.
   glClearColor(0.52, 0.8, 0.92, 0.0);
   glEnable(GL_CULL_FACE);
   glCullFace(GL_BACK);
   glEnable(GL_DEPTH_TEST);
}

///////////////////////////
//The special keys currently only F1-F12
//the only purpose of these is to change
//the view of the camera around the robot
//as well F1-F3 changes the angle of the robots head
///////////////////////////
void specialKeys( int key, int x, int y ){
   if(paused==false){
      switch(key){
	 case GLUT_KEY_F1://turn head to face forwards (the default)
	    break;
	 case GLUT_KEY_F2://turn robot head to the right
	    break;
	 case GLUT_KEY_F3://turn robot head to the left
	    break;
	 case GLUT_KEY_F4://makes the view go back to the regular view
	    eyeX = 0;
	    eyeY = 0;
	    eyeZ = angleViewDist;
	    break;
	 case GLUT_KEY_F5://looks at robot from the BACK LEFT
	    eyeX =  angleViewDist;
	    eyeY = -angleViewDist;
	    eyeZ =  angleViewDist;
	    break;
	 case GLUT_KEY_F6://looks at robot from the BACK RIGHT
	    eyeX = -angleViewDist;
	    eyeY = -angleViewDist;
	    eyeZ =  angleViewDist;
	    break;
	 case GLUT_KEY_F7://looks at robot from the FRONT RIGHT
	    eyeX = -angleViewDist;
	    eyeY = -angleViewDist;
	    eyeZ = -angleViewDist;
	    break;
	 case GLUT_KEY_F8://looks at robot from the FRONT LEFT
	    eyeX =  angleViewDist;
	    eyeY = -angleViewDist;
	    eyeZ = -angleViewDist;
	    break;
	 case GLUT_KEY_F9://looks at robot from the BACK LEFT at GREATER dist
	    eyeX =  angleViewDist*2;
	    eyeY = -angleViewDist*2;
	    eyeZ =  angleViewDist*2;
	    break;
	 case GLUT_KEY_F10://looks at robot from the BACK RIGHT at GREATER dist
	    eyeX = -angleViewDist*2;
	    eyeY = -angleViewDist*2;
	    eyeZ =  angleViewDist*2;
	    break;
	 case GLUT_KEY_F11://looks at robot from the FRONT RIGHT at GREATER dist
	    eyeX = -angleViewDist*2;
	    eyeY = -angleViewDist*2;
	    eyeZ = -angleViewDist*2;
	    break;
	 case GLUT_KEY_F12://looks at robot from the FRONT LEFT at GREATER dist
	    eyeX =  angleViewDist*2;
	    eyeY = -angleViewDist*2;
	    eyeZ = -angleViewDist*2;
	    break;

	 default:
	    printf ("KP: No action for %d.\n", key);
	    break;
      }
   }
}

void specialKeysUp( int key, int x, int y ){
   if(paused==false){
      switch(key){
	 case GLUT_KEY_F2:
	 case GLUT_KEY_F3:
	    cout << "F2UP ";
	    break;
	 default:
	    break;
      }
   }
}

void myKeyboardKey(unsigned char key, int x, int y){
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

	 default:
	    printf ("KP: No action for %d.\n", key);
	    break;
      }
   }
}
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

//For debugging, to be changed later
void myMouse(int button, int state, int x, int y){
   switch(button){
      case GLUT_LEFT_BUTTON:
	 if(state == GLUT_DOWN ){
	    headRotationAngle = 90;
	 }else{
	    headRotationAngle = 0;
	 }
	 break;
      case GLUT_RIGHT_BUTTON:
	 if(state == GLUT_DOWN ){
	    headRotationAngle = -90;
	 }else{
	    headRotationAngle = 0;
	 }
	 break;	 
   }
}

void drawHead(){  
   float backHeadScale = headScale * 0.55;
   glPushMatrix();
   glTranslatef(headX, headY, headZ);
   glRotatef(rotate_cube, 0.0, 0.0, 1.0);
   drawCube(headScale, headScale, headScale, 0, 0, 0);
   drawNeck();
   drawEyes();
   drawAntenna();
   // square on back of head for identification
   glBegin(GL_POLYGON);
   glColor3f(0.5, 0.5, 1.0);
   glVertex3f(backHeadScale, -backHeadScale, -headScale-0.1);
   glVertex3f(backHeadScale, backHeadScale, -headScale-0.1);
   glVertex3f(-backHeadScale, backHeadScale,-headScale-0.1);
   glVertex3f(-backHeadScale, -backHeadScale, -headScale-0.1);
   glEnd();
   glPopMatrix();
   glMatrixMode(GL_MODELVIEW);
}

void drawAndRotateHead(){
   glRotatef(headRotationAngle, 0, 1, 0);
   drawHead();
   glRotatef(-headRotationAngle, 0, 1, 0);
}

void drawNeck(){
   float neckToHeadRatio = 0.70;
   float neckRadius = headScale * neckToHeadRatio;
   float neckDiameter = neckRadius *2;     
   float neckHeight = 1;
   glPushMatrix();
   glColor3f(1.0, 0.27, 0);
   // I am using thaumaturgy here to find the proper location
   glTranslatef(headX, headY-neckHeight*2, -headScale+neckDiameter*neckToHeadRatio);
   glRotatef(90, 1, 0, 0);
   gluCylinder(neckQuad, neckRadius, neckRadius, neckHeight, 10, 10);
   glPopMatrix();
}

void drawEyes(){
   float eyeRadius = 0.5;
   float resolution = 10;
   float headCenterOffset = headScale + 0.01;
   //Right EyebackHeadScale
   glPushMatrix();   
   glTranslatef(headScale/2, headScale/3, headCenterOffset);
   glRotatef(180, 0, 1, 0);
   glColor3f(1.0,1.0, 1.0);
   gluDisk(eyeQuad, 0, eyeRadius, resolution, 1);
   glPopMatrix();
   //Left Eye
   glPushMatrix();
   glTranslatef(-headScale/2, headScale/3, headCenterOffset);
   glRotatef(180, 0, 1, 0);
   glColor3f(1.0, 1.0, 1.0);
   gluDisk(eyeQuad, 0, eyeRadius, resolution, 1);
   glPopMatrix();
}

void drawAntenna(){
   antY=headScale;
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

void rotateAntena(){
   antAngle += 5 - headRotationAngle;
   glTranslatef(antX, antY, antZ);
   glRotatef(antAngle, 0, 1, 0);
   glTranslatef(-antX, -antY, -antZ);
}

void drawBody(){  
   glPushMatrix();
   drawEyes();
   drawAntenna();
   // square on back of head for identification
   glTranslatef(headX, headY, headZ);
   glRotatef(rotate_cube, 0.0, 0.0, 1.0);
   //translate triangles down by headScale, -1 for neck height * 2.25 for body height
   drawCube(headScale*1.5, headScale*2, headScale*1.5, 0, -(headScale+1)*2.25, 0);  
   drawBackTriangles();
   glPopMatrix();
   
   glMatrixMode(GL_MODELVIEW);
}

void drawBackTriangles(){
   // triangles on back of body for identification
   float backPolyScale = headScale * 1.5 * 0.55;
   glBegin(GL_POLYGON);
   glColor3f(1.0, 0.1, 0.1);
   glVertex3f(backPolyScale, -backPolyScale*4, -headScale*1.6);
   glVertex3f(0, -backPolyScale*2, -headScale*1.6); //Point
   glVertex3f(-backPolyScale, -backPolyScale*4, -headScale*1.6);
   glEnd();
   glBegin(GL_POLYGON);
   glColor3f(1.0, 0.1, 0.1);
   glVertex3f(backPolyScale, -backPolyScale*6, -headScale*1.6);
   glVertex3f(0, -backPolyScale*4, -headScale*1.6); //Point
   glVertex3f(-backPolyScale, -backPolyScale*6, -headScale*1.6);
   glEnd();
}
