#include "Enemy.h"

Enemy::Enemy(string s, float x, float y, float ancho, float alto, Game* game)
	: Actor(s, x, y, ancho, alto, game) {

	state = game->stateMoving;

	aDying = new Animation("res/enemigo_morir.png", width, height,
		280, 40, 6, 8, false, game);

	aHitted = new Animation("res/enemigo_hitted.png", width, height,
		108, 40, 6, 1, false, game);

	aMoving = new Animation("res/enemigo_movimiento.png", width, height,
		108, 40, 6, 3, true, game);
	animation = aMoving;

	vx = 1;
	vxIntelligence = -1;
	vx = vxIntelligence;

	vidas = 1;

}

void Enemy::update(float xPlayer, float yPLayer) {
	// Actualizar la animación
	bool endAnimation = animation->update();

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

void Enemy::impacted(int damage) {
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

void Enemy::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}

ProjectileEnemigo* Enemy::shoot() {
	return NULL;
}