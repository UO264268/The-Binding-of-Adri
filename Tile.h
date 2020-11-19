#pragma once
#include "Actor.h"

class Tile : public Actor
{
public:
	Tile(string filename, float x, float y, bool desctructibleByShoot, bool superSalto, Game* game);
	bool desctructibleByShoot;
	bool superSalto;
};

