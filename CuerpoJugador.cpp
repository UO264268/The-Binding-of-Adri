#include "CuerpoJugador.h"

CuerpoJugador::CuerpoJugador(float x, float y, Game* game)
	: Actor("res/player/isaac_cuerpo_parado.png", x, y, 48, 20, game) {

	caminarDerecha = new Animation("res/player/isaac_cuerpo_derecha.png", width, height,
		320, 14, 2, 10, true, game);
	caminarIzquierda = new Animation("res/player/isaac_cuerpo_izquierda.png", width, height,
		320, 14, 2, 10, true, game);
	caminarAbajo = new Animation("res/player/isaac_cuerpo_defrente.png", width, height,
		320, 15, 2, 10, true, game);
	caminarArriba = new Animation("res/player/isaac_cuerpo_defrente.png", width, height,
		320, 15, 2, 10, true, game);

	cuerpoParado = new Animation("res/player/isaac_cuerpo_parado.png", width, height,
		32, 13, 1, 1, true, game);

	animacion = cuerpoParado;

}

void CuerpoJugador::update(int orientacionCaminar) {
	bool endAnimationCuerpo = animacion->update();

	
	if (orientacionCaminar == game->orientationRight) {
		animacion = caminarDerecha;
	}
	if (orientacionCaminar == game->orientationLeft) {
			animacion = caminarIzquierda;
	}
	


	if (orientacionCaminar == game->orientationBottom) {
		animacion = caminarAbajo;
	}

	if (orientacionCaminar == game->orientationUp) {
		animacion = caminarArriba;
	}

	if (orientacionCaminar == game->noDisparando) {
		animacion = cuerpoParado;
	}
}

void CuerpoJugador::moveX(float axis) {
	x = axis;
}

void CuerpoJugador::moveY(float axis) {
	y = axis;
}

void CuerpoJugador::draw(float scrollX, float scrollY) {
	animacion->draw(x - scrollX, y - scrollY);
}

