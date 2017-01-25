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

	virtual void shootBomb() {}

	virtual bool isEnemy() {
		return false;
	}

	virtual bool isPlayer() {
		return false;
	}

	virtual void startShooting() {}
};

