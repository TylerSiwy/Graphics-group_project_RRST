
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
