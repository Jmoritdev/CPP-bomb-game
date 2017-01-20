#pragma once

#include "EntityMoving.h"

class Projectile : public EntityMoving {

protected:

	Entity* shooter;

public:

	Projectile() : EntityMoving() {}

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
		Entity::explode();
	}



};

