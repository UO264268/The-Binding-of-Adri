#pragma once

#include "Animation.h" 
#include "Enemy.h"

class Alien : public Enemy
{
public:
	Alien(float x, float y, Game* game);
	void update() override;
	void impacted() override;
	void draw(float scrollX, float scrollY) override;
	ProjectileEnemigo* shoot() override;
};
