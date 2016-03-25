
#include <string>
#include <vector>
#include <windows.h>
#include <algorithm>
#include "GL/glut.h"
#include "IL/ilut.h"

using namespace std;

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

class XY_Coordinate
{
public:

	XY_Coordinate(float _x, float _y, float _u, float _v){ x=_x; y=_y; u = _u; v=_v;}

	float x;
	float y;
	float u;
	float v;
};

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################



// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

typedef struct _SpriteSheetInfo
{
	unsigned int textureID;
	float width,height;
}SpriteSheetInfo;

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

typedef struct _SpriteSize
{
	float width, height;
	float normalizedWidth,normalizedHeight;
}SpriteSize;

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

// this class takes care of everything related to sprites - loading/drawing/setting states etc.

class Sprite
{
public:

	// FUNCTIONS = METHODS

	Sprite(string spriteSheetFilename);

	virtual void draw();


	void loadSpriteSheet(const char *filename);
	void setSpriteFrameSize(int width, int height);
	void setLayerID(float value) { layerID = value; }
	void setCenter(float x, float y) { centerX = x; centerY = y; }
	void setPosition(float x, float y) { positionX = x; positionY = y; }
	void setOrientation(float _theta) { theta = _theta; }
	float getOrientation() {return theta;}


	// DATA = ATTRIBUTES

	SpriteSize sz;
	SpriteSheetInfo sheet;
	unsigned int numberOfAnimations;
	unsigned int currentAnimation;

	float positionX;
	float positionY;
	float centerX;
	float centerY;
	float theta;							// orientation
	int layerID;							// which layer this sprite is on, lower is further away, background is 0, foreground > 0
};

// ########################################################################################################################
// ########################################################################################################################
// ########################################################################################################################

