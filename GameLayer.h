#pragma once

#include "Layer.h"
#include "Player.h"
#include "Background.h"

#include "Enemy.h"
#include "Projectile.h"
#include "Text.h"
#include "Tile.h"
#include "Pad.h"
#include "recolectable.h";

#include "EnemigoBasico.h"
#include "EnemigoSinCabeza.h"
#include "EnemigoDispara.h"

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
	void mouseToControls(SDL_Event event); // USO DE MOUSE
	void gamePadToControls(SDL_Event event); // USO DE GAMEPAD
	void loadMap(string name);
	void loadMapObject(char character, float x, float y);
	void calculateScroll();
	Actor* message;
	bool pause;
	// Elementos de interfaz
	SDL_GameController* gamePad;
	Pad* pad;
	Actor* buttonJump;
	Actor* buttonShoot;

	Tile* cup; // Elemento de final de nivel
	Space* space;
	float scrollX;
	float scrollY;
	int mapWidth;
	int mapHeight;
	list<Tile*> tiles;

	Audio* audioBackground;
	Text* textPoints;
	Text* textRecolectable;
	int points;
	int recolectable;
	int newEnemyTime = 0;
	Player* player;
	Background* background;
	Actor* backgroundPoints;
	Actor* backgroundRecolectable;
	list<Enemy*> enemies;
	list<Projectile*> projectiles;
	list<ProjectileEnemigo*> projectilesEnemigos;
	list<Recolectable*> recolectables;

	bool controlContinue = false;
	bool controlShootUp = false;
	bool controlShootDown = false;
	bool controlShootLeft = false;
	bool controlShootRight = false;
	int controlMoveY = 0;
	int controlMoveX = 0;

	bool controlShoot = false;
};

