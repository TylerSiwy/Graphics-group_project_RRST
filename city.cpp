#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "city.h"
using namespace std;

City::zone::zone(bool isRoad) {
   road = isRoad;
}

City::City(int xSize, int zSize) {
   vector<City::zone> roads;
   vector<City::zone> blocks;
   for(int i = 0; i < xSize * 2 + 1; i++)
      roads.push_back(City::zone(true));
   blocks.push_back(City::zone(true));
   for(int i = 0; i < xSize; i++) {
      blocks.push_back(City::zone(false));
      blocks.push_back(City::zone(true));
   }   
   cityLayout.push_back(roads);
   for(int i = 0; i < zSize; i++) {
      cityLayout.push_back(blocks);
      cityLayout.push_back(roads);
   }
}

void City::drawCity(double blockSize) {
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glTranslatef((-static_cast<double>(cityLayout[0].size() - 1) / 2) * blockSize,
		0, (-static_cast<double>(cityLayout.size() - 1) / 2) * blockSize);
   for(int i = 0; i < cityLayout.size(); i++)
      for(int j = 0; j < cityLayout[i].size(); j++) {
	 if(cityLayout[i][j].road) {
	    glPushMatrix();

	    glTranslatef(blockSize * j, 0, blockSize * i);
	    glBegin(GL_QUADS);
	    glColor3f(0.1, 0.1, 0.1);
	    glVertex3f(blockSize / 2, 0, -blockSize / 2);
	    glVertex3f(-blockSize / 2, 0, -blockSize / 2);
	    glVertex3f(-blockSize / 2, 0, blockSize / 2);
	    glVertex3f(blockSize / 2, 0, blockSize / 2);
	    glEnd();
	    glPopMatrix();
	 }
	 else {
	    glPushMatrix();

	    glTranslatef(blockSize * j, 0, blockSize * i);
	    glBegin(GL_QUADS);
	    glColor3f(0.376, 0.502, 0.22);
	    glVertex3f(blockSize / 2, 0, -blockSize / 2);
	    glVertex3f(-blockSize / 2, 0, -blockSize / 2);
	    glVertex3f(-blockSize / 2, 0, blockSize / 2);
	    glVertex3f(blockSize / 2, 0, blockSize / 2);
	    glEnd();
	    glPopMatrix();
	 }

      }
   glPopMatrix();
}

void City::printLayout() {
   for(int i = 0; i < cityLayout.size(); i++) {
      for(int j = 0; j < cityLayout[i].size(); j++) {
	 if(cityLayout[i][j].road)
	    cout << 'R';
	 else
	    cout << ' ';
      }
      cout << endl;
   }
}

bool City::isRoad(int x, int z) {
   if(x >= cityLayout[0].size() || x < 0)
      return false;
   if(z >= cityLayout.size() || z < 0)
      return false;
   return zone.road;
}
