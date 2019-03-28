#pragma once
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>   // OpenGL itself.
#include <GL/glu.h>  // GLU support library.
#include <GL/glut.h> // GLUT support library.
#include <iostream>
#include <cmath>
using namespace std;

class Robot {
  public:
   Robot();
   void setHeadRotationAngle(float newAngle);
   int smoothRotate(float angle); // Smoothly rotates the robot's head
   void draw(float scale,bool paused); //Draws all compenents of the robot
  protected:
   //All other components should be dynamically sized from headScale
   float headScale;
    //Used to translate the robot to the correct position on creation
   float robotOffset;
   float headX, headY, headZ;
   float headRotationAngle;

   float currentAngle; // Added for smooth rotation
   
   float antX, antY, antZ;
   float antAngle;
   float neckX, neckY, neckZ;
   float neckToHeadRatio;
   float headToBodyScalar;
   float bodyHeight;
   float bodyWidth;
   float neckHeight;
   float headHeight;
   //Angle of head for rotation during initial setup
   float rotate_cube;
   GLUquadric *antQuad;
   GLUquadric *neckQuad;
   GLUquadric *quad;
   GLUquadric *eyeQuad;
  private:
   void drawCube(float xScale, float yScale, float zScale,
		 float xTrans, float yTrans, float zTrans);
   void drawAndRotateHead(bool paused); //Draws the head and handles it's rotation
   void drawHead(bool paused); //Draws the head, including eyes, antenna, and neck
   void drawEyes(); //Draws only the eyes
   void drawAntenna(bool paused); //Draws only the antenna
   void rotateAntenna(bool paused); //Does the antenna's rotation
   void drawNeck(); //Draws only the neck
   void drawBody(); //Draws the body, including the backTriangles
   void drawBackTriangles(); //Draws only the backTriangles

   float getHeadRotationAngle();
};

