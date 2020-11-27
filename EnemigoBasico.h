#pragma once

#include "Animation.h" 
#include "Enemy.h"
#include "EnemigoSinCabeza.h"

class EnemigoBasico : public Enemy
{
public:
	EnemigoBasico(float x, float y, Game* game);
	void update(float x = 0, float y = 0) override;
	Enemy* impacted(int damage = 1) override;
	void draw(float scrollX, float scrollY) override;

	Animation* movimientoX;
	Animation* movimientoY;
	Animation* parado;
	Animation* sangre;
	Animation* aCabeza;
	Animation* animationCabeza;
	Animation* animationCuerpo;
	Animation* aHittedCabeza;
};
