#pragma once
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/glut.h"
#include "IL/il.h"
#include "IL/ilu.h"
#include "IL/ilut.h"
#include "Sprite.h"
#include "Timer.h"
#include <algorithm>
#include <cmath>
#include <string.h>
#include <sstream>
#include <stdio.h>
#include "carSprite.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* these are enumerated types (just names) of game states
   that the game can be in at any moment.  These help you
   manage the flow of the game.  Especially if you want 
   to do different updates (call different update functions)
   or have different behaviour for input (i.e. mouse and keyboard
   functions might have different behaviour in-game (STATE_GAMEPLAY)
   versus when in the Menu (STATE_MAINMENU)
*/
enum {
	STATE_GAMEPLAY=0, 
	STATE_MAINMENU, 
	STATE_CREDITS
};

// convenience structure to hold rgb values
typedef struct _RGBColor
{
	float red,green,blue;
}RGBColor;

// GameStateInfo
// this stores anything related to the state of the game
// i.e. what level are we on?, what is the score? etc.
typedef struct _GameStateInfo
{
	int gameState; // the game state, see enum's above
	RGBColor bgClearColor; // the default clear color of the background

	// window width/height are the actual size of the window
	int windowWidth, windowHeight;

	// screen width/height are the apparent size of the window
	// i.e. you can have a 640x480 game screen stretched to 1280x1024
	// your calculations for actual pixel locations will depend on the ratio
	//   between screen and window width/height
	int screenWidth, screenHeight;

	float ratioWidth,ratioHeight;
}GameStateInfo;

class Game
{
public:
	/* initialization */
	Game(void);
	~Game(void);
	void initializeGame();
	void drawMap();
	void drawHUD();

	void setScreenSize(int w, int h)
	{
		stateInfo.screenWidth = w;
		stateInfo.screenHeight = h;
	}
	void updateScreenRatio()
	{	// sets the screen-to-window pixel coordinates ratio
		stateInfo.ratioWidth = stateInfo.screenWidth/(float)stateInfo.windowWidth;
		stateInfo.ratioHeight = stateInfo.screenHeight/(float)stateInfo.windowHeight;
		/* these are only really used for the mouse function
		   to get actual screen pixel coordinates from the window coordinates */
	}
	void setNewWindowSize(int width,int height)
	{// sets the window size in pixels for the window itself
		stateInfo.windowWidth = width;
		stateInfo.windowHeight = height;
	}
	void addSpriteToDrawList(Sprite *s);
	void draw(); // called from the main
	void PreDraw(); // prior to drawing
	void DrawGame(); // actual drawing the frame
	void PostDraw(); // cleanup and prepare for next frame
	void drawSprites(); // draw the sprite list
	void drawTestPrimitives(); // test function
	void update(); // called from main frequently

	

	GameStateInfo stateInfo;

	std::vector<Sprite*> spriteListToDraw;
	std::vector<carSprite*> Car;
	std::vector<Sprite*> Road;
	std::vector<Sprite*> Tower;

	Timer *renderingTimer;
	Timer *updateTimer;
	
	
	static const int width = 50;		//pixel width of sprite
	static const int height = 50;		//pixel height of sprite
	static const int column = 20;		//number of columns
	static const int row = 40;			//number of rows
	static const int numCar = 40;		//number of cars
	long numOfUpdates;					//number of updates (for avgQOS calc.)
	double avgQOS;						
	double currentQOS;
	static const int cellRange = 40;	//Tower service range
	char map[column*row];				//char array containing map, 1d for some efficiency
};
