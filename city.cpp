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

   // Set up randomization
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

   // Solid length of road template
   for(int i = 0; i < xSize * 2 + 1; i++)
      roads.push_back(City::zone(true));

   // Add to city
   cityLayout.push_back(roads);

   // Create length of alternating roads and blocks. Recreate every time so that the buildings are different.
   for(int i = 0; i < zSize; i++) {
      blocks.push_back(City::zone(true));
      for(int j = 0; j < xSize; j++) {
	 blocks.push_back(City::zone(false));
	 blocks.push_back(City::zone(true));
      }
      // Alternate between both templates
      cityLayout.push_back(blocks);
      cityLayout.push_back(roads);
      blocks.clear();
   }
}

void City::drawCity(double blockSize, GLenum mode) {
   int buildingsDrawn = 1;
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   // Centre city on (0,0)
   glTranslatef((-static_cast<double>(cityLayout[0].size() - 1) / 2) * blockSize,
		0, (-static_cast<double>(cityLayout.size() - 1) / 2) * blockSize);

   // Go through every gridspace in the city
   for(unsigned int i = 0; i < cityLayout.size(); i++)
      for(unsigned int j = 0; j < cityLayout[i].size(); j++) {

	 // If this gridspace is a road
	 if(cityLayout[i][j].road) {
	    glPushMatrix();

	    // Move to gridspace location
	    glTranslatef(blockSize * j, 0, blockSize * i);
            // Draw road
	    if(mode == GL_RENDER) {
	       glBegin(GL_QUADS);
	       glColor3f(0.1, 0.1, 0.1);
	       glVertex3f(blockSize / 2, 0, -blockSize / 2);
	       glVertex3f(-blockSize / 2, 0, -blockSize / 2);
	       glVertex3f(-blockSize / 2, 0, blockSize / 2);
	       glVertex3f(blockSize / 2, 0, blockSize / 2);
	       glEnd();
	    }
	    glPopMatrix();
	 }

	 // If gridspace is a city block
	 else {
	    glPushMatrix();

	    // Move to gridspace location
	    glTranslatef(blockSize * j, 0, blockSize * i);

	    // Draw grass under building space
	    if(mode == GL_RENDER) {
	       glBegin(GL_QUADS);
	       glColor3f(0.376, 0.502, 0.22);
	       glVertex3f(blockSize / 2, 0, -blockSize / 2);
	       glVertex3f(-blockSize / 2, 0, -blockSize / 2);
	       glVertex3f(-blockSize / 2, 0, blockSize / 2);
	       glVertex3f(blockSize / 2, 0, blockSize / 2);
	       glEnd();
	    }
	    // For every building slot on the block
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
	       if(cityLayout[i][j].buildingsOnBlock[k]) {

		  // For building selection
		  if(mode == GL_SELECT) {
		     glLoadName(buildingsDrawn++);
		  }
		  
                  // Draw building
		  ////////////////////////////////////////////
		  cityLayout[i][j].buildingsOnBlock[k] -> draw(0.40 * blockSize);
	       }
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

int City::countBuildings() {
   int count = 0;
   for(unsigned int i = 0; i < cityLayout.size(); i++) {
      for(unsigned int j = 0; j < cityLayout[i].size(); j++) {
	 for(unsigned int k = 0; k < cityLayout[i][j].buildingsOnBlock.size(); k++) {
	    if(cityLayout[i][j].buildingsOnBlock[k])
	       count++;
	 }
      }
   }
   return count;
}


void City::countIndex(int index, int &x, int &z, int &l) {
   int count = 0;
   for(unsigned int i = 0; i < cityLayout.size(); i++) {
      for(unsigned int j = 0; j < cityLayout[i].size(); j++) {
	 for(unsigned int k = 0; k < cityLayout[i][j].buildingsOnBlock.size(); k++) {
	    if(cityLayout[i][j].buildingsOnBlock[k])
	       count++;
	    if(count == index) {
	       x=i;
	       z=j;
	       l=k;
	       return;
	    }
	 }
      }
   }
   return;
   // return count;
}





void City::attackBuilding(int x, int z, int l) {
   int i=x;
   int j=z;
   int k=l;
//   if(index <= this -> countBuildings()){
//      int count = 0;
   //     for(unsigned int i = 0; i < cityLayout.size(); i++) {
//	 for(unsigned int j = 0; j < cityLayout[i].size(); j++) {
//	    for(unsigned int k = 0; k < cityLayout[i][j].buildingsOnBlock.size(); k++) {
//	       if(cityLayout[i][j].buildingsOnBlock[k]) {
//		  count++;

//		  if(count == index) {
		     //This is need to "destroy" the object given these 3 coords
		     //however we decide to "destroy" the objects
		     /* cout << " BUILDING values for index " << count<<endl;
		     cout << "RobotX: " << RX << endl;
		     cout << "RobotZ: " << RZ << endl;
		     cout << "[i] " << i <<endl;
		     cout << "[j] " << j <<endl;
		     cout << "[k] " << k <<endl;*/
		     
		     cityLayout[i][j].buildingsOnBlock[k] -> reduceHealth(1);
		     if(cityLayout[i][j].buildingsOnBlock[k] -> getBuildingHealth() == 0) {
			delete cityLayout[i][j].buildingsOnBlock[k];
			cityLayout[i][j].buildingsOnBlock[k] = nullptr;
		     }
		     
//		  }
//	       } 
//	    }
//	 }
//      }
//   }
}
