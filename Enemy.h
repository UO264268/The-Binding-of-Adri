#pragma once

#include "Actor.h"
#include "Animation.h" 
#include "projectileEnemigo.h"

class Enemy : public Actor
{
public:
	Enemy(string s, float x, float y, float ancho, float alto, Game* game);
	virtual void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	virtual void update();
	virtual void impacted(); // Recibe impacto y pone animación de morir
	virtual ProjectileEnemigo* shoot();
	float vxIntelligence;
	int state;
	Animation* aDying;
	Animation* aMoving;
	Animation* animation; // Referencia a la animación mostrada
	Animation* aShooting;
	int shootCadence = 70;
	int shootTime = 20;
};
