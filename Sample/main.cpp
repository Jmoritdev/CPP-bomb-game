#include "Player.h"
#include "Enemy.h"
#include "Settings.h"
#include "Prop.h"
#include "Border.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <SDL_ttf.h>


//Screen dimension constants
static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 480;

static const int SPAWN_INTERVAL_ENEMY = 2;
static const int SPAWN_INTERVAL_CRATE = 2;

static const int ENEMY_SHOOTING_INTERVAL = 1;

static const int MAX_CRATES = 15;
static const int MAX_ENEMIES = 6;

//header file that stores global variables such as screen width etc.
Settings settings;

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//the font
TTF_Font *font = NULL;

Texture scoreTexture;

int killcount = 0;



bool init() {
	//Initialization flag
	bool success = true;

	srand(time(NULL));

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	} else {
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
									*settings.getScreenWidth(), *settings.getScreenHeight(), SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		} else {
			//Create vsynced renderer for window
			if (settings.getVSync()) {
				gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			} else {
				gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED );
			}
			
			if (gRenderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			} else {
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
					printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
					success = false;
				} else {
					//Initialize SDL_ttf
					if (TTF_Init() == -1) {
						printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
						success = false;
					} else {
						font = TTF_OpenFont("./Sprites/lazy.ttf", 28);
						if (font == NULL) {
							printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
							success = false;
						}
					}
				}
			}
		}
	}

	return success;
}

