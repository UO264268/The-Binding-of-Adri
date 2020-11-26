#pragma once

#include "Actor.h"
#include "Projectile.h" 
#include "Audio.h"
#include "Animation.h" // incluir animacion 
#include "Bomba.h"

class Player : public Actor
{
public:
	Player(float x, float y, Game* game);
	Projectile* shoot();
	void update();
	void moveX(float axis);
	void moveY(float axis);
	void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	void loseLife(float damage = 0.5);
	Bomba* ponerBomba();

	float lifes = 3;
	int invulnerableTime = 0;
	int orientacionCaminar;
	int orientacionDisparos;
	int state;
	
	Animation* caminarDerecha;
	Animation* caminarIzquierda;
	Animation* caminarAbajo;
	Animation* caminarArriba;

	

	Animation* cuerpoParado;

	Animation* animacionCabeza; // Referencia a la animación mostrada
	Animation* animacionCuerpo; // Referencia a la animación mostrada
	Audio* audioShoot;

	int shootCadence = 20;
	int shootTime = 0;
	
	int bombCadence = 8;
	int bombTime = 0;

	int bombas = 3;
};

