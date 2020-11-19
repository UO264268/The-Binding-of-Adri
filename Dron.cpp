#include "Dron.h"

Dron::Dron(float x, float y, Game* game)
	: Enemy("res/enemy2.png", x, y, 49, 44, game) {

	state = game->stateMoving;

	aShooting = new Animation("res/enemy2_animacion_disparo.png", width, height,
		2560, 128, 2, 20, false, game);

	aDying = new Animation("res/enemy2_muerte.png", width, height,
		1152, 204, 2, 6, false, game);

	aMoving = new Animation("res/enemy2_animacion.png", width, height,
		2184, 92, 2, 24, true, game);
	animation = aMoving;

	vx = 2;
	vxIntelligence = -2;
	vx = vxIntelligence;

}

void Dron::update() {
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
	}

	if (state == game->stateMoving) {
		animation = aMoving;
	}
	if (state == game->stateDying) {
		animation = aDying;
	}

	// Establecer velocidad
	if (state != game->stateDying) {
		// no está muerto y se ha quedado parado
		if (vx == 0) {
			vxIntelligence = vxIntelligence * -1;
			vx = vxIntelligence;
		}
		if (outRight) {
			// mover hacia la izquierda vx tiene que ser negativa
			if (vxIntelligence > 0) {
				vxIntelligence = vxIntelligence * -1;
			}
			vx = vxIntelligence;
		}
		if (outLeft) {
			// mover hacia la derecha vx tiene que ser positiva
			if (vxIntelligence < 0) {
				vxIntelligence = vxIntelligence * -1;
			}
			vx = vxIntelligence;
		}

	}
	else {
		vx = 0;
	}

	if (shootTime > 0) {
		shootTime--;
	}

}

ProjectileEnemigo* Dron::shoot() {
	if (shootTime == 0 && state != game->stateDying && state != game->stateDead) {
		state = game->stateShooting;
		aShooting->currentFrame = 0;
		shootTime = shootCadence;
		ProjectileEnemigo* projectile = new ProjectileEnemigo(x, y, game);

		return projectile;
	}
	else {
		return NULL;
	}
}

void Dron::impacted() {
	if (state != game->stateDying) {
		state = game->stateDying;
	}
}

void Dron::draw(float scrollX) {
	animation->draw(x - scrollX, y);
}