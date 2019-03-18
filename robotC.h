#pragma once
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>   // OpenGL itself.
#include <GL/glu.h>  // GLU support library.
#include <GL/glut.h> // GLUT support library.
#include <iostream>
using namespace std;

class Robot {
  public:
   Robot();
   void setHeadRotationAngle(float newAngle);
   void smoothRotate(float angle); // Smoothly rotates the robot's head
   void draw(float scale); //Draws all compenents of the robot
  protected:
   //All other components should be dynamically sized from headScale
   float headScale; 
   float headX, headY, headZ;
   float headRotationAngle;

   float currentAngle; // Added for smooth rotation
   
   float antX, antY, antZ;
   float antAngle;
   float neckX, neckY, neckZ;
   //Angle of head for rotation during initial setup
   float rotate_cube;
   GLUquadric *antQuad;
   GLUquadric *neckQuad;
   GLUquadric *quad;
   GLUquadric *eyeQuad;
  private:
   void drawCube(float xScale, float yScale, float zScale,
		 float xTrans, float yTrans, float zTrans);
   void drawAndRotateHead(); //Draws the head and handles it's rotation
   void drawHead(); //Draws the head, including eyes, antenna, and neck
   void drawEyes(); //Draws only the eyes
   void drawAntenna(); //Draws only the antenna
   void rotateAntenna(); //Does the antenna's rotation
   void drawNeck(); //Draws only the neck
   void drawBody(); //Draws the body, including the backTriangles
   void drawBackTriangles(); //Draws only the backTriangles

   float getHeadRotationAngle();
};

