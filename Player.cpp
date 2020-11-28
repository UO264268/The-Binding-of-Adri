#include "Player.h"

Player::Player(float x, float y, Game* game)
	: Actor("res/jugador.png", x, y, 48, 23, game) {

	cabezaJugador = new CabezaJugador(x, y-20, game);
	cuerpoJugador = new CuerpoJugador(x, y, game);
	
	orientacionCaminar = game->orientationBottom;
	orientacionDisparos = game->orientationBottom;
	state = game->stateMoving;
}

void Player::deleteAnimations() {
	cabezaJugador->deleteAnimations();
	cuerpoJugador->deleteAnimations();
	delete cabezaJugador;
	delete cuerpoJugador;
}

void Player::update() {
	if (invulnerableTime > 0) {
		invulnerableTime--;
	}

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
	if (vy == 0 && vx == 0) {
		orientacionCaminar = game->noDisparando;
	}

	cabezaJugador->update(orientacionDisparos);
	cuerpoJugador->update(orientacionCaminar);

	if (bombTime > 0) {
		bombTime--;
	}

	cabezaJugador->moveX(x);
	cuerpoJugador->moveX(x);

	cabezaJugador->moveY(y - 17);
	cuerpoJugador->moveY(y);
}

void Player::moveX(float axis) {
	vx = axis * 5;
}

void Player::moveY(float axis) {
	vy = axis * 5;
}

Projectile* Player::shoot() {
	return cabezaJugador->shoot();
}

void Player::draw(float scrollX, float scrollY) {
	if (invulnerableTime == 0) {
		cuerpoJugador->draw(scrollX, scrollY);
		cabezaJugador->draw(scrollX, scrollY);
	}
	else {
		if (invulnerableTime % 10 >= 0 && invulnerableTime % 10 <= 5) {
			cuerpoJugador->draw(scrollX, scrollY);
			cabezaJugador->draw(scrollX, scrollY);
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

