#pragma once
#include <iostream>
#include <vector>
using namespace std;

class City {
  public:
   class zone {
     public:
      zone(bool isRoad);
      bool road;
   };
   City(int length, int width);

   void drawCity(double blockSize);
   void printLayout();
   // private:
   vector<vector<zone>> cityLayout;
   int cityLength;
   int cityWidth;
};
