//// ########################################################################################################################
//// ########################################################################################################################
//// ########################################################################################################################
//#include <iostream>
//#include <vector>
//#include "Timer.h"
//#include "Sprite.h"
//#include "Map.h"
//
//using namespace std;
//
//typedef struct 
//{
//	float red;
//	float green;
//	float blue;
//} RGBColor;
//
//class GameStateInfo 
//{
//public:
//
//	// names of game states that the game can be in at any moment.  These help you manage the flow of the game.  
//	// Especially if you want to do different updates or have different behaviour for input 
//	// i.e. mouse and keyboard functions might have different behaviour in-game (STATE_GAMEPLAY) versus when in the Menu (STATE_MAINMENU)
//	enum 
//	{
//		STATE_GAMEPLAY,
//		STATE_MAINMENU, 
//		STATE_CREDITS
//	} gameState;			// the game state, see enum's above
//
//	RGBColor bgClearColor;	// the default clear color of the background
//	int windowWidth;		// window width
//	int windowHeight;		// window height
//	int screenWidth;		// screen width - you can have a 640x480 game screen stretched to 1280x1024
//	int screenHeight;		// screen height - you can have a 640x480 game screen stretched to 1280x1024
//	float ratioWidth;
//	float ratioHeight;
//
//	int score;
//};
//
//
//class Simulation
//{
//public:
//
//	Simulation();
//	~Simulation();
//	virtual void initializeGame();
//
//	void setScreenSize(int w, int h);
//	void setNewWindowSize(int width,int height);
//	void updateScreenRatio();										// used for the mouse function to get actual screen pixel coordinates from the window coordinates
//	void addSpriteToDrawList(Sprite *s);							// add a sprite to the draw list
//	void addSpriteToUpdateList(Sprite *s);							// add a sprite to the update list
//	void addSpriteToBumpList(Sprite *s);							// add a sprite to the collision list
//	void deleteSpriteDrawList();									// freee up all space used by sprites (this listh should have them all)
//	void draw();													// draw/rendering routines, called from the main
//	void PreDraw();													// prior to drawing
//	void DrawGame();												// actual drawing the frame
//	void PostDraw();												// cleanup and prepare for next frame
//	void drawSprites();												// draw the sprite list
//	void updateSprites();											// update the sprite list
//	virtual void drawHUD() {}										// draw statics
//	void update();													// update routines, called from game loop frequently
//
//	GameStateInfo stateInfo;				// game state info
//	vector<Sprite*> spriteListToDraw;	// sprite list to draw
//	vector<Sprite*> spriteListToUpdate;	// sprite list to detect collisions
//	Sprite *testSprite;						// individual sprites to manipulate by name
//	//Sprite *animatedSprite;					// individual sprites to manipulate by name
//	//Sprite *animatedSprite2;				// individual sprites to manipulate by name
//	Sprite *Dkong;							// individual sprites to manipulate by name
//
//	Timer *renderingTimer;	// timer for rendering and animation
//	Timer *updateTimer;		// timer for physics/collisions etc.
//};
//
//// ########################################################################################################################
//// ########################################################################################################################
//// ########################################################################################################################
//
