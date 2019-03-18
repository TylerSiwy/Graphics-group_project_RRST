#include "robotC.h"

Robot::Robot(){
   //initializing variables
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
   neckToHeadRatio = 0.70;
   rotate_cube = 0;
   //For smooth rotation
   currentAngle = 0;
   headToBodyScalar = 2;
   neckHeight = headScale/4;
   bodyHeight = headScale * 2.25;
   robotOffset = 0;
}

void Robot::draw(float scale){
   robotOffset = headScale + neckToHeadRatio*headScale + bodyHeight; 
   headHeight = headScale * 2;
   glMatrixMode(GL_MODELVIEW);
   headScale = scale; 
   glPushMatrix();
   //glRotatef(90, 0, 1, 0); //For debugging only
   glTranslatef(0, robotOffset, 0);
   drawAndRotateHead();
   drawBody();
   glPopMatrix();
}

// Smoothly rotates the robot's head to left or right. Where angle
// is the max angle to rotate to.
void Robot::smoothRotate(float angle){
   if(angle > 0){
      currentAngle += 10;
      if(currentAngle > angle)
	 currentAngle = angle;
      //rotateRight = true;
   }
   if(angle < 0){
      currentAngle -= 10;
      if(currentAngle < angle)
	 currentAngle = angle;
      //rotateLeft = true;
   }
}

void Robot::drawAndRotateHead(){
   glPushMatrix();
   //glRotatef(smoothRotate(headRotationAngle), 0, 1, 0);
   drawHead();
   glPopMatrix();
}

void Robot::setHeadRotationAngle(float newAngle){
   headRotationAngle = newAngle;
}

float Robot::getHeadRotationAngle(){
   return headRotationAngle;
}

void Robot::drawHead(){
   float backHeadScale = headScale * 0.55; //used for the square on back of head
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
   float eyeRadius = 0.3*headScale;
   float resolution = 10;
   float headCenterOffset = headScale + 0.01;
   //Right Eye
   glPushMatrix();   
   glTranslatef(headScale/2, headScale/3, headCenterOffset);
   glColor3f(1.0,1.0, 1.0);
   gluDisk(eyeQuad, 0, eyeRadius, resolution, 1);
   glPopMatrix();
   //Left Eye
   glPushMatrix();
   glTranslatef(-headScale/2, headScale/3, headCenterOffset);
   glColor3f(1.0, 1.0, 1.0);
   gluDisk(eyeQuad, 0, eyeRadius, resolution, 1);
   glPopMatrix();
}

void Robot::drawAntenna(){
   antY=headScale;
   float antRadius = 0.15;
   float antHeight = 0.75*headScale;
   float antRotation = 270;
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   rotateAntenna();
   glTranslatef(antX, antY, antZ);
   glRotatef(antRotation, 1.0, 0 ,0.0);
   glColor3f(0.6,0.1,0.3); //Purple
   gluCylinder(antQuad, antRadius, 0.05, antHeight, 10, 10); //Cone Shaped
   drawCube(0.6*headScale, 0.2*headScale, 0.05*headScale, 0, 0, antHeight);
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
   float neckRadius = headScale * neckToHeadRatio;
   float neckDiameter = neckRadius *2;     
   neckY = abs(headY - headScale);
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glColor3f(1.0, 0.27, 0);
   // I am using thaumaturgy here to find the proper location
   glTranslatef(headX, -neckY, -headScale+neckDiameter*neckToHeadRatio);
   glRotatef(90, 1, 0, 0);
   gluCylinder(neckQuad, neckRadius, neckRadius, neckHeight, 10, 10);
   glPopMatrix();
}

void Robot::drawBody(){
   glPushMatrix();
   // square on back of head for identification
   glTranslatef(headX, -(headHeight+neckHeight+neckY), headZ);
   glRotatef(rotate_cube, 0.0, 0.0, 1.0);
   //translate body down by headScale, -1 for neck height * 2.25 for body height
   drawCube(headScale*1.5, headScale*headToBodyScalar,
	    headScale*1.5, 0, 0, 0);  
   drawBackTriangles();
   glPopMatrix();  
   glMatrixMode(GL_MODELVIEW);
}

void Robot::drawBackTriangles(){
   // triangles on back of body for identification
   float backPolyScale = headScale;
   glPushMatrix();
   glBegin(GL_POLYGON);
   glColor3f(1.0, 0.1, 0.1);
   glVertex3f(backPolyScale, bodyHeight/8, -headScale*3.6);
   glVertex3f(-backPolyScale, bodyHeight/8,  -headScale*3.6); 
   glVertex3f(0, backPolyScale*2, -headScale*3.6);  //Point
   glEnd();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0,-bodyHeight/3,0);
   glBegin(GL_POLYGON);
   glColor3f(1.0, 0.1, 0.1);
   glVertex3f(backPolyScale, bodyHeight/8, -headScale*3.6);
   glVertex3f(-backPolyScale, bodyHeight/8,  -headScale*3.6); 
   glVertex3f(0, backPolyScale*2, -headScale*3.6);  //Point
   glEnd();
   glPopMatrix();
  

      
   glEnd();
}

void Robot::drawCube(float xScale, float yScale, float zScale,
		     float xTrans, float yTrans, float zTrans){  
   glPushMatrix();
   glTranslatef(xTrans ,yTrans, zTrans);
   //FRONT
   glBegin(GL_POLYGON);
   glColor3f(0.1, 0.5, 0.5);
   glVertex3f(-xScale, -yScale, -zScale);
   glVertex3f(-xScale, yScale, -zScale);
   glVertex3f(xScale, yScale, -zScale);  
   glVertex3f(xScale, -yScale, -zScale);
   glEnd();
   
   //BACK
    glBegin(GL_POLYGON);
   glColor3f(0.8, 0.5, 0.3);
   glVertex3f(xScale, -yScale, zScale);
   glVertex3f(xScale, yScale, zScale);
   glVertex3f(-xScale, yScale, zScale);
   glVertex3f(-xScale, -yScale, zScale);
   glEnd();
 
   // Purple side - RIGHT
   glBegin(GL_POLYGON);
   glColor3f(1.0, 0.0, 1.0);
   glVertex3f( xScale, -yScale, -zScale);
   glVertex3f( xScale, yScale, -zScale);
   glVertex3f( xScale, yScale, zScale);
   glVertex3f( xScale, -yScale, zScale);  
   glEnd();
 
   // Green side - LEFT
   glBegin(GL_POLYGON);
   glColor3f(0.0, 1.0, 0.0);
   glVertex3f(-xScale, -yScale, zScale);
   glVertex3f(-xScale, yScale, zScale);
   glVertex3f(-xScale, yScale, -zScale);
   glVertex3f(-xScale, -yScale, -zScale);
   glEnd();
 
   // Blue side - TOP
   glBegin(GL_POLYGON);
   glColor3f(0.0, 0.0, 1.0);
   glVertex3f(xScale, yScale, zScale);
   glVertex3f(xScale, yScale, -zScale);
   glVertex3f(-xScale, yScale, -zScale);
   glVertex3f(-xScale, yScale, zScale);
   glEnd();
 
   // Red side - BOTTOM
   glBegin(GL_POLYGON);
   glColor3f(1.0, 0.0, 0.0);
   glVertex3f(xScale, -yScale, -zScale);
   glVertex3f(xScale, -yScale, zScale);
   glVertex3f(-xScale, -yScale, zScale);
   glVertex3f(-xScale, -yScale, -zScale);
   glEnd();

   glPopMatrix();
}
