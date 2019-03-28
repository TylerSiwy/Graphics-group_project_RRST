#pragma once
#include <iostream>
#include <vector>
#include "buildings.h" 
using namespace std;

class City {
  public:
   // Sizes are in city blocks
   City(int xSize, int zSize);
   void drawCity(double blockSize, GLenum mode);

   // Prints the city's layout to the console
   void printLayout();
   bool isRoad(unsigned int x, unsigned int z);
   int countBuildings();
   void countIndex(int index, int &x,int &z, int &l);
   //void attackBuilding(int index);
   void attackBuilding(int x, int z, int l);
  private:
   class zone {
     public:
      zone(bool isRoad);
      bool road;
      vector<Building*> buildingsOnBlock;
   };
   bool arr[1601] = {true};//////////
   vector<vector<zone>> cityLayout;
};
