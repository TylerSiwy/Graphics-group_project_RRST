#prama once
#include <iostream>
#include <vector>
using namespace std;

class Building {
  public:
   virtual void draw()=0;
  private:
   int buildingScale;
   int clicks;//Number of clicks from the user
};

class StrongBuilding: public Building {
  public:
   void draw();
}

class WeakBuilding: public Building {
  public:
   void draw();
}

class UnbreakableBuilding: public Building {
  public:
   void draw();
}
