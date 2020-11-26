#include "Bomba.h"

Bomba::Bomba(float x, float y, Game* game)
	: Actor("res/moneda.png", x, y, 40, 40, game) {

	aExploding = new Animation("res/recolectables/bomba.png", width, height, 88, 21, 4, 4, false, game);
	animation = aExploding;

	a = 1;

	state = game->stateExploding;
}

void Bomba::update() {
	// Actualizar la animación
	bool endAnimation = animation->update();

	// Acabo la animación, no sabemos cual
	if (endAnimation) {
		if (state == game->stateExploding && a == 0) {
			state = game->stateExploited;
		}
		else if (state == game->stateExploding && a > 0) {
			a--;
			animation->currentFrame = 0;
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
