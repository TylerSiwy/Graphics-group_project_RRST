#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Building {
  public:
   virtual void draw()=0;
  protected:
   int buildingScale;
   int clicks;//Number of clicks from the user
};

class StrongBuilding: public Building {
  public:
   StrongBuilding();
   void draw();
};

class WeakBuilding: public Building {
  public:
   WeakBuilding();
   void draw();
};

class UnbreakableBuilding: public Building {
  public:
   UnbreakableBuilding();
   void draw();
};
