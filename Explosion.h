#pragma once

#include "Actor.h"
#include "Animation.h"

class Explosion : public Actor
{
public:
	Explosion(float x, float y, Game* game);
	void update();
	void draw(float scrollX = 0, float scrollY = 0) override;

	Animation* aExploding;
	Animation* animation;

	int state;
};
