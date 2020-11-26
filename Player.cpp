#include "Player.h"

Player::Player(float x, float y, Game* game)
	: Actor("res/jugador.png", x, y, 32, 20, game) {

	
	orientacionCaminar = game->orientationBottom;
	orientacionDisparos = game->orientationBottom;
	state = game->stateMoving;
	audioShoot = new Audio("res/efecto_disparo.wav", false);

	caminarDerecha = new Animation("res/player/isaac_cuerpo_derecha.png", width, height,
		320, 14, 2, 10, true, game);
	caminarIzquierda = new Animation("res/player/isaac_cuerpo_izquierda.png", width, height,
		320, 14, 2, 10, true, game);
	caminarAbajo = new Animation("res/player/isaac_cuerpo_defrente.png", width, height,
		320, 15, 2, 10, true, game);
	caminarArriba = new Animation("res/player/isaac_cuerpo_defrente.png", width, height,
		320, 15, 2, 10, true, game);

	dispararDerecha = new Animation("res/player/isaac_cabeza_disparando_derecha.png", width, height,
		58, 25, 10, 2, true, game);
	dispararIzquierda = new Animation("res/player/isaac_cabeza_disparando_izquierda.png", width, height,
		58, 25, 10, 2, true, game);
	dispararAbajo = new Animation("res/player/isaac_cabeza_disparando_abajo.png", width, height,
		58, 25, 10, 2, true, game);
	dispararArriba = new Animation("res/player/isaac_cabeza_disparando_arriba.png", width, height,
		58, 25, 10, 2, true, game);

	cuerpoParado = new Animation("res/player/isaac_cuerpo_parado.png", width, height,
		32, 13, 1, 1, true, game);

	animacionCabeza = dispararAbajo;
	animacionCuerpo = cuerpoParado;

}


void Player::update() {
	if (invulnerableTime > 0) {
		invulnerableTime--;
	}

	bool endAnimationCabeza = animacionCabeza->update();
	bool endAnimationCuerpo = animacionCuerpo->update();

	// Establecer orientación
	if (vx > 0) {
		orientacionCaminar = game->orientationRight;
	}
	if (vx < 0) {
		orientacionCaminar = game->orientationLeft;
	}
	if (vy > 0) {
		orientacionCaminar = game->orientationUp;
	}
	if (vy < 0) {
		orientacionCaminar = game->orientationBottom;
	}

	if (state == game->stateMoving) {
		if (vx != 0) {
			if (orientacionCaminar == game->orientationRight) {
				animacionCuerpo = caminarDerecha;
				animacionCabeza = dispararDerecha;
			}

			if (orientacionCaminar == game->orientationLeft) {
				animacionCuerpo = caminarIzquierda;
				animacionCabeza = dispararIzquierda;
			}
		}

		if (vy != 0) {
			if (orientacionCaminar == game->orientationBottom) {
				animacionCuerpo = caminarAbajo;
				animacionCabeza = dispararArriba;
			}

			if (orientacionCaminar == game->orientationUp) {
				animacionCuerpo = caminarArriba;
				animacionCabeza = dispararAbajo;
			}
		}

		if (vx == 0 && vy == 0) {
			animacionCuerpo = cuerpoParado;
		}
	}

	
	if (orientacionDisparos == game->orientationBottom) {
		animacionCabeza = dispararAbajo;
	}

	if (orientacionDisparos == game->orientationUp) {
		animacionCabeza = dispararArriba;
	}

	if (orientacionDisparos == game->orientationLeft) {
		animacionCabeza = dispararIzquierda;
	}

	if (orientacionDisparos == game->orientationRight) {
		animacionCabeza = dispararDerecha;
	}

	if (shootTime > 0) {
		shootTime--;
	}

	if (bombTime > 0) {
		bombTime--;
	}
}

void Player::moveX(float axis) {
	vx = axis * 5;
}

void Player::moveY(float axis) {
	vy = axis * 5;
}

Projectile* Player::shoot() {
	if (shootTime == 0) {
		audioShoot->play();
		shootTime = shootCadence;
		Projectile* projectile = new Projectile(x, y, game);
		
		return projectile;
	}
	else {
		return NULL;
	}
}

void Player::draw(float scrollX, float scrollY) {
	if (invulnerableTime == 0) {
		animacionCuerpo->draw(x - scrollX, y - scrollY);
		animacionCabeza->draw(x - scrollX, y - scrollY - 23);
	}
	else {
		if (invulnerableTime % 10 >= 0 && invulnerableTime % 10 <= 5) {
			animacionCuerpo->draw(x - scrollX, y - scrollY);
			animacionCabeza->draw(x - scrollX, y - scrollY - 23);
		}
	}
}

void Player::loseLife(float damage) {
	if (invulnerableTime <= 0) {
		if ((lifes-damage) > 0) {
			lifes = lifes - damage;
			invulnerableTime = 100;
			// 100 actualizaciones 
		}
		else {
			lifes = 0;
		}
	}
}

Bomba* Player::ponerBomba() {
	if (bombTime == 0 && bombas > 0) {
		bombTime = bombCadence;
		Bomba* bomba = new Bomba(x, y, game);
		bombas--;
		return bomba;
	}
	else {
		return NULL;
	}
}

