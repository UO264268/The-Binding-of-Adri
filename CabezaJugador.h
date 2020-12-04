#pragma once

#include "Actor.h"
#include "Projectile.h" 
#include "Audio.h"
#include "Animation.h"
#include <list>

class CabezaJugador : public Actor
{
public:
	CabezaJugador(float x, float y, Game* game);

	list<Projectile*> shoot(bool tripleShoot, bool doubleShoot, bool brimstone);
	void update(int orientacionDisparos);
	void moveX(float x);
	void moveY(float y);
	void draw(float scrollX = 0, float scrollY = 0) override;

	Animation* dispararDerecha;
	Animation* dispararIzquierda;
	Animation* dispararAbajo;
	Animation* dispararArriba;

	Animation* animacion;

	int orientacion;

	int shootCadence = 20;
	int shootTime = 0;
};

