#include "projectileEnemigo.h"

ProjectileEnemigo::ProjectileEnemigo(float x, float y, Game* game) :
	Actor("res/enemy2_disparo.png", x, y, 17, 17, game) {
	vx = -9;
	vy = 0; // La gravedad inicial es 1
	animacion = new Animation("res/enemy2_disparo.png", width, height,
		24, 24, 1, 1, true, game);

}

void ProjectileEnemigo::update() {
	vy = vy - 1; // La gravedad suma 1 en cada actualización restamos para anularla 
	animacion->update();
}

void ProjectileEnemigo::draw(float scrollX, float scrollY) {
	animacion->draw(x - scrollX, y - scrollY);
}
