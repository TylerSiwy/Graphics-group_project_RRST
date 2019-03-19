#pragma once
#include <iostream>
#include <vector>
#include "buildings.h"
using namespace std;

class City {
  public:
   // Sizes are in city blocks
   City(int xSize, int zSize);
   void drawCity(double blockSize);

   // Prints the city's layout to the console
   void printLayout();
   bool isRoad(unsigned int x, unsigned int z);
  private:
   class zone {
     public:
      zone(bool isRoad);
      bool road;
      vector<Building*> buildingsOnBlock;
   };
   vector<vector<zone>> cityLayout;
};
