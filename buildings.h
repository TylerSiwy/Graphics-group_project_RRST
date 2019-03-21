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
   int getBuildingHealth(){return buildingHealth;};
   virtual ~Building() {};
   virtual void draw(float scale) = 0; 
   virtual void reduceHealth(int damage) = 0;
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
   int buildingHealth;
   float redScalar;
   float reduceScalar;
   
};

class StrongBuilding: public Building {
  public:
   StrongBuilding();
   ~StrongBuilding() {};
   void reduceHealth(int damage);
   void draw(float scale);
  private:
   
};

class WeakBuilding: public Building {
  public:
   WeakBuilding();
   ~WeakBuilding() {};
   void reduceHealth(int damage);
   void draw(float scale);
};

class UnbreakableBuilding: public Building {
  public:
   UnbreakableBuilding();
   ~UnbreakableBuilding() {};
   void reduceHealth(int damage);
   void draw(float scale);
};
