#pragma once

#include "Animation.h" 
#include "Enemy.h"
#include "Explosion.h"

class MoscaBomba : public Enemy
{
public:
	MoscaBomba(float x, float y, Game* game);
	void update(float x = 0, float y = 0) override;
	Enemy* impacted(int damage = 1) override;
	void draw(float scrollX, float scrollY) override;
	Explosion* explode();
};

