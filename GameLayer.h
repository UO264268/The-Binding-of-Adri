#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"

#include "Enemy.h"
#include "Projectile.h"
#include "Text.h"
#include "Tile.h"
#include "Pad.h"
#include "Recolectable.h";
#include "BombaRecolectable.h"
#include "VidasRecolectable.h"

#include "EnemigoBasico.h"
#include "EnemigoSinCabeza.h"
#include "EnemigoDispara.h"
#include "MoscaBomba.h"
#include "Explosion.h"
#include "Bomba.h"

#include "Audio.h"
#include "Space.h" // importar

#include <fstream> // Leer ficheros
#include <sstream> // Leer líneas / String
#include <list>

class GameLayer : public Layer
{
public:
	GameLayer(Game* game);
	void init() override;
	void processControls() override;
	void update() override;
	void draw() override;
	void keysToControls(SDL_Event event);
	void gamePadToControls(SDL_Event event); // USO DE GAMEPAD
	void loadMap(string name);
	void loadMapObject(char character, float x, float y);
	void calculateScroll();
	Actor* message;
	bool pause;
	// Elementos de interfaz
	SDL_GameController* gamePad;
	Pad* pad;

	Tile* cup; // Elemento de final de nivel
	Space* space;
	float scrollX;
	float scrollY;
	int mapWidth;
	int mapHeight;
	list<Tile*> tiles;

	Audio* audioBackground;
	Text* textBombas;
	Text* textVidas;
	Player* player;
	Background* background;
	Actor* backgroundBombas;
	Actor* backgroundVidas;
	list<Enemy*> enemies;
	list<Projectile*> projectiles;
	list<ProjectileEnemigo*> projectilesEnemigos;
	list<Recolectable*> recolectables;
	list<Explosion*> explosiones;
	list<Bomba*> bombas;

	bool controlContinue = false;
	bool controlShootUp = false;
	bool controlShootDown = false;
	bool controlShootLeft = false;
	bool controlShootRight = false;
	bool controlBomba = false;
	int controlMoveY = 0;
	int controlMoveX = 0;

	bool controlShoot = false;
};

