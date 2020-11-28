#include "Caca.h"

Caca::Caca(float x, float y, Game* game)
	: Tile("res/mapeado/caca3.png", x, y, 40, 32, true, true, game) {
}

void Caca::perderVida() {
	vida--;
	if(vida==2)
		texture = game->getTexture("res/mapeado/caca2.png");
	if(vida==1)
		texture = game->getTexture("res/mapeado/caca1.png");
}