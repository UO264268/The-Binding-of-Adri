#pragma once

#include "Recolectable.h"

class BombaRecolectable : public Recolectable
{
public:
	BombaRecolectable(float x, float y, Game* game);
	int recoger() override;
};

