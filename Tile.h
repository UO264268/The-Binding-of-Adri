#pragma once
#include "Actor.h"

class Tile : public Actor
{
public:
	Tile(string filename, float x, float y, bool desctructibleByBomb, Game* game);
	bool desctructibleByBomb;
};

