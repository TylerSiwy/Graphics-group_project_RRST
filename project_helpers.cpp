
void drawCube(float xScale, float yScale, float zScale,
	      float xTrans, float yTrans, float zTrans){  
   glPushMatrix();
   glTranslatef(xTrans ,yTrans, zTrans);
   /*Cutting these in half since each vertex is the scale distance from the
     centerpoint and we want it to be to the scale provided, not twice as large.
     We could probably find a better solution later. */
   /*xScale = xScale / 2;
   yScale = yScale / 2;
   zScale = zScale / 2;*/
   // Puke Green - FRONT
   glBegin(GL_POLYGON);
   glColor3f(0.1, 0.5, 0.5);
   glVertex3f(xScale, -yScale, -zScale); 
   glVertex3f(xScale, yScale, -zScale); 
   glVertex3f(-xScale, yScale, -zScale);
   glVertex3f(-xScale, -yScale, -zScale); 
   glEnd();
 
   // Brown Face - BACK
   glBegin(GL_POLYGON);
   glColor3f(0.8, 0.5, 0.3);  
   glVertex3f(-xScale, -yScale, zScale);
   glVertex3f(-xScale, yScale, zScale);
   glVertex3f(xScale, yScale, zScale);
   glVertex3f(xScale, -yScale, zScale);
   glEnd();
 
   // Purple side - RIGHT
   glBegin(GL_POLYGON);
   glColor3f(1.0, 0.0, 1.0);
   glVertex3f( xScale, -yScale, zScale);
   glVertex3f( xScale, yScale, zScale);
   glVertex3f( xScale, yScale, -zScale);
   glVertex3f( xScale, -yScale, -zScale);
   glEnd();
 
   // Green side - LEFT
   glBegin(GL_POLYGON);
   glColor3f(0.0, 1.0, 0.0);
   glVertex3f(-xScale, -yScale, -zScale);
   glVertex3f(-xScale, yScale, -zScale);
   glVertex3f(-xScale, yScale, zScale);
   glVertex3f(-xScale, -yScale, zScale);
   glEnd();
 
   // Blue side - TOP
   glBegin(GL_POLYGON);
   glColor3f(0.0, 0.0, 1.0);
   glVertex3f(-xScale, yScale, zScale);
   glVertex3f(-xScale, yScale, -zScale);
   glVertex3f(xScale, yScale, -zScale);
   glVertex3f(xScale, yScale, zScale);
   glEnd();
 
   // Red side - BOTTOM
   glBegin(GL_POLYGON);
   glColor3f(1.0, 0.0, 0.0);
   glVertex3f(-xScale, -yScale, -zScale);
   glVertex3f(-xScale, -yScale, zScale);
   glVertex3f(xScale, -yScale, zScale);
   glVertex3f(xScale, -yScale, -zScale);
   glEnd();

   glPopMatrix();
}


