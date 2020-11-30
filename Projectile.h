#pragma once

#include "Actor.h"
#include "Animation.h"

class Projectile : public Actor
{
public:
	Projectile(float x, float y, Game* game);
	void update();
	void draw(float scrollX = 0, float scrollY = 0) override;
	Animation* animation;
	void deleteAnimations();
	int lifeCycle = 0;
};

