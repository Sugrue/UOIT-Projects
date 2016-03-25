#include <stdlib.h>
#include "GL/glut.h"
#include "Primitives.h"
#include <iostream>
#include <vector>

using namespace std;

class Grid 
{
public:
	void setMap(vector <char[]> m);
	vector<char[]> getMap();
	void Draw();
	void setGridX(int x);
	void setGridY(int y);


private:
	int GridY;
	int GridX;
	vector <char[]> Map;

	
};