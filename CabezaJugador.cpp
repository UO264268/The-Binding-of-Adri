#include "CabezaJugador.h"

CabezaJugador::CabezaJugador(float x, float y, Game* game)
	: Actor("res/player/cabeza.png", x, y, 43, 27, game) {

	dispararDerecha = new Animation("res/player/isaac_cabeza_disparando_derecha.png", width, height,
		58, 25, 10, 2, true, game);
	dispararIzquierda = new Animation("res/player/isaac_cabeza_disparando_izquierda.png", width, height,
		58, 25, 10, 2, true, game);
	dispararAbajo = new Animation("res/player/isaac_cabeza_disparando_abajo.png", width, height,
		58, 25, 10, 2, true, game);
	dispararArriba = new Animation("res/player/isaac_cabeza_disparando_arriba.png", width, height,
		58, 25, 10, 2, true, game);

	animacion = dispararAbajo;
}

void CabezaJugador::update(int orientacionDisparos) {
	bool endAnimationCabeza = animacion->update();

	this->orientacion = orientacionDisparos;

	if (orientacionDisparos == game->orientationBottom) {
		animacion = dispararAbajo;
	}

	if (orientacionDisparos == game->orientationUp) {
		animacion = dispararArriba;
	}

	if (orientacionDisparos == game->orientationLeft) {
		animacion = dispararIzquierda;
	}

	if (orientacionDisparos == game->orientationRight) {
		animacion = dispararDerecha;
	}

	shootTime--;
	
}

void CabezaJugador::moveX(float axis) {
	x = axis;
}

void CabezaJugador::moveY(float axis) {
	y = axis;
}

list<Projectile*> CabezaJugador::shoot(bool tripleShoot, bool doubleShoot, bool brimstone) {
	list<Projectile*> projectiles;

	if (brimstone || shootTime < 0) {
		if (doubleShoot & tripleShoot) {
			if (orientacion == game->orientationBottom || orientacion == game->orientationUp) {
				Projectile* projectile1 = new Projectile(x - 20, y, game);
				Projectile* projectile2 = new Projectile(x - 10, y, game);
				Projectile* projectile3 = new Projectile(x, y, game);
				Projectile* projectile4 = new Projectile(x + 10, y, game);
				Projectile* projectile5 = new Projectile(x + 20, y, game);

				projectiles.push_back(projectile1);
				projectiles.push_back(projectile2);
				projectiles.push_back(projectile3);
				projectiles.push_back(projectile4);
				projectiles.push_back(projectile5);
			}

			if (orientacion == game->orientationLeft || orientacion == game->orientationRight) {
				Projectile* projectile1 = new Projectile(x, y - 20, game);
				Projectile* projectile2 = new Projectile(x, y - 10, game);
				Projectile* projectile3 = new Projectile(x, y, game);
				Projectile* projectile4 = new Projectile(x, y + 10, game);
				Projectile* projectile5 = new Projectile(x, y + 20, game);

				projectiles.push_back(projectile1);
				projectiles.push_back(projectile2);
				projectiles.push_back(projectile3);
				projectiles.push_back(projectile4);
				projectiles.push_back(projectile5);
			}

		}
		else if(tripleShoot){
			shootTime = shootCadence;
			
			if (orientacion == game->orientationBottom || orientacion == game->orientationUp) {
				Projectile* projectile1 = new Projectile(x - 10, y, game);
				Projectile* projectile2 = new Projectile(x, y, game);
				Projectile* projectile3 = new Projectile(x + 10, y, game);

				projectiles.push_back(projectile1);
				projectiles.push_back(projectile2);
				projectiles.push_back(projectile3);
			}

			if (orientacion == game->orientationLeft || orientacion == game->orientationRight) {
				Projectile* projectile1 = new Projectile(x, y - 10, game);
				Projectile* projectile2 = new Projectile(x, y, game);
				Projectile* projectile3 = new Projectile(x, y + 10, game);

				projectiles.push_back(projectile1);
				projectiles.push_back(projectile2);
				projectiles.push_back(projectile3);
			}
		}
		else if (doubleShoot) {
			if (orientacion == game->orientationBottom || orientacion == game->orientationUp) {
				Projectile* projectile1 = new Projectile(x - 10, y, game);
				Projectile* projectile2 = new Projectile(x + 10, y, game);
				
				projectiles.push_back(projectile1);
				projectiles.push_back(projectile2);
			}

			if (orientacion == game->orientationLeft || orientacion == game->orientationRight) {
				Projectile* projectile1 = new Projectile(x, y - 10, game);
				Projectile* projectile2 = new Projectile(x, y + 10, game);

				projectiles.push_back(projectile1);
				projectiles.push_back(projectile2);
			}
		}
		else {
			Projectile* projectile = new Projectile(x, y, game);
			projectiles.push_back(projectile);
		}
		
		shootTime = shootCadence;
	}

	return projectiles;
}

void CabezaJugador::draw(float scrollX, float scrollY) {
	animacion->draw(x - scrollX, y - scrollY);	
}


