#pragma once

#include "Animation.h" 
#include "Enemy.h"

class Dron : public Enemy
{
public:
	Dron(float x, float y, Game* game);
	void update() override;
	void impacted() override;
	void draw(float scrollX) override;
	ProjectileEnemigo* shoot() override;
};



