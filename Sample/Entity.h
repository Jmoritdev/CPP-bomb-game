#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include <algorithm>
#include "Texture.h"
#include "Settings.h"

class Entity {

protected:

	//The X and Y offsets of the entity
	int posX, posY;

	//width and height
	int width, height;

	Settings* settings;
	SDL_Renderer* renderer;

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
		this->renderer = renderer;

		//Load texture
		if (!texture.loadFromFile(texturePath, renderer)) {
			printf("Failed to load texture!\n");
		}
	}

	~Entity() {
		free();
	}

	//Shows the dot on the screen
	void render() {
		//Show the dot
		texture.render(posX, posY, renderer);
	}

	bool loadFromFile(std::string path) {
		return texture.loadFromFile(path, renderer);
	}

	void free() {
		texture.free();
		renderer = NULL;
		settings = NULL;
	}

	//this function brute force checks all entities in the game for collision.
	bool isColliding() {

		//a constant iterator for a vector that stores pointers to entitys
		std::vector<Entity*>::const_iterator iterator;

		//a pointer to a vector that stores pointers to all entities currently initialized
		std::vector<Entity*>* entityList = settings->getEntities();

		//initialize the coordinates of the passed rectangle
		int leftA, rightA, topA, bottomA;

		leftA = getHitbox()->x;
		rightA = getHitbox()->x + getHitbox()->w;
		topA = getHitbox()->y;
		bottomA = getHitbox()->y + getHitbox()->h;

		//go through the list of entities
		for (iterator = entityList->begin(); iterator != entityList->end(); ++iterator) {

			//do not check yourself					
			if ((*iterator) != this && 
				//check if you are NOT (a border and the iterator a projectile), or the other way around
				!((*iterator)->isProjectile() && this->isBorder() || ((*iterator)->isBorder() && this->isProjectile())) &&
				//check if you are not the shooter of the projectile, or the other way around
				(*iterator)->getShooter() != this && this->getShooter() != (*iterator)){

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

				if (this->isProjectile()) {
					this->explode();
				}
				entityList = NULL;
				return true;

			}
		}
		
		entityList = NULL;
		return false;
	}

	SDL_Rect* getHitbox() {
		return &hitbox;
	}

	virtual Entity* getShooter() {
		return NULL;
	}

	virtual void move() {}

	virtual std::vector<Entity*>* getProjectileList() {
		return NULL;
	}

	virtual void explode() {}

	virtual bool isProjectile() {
		return false;
	}

	virtual bool isBorder() {
		return false;
	}

	virtual bool isProp() {
		return false;
	}

	virtual bool collideWithBorder() {
		return true;
	}

};

