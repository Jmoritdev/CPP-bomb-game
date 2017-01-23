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


//Screen dimension constants
static const int SCREEN_WIDTH = 640;
static const int SCREEN_HEIGHT = 480;

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



bool init() {
	//Initialization flag
	bool success = true;

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

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
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

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
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

		//top border
		settings.addEntity(new Border("./Sprites/borderTopBottom.bmp", gRenderer, &settings, 100, 100, 440, 1));
		//bottom border
		settings.addEntity(new Border("./Sprites/borderTopBottom.bmp", gRenderer, &settings, 100, 380, 440, 1));
		//left border
		settings.addEntity(new Border("./Sprites/borderLeftRight.bmp", gRenderer, &settings, 100, 100, 1, 280));
		//right border
		settings.addEntity(new Border("./Sprites/borderLeftRight.bmp", gRenderer, &settings, 540, 100, 1, 280));

		Player* player = new Player("./Sprites/dot.bmp", gRenderer, &settings, 400, 300);

		settings.addEntity(player);
		settings.addEntity(new Enemy("./Sprites/enemy.bmp", gRenderer, &settings, 200, 200));
		settings.addEntity(new Prop("./Sprites/crate.bmp", gRenderer, &settings, 100, 100));

		//preparing some pointers to use for looping in the game loop
		std::vector<Entity*>::const_iterator iterator;

		//a pointer to a list with pointers of all entities
		std::vector<Entity*>* entityList = settings.getEntities();

		//a pointer to a list with pointers of all entities that are going to die
		std::vector<Entity*>* toDieList = settings.getToDieList();

		//While application is running
		while (!quit) {
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
				if (!(*iterator)->isBorder() || !(*iterator)->isProp()) {
					(*iterator)->move();
					(*iterator)->render();
				}
			}

			//iterate over the deathlist
			for (iterator = toDieList->begin(); iterator != toDieList->end(); ++iterator) {
				//find the element in entitylist
				std::vector<Entity*>::const_iterator itTemp = std::find(entityList->begin(), entityList->end(), (*iterator));
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
			

			//Update screen
			SDL_RenderPresent(gRenderer);
		}

	}

	//Free resources and close SDL
	close();

	return 0;
}