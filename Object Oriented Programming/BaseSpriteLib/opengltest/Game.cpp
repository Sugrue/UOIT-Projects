#include "Game.h"
#include "drawPrimitives.h"


using namespace std;

/* this is called by std::sort to sort the list based on layerID 
 *  for drawing in the proper order 
 */



bool spriteSortingFunction(Sprite *s1, Sprite *s2)
{
	// return true if s1's layerID is less than s2's layerID
	return (s1->layerID < s2->layerID);
}
Game::Game(void)
{
	/* green background */
	stateInfo.bgClearColor.red = 0;
	stateInfo.bgClearColor.green = 1;
	stateInfo.bgClearColor.blue = 0;

	/* init state */
	stateInfo.gameState = STATE_GAMEPLAY;
	renderingTimer = new Timer("RENDER");
	updateTimer = new Timer("UPDATE");

/* Map data – a new variable is used simply for ease of input, the contains are then transferred to the actual map variable
	Map Legend:

	# = Roads
	I = Intersection (helps keep the cars moving without getting clumped in one spot) – Optional but Recommended
	X = towers
	‘ ‘ = empty space, any character may be used for this
*/

char Temp[] = 
{	' ', 'I', '#', '#', '#','#', 'I', '#', '#', 'I','#', '#', 'I', '#', '#','#', '#', '#', 'I', ' ',
	' ', '#', ' ', ' ', ' ',' ', '#', ' ', ' ', ' ',' ', ' ', '#', ' ', ' ',' ', ' ', ' ', '#', ' ',
	' ', '#', ' ', ' ', ' ',' ', '#', ' ', ' ', ' ',' ', ' ', '#', ' ', ' ',' ', ' ', ' ', '#', ' ',
	' ', '#', ' ', ' ', ' ',' ', '#', ' ', ' ', ' ',' ', ' ', '#', ' ', ' ',' ', ' ', ' ', '#', ' ',
	' ', '#', ' ', ' ', ' ',' ', '#', ' ', ' ', ' ',' ', ' ', '#', ' ', ' ',' ', ' ', ' ', '#', ' ',
	' ', '#', ' ', ' ', ' ',' ', '#', ' ', ' ', ' ',' ', ' ', '#', ' ', ' ',' ', ' ', ' ', '#', ' ',
	' ', '#', ' ', ' ', ' ',' ', '#', ' ', ' ', ' ',' ', ' ', '#', ' ', ' ',' ', ' ', ' ', '#', ' ',
	' ', 'I', '#', '#', '#','#', 'I', '#', '#', '#','#', '#', 'I', '#', '#','#', '#', '#', 'I', ' ',
	' ', '#', ' ', ' ', ' ',' ', '#', ' ', ' ', ' ',' ', ' ', '#', ' ', ' ',' ', ' ', ' ', '#', ' ',
	' ', '#', ' ', ' ', ' ',' ', '#', ' ', ' ', ' ',' ', ' ', '#', ' ', ' ',' ', ' ', ' ', '#', ' ',
	' ', '#', ' ', ' ', ' ',' ', '#', ' ', ' ', 'X',' ', ' ', '#', ' ', ' ',' ', ' ', ' ', '#', ' ',
	' ', '#', ' ', ' ', ' ',' ', '#', ' ', ' ', ' ',' ', ' ', '#', ' ', ' ',' ', ' ', ' ', '#', ' ',
	' ', '#', ' ', ' ', ' ',' ', '#', ' ', ' ', ' ',' ', ' ', '#', ' ', ' ',' ', ' ', ' ', '#', ' ',
	' ', '#', ' ', ' ', ' ',' ', '#', ' ', ' ', ' ',' ', ' ', '#', ' ', ' ',' ', ' ', ' ', '#', ' ',
	' ', 'I', '#', '#', '#','#', 'I', '#', '#', 'I','#', '#', 'I', '#', '#','#', '#', '#', 'I', ' ',
	' ', '#', ' ', ' ', ' ',' ', '#', ' ', ' ', '#',' ', ' ', '#', ' ', ' ',' ', ' ', ' ', '#', ' ',
	' ', '#', ' ', ' ', ' ',' ', '#', ' ', ' ', '#',' ', ' ', '#', ' ', ' ',' ', ' ', ' ', '#', ' ',
	' ', '#', ' ', ' ', ' ',' ', 'I', '#', '#', 'I','#', '#', 'I', ' ', ' ',' ', ' ', ' ', '#', ' ',
	' ', '#', ' ', ' ', ' ',' ', '#', ' ', ' ', '#',' ', ' ', '#', ' ', ' ',' ', ' ', ' ', '#', ' ',
	' ', '#', ' ', ' ', ' ',' ', '#', ' ', ' ', '#',' ', ' ', '#', ' ', ' ',' ', ' ', ' ', '#', ' ',
	' ', '#', ' ', ' ', ' ',' ', '#', ' ', ' ', '#',' ', ' ', '#', ' ', ' ',' ', ' ', ' ', '#', ' ',
	' ', 'I', '#', '#', '#','#', 'I', '#', '#', 'I','#', '#', 'I', '#', '#','#', '#', '#', 'I', ' ',
	' ', '#', ' ', ' ', ' ',' ', '#', ' ', ' ', ' ',' ', ' ', '#', ' ', ' ',' ', ' ', ' ', '#', ' ',
	' ', '#', ' ', ' ', ' ',' ', '#', ' ', ' ', ' ',' ', ' ', '#', ' ', ' ',' ', ' ', ' ', '#', ' ',
	' ', '#', ' ', ' ', ' ',' ', '#', ' ', ' ', 'X',' ', ' ', '#', ' ', ' ',' ', ' ', ' ', '#', ' ',
	' ', '#', ' ', ' ', ' ',' ', '#', ' ', ' ', ' ',' ', ' ', '#', ' ', ' ',' ', ' ', ' ', '#', ' ',
	' ', '#', ' ', ' ', ' ',' ', '#', ' ', ' ', ' ',' ', ' ', '#', ' ', ' ',' ', ' ', ' ', '#', ' ',
	' ', '#', ' ', ' ', ' ',' ', '#', ' ', ' ', ' ',' ', ' ', '#', ' ', ' ',' ', ' ', ' ', '#', ' ',
	' ', 'I', '#', 'I', '#','#', 'I', '#', '#', '#','#', '#', 'I', '#', '#','#', 'I', '#', 'I', ' ',
	' ', ' ', ' ', '#', ' ',' ', '#', ' ', ' ', ' ',' ', ' ', '#', ' ', ' ',' ', '#', ' ', ' ', ' ',
	' ', ' ', ' ', '#', ' ',' ', '#', ' ', ' ', ' ',' ', ' ', '#', ' ', ' ',' ', '#', ' ', ' ', ' ',
	' ', ' ', ' ', '#', ' ',' ', '#', ' ', ' ', ' ',' ', ' ', '#', ' ', ' ',' ', '#', ' ', ' ', ' ',
	' ', ' ', ' ', '#', ' ',' ', '#', ' ', ' ', ' ',' ', ' ', '#', ' ', ' ',' ', '#', ' ', ' ', ' ',
	' ', ' ', ' ', '#', ' ',' ', '#', ' ', ' ', ' ',' ', ' ', '#', ' ', ' ',' ', '#', ' ', ' ', ' ',
	' ', ' ', ' ', '#', ' ',' ', '#', ' ', ' ', ' ',' ', ' ', '#', ' ', ' ',' ', '#', ' ', ' ', ' ',
	' ', ' ', ' ', '#', ' ',' ', '#', ' ', ' ', ' ',' ', ' ', '#', ' ', ' ',' ', '#', ' ', ' ', ' ',
	' ', ' ', ' ', '#', ' ',' ', '#', ' ', ' ', ' ',' ', ' ', '#', ' ', ' ',' ', '#', ' ', ' ', ' ',
	' ', ' ', ' ', 'I', '#','#', 'I', '#', '#', '#','#', '#', 'I', '#', '#','#', 'I', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' '};
	strcpy(map,Temp); //copies map to map variable
	numOfUpdates = 1; //used in calculation of avg QOS
	avgQOS = 1; 
}
Game::~Game(void){} //destructor

