#include "CabezaJugador.h"

CabezaJugador::CabezaJugador(float x, float y, Game* game)
	: Actor("res/player/cabeza.png", x, y, 43, 27, game) {
	audioShoot = new Audio("res/efecto_disparo.wav", false);

	dispararDerecha = new Animation("res/player/isaac_cabeza_disparando_derecha.png", width, height,
		58, 25, 10, 2, true, game);
	dispararIzquierda = new Animation("res/player/isaac_cabeza_disparando_izquierda.png", width, height,
		58, 25, 10, 2, true, game);
	dispararAbajo = new Animation("res/player/isaac_cabeza_disparando_abajo.png", width, height,
		58, 25, 10, 2, true, game);
	dispararArriba = new Animation("res/player/isaac_cabeza_disparando_arriba.png", width, height,
		58, 25, 10, 2, true, game);

	animacion = dispararAbajo;
}

void CabezaJugador::update(int orientacionDisparos) {
	bool endAnimationCabeza = animacion->update();

	if (orientacionDisparos == game->orientationBottom) {
		animacion = dispararAbajo;
	}

	if (orientacionDisparos == game->orientationUp) {
		animacion = dispararArriba;
	}

	if (orientacionDisparos == game->orientationLeft) {
		animacion = dispararIzquierda;
	}

	if (orientacionDisparos == game->orientationRight) {
		animacion = dispararDerecha;
	}

	if (shootTime > 0) {
		shootTime--;
	}
}

void CabezaJugador::moveX(float axis) {
	x = axis;
}

void CabezaJugador::moveY(float axis) {
	y = axis;
}

Projectile* CabezaJugador::shoot() {
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

void CabezaJugador::draw(float scrollX, float scrollY) {
	animacion->draw(x - scrollX, y - scrollY);	
}

