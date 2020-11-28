#pragma once

#include "Animation.h" 
#include "Enemy.h"

class EnemigoDispara : public Enemy
{
public:
	EnemigoDispara(float x, float y, Game* game);
	void update(float x = 0, float y = 0) override;
	Enemy* impacted(int damage = 1) override;
	void draw(float scrollX, float scrollY) override;
	ProjectileEnemigo* shoot() override;
	void deleteAnimations() override;

	int cdCambioDireccion = 0;

	float jugadorX;
	float jugadorY;
};
