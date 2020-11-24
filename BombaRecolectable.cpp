#include "BombaRecolectable.h"

BombaRecolectable::BombaRecolectable(float x, float y, Game* game)
	: Recolectable(x, y, game) {
	
	animation = new Animation("res/recolectable.png", width, height, 256, 32, 6, 8, true, game);
}

int BombaRecolectable::recoger() {
	return game->bomba;
}