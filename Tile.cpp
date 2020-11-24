#include "Tile.h"

Tile::Tile(string filename, float x, float y, bool desctructibleByBomb, Game* game)
	: Actor(filename, x, y, 40, 32, game) {
	this->desctructibleByBomb = desctructibleByBomb;
}

