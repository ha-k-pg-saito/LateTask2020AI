#ifndef Game_h_
#define Game_h_

#include"AI_Rule.h"
#include"AI_State.h"
#include"Item.h"
#include"Collision.h"

class Game
{
public:
	Game();
	~Game();
	void Update();
	void Draw();

private:
	unsigned int Timer;

	AI_Rule     AI_R;
	AI_State    AI_S;
	Collision collision;

};


#endif
