#pragma once

#include "Actor.h"
#include "Animation.h"

class Puerta : public Actor
{
public:
	Puerta(int lado, float x, float y, Game* game);
	int siguienteNivel();
	void abrir();
	void draw(float scrollX = 0, float scrollY = 0) override;
	void deleteAnimations();
	
	int lado;
	int nivelActual;
	bool abierta = false;

	Animation* animacionAbierta;
	Animation* animacionCerrada;
	Animation* animacion;
};

