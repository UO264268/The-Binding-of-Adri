#include "Item.h"

Item::Item(float x, float y, int item, Game* game)
	: Actor("", x, y, 48, 48, game) {
	this->item = item;

	if (this->item == this->venda) {
		this->texture = game->getTexture("res/items/venda.png");
	} else if (this->item == this->vente_vente) {
		this->texture = game->getTexture("res/items/vente_vente.png");
	} else if (this->item == this->brimstone) {
		this->texture = game->getTexture("res/items/brimstone.png");
	} else if (this->item == this->oblea) {
		this->texture = game->getTexture("res/items/oblea.png");
	} else if (this->item == this->collar_guppy) {
		this->texture = game->getTexture("res/items/collar_guppy.png");
	} else if (this->item == this->ojo) {
		this->texture = game->getTexture("res/items/ojo.png");
	}
}

bool Item::equals(Item* i) {
	if (this->item == i->item) {
		return true;
	}

	return false;
}