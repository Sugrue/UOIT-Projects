#include "Sprite.h"

using namespace std;

typedef struct MoveOpt {
	bool left;
	bool right;
	bool up;
	bool down;
	int options;
};

class carSprite : public Sprite {
public:
		bool inRange;
		int direction;
		int sameMove;
		int range;
		static const int maxUnchangedPath =10;


		carSprite(std::string spriteSheetFilename);
		~carSprite(void);
		virtual void update(std::vector<Sprite*> cars, std::vector<Sprite*> towers, const char Map[]);
		void setRange(int R) {range = R;};
		bool getInRange() {return inRange;};
		bool checkOnRoad(std::vector<Sprite*> s1, int x, int y);
		void randMove(std::vector<Sprite*> s1, const char Map []);
		bool withinRange(std::vector<Sprite*> s1);
		MoveOpt numOfOption(std::vector<Sprite*> s1);

		
		
};