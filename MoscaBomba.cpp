#include "MoscaBomba.h"

MoscaBomba::MoscaBomba(float x, float y, Game* game)
	: Enemy("res/enemigo.png", x, y, 48, 48, game) {

	state = game->stateMoving;

	aHitted = new Animation("res/enemigos/mosca_bomba_hitted.png", width, height,
		32, 32, 6, 1, false, game);

	aMoving = new Animation("res/enemigos/mosca_bomba.png", width, height,
		64, 32, 6, 2, true, game);
	animation = aMoving;

	vx = 0;
	vy = 0;

	vxIntelligence = 2;
	vyIntelligence = 2;

	vx = vxIntelligence;
	vy = vyIntelligence;

	vidas = 3;

}

void MoscaBomba::deleteAnimations() {
	
	delete aHitted;
	delete aShooting;
	delete aMoving;
	delete aDying;
}

void MoscaBomba::update(float xPlayer, float yPlayer) {
	// Actualizar la animación
	bool endAnimation = animation->update();

	// Acabo la animación, no sabemos cual
	if (endAnimation) {
		if (state == game->stateHitted) {
			state = game->stateMoving;
		}
	}

	if (state == game->stateMoving) {
		animation = aMoving;
	}
	if (state == game->stateHitted) {
		animation = aHitted;
	}

	if (state != game->stateDying) {
		if (vx == 0) {
			vxIntelligence = vxIntelligence * -1;
		}
		if (vy == 0) {
			vyIntelligence = vyIntelligence * -1;
		}

		vx = vxIntelligence;
		vy = vyIntelligence;
	}
	else {
		vx = 0;
		vy = 0;
	}

	if (shootTime > 0) {
		shootTime--;
	}

}

Enemy* MoscaBomba::impacted(int damage) {
	if (state != game->stateDying) {
		if ((vidas - damage) > 0) {
			state = game->stateHitted;
			aHitted->currentFrame = 0;
			vidas = vidas - damage;
			// 100 actualizaciones 
		}
		else {
			vidas = 0;
			state = game->stateDying;
		}

		return NULL;
	}
}

void MoscaBomba::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}

Explosion* MoscaBomba::explode() {
	if (state == game->stateDying) {
		state = game->stateDead;
		Explosion* explosion = new Explosion(x, y, game);
		return explosion;
	}
	return NULL;
}