void close() {
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Free global font
	TTF_CloseFont(font);
	font = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

//setup the default crates, the borders, spawn the player etc..
void setupDefault() {

	//top border
	settings.addEntity(new Border("./Sprites/borderTopBottom.bmp", gRenderer, &settings, 100, 100, 440, 1));
	//bottom border
	settings.addEntity(new Border("./Sprites/borderTopBottom.bmp", gRenderer, &settings, 100, 380, 440, 1));
	//left border
	settings.addEntity(new Border("./Sprites/borderLeftRight.bmp", gRenderer, &settings, 100, 100, 1, 280));
	//right border
	settings.addEntity(new Border("./Sprites/borderLeftRight.bmp", gRenderer, &settings, 540, 100, 1, 280));

	settings.addEntity(new Prop("./Sprites/crate.bmp", gRenderer, &settings, 150, 150));

	settings.addEntity(new Prop("./Sprites/crate.bmp", gRenderer, &settings, 320, 240));

	settings.addEntity(new Prop("./Sprites/crate.bmp", gRenderer, &settings, 390, 150));

	settings.addEntity(new Prop("./Sprites/crate.bmp", gRenderer, &settings, 420, 300));

	settings.addEntity(new Prop("./Sprites/crate.bmp", gRenderer, &settings, 150, 300));

}

void spawnEnemy() {

	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> distributionX(120, 520); 
	std::uniform_int_distribution<int> distributionY(120, 360); 
	std::uniform_int_distribution<int> randomBool(0, 1); 


	int randomX;
	int randomY;

	//should it be along the x axis (yes / no)
	int isX = randomBool(rng);

	//should it be along the top or bottom(yes / no)
	int isTop = randomBool(rng);

	//should it be left or right
	int isLeft = randomBool(rng);


	if (isX) {
		randomX = distributionX(rng);
		if (isTop) {
			randomY = 1;
		} else {
			randomY = 459;
		}
	} else {
		randomY = distributionY(rng);
		if (isLeft) {
			randomX = 1;
		} else {
			randomX = 619;
		}
	}

	if (isX) {
		if (isTop) {
			settings.addEntity(new Enemy("./Sprites/enemy.bmp", gRenderer, &settings, 180, randomX, randomY, 20, 20, 0, 1));
		} else {
			settings.addEntity(new Enemy("./Sprites/enemy.bmp", gRenderer, &settings, 0, randomX, randomY, 20, 20, 0, -1));
		}
		
	} else {
		if (isLeft) {
			settings.addEntity(new Enemy("./Sprites/enemy.bmp", gRenderer, &settings, 90, randomX, randomY, 20, 20, 1, 0));
		} else {
			settings.addEntity(new Enemy("./Sprites/enemy.bmp", gRenderer, &settings, 270, randomX, randomY, 20, 20, -1, 0));
		}
	}
}

void spawnCrate() {
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distributionX(120, 530); // define the range
	std::uniform_int_distribution<> distributionY(120, 370); // define the range

	int randomX = distributionX(eng);
	int randomY = distributionY(eng);

	settings.addEntity(new Prop("./Sprites/crate.bmp", gRenderer, &settings, randomX, randomY, 20, 20));
}

int main(int argc, char* args[]) {
	settings = Settings();

	//Start up SDL and create window
	if (!init()) {
		printf("Failed to initialize!\n");
	} else {
		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;

		//setup default crates and the player
		setupDefault();

		Player* player = new Player("./Sprites/dot.bmp", gRenderer, &settings, 400, 300);
		settings.addEntity(player);

		//preparing some pointers to use for looping in the game loop
		std::vector<Entity*>::const_iterator iterator;

		//a pointer to a list with pointers of all entities
		std::vector<Entity*>* entityList = settings.getEntities();

		//a pointer to a list with pointers of all entities that are going to die
		std::vector<Entity*>* toDieList = settings.getToDieList();

		//a pointer to a list with pointers of all entities that are going to live 
		//(used for bombs that are shot while iterating over the entitylist)
		std::vector<Entity*>* toAddList = settings.getToAddList();

		int frames = 0;

		//tracks the previous killcount to check if the killcount has changed
		int previousKillCount = 0;

		//While application is running
		while (!quit) {

			++frames;

			//I am not proud of this, but I couldn't think of anything better
			if (frames % (SPAWN_INTERVAL_CRATE * 60) == 0) {
				spawnCrate();
			} 
			if (frames % (SPAWN_INTERVAL_ENEMY * 60) == 0) {
				spawnEnemy();
			}
																		       
			

			//Handle events on queue
			while (SDL_PollEvent(&e) != 0) {
				//User requests quit
				if (e.type == SDL_QUIT) {
					quit = true;
				}

				//Handle input for the player
				player->handleEvent(e);
			}

			//Clear screen
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);

			//move and render everything
			for (iterator = entityList->begin(); iterator != entityList->end(); ++iterator) {
				(*iterator)->move();
				(*iterator)->render();
				if ((*iterator)->isEnemy() && frames % (ENEMY_SHOOTING_INTERVAL * 60) == 0) {
					(*iterator)->shootBomb();
				}
			}

			//iterate over the deathlist
			for (iterator = toDieList->begin(); iterator != toDieList->end(); ++iterator) {
				//find the element in entitylist
				std::vector<Entity*>::const_iterator itTemp = std::find(entityList->begin(), entityList->end(), (*iterator));
				
				if ((*iterator)->isPlayer()) {
					quit = true;
				}
				if ((*iterator)->isEnemy()) {
					killcount++;
				}

				//free memory on the heap and remove the pointer in entityList
				delete *itTemp;
				entityList->erase(itTemp);

				//erase the pointer from the deathlist
				toDieList->erase(iterator);
				
				if (toDieList->empty()) {
					break;
				} 
				iterator = toDieList->begin();
			}

			//iterate over the toAddList
			for (iterator = toAddList->begin(); iterator != toAddList->end(); ++iterator) {
				settings.addEntity(*iterator);
			}
			toAddList->clear();
			
			//has the killcount changed
			if (killcount != previousKillCount) {

				//change the killcount text
				std::string killcountText = "Killcount: " + std::to_string(killcount);
				
				scoreTexture.loadFromRenderedText(font, killcountText, { 0,0,0 }, gRenderer);
				previousKillCount++;
			}
			scoreTexture.render(450, 20, gRenderer);

			//Update screen
			SDL_RenderPresent(gRenderer);
		}

	}

	//Free resources and close SDL
	close();

	return 0;
}

