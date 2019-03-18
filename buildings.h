#pragma once
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
using namespace std;

class Building {
  public:
   virtual void draw(float scale)=0;
  protected:
   void drawCube(float xScale, float yScale, float zScale,
		 float xTrans, float yTrans, float zTrans);
   void drawRectBuilding(float xScale, float yScale, float zScale,
			 float xTrans, float yTrans, float zTrans,
			 float buildingR, float buildingG, float buildingB);
   void drawPyramidBuilding(float scale, float buildingR,
			    float buildingG, float buildingB);
   void drawCylinderBuilding(float scale);
   GLUquadric *quad;
   int buildingScale;
   int clicks;//Number of clicks from the user
};

class StrongBuilding: public Building {
  public:
   StrongBuilding();
   void draw(float scale);
};

class WeakBuilding: public Building {
  public:
   WeakBuilding();
   void draw(float scale);
};

class UnbreakableBuilding: public Building {
  public:
   UnbreakableBuilding();
   void draw(float scale);
};
