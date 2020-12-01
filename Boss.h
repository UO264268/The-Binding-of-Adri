#pragma once

#include "Actor.h"
#include "Animation.h"
#include "ProjectileEnemigo.h"
#include "Enemy.h"
#include "EnemigoBasico.h"
#include "EnemigoSinCabeza.h"
#include <list>
#include <math.h>

class Boss : public Actor
{
public:
	Boss(float x, float y, Game* game);
	void draw(float scrollX = 0, float scrollY = 0) override;
	void update();
	list<ProjectileEnemigo*> shoot();
	list<Enemy*> generarEnemigo();
	void impacted(int damage);

	int state;

	Animation* aMoving;
	Animation* animation;
	Animation* aHitted;

	int vidas = 50;
	int shootCadence = 3;
	int shootTime = 2;
	int enemigoTime = 40;
	int enemigoCadence = 400;
	float daño = 1;

	int cicloDisparos = 0;
};

