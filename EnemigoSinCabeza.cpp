#include "EnemigoSinCabeza.h"

EnemigoSinCabeza::EnemigoSinCabeza(float x, float y, Game* game)
	: Enemy("res/enemy2.png", x, y, 49, 44, game) {

	state = game->stateMoving;

	aShooting = new Animation("res/enemy2_animacion_disparo.png", width, height,
		2560, 128, 2, 20, false, game);

	aHitted = new Animation("res/enemigo_hitted.png", width, height,
		108, 40, 6, 1, false, game);

	aDying = new Animation("res/enemy2_muerte.png", width, height,
		1152, 204, 2, 6, false, game);

	aMoving = new Animation("res/enemy2_animacion.png", width, height,
		2184, 92, 2, 24, true, game);
	animation = aMoving;

	vx = 1;
	vy = 1;

	vxIntelligence = -1;
	vyIntelligence = -1;

	vx = vxIntelligence;
	vy = vyIntelligence;

	vidas = 2;
}

void EnemigoSinCabeza::update(float xPlayer, float yPLayer) {
	// Actualizar la animación
	bool endAnimation = animation->update();

	// Acabo la animación, no sabemos cual
	if (endAnimation) {
		// Estaba muriendo
		if (state == game->stateDying) {
			state = game->stateDead;
		}

		if (state == game->stateShooting) {
			state = game->stateMoving;
		}

		if (state == game->stateHitted) {
			state = game->stateMoving;
		}
	}

	if (state == game->stateMoving) {
		animation = aMoving;
	}
	if (state == game->stateDying) {
		animation = aDying;
	}
	if (state == game->stateHitted) {
		animation = aHitted;
	}

	// Establecer velocidad
	if (state != game->stateDying) {
		if (cdCambioDireccion == 0) {
			vxIntelligence = ((rand() % 3) - 1) * 2;
			vyIntelligence = ((rand() % 3) - 1) * 2;

			vx = vxIntelligence;
			vy = vyIntelligence;

			cdCambioDireccion = 25;
		}
	}
	else {
		vx = 0;
	}

	if (cdCambioDireccion > 0) {
		cdCambioDireccion--;
	}

	if (shootTime > 0) {
		shootTime--;
	}

}

ProjectileEnemigo* EnemigoSinCabeza::shoot() {
	if (shootTime == 0 && state != game->stateDying && state != game->stateDead) {
		state = game->stateShooting;
		aShooting->currentFrame = 0;
		shootTime = shootCadence;

		int vx = 0;
		int vy = 0;

		while (vx == 0 && vy == 0) {
			vx = ((rand() % 3) - 1) * 7;
			vy = ((rand() % 3) - 1) * 7;
		}
		
		ProjectileEnemigo* projectile = new ProjectileEnemigo(x, y, vx, vy, game);

		return projectile;
	}
	else {
		return NULL;
	}
}

void EnemigoSinCabeza::impacted(int damage) {
	if (state != game->stateDying) {
		if ((vidas - damage) > 0) {
			state = game->stateHitted;
			vidas = vidas - damage;
			// 100 actualizaciones 
		}
		else {
			vidas = 0;
			state = game->stateDying;
		}
	}
}

void EnemigoSinCabeza::draw(float scrollX, float scrollY){
	animation->draw(x - scrollX, y - scrollY);
}