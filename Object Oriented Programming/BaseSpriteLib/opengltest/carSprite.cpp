#include "carSprite.h"


using namespace std;

carSprite::carSprite(std::string spriteSheetFilename) :
Sprite(spriteSheetFilename){
	//constructor
	sameMove = maxUnchangedPath;
	range = 7;
	inRange = false;
}
bool carSprite::checkOnRoad(std::vector<Sprite*> s1, int x, int y){
	//checks to see if a road exist at the provided location
	for (int i = 0; i < s1.size(); i++) {
		if (s1[i]->positionX == x && s1[i]->positionY == y) 
			return true;
	}
	return false;
}
MoveOpt carSprite::numOfOption(std::vector<Sprite*> s1) {
	//checks whats moves are available to the car (up,down,left,right). IE checks if a road exists

	MoveOpt availableMove;
	availableMove.down = false;
	availableMove.up = false;
	availableMove.left = false;
	availableMove.right = false;
	availableMove.options = 0;

	if (checkOnRoad(s1,this->positionX, this->positionY+50)){ //up
		availableMove.up = true;
		availableMove.options++;
	}
	if (checkOnRoad(s1,this->positionX, this->positionY-50)){ //down
		availableMove.down = true;
		availableMove.options++;
	}
	if (checkOnRoad(s1,this->positionX+50, this->positionY)){ //right
		availableMove.right = true;
		availableMove.options++;
	}
	if (checkOnRoad(s1,this->positionX-50, this->positionY)){ //left
		availableMove.left = true;
		availableMove.options++;
	}

	return availableMove;
}
void carSprite::randMove(std::vector<Sprite*> s1, const char Map[]) {
/*  randMove function – initial explanation 
		This function is comprised of a couple sections. A few things need to be known before explaining
			1.	A thresh hold is set, to allow the car to continue on its path without having to re-compute 
				a random decision 
			2.	The function will only recomputed a new direction if any of the following conditions are met
				a.	The car has exhausted its amount of continuous moves (set in a const in the header)
				b.	The road in (in the direction of travail) before its continuous moves are exhausted
				c.	The Car arrives at an intersection (this allows for more random paths and less clumping)
			3.	The car will avoid going in the reverse of its direction (IE. It will pick any direction but
				down if it is initially heading up, meaning if the only option is down, it will wait skip the 
				down option on its first run, then take it if no other option exist on the next cycle)
			4.	To make the moves more random, a random value between 1 and the total amount of options is 
				selected, meaning that the chosen direction/option will not necessarly be the first available 
				in the list of if statements. This is done to prevent long loops of random number being selected
				that cannot be applied, IE if the only option is up (1) and the rnd number generator dos 20 cylces 
				selecting any number but 1.
*/


	bool directionGood = false; //stores if the initial direction is still possible (if a road exist)

	//checks if the continuous moves variable is not exhaused, and if none of the other recalculation requirements are met
	if (sameMove > 0 && direction > 0 && direction < 5 && Map[((int)this->positionX/50)-1+((40-((int)this->positionY/50))*20)] != 'I')
		switch (direction)
		{
			case 1:
				if (checkOnRoad(s1,this->positionX, this->positionY+50)){ //up
					this->positionY = getPositionY() + 50.0;
					sameMove--;
					directionGood = true;
				}
				break;

			case 2:
				if (checkOnRoad(s1,this->positionX, this->positionY-50)){ //down
					directionGood = true;
					this->positionY = getPositionY() - 50.0;
					sameMove--;
				}
				break;

			case 3:
				if (checkOnRoad(s1,this->positionX+50, this->positionY)){ //right
					directionGood = true;
					this->positionX = getPositionX() + 50.0;
					sameMove--;
				}
				break;

			case 4:
				if (checkOnRoad(s1,this->positionX-50, this->positionY)){ //left
					directionGood = true;
					this->positionX = getPositionX() - 50.0;
					sameMove--;
				}
				break;
		}

	//checks if recalculation is needed, checks if any of the conditions are met
	if (!directionGood || sameMove < 0 || Map[((int)this->positionX/50)-1+((40-((int)this->positionY/50))*20)] == 'I' ) {
		int floor, ceiling, range, rnd, option = 0;
		bool move = false;
		MoveOpt availableMove;
			
		//checks amount of moves available/ which moves are available
		availableMove = numOfOption(s1);
		option = availableMove.options;
		sameMove = maxUnchangedPath;
		
		//checks if an option exists
		if (!option == 0) {
			//gets the random number used to decide which available move to take
			floor = 1;
			ceiling = option;
			range = (ceiling - floor);
			rnd = floor + int((range * rand()) / (RAND_MAX + 1.1));
			
			//explaination is provided for up, the other direction are just a repetition
			if (availableMove.up) {
				//checks if the rnd number is 1, in which case this move will be 
				//selected provided the previous direction was not its oposite
				
				if (rnd == 1 && direction != 2) {
					this->positionY = getPositionY() + 50.0; //moves the car
					direction = 1; //sets the current direction
						rnd--; //lowers rnd, to ensure no other moves are also selected/applied
				} else {
					//if the reason this move was not selected is do to rnd not being equal to 1, 
					//lower it so another option may be selected
					if (rnd != 1)
						rnd--;
					//if the reason this move was not selected is do to the previous direction
					//being its oposite, then reset the direction so that if this direction is 
					//the cars only option, on the next run it may be selected
					if (direction == 2)
						direction = 0;
					}
			}
			if (availableMove.down){
				if (rnd ==1 && direction != 1) {
					this->positionY = getPositionY() - 50.0;
					direction = 2;
					rnd--;
				} else {
					if (rnd != 1)
						rnd--;
					if (direction == 1)
						direction = 0;
				}
			}
			if (availableMove.right){
				if (rnd ==1 && direction != 4) {
					this->positionX = getPositionX() + 50.0;
					direction = 3;
					rnd--;
				} else {
					if (rnd != 1)
						rnd--;
					if (direction == 4)
						direction = 0;
				}
			}
			if (availableMove.left){
				if (rnd ==1 && direction != 3) {
					this->positionX = getPositionX() - 50.0;
					direction = 4;
					rnd--;
				} else {
					if (rnd != 1)
						rnd--;
					if (direction == 3)
						direction = 0;
					}
				}
		}
	}
}
bool carSprite::withinRange(std::vector<Sprite*> s1) {
	//checks if the car is within range of any of the towers, if there is a change in its
	//in/out of range status, update the car sprite frame to reflect the change (red = not in range,
	// geen = in range)

	for (int i=0; i<s1.size();i++) {
		if (range*50 >= sqrt(pow(this->positionX - s1[i]->positionX,2) + pow(this->positionY - s1[i]->positionY,2))) {//check if the car is in range of any tower
			if (!inRange) //if there is a change in state update the sprite frame
				this->nextFrame();
			inRange = true; //set the car "inrange" value to be pulled by the qos calculations
			return true; //return its range status
		}
	}
	if (inRange) //if not in range, but there was a change, update the sprite frame
		this->nextFrame();
	inRange = false; //set the car "inrange" value to be pulled by the qos calculation
	return false; //return its range status
}
void carSprite::update(std::vector<Sprite*> cars, std::vector<Sprite*> towers, const char Map[]) {
	randMove(cars, Map); //calls randMove, providing it with the map and a road vector sprite
	withinRange(towers); //calls in range, providing it with a tower vector sprite
}