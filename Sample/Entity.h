#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include "Texture.h"
#include "Settings.h"

class Entity {

protected:

	//The X and Y offsets of the entity
	int posX, posY;

	//width and height
	int width, height;

	Settings* settings;

	SDL_Rect hitbox;


private:

	Texture texture;

public:
	static const int DEFAULT_SIZE = 20;
	static const int DEFAULT_POS = 0;

	Entity() {
		//Initialize the offsets
		posX = DEFAULT_POS;
		posY = DEFAULT_POS;

		width = DEFAULT_SIZE;
		height = DEFAULT_SIZE;

		hitbox.w = width;
		hitbox.h = height;
	}

	Entity(std::string texturePath, SDL_Renderer* renderer, Settings* settings, int localX = DEFAULT_POS, int localY = DEFAULT_POS, 
		   int width = DEFAULT_SIZE, int height = DEFAULT_SIZE) {

		//Initialize the offsets
		posX = localX;
		posY = localY;

		this->width = width;
		this->height = height;

		hitbox.w = width;
		hitbox.h = height;
		hitbox.x = localX;
		hitbox.y = localY;

		this->settings = settings;

		//Load texture
		if (!texture.loadFromFile(texturePath, renderer)) {
			printf("Failed to load texture!\n");
		}
	}

	~Entity() {
		free();
	}

	//Shows the dot on the screen
	void render(SDL_Renderer* renderer) {
		//Show the dot
		texture.render(posX, posY, renderer);
	}

	bool loadFromFile(std::string path, SDL_Renderer* renderer) {
		return texture.loadFromFile(path, renderer);
	}

	void free() {
		texture.free();
		settings = NULL;
	}

	//this function brute force checks all entities in the game for collision.
	bool isColliding() {

		//a constant iterator for a vector that stores pointers to entitys
		std::vector<Entity*>::const_iterator iterator;

		//a pointer to a vector that stores pointers to all entities currently initialized
		std::vector<Entity*>* pList = settings->getEntities();

		//initialize the coordinates of the passed rectangle
		int leftA, rightA, topA, bottomA;

		leftA = getHitbox()->x;
		rightA = getHitbox()->x + getHitbox()->w;
		topA = getHitbox()->y;
		bottomA = getHitbox()->y + getHitbox()->h;


		//go through the list of entities
		for (iterator = pList->begin(); iterator != pList->end(); ++iterator) {

			//do not check yourself for collisions
			if ((*iterator) != this) {

				SDL_Rect* hitboxB = (*iterator)->getHitbox();

				//initialize coordinates for all sides of the object we're checking collision with
				int leftB = hitboxB->x;
				int rightB = (hitboxB->x) + (hitboxB->w);
				int topB = hitboxB->y;
				int bottomB = (hitboxB->y) + (hitboxB->h);

				if (rightA <= leftB) {
					continue;
				}

				if (leftA >= rightB) {
					continue;
				}

				if (bottomA <= topB) {
					continue;
				}

				if (topA >= bottomB) {
					continue;
				}

				pList = NULL;
				return true;

			}
		}

		pList = NULL;
		return false;
		////The sides of the rectangles
		//int leftA, leftB;
		//int rightA, rightB;
		//int topA, topB;
		//int bottomA, bottomB;

		////Calculate the sides of rect A
		//leftA = a.x;
		//rightA = a.x + a.w;
		//topA = a.y;
		//bottomA = a.y + a.h;

		////Calculate the sides of rect B
		//leftB = b.x;
		//rightB = b.x + b.w;
		//topB = b.y;
		//bottomB = b.y + b.h;

		//if (rightA <= leftB) {
		//	return false;
		//}

		//if (leftA >= rightB) {
		//	return false;
		//}

		//if (bottomA <= topB) {

		//	return false;
		//}

		//if (topA >= bottomB) {
		//	return false;
		//}



		//std::cout << "colliding!";
		////If none of the sides from A are outside B
		//return true;
	}

	SDL_Rect* getHitbox() {
		return &hitbox;
	}

};

