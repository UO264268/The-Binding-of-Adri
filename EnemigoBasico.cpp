#include "EnemigoBasico.h"

EnemigoBasico::EnemigoBasico(float x, float y, Game* game)
	: Enemy("res/enemigo.png", x, y, 36, 40, game) {

	state = game->stateMoving;

	aDying = new Animation("res/enemigo_morir.png", width, height,
		280, 40, 6, 8, false, game);

	aMoving = new Animation("res/enemigo_movimiento.png", width, height,
		108, 40, 6, 3, true, game);
	animation = aMoving;

	vx = 1;
	vy = 0;
	
	vxIntelligence = -1;
	vyIntelligence = 0;

	vx = vxIntelligence;
	vy = vyIntelligence;

}

void EnemigoBasico::update(float xPlayer, float yPlayer) {
	// Actualizar la animaci�n
	bool endAnimation = animation->update();

	// Acabo la animaci�n, no sabemos cual
	if (endAnimation) {
		// Estaba muriendo
		if (state == game->stateDying) {
			state = game->stateDead;
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
		if (x > xPlayer) { //Player a la derecha del enemigo
			vxIntelligence = -1;
		}
		else if (x < xPlayer) { //Player a la izquierda del enemigo
			vxIntelligence = 1;
		}
		else { //Player con la misma x del enemigo
			vxIntelligence = 0;
		}

		if (y > yPlayer) { //Player debajo del enemigo
			vyIntelligence = -1;
		}
		else if (y < yPlayer) { //Player arriba del enemigo
			vyIntelligence = 1;
		}
		else { //Player a la misma altura del enemigo
			vyIntelligence = 0;
		}

		vx = vxIntelligence;
		vy = vyIntelligence;
	}
	else {
		vx = 0;
	}

}

void EnemigoBasico::impacted() {
	if (state != game->stateDying) {
		state = game->stateDying;
	}
}

void EnemigoBasico::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}

ProjectileEnemigo* EnemigoBasico::shoot() {
	return NULL;
}
