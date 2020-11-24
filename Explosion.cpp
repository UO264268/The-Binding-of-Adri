#include "Explosion.h"

Explosion::Explosion(float x, float y, Game* game)
	: Actor("res/moneda.png", x, y, 125, 125, game) {
	
	state = game->stateExploding;

	aExploding = new Animation("res/explosion.png", width, height,
		1152, 96, 2, 12, false, game);

	animation = aExploding;

	vx = 0;
	vy = 0;
}

void Explosion::update() {
	bool endAnimation = animation->update();

	if (endAnimation) {
		state = game->stateExploited;
	}
}

void Explosion::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}
