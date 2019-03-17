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
   quad = gluNewQuadric();
}

void StrongBuilding:: draw(float scale){
   drawRectBuilding(scale, scale*3, scale,
		    0, 0, 0,
		    0.6, 0.6, 0.6);
}

WeakBuilding::WeakBuilding(){
   clicks = 0;
   quad = gluNewQuadric();
}

void WeakBuilding::draw(float scale){
   drawCylinderBuilding(scale, quad);
}

UnbreakableBuilding::UnbreakableBuilding(){
   clicks = 0;
   quad = gluNewQuadric();
}

void UnbreakableBuilding::draw(float scale){
   drawPyramidBuilding(scale, 0.75, 0.75, 0.5);
}
