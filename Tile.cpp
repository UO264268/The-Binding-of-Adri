#include "Tile.h"

Tile::Tile(string filename, float x, float y, bool desctructibleByShoot, bool superSalto, Game* game)
	: Actor(filename, x, y, 40, 32, game) {
	this->desctructibleByShoot = desctructibleByShoot;
	this->superSalto = superSalto;
}

