#pragma once

#include "EntityMoving.h"
#include "Explosion.h"

class Projectile : public EntityMoving {

protected:

	// a pointer to the shooter of the projectile
	Entity* shooter;

public:

	Projectile(std::string texturePath, SDL_Renderer* renderer, Settings* settings, Entity* shooter, int localX = DEFAULT_POS, int localY = DEFAULT_POS,
		int width = DEFAULT_SIZE, int height = DEFAULT_SIZE, int localVelX = 0, int localVelY = 0) :
		EntityMoving(texturePath, renderer, settings, localX, localY, width, height, localVelX, localVelY) {

		this->shooter = shooter;

	}

	~Projectile() {
		shooter = NULL;
	}

	Entity* getShooter() {
		return shooter;
	}

	void explode() {
		//create an explosion then check if the explosion is hitting anything
		Explosion* explosion = new Explosion("Sprites/explosion1.bmp", renderer, settings, 50, posX, posY);
		explosion->checkCollision();

		//after exploding, free the memory on the heap and clear the pointer
		delete explosion;
		explosion = NULL;
	}

	bool isProjectile() {
		return true;
	}

	bool collideWithBorder() {
		return false;
	}

};

