#pragma once

#include "Actor.h"
#include "Animation.h" 


class ProjectileEnemigo : public Actor
{
public:
	ProjectileEnemigo(float x, float y, Game* game);
	Animation* animacion;
	void update();
	void draw(float scrollX) override;
};

