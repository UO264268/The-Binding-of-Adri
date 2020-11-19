#pragma once
#include "Actor.h"
#include "Animation.h"

class Recolectable : public Actor
{
public:
	Recolectable(float x, float y, Game* game);
	void update();
	Animation* animation;
	void draw(float scrollX) override;
};

