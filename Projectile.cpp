#include "Projectile.h"

Projectile::Projectile(float x, float y, Game* game) :
	Actor("res/disparo_jugador2.png", x, y, 20, 20, game) {
	vx = 15;
	vy = -10; // La gravedad inicial es 1
}

void Projectile::update() {
	if (vy != 0)
		vy = vy + 0.00001; // La gravedad suma 1 en cada actualización restamos para anularla 
	if (vx != 0) {
		if (vx < 0)
			vx = vx + 0.000001;
		if (vx > 0)
			vx = vx - 0.000001;
	}
}
