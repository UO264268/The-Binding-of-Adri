#include "BombaRecolectable.h"

BombaRecolectable::BombaRecolectable(float x, float y, Game* game)
	: Recolectable(x, y, game) {
	
	animation = new Animation("res/recolectables/bomba_recolectable.png", width, height, 20, 21, 6, 1, true, game);
}

int BombaRecolectable::recoger() {
	return game->bomba;
}