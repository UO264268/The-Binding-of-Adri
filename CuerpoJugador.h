#pragma once

#include "Actor.h"
#include "Animation.h"

class CuerpoJugador : public Actor
{
public:
	CuerpoJugador(float x, float y, Game* game);
	void update(int orientacion);
	void moveX(float axis);
	void moveY(float axis);
	void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir

	Animation* caminarDerecha;
	Animation* caminarIzquierda;
	Animation* caminarAbajo;
	Animation* caminarArriba;
	Animation* cuerpoParado;

	// Referencia a la animación mostrada
	Animation* animacion; // Referencia a la animación mostrada
};

