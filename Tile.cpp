#include "Tile.h"

Tile::Tile(string filename, float x, float y, bool desctructibleByBomb, Game* game)
	: Actor(filename, x, y, 40, 32, game) {
	this->desctructibleByBomb = desctructibleByBomb;
}

Tile::Tile(string filename, float x, float y, float width, float height, bool desctructibleByBomb, Game* game)
	: Actor(filename, x, y, width, height, game) {
	this->desctructibleByBomb = desctructibleByBomb;
}

Tile::Tile(string filename, float x, float y, float width, float height, bool desctructibleByBomb, bool destructibleByShoot, Game* game)
	: Actor(filename, x, y, width, height, game) {
	this->desctructibleByBomb = desctructibleByBomb;
	this->destructibleByShoot = destructibleByShoot;
}

