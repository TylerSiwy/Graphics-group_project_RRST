#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdlib>
#include "city.h"
using namespace std;

City::zone::zone(bool isRoad) {
   static bool seeded = false;
   if(!seeded) {
      srand(time(NULL));
      seeded = true;
   }
   road = isRoad;
   if(!isRoad) {
      for(int i = 0; i < 4; i++) {
	 switch(rand() % 3) {
	    case 0:
	       buildingsOnBlock.push_back(new UnbreakableBuilding);
	       break;
	    case 1:
	       buildingsOnBlock.push_back(new WeakBuilding);
	       break;
	    case 2:
	       buildingsOnBlock.push_back(new StrongBuilding);
	       break;
	    default:
	       buildingsOnBlock.push_back(nullptr);
	       break;
	 }
      }
   }
}

City::City(int xSize, int zSize) {
   vector<City::zone> roads;
   vector<City::zone> blocks;
   for(int i = 0; i < xSize * 2 + 1; i++)
      roads.push_back(City::zone(true));
   
   
   cityLayout.push_back(roads);
   for(int i = 0; i < zSize; i++) {
      blocks.push_back(City::zone(true));
      for(int j = 0; j < xSize; j++) {
	 blocks.push_back(City::zone(false));
	 blocks.push_back(City::zone(true));
      }
      cityLayout.push_back(blocks);
      cityLayout.push_back(roads);
      blocks.clear();
   }
}

void City::drawCity(double blockSize) {
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glTranslatef((-static_cast<double>(cityLayout[0].size() - 1) / 2) * blockSize,
		0, (-static_cast<double>(cityLayout.size() - 1) / 2) * blockSize);
   for(unsigned int i = 0; i < cityLayout.size(); i++)
      for(unsigned int j = 0; j < cityLayout[i].size(); j++) {
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
	    
	    for(unsigned int k = 0; k < cityLayout[i][j].buildingsOnBlock.size(); k++) {
	       glPushMatrix();
	       switch(k) {
		 case 0:
		    glTranslatef(-blockSize/4, 0, -blockSize/4);
		    break;
		  case 1:
		     glTranslatef(blockSize/4, 0, -blockSize/4);
		     break;
		  case 2:
		     glTranslatef(blockSize/4, 0, blockSize/4);
		     break;
		  case 3:
		     glTranslatef(-blockSize/4, 0, blockSize/4);
		     break;
		     }
	       if(cityLayout[i][j].buildingsOnBlock[k])
		  cityLayout[i][j].buildingsOnBlock[k] -> draw(0.40 * blockSize);
	       glPopMatrix();
	    }
	    
	    glPopMatrix();
	 }

      }
   glPopMatrix();
}

void City::printLayout() {
   for(unsigned int i = 0; i < cityLayout.size(); i++) {
      for(unsigned int j = 0; j < cityLayout[i].size(); j++) {
	 if(cityLayout[i][j].road)
	    cout << 'R';
	 else
	    cout << ' ';
      }
      cout << endl;
   }
}

bool City::isRoad(unsigned int x, unsigned int z) {
   if(x >= cityLayout[0].size() || x < 0)
      return false;
   if(z >= cityLayout.size() || z < 0)
      return false;
   return cityLayout[z][x].road;
}
