#include "Projectile.h"

Projectile::Projectile(float x, float y, Game* game) :
	Actor("res/disparo_jugador2.png", x, y, 20, 20, game) {
	vx = 10;
	vy = 0; // La gravedad inicial es 1

	animation = new Animation("res/player/disparo.png", width, height, 13, 14, 6, 1, true, game);
}

void Projectile::update() {
	animation->update();
}

void Projectile::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}

void Projectile::deleteAnimations() {
	delete animation;
}
