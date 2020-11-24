#include "Explosion.h"

Explosion::Explosion(float x, float y, Game* game)
	: Actor("res/moneda.png", x, y, 250, 250, game) {
	
	state = game->stateExploding;

	aExploding = new Animation("res/enemy2_muerte.png", width, height,
		1152, 204, 2, 6, false, game);

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
