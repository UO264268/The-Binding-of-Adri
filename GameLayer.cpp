#include "GameLayer.h"

GameLayer::GameLayer(Game* game)
	: Layer(game) {
	//llama al constructor del padre : Layer(renderer)
	pause = true;
	message = new Actor("res/mensaje_como_jugar.png", WIDTH * 0.5, HEIGHT * 0.5,
		WIDTH, HEIGHT, game);

	gamePad = SDL_GameControllerOpen(0);
	init();
}


void GameLayer::init() {
	pad = new Pad(WIDTH * 0.15, HEIGHT * 0.80, game);

	buttonJump = new Actor("res/boton_salto.png", WIDTH * 0.9, HEIGHT * 0.55, 100, 100, game);
	buttonShoot = new Actor("res/boton_disparo.png", WIDTH * 0.75, HEIGHT * 0.83, 100, 100, game);

	space = new Space(0);
	scrollX = 0;
	scrollY = 0;
	tiles.clear();

	audioBackground = new Audio("res/musica_ambiente.mp3", true);
	audioBackground->play();

	points = 0;
	textPoints = new Text("hola", WIDTH * 0.92, HEIGHT * 0.04, game);
	textPoints->content = to_string(points);

	recolectable = 0;
	textRecolectable = new Text("hola", WIDTH * 0.8, HEIGHT * 0.04, game);
	textRecolectable->content = to_string(recolectable);

	background = new Background("res/fondo_2.png", WIDTH * 0.5, HEIGHT * 0.5, -1, game);
	backgroundPoints = new Actor("res/icono_puntos.png",
		WIDTH * 0.85, HEIGHT * 0.05, 24, 24, game);
	backgroundRecolectable = new Actor("res/icono_recolectable.png",
		WIDTH * 0.72, HEIGHT * 0.08, 40, 40, game);

	enemies.clear(); // Vaciar por si reiniciamos el juego
	projectiles.clear(); // Vaciar por si reiniciamos el juego
	projectilesEnemigos.clear();

	loadMap("res/" + to_string(game->currentLevel) + ".txt");
}

void GameLayer::loadMap(string name) {
	char character;
	string line;
	ifstream streamFile(name.c_str());
	if (!streamFile.is_open()) {
		cout << "Falla abrir el fichero de mapa" << endl;
		return;
	}
	else {
		// Por línea
		for (int i = 0; getline(streamFile, line); i++) {
			istringstream streamLine(line);
			mapWidth = line.length() * 40; // Ancho del mapa en pixels
			mapHeight = (i+1)*40;
			// Por carácter (en cada línea)
			for (int j = 0; !streamLine.eof(); j++) {
				streamLine >> character; // Leer character 
				cout << character;
				float x = 40 / 2 + j * 40; // x central
				float y = 32 + i * 32; // y suelo
				loadMapObject(character, x, y);
			}

			cout << character << endl;
		}
	}
	streamFile.close();
}

