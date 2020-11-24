#include "Bomba.h"

Bomba::Bomba(float x, float y, Game* game)
	: Actor("res/moneda.png", x, y, 40, 40, game) {

	aExploding = new Animation("res/recolectable.png", width, height, 256, 32, 6, 8, false, game);
	animation = aExploding;

	vx = 0;

	state = game->stateExploding;
}

void Bomba::update() {
	// Actualizar la animación
	bool endAnimation = animation->update();

	// Acabo la animación, no sabemos cual
	if (endAnimation) {
		if (state == game->stateExploding) {
			state = game->stateExploited;
		}
	}
}

void Bomba::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}

Explosion* Bomba::explode() {
	if (state == game->stateExploited) {
		Explosion* explosion = new Explosion(x, y, game);
		return explosion;
	}
	return NULL;
}
