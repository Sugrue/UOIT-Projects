#include "Grid.h"

void Grid::setMap(vector<char[]> m) {
	Map = m;
}

vector<char[]> Grid::getMap(){
	return Map;
}
void Grid::Draw(){

	setColor(0.2, 0.2, 0);
	for(int i = 0; i < GridX; i++)
	{
		for(int j = 0, c = Map[i][j]; c != 0; j++, c = Map[i][j])
		{
			if (Map[i][j] == '#')
				drawRectangle(true, 
					i*GridX, 
					j*GridY, 
					0.5,
					0.5,
					0);
				break;
			}
		}
	}