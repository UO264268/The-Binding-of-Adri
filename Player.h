#pragma once

#include "Actor.h"
#include "Projectile.h" 
#include "Audio.h"
#include "Animation.h" // incluir animacion 
#include "Bomba.h"
#include "CabezaJugador.h"
#include "CuerpoJugador.h"
#include "Item.h"
#include <list>

class Player : public Actor
{
public:
	Player(float x, float y, Game* game);
	
	list<Projectile*> shoot();
	void update();
	void moveX(float axis);
	void moveY(float axis);
	void draw(float scrollX = 0, float scrollY = 0) override; // Va a sobrescribir
	void loseLife(float damage = 0.5);
	Bomba* ponerBomba();
	void moveToCoordinates(float x, float y);
	void recogerItem(Item* i);

	float lifes = 3;
	int invulnerableTime = 0;
	int orientacionCaminar;
	int orientacionDisparos;
	int state;
	
	CabezaJugador* cabezaJugador;
	CuerpoJugador* cuerpoJugador;

	list<Item*> items;

	int bombCadence = 8;
	int bombTime = 0;

	int bombas = 1;

	bool brimstone = false;
	bool tripleShoot = false;
	bool doubleShoot = false;
	bool oblea = false;
	bool collar_guppy = false;
};

