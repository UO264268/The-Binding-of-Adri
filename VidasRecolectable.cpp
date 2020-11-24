#include "VidasRecolectable.h"

VidasRecolectable::VidasRecolectable(float x, float y, Game* game)
	: Recolectable(x, y, game) {

	animation = new Animation("res/corazon.png", width, height, 256, 32, 6, 1, true, game);
}

int VidasRecolectable::recoger() {
	return game->corazon;
}