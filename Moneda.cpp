#include "Moneda.h"

Moneda::Moneda(float x, float y, Game* game)
	: Actor("res/moneda.png", x, y, 40, 40, game) {

	vx = 1.5;
}

void Moneda::update() {
	x = x - vx;
}
