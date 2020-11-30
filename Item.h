#pragma once

#include "Actor.h"

class Item : public Actor
{
public:
	Item(float x, float y, int item, Game* game);

	bool equals(Item* i);

	int item = -1;

	int const venda = 0;
	int const vente_vente = 1;
	int const brimstone = 2;
	int const collar_guppy = 3;
	int const ojo = 4;
	int const oblea = 5;
};

