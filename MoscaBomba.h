#pragma once

#include "Animation.h" 
#include "Enemy.h"
#include "Explosion.h"
#include "Audio.h"

class MoscaBomba : public Enemy
{
public:
	MoscaBomba(float x, float y, Audio* audioMosca, Game* game);
	void update(float x = 0, float y = 0) override;
	Enemy* impacted(int damage = 1) override;
	void draw(float scrollX, float scrollY) override;
	void deleteAnimations() override;
	Explosion* explode();
	Audio* audioMosca;

	int audioTime = 0;
	int audioCadence = 55;
};

