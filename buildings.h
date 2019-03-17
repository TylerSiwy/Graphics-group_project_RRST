#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Building {
  public:
   virtual void draw(float scale)=0;
  protected:
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
