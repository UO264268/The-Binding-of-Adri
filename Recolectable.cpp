#include "recolectable.h"


Recolectable::Recolectable(float x, float y, Game* game)
	: Actor("res/icono_recolectable.png", x, y, 40, 40, game) {

	vx = 0;

	animation = new Animation("res/recolectable.png", width, height, 256, 32, 6, 8, true, game);
}

void Recolectable::update() {
	animation->update();
}

void Recolectable::draw(float scrollX) {
	animation->draw(x - scrollX, y);
}