void Game::drawMap() {
	//draws roads and towers based on the contains of the map
	//adds roads to a road sprite vector and tower to sprite vector for later reference

	Sprite* Temp;

	for (int i= 1; map[i]; i++) {
		if (map[i-1]=='#' || map[i-1]=='I') {
			Temp = new Sprite("images/road.png");
			Temp->setNumberOfAnimations(1);
			Temp->setSpriteFrameSize(width, height);
			Temp->addSpriteAnimFrame(0,0,0);
			Temp->setPosition( ((i%column)*width), (row-(i/column))*height);
			Temp->setLayerID(0);
			this->addSpriteToDrawList(Temp);
			this->Road.insert(this->Road.end(), Temp);
		}
		if (map[i-1]=='X') {
			Temp = new Sprite("images/tower.png");
			Temp->setNumberOfAnimations(1);
			Temp->setSpriteFrameSize(width, height);
			Temp->addSpriteAnimFrame(0,0,0);
			Temp->setPosition( ((i%column)*width), (row-(i/column))*height);
			Temp->setLayerID(1);
			this->addSpriteToDrawList(Temp);
			this->Tower.insert(this->Tower.end(), Temp);
		}

	}
}
void Game::drawHUD() {
	//draws the HUD that displaces QOS stats

	std::ostringstream Temp;
	std::string strQOS;

	setColor(0,0,0);
	drawRectangle(true,0,0,1100,100,0);
	setColor(1,1,1);
	drawRectangle(true,10,10,1080,80,0);
	setColor(0,0,0);

	Temp<<"Cur. QOS: "<<currentQOS<<"%";
	strQOS = Temp.str();
	drawText(strQOS,20,20);
	Temp.str("");

	Temp<<"Avg. QOS: "<<avgQOS<<"%";
	strQOS = Temp.str();
	drawText(strQOS,520,20);
}
void Game::initializeGame()
{
	//initializes the game

	int floor = 1, ceiling = 3, range = (ceiling - floor);
	int carPlacementRND = 120;
	int j = 0;
	drawMap(); //draws map
	
	//populates the carSprite vector with all the cars
	for (int i=0; i<numCar; i++) {
		this->Car.insert(this->Car.end(), new carSprite("images/car.png"));
		this->Car[i]->setSpriteFrameSize(50,50);
		this->Car[i]->setNumberOfAnimations(1);
		this->Car[i]->addSpriteAnimFrame(0, 0,0);
		this->Car[i]->addSpriteAnimFrame(0,50,0);
		this->Car[i]->setCurrentAnimation(2);
		this->Car[i]->nextFrame();
		this->Car[i]->setLayerID(2);
		this->addSpriteToDrawList(this->Car[i]);
	}

	//places cars in a random fashion on the map, then adds them to the draw sprite list
	for (int i= 1; map[i]; i++) {
		if (map[i-1]=='#' || map[i-1]=='I' && j < this->Car.size()) {
			if (carPlacementRND == 0) {
				this->Car[j]->setPosition( ((i%column)*width), (row-(i/column))*height);
				this->addSpriteToDrawList(this->Car[j]);
				j++;
				carPlacementRND = floor + int((range * rand()) / (RAND_MAX + 1.1));
			} else 
				carPlacementRND -= 1;
			

		} else if (!(j < this->Car.size()))
			break;
	}	
}

