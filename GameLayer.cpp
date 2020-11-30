#include "GameLayer.h"

GameLayer::GameLayer(Game* game) //https://gyazo.com/17d61411a9793ae013f0b8820e8fbf03
	: Layer(game) {
	//llama al constructor del padre : Layer(renderer)
	pause = true;
	message = new Actor("res/menu/controls.png", WIDTH * 0.5, HEIGHT * 0.5, WIDTH * 0.7, HEIGHT * 0.5,
		game);

	gamePad = SDL_GameControllerOpen(0);
	init();
}


void GameLayer::init() {
	pad = new Pad(WIDTH * 0.15, HEIGHT * 0.80, game);

	space = new Space(0);
	scrollX = 0;
	scrollY = 0;
	tiles.clear();

	audioBackground = new Audio("res/musica_ambiente.mp3", true);
	audioBackground->play();

	textVidas = new Text("hola", WIDTH * 0.92, HEIGHT * 0.05, game);
	textVidas->content = to_string(0);

	textBombas = new Text("hola", WIDTH * 0.8, HEIGHT * 0.05, game);
	textBombas->content = to_string(0);
	
	background = new Background("res/mapeado/fondo.png", WIDTH * 0.5, HEIGHT * 0.5, 0, game);
	backgroundVidas = new Actor("res/recolectables/icono_vida.png",
		WIDTH * 0.85, HEIGHT * 0.05, 39, 42, game);
	backgroundBombas = new Actor("res/recolectables/icono_bomba.png",
		WIDTH * 0.76, HEIGHT * 0.05, 39, 39, game);

	for (auto const& puerta : puertas) {
		puerta->deleteAnimations();
		delete puerta;
	}

	space->removeDynamicActor(player);

	if (player == NULL) {
		player = new Player(620, 384, game);
	}
	else {
		if (entrada == game->puertaAbajo) {
			player->moveToCoordinates(620, 50);
		}
		else if (entrada == game->puertaArriba) {
			player->moveToCoordinates(620, 685);
		}
		else if (entrada == game->puertaIzquierda) {
			player->moveToCoordinates(1205, 384);
		}
		else if (entrada == game->puertaDerecha) {
			player->moveToCoordinates(75, 384);
		}

		if (player->lifes == 0) {
			game->currentLevel = 0;
			player = new Player(620, 384, game);
		}
	}

	space->addDynamicActor(player);

	enemies.clear(); // Vaciar por si reiniciamos el juego
	projectiles.clear(); // Vaciar por si reiniciamos el juego
	projectilesEnemigos.clear();
	explosiones.clear();
	puertas.clear();
	recolectables.clear();
	items.clear();

	loadMap("res/mapas/" + to_string(game->currentLevel) + ".txt");
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
			mapHeight = (i+1)*32;
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
	case 'E': {
		Enemy* enemy = NULL;

		int num = rand() % 4;

		if (num == 0) {
			enemy = new EnemigoBasico(x, y, game);
		}
		else if (num == 1) {
			enemy = new EnemigoSinCabeza(x, y, game);
		}
		else if (num == 2) {
			enemy = new EnemigoDispara(x, y, game);
		}
		else if (num == 3) {
			enemy = new MoscaBomba(x, y, game);
		}

		// modificación para empezar a contar desde el suelo.
		enemy->y = enemy->y - enemy->height / 2;
		enemies.push_back(enemy);
		space->addDynamicActor(enemy);
		break;
	}
	case 'T': {
		Tile* tile = new Tile("res/mapeado/pared_arriba.png", x, y, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'B': {
		Tile* tile = new Tile("res/mapeado/pared_abajo.png", x, y, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'D': {
		Tile* tile = new Tile("res/mapeado/pared_derecha.png", x, y, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'I': {
		Tile* tile = new Tile("res/mapeado/pared_izquierda.png", x, y, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case '7': {
		Tile* tile = new Tile("res/mapeado/pared_esquina_arriba_izquierda.png", x, y, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case '9': {
		Tile* tile = new Tile("res/mapeado/pared_esquina_arriba_derecha.png", x, y, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case '3': {
		Tile* tile = new Tile("res/mapeado/pared_esquina_abajo_derecha.png", x, y, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case '1': {
		Tile* tile = new Tile("res/mapeado/pared_esquina_abajo_izquierda.png", x, y, false, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}case '8': {
		Puerta* tile = new Puerta(game->puertaArriba, x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		puertas.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case '4': {
		Puerta* tile = new Puerta(game->puertaIzquierda, x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		puertas.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case '6': {
		Puerta* tile = new Puerta(game->puertaDerecha, x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		puertas.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case '2': {
		Puerta* tile = new Puerta(game->puertaAbajo, x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		puertas.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'r': {
		int num = rand() % 2;
		Recolectable* recolectable;

		if(num == 0)
			 recolectable = new BombaRecolectable(x, y, game);
		else
			recolectable = new VidasRecolectable(x, y, game);

		recolectable->y = recolectable->y - recolectable->height / 2;
		recolectables.push_back(recolectable);
		space->addDynamicActor(recolectable);
		break;
	}
	case 'R': {
		Tile* tile = new Tile("res/mapeado/roca.png", x, y, true, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'C': {
		Tile* tile = new Caca(x, y, game);
		// modificación para empezar a contar desde el suelo.
		tile->y = tile->y - tile->height / 2;
		tiles.push_back(tile);
		space->addStaticActor(tile);
		break;
	}
	case 'i': {
		if(player->items.size() + items.size() < 6){
			int num = rand() % 6;

			bool enLista = false;

			for (auto const& i : player->items) {
				enLista = (num == i->item) || enLista;
			}

			for (auto const& i : items) {
				enLista = (num == i->item) || enLista;
			}

			while (enLista) {
				num = rand() % 6;

				enLista = false;
				
				for (auto const& i : player->items) {
					enLista = (num == i->item) || enLista;
				}

				for (auto const& i : items) {
					enLista = (num == i->item) || enLista;
				}
			}
		
			Item* item = new Item(x, y, num, game);
			// modificación para empezar a contar desde el suelo.
			item->y = item->y - item->height / 2;
			items.push_back(item);
			space->addDynamicActor(item);
		}
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

	player->orientacionDisparos = game->noDisparando;

	if (controlShootUp) {
		list<Projectile*> newProjectiles = player->shoot();
		player->orientacionDisparos = game->orientationUp;

		for(auto const& p : newProjectiles){
			p->vx = 0;
			p->vy = -10;
			space->addDynamicActor(p);
			projectiles.push_back(p);
		}
		
	} 
	if (controlShootDown) {
		list<Projectile*> newProjectiles = player->shoot();
		player->orientacionDisparos = game->orientationBottom;
		
		for (auto const& p : newProjectiles) {
			p->vx = 0;
			p->vy = 10;
			space->addDynamicActor(p);
			projectiles.push_back(p);
		}
	}
	if (controlShootLeft) {
		list<Projectile*> newProjectiles = player->shoot();
		player->orientacionDisparos = game->orientationLeft;
		
		for (auto const& p : newProjectiles) {
			p->vx = -10;
			p->vy = 0;
			space->addDynamicActor(p);
			projectiles.push_back(p);
		}
	}
	if (controlShootRight) {
		list<Projectile*> newProjectiles = player->shoot();
		player->orientacionDisparos = game->orientationRight;

		for (auto const& p : newProjectiles) {
			p->vx = 10;
			p->vy = 0;
			space->addDynamicActor(p);
			projectiles.push_back(p);
		}
	}

	if (controlBomba) {
		Bomba* newBomba = player->ponerBomba();
		if (newBomba != NULL) {
			space->addDynamicActor(newBomba);
			bombas.push_back(newBomba);
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
	list<Recolectable*> deleteRecolectables;
	list<Item*> deleteItems;
	list<Enemy*> deleteEnemies;

	if (game->currentLevel == 0 && passed0) {
		for (auto const& enemy : enemies) {
			deleteEnemies.push_back(enemy);
		}

		for (auto const& recolectable : recolectables) {
			deleteRecolectables.push_back(recolectable);
		}

		for (auto const& item : items) {
			deleteItems.push_back(item);
		}
	}
	if (game->currentLevel == 1 && passed1) {
		for (auto const& enemy : enemies) {
			deleteEnemies.push_back(enemy);
		}

		for (auto const& recolectable : recolectables) {
			deleteRecolectables.push_back(recolectable);
		}

		for (auto const& item : items) {
			deleteItems.push_back(item);
		}
	}
	if (game->currentLevel == 2 && passed2) {
		for (auto const& enemy : enemies) {
			deleteEnemies.push_back(enemy);
		}

		for (auto const& recolectable : recolectables) {
			deleteRecolectables.push_back(recolectable);
		}

		for (auto const& item : items) {
			deleteItems.push_back(item);
		}
	}
	if (game->currentLevel == 3 && passed3) {
		for (auto const& enemy : enemies) {
			deleteEnemies.push_back(enemy);
		}

		for (auto const& recolectable : recolectables) {
			deleteRecolectables.push_back(recolectable);
		}

		for (auto const& item : items) {
			deleteItems.push_back(item);
		}
	}
	if (game->currentLevel == 4 && passed4) {
		for (auto const& enemy : enemies) {
			deleteEnemies.push_back(enemy);
		}

		for (auto const& recolectable : recolectables) {
			deleteRecolectables.push_back(recolectable);
		}

		for (auto const& item : items) {
			deleteItems.push_back(item);
		}
	}
	if (game->currentLevel == 5 && passed5) {
		for(auto const& enemy : enemies) {
			deleteEnemies.push_back(enemy);
		}

		for (auto const& recolectable : recolectables) {
			deleteRecolectables.push_back(recolectable);
		}

		for (auto const& item : items) {
			deleteItems.push_back(item);
		}
	}
	if (game->currentLevel == 6 && passed6) {
		for (auto const& enemy : enemies) {
			deleteEnemies.push_back(enemy);
		}

		for (auto const& recolectable : recolectables) {
			deleteRecolectables.push_back(recolectable);
		}
		
		for (auto const& item : items) {
			deleteItems.push_back(item);
		}
	}
	if (game->currentLevel == 7 && passed7) {
		for (auto const& enemy : enemies) {
			deleteEnemies.push_back(enemy);
		}

		for (auto const& recolectable : recolectables) {
			deleteRecolectables.push_back(recolectable);
		}

		for (auto const& item : items) {
			deleteItems.push_back(item);
		}
	}
	if (game->currentLevel == 8 && passed8) {
		for (auto const& enemy : enemies) {
			deleteEnemies.push_back(enemy);
		}

		for (auto const& recolectable : recolectables) {
			deleteRecolectables.push_back(recolectable);
		}

		for (auto const& item : items) {
			deleteItems.push_back(item);
		}
	}
	if (game->currentLevel == 9 && passed9) {
		for (auto const& enemy : enemies) {
			deleteEnemies.push_back(enemy);
		}

		for (auto const& recolectable : recolectables) {
			deleteRecolectables.push_back(recolectable);
		}

		for (auto const& item : items) {
			deleteItems.push_back(item);
		}
	}
	if (game->currentLevel == 10 && passed10) {
		for (auto const& enemy : enemies) {
			deleteEnemies.push_back(enemy);
		}

		for (auto const& recolectable : recolectables) {
			deleteRecolectables.push_back(recolectable);
		}

		for (auto const& item : items) {
			deleteItems.push_back(item);
		}

		cup = new Tile("res/recolectables/copa.png", 620, 384, false, game);
		// modificación para empezar a contar desde el suelo.
		cup->y = cup->y - cup->height / 2;
		space->addDynamicActor(cup); // Realmente no hace falta
	}

	if (pause) {
		return;
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

		
		Explosion* newExplosion = enemy->explode();

		if (newExplosion != NULL) {
			deleteEnemies.push_back(enemy);
			
			space->addDynamicActor(newExplosion);
			explosiones.push_back(newExplosion);
		}	
	}

	for (auto const& delEnemy : deleteEnemies) {
		enemies.remove(delEnemy);
		space->removeDynamicActor(delEnemy);
		delEnemy->deleteAnimations();
		delete delEnemy;
	}
	deleteEnemies.clear();

	for (auto const& projectile : projectiles) {
		projectile->update();
	}
	for (auto const& projectile : projectilesEnemigos) {
		projectile->update();
	}
	for (auto const& recolectable : recolectables) {
		recolectable->update();
	}

	for (auto const& bomba : bombas) {
		bomba->update();
	}

	for (auto const& explosion : explosiones) {
		explosion->update();
	}

	for (auto const& bomba : bombas) {
		Explosion* newExplosion = bomba->explode();
		
		if (newExplosion != NULL) {
			space->addDynamicActor(newExplosion);
			explosiones.push_back(newExplosion);
		}
	}

	list<Explosion*> deleteExplosiones;

	for (auto const& explosion : explosiones) {
		if (!explosion->hitted) {
			if (player->isOverlap(explosion)) {
				player->loseLife(1);
				if (player->lifes <= 0) {
					init();
					return;
				}
			}
		}
	}

	// Colisiones
	for (auto const& enemy : enemies) {
		if (player->isOverlap(enemy)) {
			player->loseLife(enemy->daño);
			if (player->lifes <= 0) {
				init();
				return;
			}
		}
	}

	for (auto const& puerta : puertas) {
		if (player->isOverlap(puerta)) {
			if(puerta->abierta){
				if (game->currentLevel == 0) {
					passed0 = true;
				}
				if (game->currentLevel == 1) {
					passed1 = true;
				}
				if (game->currentLevel == 2) {
					passed2 = true;
				}
				if (game->currentLevel == 3) {
					passed3 = true;
				}
				if (game->currentLevel == 4) {
					passed4 = true;
				}
				if (game->currentLevel == 5) {
					passed5 = true;
				}
				if (game->currentLevel == 6) {
					passed6 = true;
				}
				if (game->currentLevel == 7) {
					passed7 = true;
				}
				if (game->currentLevel == 8) {
					passed8 = true;
				}
				if (game->currentLevel == 9) {
					passed9 = true;
				}

				game->currentLevel = puerta->siguienteNivel();
				entrada = puerta->lado;
				init();
				return;
			}
		}
	}

	

	// Colisiones
	for (auto const& r : recolectables) {
		if (player->isOverlap(r)) {

			if (r->recoger() == game->bomba) {
				player->bombas++;
			}if (r->recoger() == game->corazon) {
				player->lifes++;
			}

			bool pInList = std::find(deleteRecolectables.begin(),
				deleteRecolectables.end(),
				r) != deleteRecolectables.end();

			if (!pInList) {
				deleteRecolectables.push_back(r);
			}
		}
	}

	// Colisiones
	for (auto const& i : items) {
		if (player->isOverlap(i)) {

			player->recogerItem(i);

			bool pInList = std::find(deleteItems.begin(),
				deleteItems.end(),
				i) != deleteItems.end();

			if (!pInList) {
				deleteItems.push_back(i);
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

	list<Projectile*> deleteProjectiles;
	list<Tile*> deleteTiles;
	list<Bomba*> deleteBombas;

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

	for (auto const& projectile : projectiles) {
		if (projectile->isInRender(scrollX, scrollY) == false || (projectile->vx == 0 && projectile->vy == 0) || projectile->lifeCycle > 120) {

			bool pInList = std::find(deleteProjectiles.begin(),
				deleteProjectiles.end(),
				projectile) != deleteProjectiles.end();

			if (!pInList) {
				deleteProjectiles.push_back(projectile);
			}
		}
	}

	for (auto const& enemy : enemies) {
		for (auto const& projectile : projectiles) {
			if (enemy->isOverlap(projectile)) {
				if (enemy->state != game->stateDead && enemy->state != game->stateDying) {
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
				}
			}
		}

		for (auto const& explosion : explosiones) {
			if (!explosion->hitted) {
				if (enemy->isOverlap(explosion)) {
					Enemy* newEnemy = enemy->impacted(2);

					if (newEnemy != NULL) {
						newEnemies.push_back(newEnemy);
					}
				}
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
			if (tile->isOverlap(projectile) && tile->destructibleByShoot) {
				((Caca*)tile)->perderVida();

				if (((Caca*)tile)->vida == 0) {
					bool pInList = std::find(deleteTiles.begin(),
						deleteTiles.end(),
						tile) != deleteTiles.end();

					if (!pInList) {
						deleteTiles.push_back(tile);
					}
				}
			}

			if (tile->isOverlap(projectile)){
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
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

		for (auto const& explosion : explosiones) {
			if (!explosion->hitted && tile->isOverlap(explosion)) {
				if (tile->desctructibleByBomb) {
					bool pInList = std::find(deleteTiles.begin(),
						deleteTiles.end(),
						tile) != deleteTiles.end();

					if (!pInList) {
						deleteTiles.push_back(tile);
					}
				}
			}
		}
	}

	for (auto const& puerta : puertas) {
		for (auto const& projectile : projectiles) {
			if (puerta->isOverlap(projectile)) {
				bool pInList = std::find(deleteProjectiles.begin(),
					deleteProjectiles.end(),
					projectile) != deleteProjectiles.end();

				if (!pInList) {
					deleteProjectiles.push_back(projectile);
				}
			}
		}

		for (auto const& projectile : projectilesEnemigos) {
			if (puerta->isOverlap(projectile)) {
				bool pInList = std::find(deleteProjectilesEnemigos.begin(),
					deleteProjectilesEnemigos.end(),
					projectile) != deleteProjectilesEnemigos.end();

				if (!pInList) {
					deleteProjectilesEnemigos.push_back(projectile);
				}
			}
		}
	}

	for (auto const& bomba : bombas) {
		if (bomba->state == game->stateExploited) {
			bool pInList = std::find(deleteBombas.begin(),
				deleteBombas.end(),
				bomba) != deleteBombas.end();

			if (!pInList) {
				deleteBombas.push_back(bomba);
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

	for (auto const& explosion : explosiones) {
		explosion->hitted = true;
	}

	for (auto const& explosion : explosiones) {
		if (explosion->state == game->stateExploited) {
			bool eInList = std::find(deleteExplosiones.begin(),
				deleteExplosiones.end(),
				explosion) != deleteExplosiones.end();

			if (!eInList) {
				deleteExplosiones.push_back(explosion);
			}
		}
	}

	for (auto const& delEnemy : deleteEnemies) {
		enemies.remove(delEnemy);
		space->removeDynamicActor(delEnemy);
		delEnemy->deleteAnimations();
		delete delEnemy;
	}
	deleteEnemies.clear();

	for (auto const& delProjectile : deleteProjectiles) {
		projectiles.remove(delProjectile);
		space->removeDynamicActor(delProjectile);
		delProjectile->deleteAnimations();
		delete delProjectile;
	}
	deleteProjectiles.clear();

	for (auto const& delProjectile : deleteProjectilesEnemigos) {
		projectilesEnemigos.remove(delProjectile);
		space->removeDynamicActor(delProjectile);
		delProjectile->deleteAnimations();
		delete delProjectile;
	}
	deleteProjectilesEnemigos.clear();

	for (auto const& delRecolectable : deleteRecolectables) {
		recolectables.remove(delRecolectable);
		space->removeDynamicActor(delRecolectable);
		delRecolectable->deleteAnimations();
		delete delRecolectable;
	}
	deleteRecolectables.clear();

	for (auto const& delTile : deleteTiles) {
		tiles.remove(delTile);
		space->removeStaticActor(delTile);
		delete delTile;
	}
	deleteTiles.clear();

	for (auto const& delExplosion : deleteExplosiones) {
		explosiones.remove(delExplosion);
		space->removeDynamicActor(delExplosion);
		delExplosion->deleteAnimations();
		delete delExplosion;
	}
	deleteExplosiones.clear();

	for (auto const& delBomba : deleteBombas) {
		bombas.remove(delBomba);
		space->removeDynamicActor(delBomba);
		delBomba->deleteAnimations();
		delete delBomba;
	}
	deleteBombas.clear();

	for (auto const& delItem : deleteItems) {
		items.remove(delItem);
		space->removeDynamicActor(delItem);
	}
	deleteItems.clear();

	textBombas->content = to_string(player->bombas);
	textVidas->content = to_string(player->lifes);

	if (enemies.size() == 0) {
		for (auto const& puerta : puertas) {
			puerta->abrir();

			if (game->currentLevel == 10) {
				passed10 = true;
			}
		}
	}

	if (projectiles.size() > 1100) {
		for (int i = 0; i < 200; i++) {
			projectiles.pop_front();
		}
	}
}

void GameLayer::calculateScroll() {
	scrollX = 0;
	scrollY = 0;
}


void GameLayer::draw() {
	calculateScroll();

	background->draw();
	
	for (auto const& tile : tiles) {
		tile->draw(scrollX, scrollY);
	}
	for (auto const& puerta : puertas) {
		puerta->draw(scrollX, scrollY);
	}

	player->draw(scrollX, scrollY);

	for (auto const& projectile : projectilesEnemigos) {
		projectile->draw(scrollX, scrollY);
	}
	for (auto const& projectile : projectiles) {
		projectile->draw(scrollX, scrollY);
	}
	
	if(cup != NULL)
		cup->draw(scrollX, scrollY);

	for (auto const& enemy : enemies) {
		enemy->draw(scrollX, scrollY);
	}

	for (auto const& recolectable : recolectables) {
		recolectable->draw(scrollX, scrollY);
	}

	for (auto const& explosion : explosiones) {
		explosion->draw(scrollX, scrollY);
	}

	for (auto const& bomba : bombas) {
		bomba->draw(scrollX, scrollY);
	}

	for (auto const& item : items) {
		item->draw(scrollX, scrollY);
	}

	backgroundVidas->draw();
	textVidas->draw();

	backgroundBombas->draw();
	textBombas->draw();

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

void GameLayer::keysToControls(SDL_Event event) {
	if (event.type == SDL_KEYDOWN) {
		int code = event.key.keysym.sym;
		
		if (pause == true) {
			pause = false;
		}

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
			case SDLK_SPACE:
				controlBomba = true;
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
			case SDLK_SPACE:
				controlBomba = false;
				break;
		}
	}
}

	