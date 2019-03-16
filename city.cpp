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

City::City(int length, int width) {
   vector<City::zone> roads;
   vector<City::zone> blocks;
   for(int i = 0; i < length * 2 + 1; i++)
      roads.push_back(City::zone(true));
   blocks.push_back(City::zone(true));
   for(int i = 0; i < length; i++) {
      blocks.push_back(City::zone(false));
      blocks.push_back(City::zone(true));
   }   
   cityLayout.push_back(roads);
   for(int i = 0; i < width; i++) {
      cityLayout.push_back(blocks);
      cityLayout.push_back(roads);
   }
}

void City::drawCity(double blockSize) {
   //glMatrixMode(GL_MODELVIEW);
   for(int i = 0; i < cityLayout.size(); i++)
      for(int j = 0; j < cityLayout[i].size(); j++) {
	 if(cityLayout[i][j].road) {
	    glPushMatrix();

	    glTranslatef(blockSize * i, 0, blockSize * j);
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

	    glTranslatef(blockSize * i, 0, blockSize * j);
	    glBegin(GL_QUADS);
	    glColor3f(0.9, 0.9, 0.9);
	    glVertex3f(blockSize / 2, 0, -blockSize / 2);
	    glVertex3f(-blockSize / 2, 0, -blockSize / 2);
	    glVertex3f(-blockSize / 2, 0, blockSize / 2);
	    glVertex3f(blockSize / 2, 0, blockSize / 2);
	    glEnd();
	    glPopMatrix();
	 }

      }
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
