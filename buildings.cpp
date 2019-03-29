#include "buildings.h"


using namespace std;

StrongBuilding::StrongBuilding(){
   quad = gluNewQuadric();
   buildingHealth = 3;
   redScalar = 1.1;
   reduceScalar = 1.0;
}

void StrongBuilding:: draw(float scale){
   drawRectBuilding(scale, scale*3, scale,
		    0, 0, 0,
		    0.6, 0.6, 0.6);
}

void StrongBuilding::reduceHealth(int damage){
   buildingHealth -= damage;
   redScalar *= 1.15;
   reduceScalar *= 0.5;
}

WeakBuilding::WeakBuilding(){ 
   buildingHealth = 1;
}

void WeakBuilding::draw(float scale){
   drawCylinderBuilding(scale);
}

void WeakBuilding::reduceHealth(int damage){
   buildingHealth -= damage;
   
}

UnbreakableBuilding::UnbreakableBuilding(){
   buildingHealth = -1;
   quad = gluNewQuadric();
}

void UnbreakableBuilding::draw(float scale){
   drawPyramidBuilding(scale, 0.75, 0.75, 0.5);
}

void UnbreakableBuilding::reduceHealth(int damage){
   buildingHealth -= damage;
}


void Building::drawRectBuilding(float xScale, float yScale, float zScale,
		  float xTrans, float yTrans, float zTrans,
		  float buildingR, float buildingG, float buildingB){  
   glPushMatrix();
   glTranslatef(xTrans ,yTrans, zTrans);
   /*Cutting these in half since each vertex is the scale distance from the
     centerpoint and we want it to be to the scale provided, not twice as large.
     We could probably find a better solution later. */
   xScale = xScale / 2;
   zScale = zScale / 2;

   //FRONT
   glBegin(GL_POLYGON);
   //glColor3f(1.0f, 0.0f, 0.0f);     // Red
   glColor3f(buildingR*redScalar, buildingG*reduceScalar, buildingB*reduceScalar);
   glVertex3f(-xScale, yScale, -zScale);
   glVertex3f(xScale, yScale, -zScale);
   glVertex3f(xScale, 0, -zScale); 
   glVertex3f(-xScale, 0, -zScale); 
   glEnd();
 
   //BACK
   glBegin(GL_POLYGON);
   //glColor3f(0.0f, 0.0f, 1.0f);     // Blue
   glColor3f(buildingR*redScalar, buildingG*reduceScalar, buildingB*reduceScalar);
   glVertex3f(-xScale, 0, zScale);
   glVertex3f(xScale, 0, zScale);
   glVertex3f(xScale, yScale, zScale);
   glVertex3f(-xScale, yScale, zScale);
   glEnd();
 
   //RIGHT
   glBegin(GL_POLYGON);
   //glColor3f(0.0f, 1.0f, 0.0f);     // Green
   glColor3f(buildingR*0.90*redScalar, buildingG*0.90*reduceScalar, buildingB*0.90*reduceScalar);
   glVertex3f( xScale, 0, -zScale);
   glVertex3f( xScale, yScale, -zScale);
   glVertex3f( xScale, yScale, zScale);
   glVertex3f( xScale, 0, zScale);
   glEnd();
 
   //LEFT
   glBegin(GL_POLYGON);
   //glColor3f(1.0f, 0.0f, 1.0f);       // Purple
   glColor3f(buildingR*0.5*redScalar, buildingG*0.5*reduceScalar, buildingB*0.5*reduceScalar);
   glVertex3f(-xScale, 0, zScale);
   glVertex3f(-xScale, yScale, zScale);
   glVertex3f(-xScale, yScale, -zScale);
   glVertex3f(-xScale, 0, -zScale);
   glEnd();
 
   //TOP
   glBegin(GL_POLYGON);
   glColor3f(buildingR*1.1*redScalar, buildingG*1.1*reduceScalar, buildingB*1.1*reduceScalar);
   glVertex3f(xScale, yScale, zScale);
   glVertex3f(xScale, yScale, -zScale);
   glVertex3f(-xScale, yScale, -zScale);
   glVertex3f(-xScale, yScale, zScale);
   glEnd();
 
   //BOTTOM
   glBegin(GL_POLYGON);
   glColor3f(1.0, 0.0, 0.0);
   glVertex3f(-xScale, 0, -zScale);
   glVertex3f(-xScale, 0, zScale);
   glVertex3f(xScale, 0, zScale);
   glVertex3f(xScale, 0, -zScale);
   glEnd();

   glPopMatrix();
}

