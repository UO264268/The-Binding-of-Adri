#pragma once

#include "Actor.h"
#include "Projectile.h" 
#include "Audio.h"
#include "Animation.h"

class CabezaJugador
{
	CabezaJugador(float x, float y, Game* game);

	Animation* dispararDerecha;
	Animation* dispararIzquierda;
	Animation* dispararAbajo;
	Animation* dispararArriba;
};

