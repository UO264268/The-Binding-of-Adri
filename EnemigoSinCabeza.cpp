#include "EnemigoSinCabeza.h"

EnemigoSinCabeza::EnemigoSinCabeza(float x, float y, Game* game)
	: Enemy("res/enemy2.png", x, y, 48, 48, game) {

	state = game->stateMoving;

	aHitted = new Animation("res/enemigos/cuerpo_enemigo_hitted.png", width, height,
		32, 32, 6, 1, false, game);

	aDying = new Animation("res/enemigos/cuerpo_enemigo_hitted.png", width, height,
		32, 32, 6, 1, false, game);

	movimientoX = new Animation("res/enemigos/enemigo_caminar_lado.png", width, height,
		256, 32, 2, 8, true, game);

	movimientoY = new Animation("res/enemigos/enemigo_caminar_defrente.png", width, height,
		320, 32, 2, 10, true, game);
	
	parado = new Animation("res/enemigos/cuerpo_enemigo_parado.png", width, height,
		32, 32, 1, 1, true, game);

	sangre = new Animation("res/enemigos/enemigo_sinCabeza_cabeza.png", width, height,
		192, 32, 5, 4, true, game);

	animation = movimientoX;

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
	sangre->update();

	// Acabo la animación, no sabemos cual
	if (endAnimation) {
		// Estaba muriendo
		if (state == game->stateDying) {
			state = game->stateDead;
		}

		if (state == game->stateHitted) {
			state = game->stateMoving;
		}
	}

	if (state == game->stateMoving) {
		if (vx != 0) {
			animation = movimientoX;
		}

		if (vy != 0) {
			animation = movimientoY;
		}

		if (vy == 0 && vx == 0) {
			animation = parado;
		}
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

Enemy* EnemigoSinCabeza::impacted(int damage) {
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

	return NULL;
}

void EnemigoSinCabeza::draw(float scrollX, float scrollY){
	animation->draw(x - scrollX, y - scrollY);
	sangre->draw(x - scrollX, y - scrollY - 10);
}