void GameLayer::loadMapObject(char character, float x, float y)
{
	switch (character) {
	case 'C': {
		cup = new Tile("res/copa.png", x, y, false, false, game);
		// modificación para empezar a contar desde el suelo.
		cup->y = cup->y - cup->height / 2;
		space->addDynamicActor(cup); // Realmente no hace falta
		break;
	}
	case 'E': {
		Enemy* enemy = NULL;

		//int num = rand() % 3;

		int num = 2;

		if (num == 0) {
			enemy = new EnemigoBasico(x, y, game);
		}
		else if (num == 1) {
			enemy = new EnemigoSinCabeza(x, y, game);
		}
		else if (num == 2) {
			enemy = new EnemigoDispara(x, y, game);
		}

		// modificación para empezar a contar desde el suelo.
		enemy->y = enemy->y - enemy->height / 2;
		enemies.push_back(enemy);
		space->addDynamicActor(enemy);
		break;
	}
	case '1': {
		player = new Player(x, y, game);
		// modificación para empezar a contar desde el suelo.
		player->y = player->y - player->height / 2;
		space->addDynamicActor(player);
		break;
	}
	case '#': {
		Tile* tile = new Tile("res/bloque_tierra.png", x, y, false, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'R': {
		Recolectable* recolectable = new Recolectable(x, y, game);
		recolectable->y = recolectable->y - recolectable->height / 2;
		recolectables.push_back(recolectable);
		space->addDynamicActor(recolectable);
		break;
	}
	case 'U': {
		Tile* tile = new Tile("res/wooden_box.png", x, y, true, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'Y': {
		Tile* tile = new Tile("res/bloque_metal.png", x, y, false, true, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	}
}


void GameLayer::processControls() {
	// obtener controles
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_CONTROLLERDEVICEADDED) {
			gamePad = SDL_GameControllerOpen(0);
			if (gamePad == NULL) {
				cout << "error en GamePad" << endl;
			}
			else {
				cout << "GamePad conectado" << endl;
			}
		}

		// Cambio automático de input
		// PONER el GamePad
		if (event.type == SDL_CONTROLLERBUTTONDOWN || event.type == SDL_CONTROLLERAXISMOTION) {
			game->input = game->inputGamePad;
		}
		if (event.type == SDL_KEYDOWN) {
			game->input = game->inputKeyboard;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			game->input = game->inputMouse;
		}
		// Procesar teclas
		if (game->input == game->inputKeyboard) {
			keysToControls(event);
		}
		if (game->input == game->inputMouse) {
			mouseToControls(event);
		}
		// Procesar Mando
		if (game->input == game->inputGamePad) {  // gamePAD
			gamePadToControls(event);
		}
	}
	//procesar controles
	//procesar controles
	// Disparar
	if (controlContinue) {
		pause = false;
		controlContinue = false;
	}

	if (controlShootUp) {
		Projectile* newProjectile = player->shoot();
		if (newProjectile != NULL) {
			newProjectile->vx = 0;
			newProjectile->vy = -10;
			space->addDynamicActor(newProjectile);
			projectiles.push_back(newProjectile);
		}
	} 
	if (controlShootDown) {
		Projectile* newProjectile = player->shoot();
		if (newProjectile != NULL) {
			newProjectile->vx = 0;
			newProjectile->vy = 10;
			space->addDynamicActor(newProjectile);
			projectiles.push_back(newProjectile);
		}
	}
	if (controlShootLeft) {
		Projectile* newProjectile = player->shoot();
		if (newProjectile != NULL) {
			newProjectile->vx = -10;
			newProjectile->vy = 0;
			space->addDynamicActor(newProjectile);
			projectiles.push_back(newProjectile);
		}
	}
	if (controlShootRight) {
		Projectile* newProjectile = player->shoot();
		if (newProjectile != NULL) {
			newProjectile->vx = 10;
			newProjectile->vy = 0;
			space->addDynamicActor(newProjectile);
			projectiles.push_back(newProjectile);
		}
	}

	// Eje X
	if (controlMoveX > 0) {
		player->moveX(1);
	}
	else if (controlMoveX < 0) {
		player->moveX(-1);
	}
	else {
		player->moveX(0);
	}

	// Eje Y
	if (controlMoveY > 0) {
		player->moveY(1);
	}
	else if (controlMoveY < 0) {
		player->moveY(-1);
	}
	else {
		player->moveY(0);
	}
}

void GameLayer::update() {
	if (pause) {
		return;
	}

	// Nivel superado
	if (cup->isOverlap(player)) {
		game->currentLevel++;
		if (game->currentLevel > game->finalLevel) {
			game->currentLevel = 0;
		}
		message = new Actor("res/mensaje_ganar.png", WIDTH * 0.5, HEIGHT * 0.5,
			WIDTH, HEIGHT, game);
		pause = true;
		init();
	}
	
	space->update();
	background->update();
	player->update();
	for (auto const& enemy : enemies) {
		enemy->update(player->x, player->y);
		ProjectileEnemigo* newProjectile = enemy->shoot();
		if (newProjectile != NULL) {
			space->addDynamicActor(newProjectile);
			projectilesEnemigos.push_back(newProjectile);
		}
	}
	for (auto const& projectile : projectiles) {
		projectile->update();
	}
	for (auto const& projectile : projectilesEnemigos) {
		projectile->update();
	}
	for (auto const& recolectable : recolectables) {
		recolectable->update();
	}

	// Colisiones
	for (auto const& enemy : enemies) {
		if (player->isOverlap(enemy)) {
			player->loseLife(1);
			if (player->lifes <= 0) {
				init();
				return;
			}
		}
	}

	list<Recolectable*> deleteRecolectables;

	// Colisiones
	for (auto const& r : recolectables) {
		if (player->isOverlap(r)) {
			recolectable++;
			textRecolectable->content = to_string(recolectable);

			bool pInList = std::find(deleteRecolectables.begin(),
				deleteRecolectables.end(),
				r) != deleteRecolectables.end();

			if (!pInList) {
				deleteRecolectables.push_back(r);
			}
		}
	}

	list<ProjectileEnemigo*> deleteProjectilesEnemigos;

	for (auto const& projectile : projectilesEnemigos) {
		if (player->isOverlap(projectile)) {
			player->loseLife(1);
			if (player->lifes <= 0) {
				init();
				return;
			}

			bool pInList = std::find(deleteProjectilesEnemigos.begin(),
				deleteProjectilesEnemigos.end(),
				projectile) != deleteProjectilesEnemigos.end();

			if (!pInList) {
				deleteProjectilesEnemigos.push_back(projectile);
			}
		}
	}

	// Colisiones , Enemy - Projectile

	list<Enemy*> deleteEnemies;
	list<Projectile*> deleteProjectiles;
	list<Tile*> deleteTiles;

	for (auto const& projectile : projectilesEnemigos) {
		if (projectile->isInRender(scrollX, scrollY) == false || (projectile->vx == 0 && projectile->vy == 0)) {

			bool pInList = std::find(deleteProjectilesEnemigos.begin(),
				deleteProjectilesEnemigos.end(),
				projectile) != deleteProjectilesEnemigos.end();

			if (!pInList) {
				deleteProjectilesEnemigos.push_back(projectile);
			}
		}
	}

	list<Enemy*> newEnemies;

	for (auto const& enemy : enemies) {
		for (auto const& projectile : projectiles) {
			if (projectile->isInRender(scrollX, scrollY) == false || (projectile->vx == 0 && projectile->vy == 0)) {

				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}
			}

			if (enemy->isOverlap(projectile)) {
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}

				Enemy* newEnemy = enemy->impacted();

				if (newEnemy != NULL) {
					newEnemies.push_back(newEnemy);
				}

				points++;
				textPoints->content = to_string(points);
			}
		}
	}

	for (auto const& enemy : newEnemies) {
		space->addDynamicActor(enemy);
		enemies.push_back(enemy);

	}
	newEnemies.clear();

	for (auto const& tile : tiles) {
		for (auto const& projectile : projectiles) {
			if (tile->isOverlap(projectile) && tile->desctructibleByShoot) {
				bool pInList = std::find(deleteTiles.begin(),
					deleteTiles.end(),
					tile) != deleteTiles.end();

				if (!pInList) {
					deleteTiles.push_back(tile);
				}

			}
		}

		for (auto const& projectile : projectilesEnemigos) {
			if (tile->isOverlap(projectile)) {
				bool pInList = std::find(deleteProjectilesEnemigos.begin(),
					deleteProjectilesEnemigos.end(),
					projectile) != deleteProjectilesEnemigos.end();

				if (!pInList) {
					deleteProjectilesEnemigos.push_back(projectile);
				}
			}
		}
	}


	for (auto const& enemy : enemies) {
		if (enemy->state == game->stateDead) {
			bool eInList = std::find(deleteEnemies.begin(),
				deleteEnemies.end(),
				enemy) != deleteEnemies.end();

			if (!eInList) {
				deleteEnemies.push_back(enemy);
			}
		}
	}

	for (auto const& delEnemy : deleteEnemies) {
		enemies.remove(delEnemy);
		space->removeDynamicActor(delEnemy);
	}
	deleteEnemies.clear();

	for (auto const& delProjectile : deleteProjectiles) {
		projectiles.remove(delProjectile);
		space->removeDynamicActor(delProjectile);
		delete delProjectile;
	}
	deleteProjectiles.clear();

	for (auto const& delProjectile : deleteProjectilesEnemigos) {
		projectilesEnemigos.remove(delProjectile);
		space->removeDynamicActor(delProjectile);
		delete delProjectile;
	}
	deleteProjectilesEnemigos.clear();

	for (auto const& delRecolectable : deleteRecolectables) {
		recolectables.remove(delRecolectable);
		space->removeDynamicActor(delRecolectable);
		delete delRecolectable;
	}
	deleteRecolectables.clear();

	for (auto const& delTile : deleteTiles) {
		tiles.remove(delTile);
		space->removeDynamicActor(delTile);
		delete delTile;
	}
	deleteTiles.clear();

}

void GameLayer::calculateScroll() {
	// limite izquierda
	if (player->x > WIDTH * 0.3) {
		if (player->x - scrollX < WIDTH * 0.3) {
			scrollX = player->x - WIDTH * 0.3;
		}
	}

	// limite derecha
	if (player->x < mapWidth - WIDTH * 0.3) {
		if (player->x - scrollX > WIDTH * 0.7) {
			scrollX = player->x - WIDTH * 0.7;
		}
	}

	// limite arriba
	if (player->y > HEIGHT * 0.15) {
		if (player->y - scrollY < HEIGHT * 0.15) {
			scrollY = player->y - HEIGHT * 0.15;
		}
	}

	// limite abajo
	if (player->y < mapHeight - HEIGHT * 0.15) {
		if (player->y - scrollY > HEIGHT * 0.85) {
			scrollY = player->y - HEIGHT * 0.85;
		}
	}
}


void GameLayer::draw() {
	calculateScroll();

	background->draw();
	for (auto const& tile : tiles) {
		tile->draw(scrollX, scrollY);
	}
	for (auto const& projectile : projectilesEnemigos) {
		projectile->draw(scrollX, scrollY);
	}
	for (auto const& projectile : projectiles) {
		projectile->draw(scrollX, scrollY);
	}
	cup->draw(scrollX, scrollY);
	player->draw(scrollX, scrollY);
	for (auto const& enemy : enemies) {
		enemy->draw(scrollX, scrollY);
	}

	for (auto const& recolectable : recolectables) {
		recolectable->draw(scrollX, scrollY);
	}

	backgroundPoints->draw();
	textPoints->draw();

	backgroundRecolectable->draw();
	textRecolectable->draw();

	// HUD
	if (game->input == game->inputMouse) {
		buttonJump->draw(); // NO TIENEN SCROLL, POSICION FIJA
		buttonShoot->draw(); // NO TIENEN SCROLL, POSICION FIJA
		pad->draw(); // NO TIENEN SCROLL, POSICION FIJA
	}
	if (pause) {
		message->draw();
	}

	SDL_RenderPresent(game->renderer); // Renderiza
}

void GameLayer::gamePadToControls(SDL_Event event) {

	// Leer los botones
	bool buttonA = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_A);
	bool buttonB = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_B);
	bool buttonX = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_X);
	bool buttonY = SDL_GameControllerGetButton(gamePad, SDL_CONTROLLER_BUTTON_Y);
	// SDL_CONTROLLER_BUTTON_A, SDL_CONTROLLER_BUTTON_B
	// SDL_CONTROLLER_BUTTON_X, SDL_CONTROLLER_BUTTON_Y
	cout << "botones:" << buttonA << "," << buttonB << endl;
	int stickX = SDL_GameControllerGetAxis(gamePad, SDL_CONTROLLER_AXIS_LEFTX);
	int stickY = SDL_GameControllerGetAxis(gamePad, SDL_CONTROLLER_AXIS_LEFTY);
	cout << "stickX" << stickX << endl;

	// Retorna aproximadamente entre [-32800, 32800], el centro debería estar en 0
	// Si el mando tiene "holgura" el centro varia [-4000 , 4000]
	if (stickX > 4000) {
		controlMoveX = 1;
	} else if (stickX < -4000) {
		controlMoveX = -1;
	} else {
		controlMoveX = 0;
	}

	if (stickY > 4000) {
		controlMoveY = 1;
	} else if (stickY < -4000) {
		controlMoveY = -1;
	} else {
		controlMoveY = 0;
	}

	if (buttonY) {
		controlShootUp = true;
	} else if (buttonA) {
		controlShootDown = true;
	} else if (buttonX) {
		controlShootLeft = true;
	} else if (buttonB) {
		controlShootRight = true;
	} else {
		controlShootRight = false;
		controlShootLeft = false;
		controlShootDown = false;
		controlShootUp = false;
	}
}


