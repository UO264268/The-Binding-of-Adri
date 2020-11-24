#pragma once

#include "Recolectable.h"

class VidasRecolectable : public Recolectable
{
public:
	VidasRecolectable(float x, float y, Game* game);
	int recoger() override;
};