void Game::draw()
{
	/* pre-draw - setup the rendering */
	PreDraw();

	/* draw - actually render to the screen */
	DrawGame();
	
	/* post-draw - after rendering, setup the next frame */
	PostDraw();
}
void Game::PreDraw()
{
/*
 * Pre-Draw() is for setting up things that need to happen in order to draw
 *    the game, i.e. sorting, splitting things into appropriate lists etc.
 */
	/* clear the screen */
	glViewport(0,0,stateInfo.windowWidth,stateInfo.windowHeight);
	glClearColor(stateInfo.bgClearColor.red, 
				 stateInfo.bgClearColor.green, 
				 stateInfo.bgClearColor.blue, 0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity(); // clear out the transformation matrix
	glEnable(GL_TEXTURE_2D); // turn on texturing

	// if we update our timer it will tell us the elapsed time since the previous 
	// frame that we rendered
	renderingTimer->tick();


	/* sort the sprites by layerID so we draw them in the right order */
	std::sort(spriteListToDraw.begin(), spriteListToDraw.end(), spriteSortingFunction);

}
void Game::DrawGame()
{
	//draws sprites
	drawSprites();

	glDisable(GL_TEXTURE_2D);
	setColor(1,0,0);

	//places a circle around the towers, shows the cell coverage
	for (int i = 0; i < this->Tower.size(); i++) 
		drawCircle(100,7*width,this->Tower[i]->positionX, this->Tower[i]->positionY);
	
	//draws QOS hud
	drawHUD();


	glutSwapBuffers();
}
void Game::PostDraw(){}
void Game::drawSprites()
{
	std::vector<Sprite*>::iterator it; 
	for(it=spriteListToDraw.begin(); it != spriteListToDraw.end();it++)
	{
		Sprite *s = (*it);
		s->draw();
	}

}

void Game::update()
{
	//updates sprites

	updateTimer->tick();
	int withinRange = 0;

	//updates all cars and collects range information for them (in range or not)
	for (int i = 0; i < this->Car.size(); i++) {
		this->Car[i]->update(this->Road, this->Tower, this->map);
		if(this->Car[i]->getInRange())
			withinRange++;
	}

	//based on the range data collected from cars, calculates the QOS
	currentQOS = (withinRange/(numCar + 0.0))*100;
	avgQOS = ((avgQOS*numOfUpdates)+currentQOS)/(numOfUpdates+1);
	numOfUpdates++;	
}
void Game::addSpriteToDrawList(Sprite *s){	
/* 
 * addSpriteToDrawList()
 * - this function simply pushes the sprite to the end of the list
 */
	if(s)
	{
		/* push the sprite to the back of the list */
		this->spriteListToDraw.push_back(s);
	}
}