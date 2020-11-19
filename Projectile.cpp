#include "Projectile.h"

Projectile::Projectile(float x, float y, Game* game) :
	Actor("res/disparo_jugador2.png", x, y, 20, 20, game) {
	vx = 10;
	vy = 0; // La gravedad inicial es 1
}

void Projectile::update() {
	vy = vy;
	vx = vx;
}
