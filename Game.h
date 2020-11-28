#pragma once

// Todas las librerias de SDL y otras utilidades
#include <iostream>
#include <string>
using namespace std;
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <map> 

// Valores generales
#define WIDTH 1280
#define HEIGHT 736

#include "Layer.h"
class Layer;

class Game
{
public:
	Game();
	void scale();
	void loop();
	SDL_Texture* getTexture(string filename);
	map<string, SDL_Texture*> mapTextures; // map - cache
	TTF_Font* font;
	bool scaledToMax = false;
	float scaleLower = 1;
	SDL_Window* window; // ventana
	SDL_Renderer* renderer; // renderizador
	bool loopActive; // Juego activo
	Layer* layer;
	Layer* menuLayer;
	Layer* gameLayer;

	int currentLevel = 0;
	int finalLevel = 10;

	int input;
	int const inputKeyboard = 1;
	int const inputMouse = 2;
	int const inputGamePad = 3;

	int const stateMoving = 1;
	int const stateJumping = 2;
	int const stateDying = 3;
	int const stateDead = 4;
	int const stateShooting = 5;
	int const stateHitted = 6;
	int const stateExploding = 7;
	int const stateExploited = 8;

	int const noDisparando = 0;
	int const orientationRight = 1;
	int const orientationLeft = 2;
	int const orientationUp = 3;
	int const orientationBottom = 4;

	int const puertaIzquierda = 4;
	int const puertaArriba = 8;
	int const puertaAbajo = 2;
	int const puertaDerecha = 6;

	int const bomba = 1;
	int const corazon = 2;
};
