#pragma once

#include "Actor.h"
#include "Animation.h"
#include "Explosion.h"

class Bomba : public Actor
{
public:
	Bomba(float x, float y, Game* game);
	void update();
	void draw(float scrollX = 0, float scrollY = 0) override;
	Explosion* explode();

	Animation* animation;
	Animation* aExploding;

	int state;
};
