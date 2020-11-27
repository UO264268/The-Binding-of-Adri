#include "Puerta.h"

Puerta::Puerta(int lado, float x, float y, Game* game)
	: Actor("res/puertas/puerta_sala_arriba_cerrada.png", x, y, 40, 32, game) {
	this->lado = lado;
	this->nivelActual = game->currentLevel;
	
	if (lado == game->puertaIzquierda) {
		animacionAbierta = new Animation("res/puertas/puerta_sala_izquierda.png", width, height,
			49, 33, 10, 1, true, game);
		animacionCerrada = new Animation("res/puertas/puerta_sala_izquierda_cerrada.png", width, height,
			49, 33, 10, 1, true, game);
	}
	if (lado == game->puertaDerecha) {
		animacionAbierta = new Animation("res/puertas/puerta_sala_derecha.png", width, height,
			49, 33, 10, 1, true, game);
		animacionCerrada = new Animation("res/puertas/puerta_sala_derecha_cerrada.png", width, height,
			49, 33, 10, 1, true, game);
	}
	if (lado == game->puertaArriba) {
		animacionAbierta = new Animation("res/puertas/puerta_sala_arriba.png", width, height,
			49, 33, 10, 1, true, game);
		animacionCerrada = new Animation("res/puertas/puerta_sala_arriba_cerrada.png", width, height,
			49, 33, 10, 1, true, game);
	}
	if (lado == game->puertaAbajo) {
		animacionAbierta = new Animation("res/puertas/puerta_sala_abajo.png", width, height,
			49, 33, 10, 1, true, game);
		animacionCerrada = new Animation("res/puertas/puerta_sala_abajo_cerrada.png", width, height,
			49, 33, 10, 1, true, game);
	}

	animacion = animacionCerrada;
}

void Puerta::abrir() {
	animacion = animacionAbierta;
	abierta = true;
}

void Puerta::draw(float scrollX, float scrollY) {
	animacion->draw(x - scrollX, y - scrollY);
}

int Puerta::siguienteNivel() {
	switch (nivelActual) {
	case 0:
		if (lado == game->puertaArriba) {
			return 3;
		}
		if (lado == game->puertaDerecha) {
			return 1;
		}
		break;
	case 1:
		if (lado == game->puertaIzquierda) {
			return 0;
		}
		if (lado == game->puertaDerecha) {
			return 2;
		}
		break;
	case 2:
		if (lado == game->puertaIzquierda) {
			return 1;
		}
		break;
	case 3:
		if (lado == game->puertaArriba) {
			return 8;
		}
		if (lado == game->puertaAbajo) {
			return 0;
		}
		if (lado == game->puertaIzquierda) {
			return 4;
		}
		break;
	case 4:
		if (lado == game->puertaIzquierda) {
			return 5;
		}
		if (lado == game->puertaDerecha) {
			return 3;
		}
		break;
	case 5:
		if (lado == game->puertaDerecha) {
			return 4;
		}
		if (lado == game->puertaArriba) {
			return 6;
		}
		if (lado == game->puertaAbajo) {
			return 7;
		}
		break;
	case 6:
		if (lado == game->puertaAbajo){
			return 5;
		}
		break;
	case 7:
		if (lado == game->puertaArriba) {
			return 5;
		}
		break;
	case 8:
		if (lado == game->puertaAbajo) {
			return 3;
		}
		if (lado == game->puertaDerecha) {
			return 9;
		}
		break;
	case 9:
		if (lado == game->puertaDerecha) {
			return 10;
		}
		if (lado == game->puertaIzquierda) {
			return 8;
		}
		break;
	case 10:
		if (lado == game->puertaIzquierda) {
			return 9;
		}
		break;
	}
}