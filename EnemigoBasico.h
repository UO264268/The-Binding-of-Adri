#pragma once

#include "Animation.h" 
#include "Enemy.h"

class EnemigoBasico : public Enemy
{
public:
	EnemigoBasico(float x, float y, Game* game);
	void update(float x = 0, float y = 0) override;
	void impacted(int damage = 1) override;
	void draw(float scrollX, float scrollY) override;
	ProjectileEnemigo* shoot() override;
};
