#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "buildings.h"
#include "project_helpers.cpp"

using namespace std;

StrongBuilding::StrongBuilding(){
   clicks=0;
}

void StrongBuilding:: draw(){
   cout << "DRAWN STRONG";
}

WeakBuilding::WeakBuilding(){
   clicks = 0;
}

void WeakBuilding::draw(){
   cout << "DRAWN WEAK";
}

UnbreakableBuilding::UnbreakableBuilding(){
   clicks = 0;
}

void UnbreakableBuilding::draw(){
   cout << "DRAWN UNBREAKABLE";
}
