#pragma once

#include "Tile.h"

class Caca : public Tile
{
public:
	Caca(float x, float y, Game* game);
	void perderVida();
	int vida = 3;
};