void Building::drawPyramidBuilding(float scale,
			 float buildingR, float buildingG, float buildingB ){
   glPushMatrix();
   
   glBegin(GL_TRIANGLES);           // Begin drawing the pyramid
   // Front
   glColor3f(buildingR*0.9, buildingG*0.9, buildingB*0.9);
   //glColor3f(1.0f, 0.0f, 0.0f);     // Red
   glVertex3f( 0.0f, scale*2, 0.0f);
   glVertex3f(-scale/2, 0, scale/2);
   glVertex3f(scale/2, 0, scale/2);
   
   // Right
   glColor3f(buildingR*0.5, buildingG*0.5, buildingB*0.5);
   //glColor3f(0.0f, 0.0f, 1.0f);     // Blue
   glVertex3f(0.0f, scale*2, 0.0f);
   glVertex3f(scale/2, 0, scale/2);
   glVertex3f(scale/2, 0, -scale/2);
 
   // Back
   glColor3f(buildingR*0.9, buildingG*0.9, buildingB*0.9);
   //glColor3f(0.0f, 1.0f, 0.0f);     // Green
   glVertex3f(0.0f, scale*2, 0.0f);
   glVertex3f(scale/2, 0, -scale/2);
   glVertex3f(-scale/2, 0, -scale/2);

   // Left
   glColor3f(buildingR*1.1, buildingG*1.1, buildingB*1.1);
   //glColor3f(1.0f, 0.0f, 1.0f);       // Purple
   glVertex3f( 0.0f, scale*2, 0.0f);
   glVertex3f(-scale/2, 0,-scale/2);
   glVertex3f(-scale/2, 0, scale/2);
   glEnd();

   //Bottom
   glBegin(GL_POLYGON);
   glColor3f(buildingR, buildingG, buildingB);
   glVertex3f(-scale/2, 0, -scale/2);
   glVertex3f(-scale/2, 0, scale/2);
   glVertex3f(scale/2, 0, scale/2);
   glVertex3f(scale/2, 0, -scale/2);
   glEnd();

   glPopMatrix();
}

void Building::drawCylinderBuilding(float scale){
   glPushMatrix();
   glScalef(scale/2, scale*2, scale/2);
   drawCylinder();
   glTranslatef(0, 1, 0);

   glPushMatrix();

   glScalef(0.75, 0.75, 0.75);
   drawCylinder();
   glTranslatef(0, 1, 0);
   
   glPushMatrix();

   glScalef(0.75, 0.75, 0.75);
   drawCylinder();
  
   glPopMatrix();
   glPopMatrix();
   glPopMatrix();
}

void Building::drawCylinder() {
   GLUquadric *quad = gluNewQuadric();
   glPushMatrix();
   glRotatef(-90, 1, 0, 0);
   glColor3f(0.75, 0.44, 0.12);
   gluCylinder(quad, 1, 1, 1, 20, 20);
   glPopMatrix();


   glPushMatrix();
   glColor3f(0.75*1.1, 0.44*1.1, 0.12*1.1);
   glTranslatef(0, 1, 0);
   glRotatef(-90, 1, 0, 0);
   gluDisk(quad, 0, 1, 20, 20);
   glPopMatrix();
}