void GameLayer::mouseToControls(SDL_Event event) {
	// Modificación de coordenadas por posible escalado
	float motionX = event.motion.x / game->scaleLower;
	float motionY = event.motion.y / game->scaleLower;
	// Cada vez que hacen click
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		controlContinue = true;
	//	if (pad->containsPoint(motionX, motionY)) {
	//		pad->clicked = true;
	//		// CLICK TAMBIEN TE MUEVE
	//		controlMoveX = pad->getOrientationX(motionX);
	//	}
	//	if (buttonShoot->containsPoint(motionX, motionY)) {
	//		controlShoot = true;
	//	}
	//	if (buttonJump->containsPoint(motionX, motionY)) {
	//		controlMoveY = -1;
		}

	//}
	//// Cada vez que se mueve
	//if (event.type == SDL_MOUSEMOTION) {
	//	if (pad->clicked && pad->containsPoint(motionX, motionY)) {
	//		controlMoveX = pad->getOrientationX(motionX);
	//		// Rango de -20 a 20 es igual que 0
	//		if (controlMoveX > -20 && controlMoveX < 20) {
	//			controlMoveX = 0;
	//		}

	//	}
	//	else {
	//		pad->clicked = false; // han sacado el ratón del pad
	//		controlMoveX = 0;
	//	}
	//	if (buttonShoot->containsPoint(motionX, motionY) == false) {
	//		controlShoot = false;
	//	}
	//	if (buttonJump->containsPoint(motionX, motionY) == false) {
	//		controlMoveY = 0;
	//	}

	//}
	//// Cada vez que levantan el click
	//if (event.type == SDL_MOUSEBUTTONUP) {
	//	if (pad->containsPoint(motionX, motionY)) {
	//		pad->clicked = false;
	//		// LEVANTAR EL CLICK TAMBIEN TE PARA
	//		controlMoveX = 0;
	//	}

	//	if (buttonShoot->containsPoint(motionX, motionY)) {
	//		controlShoot = false;
	//	}
	//	if (buttonJump->containsPoint(motionX, motionY)) {
	//		controlMoveY = 0;
	//	}
	//}
}


