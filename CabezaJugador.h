#pragma once

#include "Actor.h"
#include "Projectile.h" 
#include "Audio.h"
#include "Animation.h"

class CabezaJugador : public Actor
{
public:
	CabezaJugador(float x, float y, Game* game);

	Projectile* shoot();
	void update(int orientacionDisparos);
	void moveX(float x);
	void moveY(float y);
	void draw(float scrollX = 0, float scrollY = 0) override;
	void deleteAnimations();

	Animation* dispararDerecha;
	Animation* dispararIzquierda;
	Animation* dispararAbajo;
	Animation* dispararArriba;

	Animation* animacion;

	Audio* audioShoot;

	int shootCadence = 20;
	int shootTime = 0;
};

