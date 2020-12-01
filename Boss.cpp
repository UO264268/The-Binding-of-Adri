#include "Boss.h"

Boss::Boss(float x, float y, Game* game)
	: Actor("res/enemigos/boss.png", x, y, 296, 420, game) {
	state = game->stateMoving;

	aMoving = new Animation("res/enemigos/boss.png", width, height, 560, 122, 3, 5, true, game);
	aHitted = new Animation("res/enemigos/boss_hitted.png", width, height, 112, 128, 3, 1, false, game);
	
	animation = aMoving;
}

void Boss::draw(float scrollX, float scrollY) {
	animation->draw(x - scrollX, y - scrollY);
}

void Boss::update() {
	bool endAnimation = animation->update();
	// Acabo la animación, no sabemos cual
	if (endAnimation) {
		// Estaba muriendo
		if (state == game->stateDying) {
			state = game->stateDead;
		}

		if (state == game->stateHitted) {
			state = game->stateMoving;
		}
	}

	if (state == game->stateMoving) {
		animation = aMoving;
	}
	if (state == game->stateDying) {
		animation = aHitted;
	}
	if (state == game->stateHitted) {
		animation = aHitted;
	}

	if (shootTime > 0) {
		shootTime--;
	}

	if (enemigoTime > 0) {
		enemigoTime--;
	}
}

list<ProjectileEnemigo*> Boss::shoot() {
	list<ProjectileEnemigo*> projectiles;

	if (shootTime == 0) {
		cicloDisparos += 12;

		shootTime = shootCadence;

		float vt = 10;

		float anguloDisparo = (cicloDisparos * M_PI) / 180;
		
		float vy = vt * cos(anguloDisparo);
		float vx = vt * sin(anguloDisparo);

		ProjectileEnemigo* projectile1 = new ProjectileEnemigo(x, y, vx * -1, vy * -1, game);
		ProjectileEnemigo* projectile2 = new ProjectileEnemigo(x, y, vx, vy, game);
		/*ProjectileEnemigo* projectile = new ProjectileEnemigo(x, y, vx, vy, game);
		ProjectileEnemigo* projectile = new ProjectileEnemigo(x, y, vx, vy, game);*/

		projectiles.push_back(projectile1);
		projectiles.push_back(projectile2);

		if (cicloDisparos == 360)
			cicloDisparos = 0;

		if (rand() % 50 == 0)
			shootTime = rand() % 300;
	}

	return projectiles;
}

list<Enemy*> Boss::generarEnemigo() {
	list<Enemy*> enemigos;

	if (enemigoTime == 0) {
		enemigoTime = enemigoCadence;

		int numEnemigos = rand() % 5 + 1;

		for (int i = 0; i < numEnemigos; i++) {
			int enemigo_num = rand() % 2;

			Enemy* enemigo;

			if (enemigo_num == 0) {
				int distanciax = (rand() % 500 + 300) * rand() % 3 - 1;
				int distanciay = (rand() % 500 + 300) * rand() % 3 - 1;
				enemigo = new EnemigoSinCabeza(x + distanciax, y + distanciay, game);
			}
			else {
				int distanciax = (rand() % 500 + 300) * rand() % 3 - 1;
				int distanciay = (rand() % 500 + 300) * rand() % 3 - 1;
				enemigo = new EnemigoBasico(x + distanciax, y + distanciay, game);
			}

			enemigos.push_back(enemigo);
		}
	}

	return enemigos;
}

void Boss::impacted(int damage) {
	if (state != game->stateDying) {
		if ((vidas - damage) > 0) {
			state = game->stateHitted;
			aHitted->currentFrame = 0;
			vidas = vidas - damage;
		}
		else {
			vidas = 0;
			state = game->stateDying;
		}
	}
}