void drawRectBuilding(float xScale, float yScale, float zScale,
		  float xTrans, float yTrans, float zTrans,
		  float buildingR, float buildingG, float buildingB){  
   glPushMatrix();
   glTranslatef(xTrans ,yTrans, zTrans);
   /*Cutting these in half since each vertex is the scale distance from the
     centerpoint and we want it to be to the scale provided, not twice as large.
     We could probably find a better solution later. */
   xScale = xScale / 2;
   //yScale = yScale / 2;
   zScale = zScale / 2;
   // Puke Green - FRONT
   glBegin(GL_POLYGON);
   glColor3f(buildingR, buildingG, buildingB);
   glVertex3f(xScale, -yScale, -zScale); 
   glVertex3f(xScale, yScale, -zScale); 
   glVertex3f(-xScale, yScale, -zScale);
   glVertex3f(-xScale, -yScale, -zScale); 
   glEnd();
 
   // Brown Face - BACK
   glBegin(GL_POLYGON);
   glColor3f(buildingR, buildingG, buildingB);  
   glVertex3f(-xScale, -yScale, zScale);
   glVertex3f(-xScale, yScale, zScale);
   glVertex3f(xScale, yScale, zScale);
   glVertex3f(xScale, -yScale, zScale);
   glEnd();
 
   // Purple side - RIGHT
   glBegin(GL_POLYGON);
   glColor3f(buildingR*0.90, buildingG*0.90, buildingB*0.90);
   glVertex3f( xScale, -yScale, zScale);
   glVertex3f( xScale, yScale, zScale);
   glVertex3f( xScale, yScale, -zScale);
   glVertex3f( xScale, -yScale, -zScale);
   glEnd();
 
   // Green side - LEFT
   glBegin(GL_POLYGON);
   glColor3f(buildingR*0.5, buildingG*0.5, buildingB*0.5);
   glVertex3f(-xScale, -yScale, -zScale);
   glVertex3f(-xScale, yScale, -zScale);
   glVertex3f(-xScale, yScale, zScale);
   glVertex3f(-xScale, -yScale, zScale);
   glEnd();
 
   // Blue side - TOP
   glBegin(GL_POLYGON);
   glColor3f(buildingR*1.1, buildingG*1.1, buildingB*1.1);
   glVertex3f(-xScale, yScale, zScale);
   glVertex3f(-xScale, yScale, -zScale);
   glVertex3f(xScale, yScale, -zScale);
   glVertex3f(xScale, yScale, zScale);
   glEnd();
 
   // Red side - BOTTOM
   glBegin(GL_POLYGON);
   glColor3f(1.0, 0.0, 0.0);
   glVertex3f(-xScale, -yScale, -zScale);
   glVertex3f(-xScale, -yScale, zScale);
   glVertex3f(xScale, -yScale, zScale);
   glVertex3f(xScale, -yScale, -zScale);
   glEnd();

   glPopMatrix();
}

void drawPyramidBuilding(float scale,
			 float buildingR, float buildingG, float buildingB ){
   glPushMatrix();
   
   glBegin(GL_TRIANGLES);           // Begin drawing the pyramid
   // Front
   //glColor3f(buildingR*0.9, buildingG*0.9, buildingB*0.9);
   glColor3f(1.0f, 0.0f, 0.0f);     // Red
   glVertex3f(scale/2, 0, scale/2);
   glVertex3f(-scale/2, 0, scale/2);
   glVertex3f( 0.0f, scale*2, 0.0f);
 
   // Right
   //glColor3f(buildingR*0.5, buildingG*0.5, buildingB*0.5);
    glColor3f(0.0f, 0.0f, 1.0f);     // Blue

   glVertex3f(scale/2, 0, -scale/2);
   glVertex3f(scale/2, 0, scale/2);
   glVertex3f(0.0f, scale*2, 0.0f);
 
   // Back
   //glColor3f(buildingR*0.9, buildingG*0.9, buildingB*0.9);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
   glVertex3f(-scale/2, 0, -scale/2);
   glVertex3f(scale/2, 0, -scale/2);
   glVertex3f(0.0f, scale*2, 0.0f);

   // Left
   //glColor3f(buildingR*1.1, buildingG*1.1, buildingB*1.1);
    glColor3f(1.0f, 0.0f, 1.0f);       // Purple

   glVertex3f(-scale/2, 0, scale/2);
   glVertex3f(-scale/2, 0,-scale/2);
   glVertex3f( 0.0f, scale*2, 0.0f);
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

void drawCylinderBuilding(float scale, GLUquadric *quad){
   float height = scale*4;
   glPushMatrix();
   glRotatef(90, 1, 0, 0);
   glColor3f(0.44, 0.26, 0.03);
   gluCylinder(quad, scale, scale, height, 20, 20);
   glPopMatrix();
   /*
   glPushMatrix();
   //glRotatef(180, 1, 0, 0);
   //glTranslatef(0, height, 0);
   gluDisk(quad, scale*0.25, scale*0.25, 20, 10);
   glPopMatrix();*/
}