void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		// Pulsada
		switch (code) {
			case SDLK_ESCAPE:
				game->loopActive = false;
				break;
			case SDLK_1:
				game->scale();
				break;
			case SDLK_d: // derecha
				controlMoveX = 1;
				break;
			case SDLK_a: // izquierda
				controlMoveX = -1;
				break;
			case SDLK_w: // arriba
				controlMoveY = -1;
				break;
			case SDLK_s: // abajo
				controlMoveY = 1;
				break;
			case SDLK_UP: //disparo arriba
				controlShootUp = true;
				break;
			case SDLK_DOWN: //disparo abajo
				controlShootDown = true;
				break;
			case SDLK_LEFT: //disparo izquierda
				controlShootLeft = true;
				break;
			case SDLK_RIGHT: //disparo derecha
				controlShootRight = true;
				break;
		}
	}if (event.type == SDL_KEYUP) {
		int code = event.key.keysym.sym;
		// Levantada
		switch (code) {
			case SDLK_d: // derecha
				if (controlMoveX == 1) {
					controlMoveX = 0;
				}
				break;
			case SDLK_a: // izquierda
				if (controlMoveX == -1) {
					controlMoveX = 0;
				}
				break;
			case SDLK_w: // arriba
				if (controlMoveY == -1) {
					controlMoveY = 0;
				}
				break;
			case SDLK_s: // abajo
				if (controlMoveY == 1) {
					controlMoveY = 0;
				}
				break;
			case SDLK_UP: //disparo arriba
				controlShootUp = false;
				break;
			case SDLK_DOWN: //disparo abajo
				controlShootDown = false;
				break;
			case SDLK_LEFT: //disparo izquierda
				controlShootLeft = false;
				break;
			case SDLK_RIGHT: //disparo derecha
				controlShootRight = false;
				break;
		}
	}
}

	