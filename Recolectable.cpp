#include "recolectable.h"


Recolectable::Recolectable(float x, float y, Game* game)
	: Actor("res/icono_recolectable.png", x, y, 40, 32, game) {

	vx = 0;

	animation = new Animation("res/recolectable.png", width, height, 256, 32, 6, 8, true, game);
}

Recolectable::Recolectable(float x, float y, float width, float height, Game* game)
	: Actor("res/icono_recolectable.png", x, y, width, height, game) {

	vx = 0;

	animation = new Animation("res/recolectable.png", width, height, 256, 32, 6, 8, true, game);
}

void Recolectable::update() {
	animation->update();
}

void Recolectable::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}

int Recolectable::recoger() {
	return 0;
}
