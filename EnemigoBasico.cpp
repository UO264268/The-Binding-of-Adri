#include "EnemigoBasico.h"

EnemigoBasico::EnemigoBasico(float x, float y, Game* game)
	: Enemy("res/enemigo.png", x, y, 48, 23, game) {

	state = game->stateMoving;

	aHitted = new Animation("res/enemigos/cuerpo_enemigo_hitted.png", width, height,
		32, 32, 6, 1, false, game);

	aHittedCabeza = new Animation("res/enemigos/enemigo_basico_cabeza_hitted.png", width, height,
		28, 25, 6, 1, false, game);

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

	aCabeza = new Animation("res/enemigos/enemigo_basico_cabeza.png", width, height,
		28, 25, 5, 1, true, game);

	animationCuerpo = movimientoX;
	animationCabeza = aCabeza;

	vx = 1;
	vy = 0;
	
	vxIntelligence = -1;
	vyIntelligence = 0;

	vx = vxIntelligence;
	vy = vyIntelligence;

	vidas = 4;
	daño = 1;
}

void EnemigoBasico::update(float xPlayer, float yPlayer) {
	// Actualizar la animación
	bool endAnimation = animationCuerpo->update();
	animationCabeza->update();
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
			animationCuerpo = movimientoX;
		}

		if (vy != 0) {
			animationCuerpo = movimientoY;
		}

		if (vy == 0 && vx == 0) {
			animationCuerpo = parado;
		}

		animationCabeza = aCabeza;
	}
	if (state == game->stateDying) {
		animationCuerpo = aDying;
	}
	if (state == game->stateHitted) {
		animationCuerpo = aHitted;
		animationCabeza = aHittedCabeza;
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
		vy = 0;
	}

}

Enemy* EnemigoBasico::impacted(int damage) {
	if (state != game->stateDying) {
		if ((vidas - damage) > 0) {
			state = game->stateHitted;
			aHitted->currentFrame = 0;
			aHittedCabeza->currentFrame = 0;
			vidas = vidas - damage;
			// 100 actualizaciones 
		}
		else {
			vidas = 0;
			state = game->stateDying;

			int a = rand() % 3;

			if (a == 0) {
				Enemy* enemy = new EnemigoSinCabeza(x, y, game);
				enemy->y = enemy->y - enemy->height / 2;
				enemy->state = game->stateMoving;
				return enemy;
			}			
		}

		return NULL;
	}
}

void EnemigoBasico::draw(float scrollX, float scrollY) {
	animationCuerpo->draw(x - scrollX, y - scrollY);
	animationCabeza->draw(x - scrollX, y - scrollY - 13);
	sangre->draw(x - scrollX, y - scrollY - 10);
}

