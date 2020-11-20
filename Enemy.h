#pragma once

#include "Actor.h"
#include "Animation.h" 
#include "projectileEnemigo.h"

class Enemy : public Actor
{
public:
	Enemy(string s, float x, float y, float ancho, float alto, Game* game);
	virtual void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	virtual void update(float x = 0, float y = 0);
	virtual void impacted(int damage = 1); // Recibe impacto y pone animación de morir
	virtual ProjectileEnemigo* shoot();
	float vxIntelligence;
	float vyIntelligence;
	int state;
	Animation* aDying;
	Animation* aMoving;
	Animation* animation; // Referencia a la animación mostrada
	Animation* aShooting;
	Animation* aHitted;
	int vidas = 1;
	int shootCadence = 70;
	int shootTime = 20;
};
