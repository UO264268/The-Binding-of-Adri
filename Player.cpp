#include "Player.h"

Player::Player(float x, float y, Game* game)
	: Actor("res/jugador.png", x, y, 48, 23, game) {

	cabezaJugador = new CabezaJugador(x, y-20, game);
	cuerpoJugador = new CuerpoJugador(x, y, game);
	
	orientacionCaminar = game->orientationBottom;
	orientacionDisparos = game->orientationBottom;
	state = game->stateMoving;
}

void Player::update() {
	if (invulnerableTime > 0) {
		invulnerableTime--;
	}

	// Establecer orientación
	if (vx > 0) {
		orientacionCaminar = game->orientationRight;
	}
	if (vx < 0) {
		orientacionCaminar = game->orientationLeft;
	}
	if (vy > 0) {
		orientacionCaminar = game->orientationUp;
	}
	if (vy < 0) {
		orientacionCaminar = game->orientationBottom;
	}
	if (vy == 0 && vx == 0) {
		orientacionCaminar = game->noDisparando;
	}

	cabezaJugador->update(orientacionDisparos);
	cuerpoJugador->update(orientacionCaminar);

	if (bombTime > 0) {
		bombTime--;
	}

	cabezaJugador->moveX(x);
	cuerpoJugador->moveX(x);

	cabezaJugador->moveY(y - 17);
	cuerpoJugador->moveY(y);
}

void Player::moveX(float axis) {
	vx = axis * 5;
}

void Player::moveY(float axis) {
	vy = axis * 5;
}

list<Projectile*> Player::shoot() {
	return cabezaJugador->shoot(tripleShoot, doubleShoot, brimstone);
}

void Player::draw(float scrollX, float scrollY) {
	if (invulnerableTime == 0) {
		cuerpoJugador->draw(scrollX, scrollY);
		cabezaJugador->draw(scrollX, scrollY);
	}
	else {
		if (invulnerableTime % 10 >= 0 && invulnerableTime % 10 <= 5) {
			cuerpoJugador->draw(scrollX, scrollY);
			cabezaJugador->draw(scrollX, scrollY);
		}
	}
}

void Player::loseLife(float damage) {
	if (oblea) {
		damage = 0.5;
	}

	if (invulnerableTime <= 0) {
		if ((lifes-damage) > 0) {
			lifes = lifes - damage;
		}
		else {
			lifes = 0;
		}

		invulnerableTime = 100;
		// 100 actualizaciones 

		if (collar_guppy && lifes == 0) {
			lifes = rand() % 2;

			cout << "Vidas: " << lifes << endl;
		}
	}
}

Bomba* Player::ponerBomba() {
	if (bombTime == 0 && bombas > 0) {
		bombTime = bombCadence;
		Bomba* bomba = new Bomba(x, y, game);
		bombas--;
		return bomba;
	}
	else {
		return NULL;
	}
}

void Player::moveToCoordinates(float x, float y) {
	this->x = x;
	this->y = y;

	cuerpoJugador->x = x;
	cuerpoJugador->y = y;

	cabezaJugador->x = x;
	cabezaJugador->y = y-17;
}

void Player::recogerItem(Item* i) {
	items.push_back(i);

	if (i->item == i->collar_guppy) {
		this->collar_guppy = true;
	}
	if (i->item == i->brimstone) {
		this->brimstone = true;
	}
	if (i->item == i->oblea) {
		this->oblea = true;
	}
	if (i->item == i->ojo) {
		this->tripleShoot = true;
		cabezaJugador->shootCadence += 20;
	}
	if (i->item == i->vente_vente) {
		this->doubleShoot = true;
	}
	if (i->item == i->venda) {
		this->lifes++;
	}
}

