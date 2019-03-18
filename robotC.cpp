#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "robotC.h"
#include "project_helpers.cpp"

using namespace std;

Robot::Robot(){
   headScale = 2.0;
   headX = headY = headZ = 0;
   headRotationAngle = 0;
   antX = antY = antZ = 0;
   antAngle = 0;
   neckX = neckY = neckZ = 0;
   antQuad = gluNewQuadric();
   neckQuad = gluNewQuadric();
   quad = gluNewQuadric();
   eyeQuad = gluNewQuadric();
   rotate_cube = 0;
}

void Robot::draw(float scale){
   headScale = scale; 
   drawAndRotateHead();
   drawBody();
}

void Robot::drawAndRotateHead(){
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glRotatef(headRotationAngle, 0, 1, 0);
   drawHead();
   glPopMatrix();
}

void Robot::drawHead(){
   float backHeadScale = headScale * 0.55;
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   //glTranslatef(headX, headY, headZ);
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
}

void Robot::drawEyes(){
   glMatrixMode(GL_MODELVIEW);
   float eyeRadius = 0.5;
   float resolution = 10;
   float headCenterOffset = headScale + 0.01;
   //Right Eye
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

void Robot::drawAntenna(){
   antY=headScale;
   float antRadius = 0.15;
   float antHeight = 1.35;
   float antRotation = 270;
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   rotateAntenna();
   glTranslatef(antX, antY, antZ);
   glRotatef(antRotation, 1.0, 0 ,0.0);
   glColor3f(0.6,0.1,0.3); //Purple
   gluCylinder(antQuad, antRadius, 0.05, antHeight, 10, 10); //Cone Shaped
   drawCube(0.8, 0.3, 0.1, 0, 0, antHeight);
   glPopMatrix(); 
}

void Robot::rotateAntenna(){
   //THIS MAY NEED TO BE PER ROBOT MOVEMENT/STEP INSTEAD OF CONSTANT PLEASE CHANGE IT RYAN!!!
   antAngle += 5 - headRotationAngle;
   glTranslatef(antX, antY, antZ);
   glRotatef(antAngle, 0, 1, 0);
   glTranslatef(-antX, -antY, -antZ);
}

void Robot::drawNeck(){
      float neckToHeadRatio = 0.70;
   float neckRadius = headScale * neckToHeadRatio;
   float neckDiameter = neckRadius *2;     
   float neckHeight = 1;
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glColor3f(1.0, 0.27, 0);
   // I am using thaumaturgy here to find the proper location
   glTranslatef(headX, headY-neckHeight*2, -headScale+neckDiameter*neckToHeadRatio);
   glRotatef(90, 1, 0, 0);
   gluCylinder(neckQuad, neckRadius, neckRadius, neckHeight, 10, 10);
   glPopMatrix();
}

void Robot::drawBody(){
   glPushMatrix();
   // square on back of head for identification
   glTranslatef(headX, headY, headZ);
   glRotatef(rotate_cube, 0.0, 0.0, 1.0);
   //translate body down by headScale, -1 for neck height * 2.25 for body height
   drawCube(headScale*1.5, headScale*2, headScale*1.5, 0, -(headScale+1)*2.25, 0);  
   drawBackTriangles();
   glPopMatrix();  
   glMatrixMode(GL_MODELVIEW);
}

void Robot::drawBackTriangles(){
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
