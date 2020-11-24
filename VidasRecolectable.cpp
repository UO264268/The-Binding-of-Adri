#include "VidasRecolectable.h"

VidasRecolectable::VidasRecolectable(float x, float y, Game* game)
	: Recolectable(x, y, game) {

	animation = new Animation("res/vida_recolectable.png", width, height, 16, 13, 6, 1, true, game);
}

int VidasRecolectable::recoger() {
	return game->corazon;
}