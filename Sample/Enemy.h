#pragma once

#include "EntityLiving.h"

class Enemy : public EntityLiving {

protected:

	int shootingAngle;

public:
	bool isShooting = false;

	Enemy(std::string texturePath, SDL_Renderer* renderer, Settings* settings, int shootingAngle, int localX = DEFAULT_POS, int localY = DEFAULT_POS, 
		int width = DEFAULT_SIZE, int height = DEFAULT_SIZE, int localVelX = 0, int localVelY = 0) :
		EntityLiving(texturePath, renderer, settings, localX, localY, width, height, localVelX, localVelY){

		this->shootingAngle = shootingAngle;
		
	}

	bool isEnemy() {
		return true;
	}
	
	//this is called once the enemy hits the border, so the player has a timeframe between the enemy spawning, 
	//and the enemy shooting bombs
	void startShooting() {
		isShooting = true;
	}

	void shootBomb() {
		if (isShooting) {
			Entity* bomb = NULL;

			switch (shootingAngle) {
				case 0:
					bomb = new Projectile("./Sprites/bomb.bmp", renderer, settings, this, posX, posY, 13, 18, 0, -10); break;
				case 90:
					bomb = new Projectile("./Sprites/bomb.bmp", renderer, settings, this, posX, posY, 13, 18, 10, 0); break;
				case 180:
					bomb = new Projectile("./Sprites/bomb.bmp", renderer, settings, this, posX, posY, 13, 18, 0, 10); break;
				case 270:
					bomb = new Projectile("./Sprites/bomb.bmp", renderer, settings, this, posX, posY, 13, 18, -10, 0); break;
				default:
					bomb = new Projectile("./Sprites/bomb.bmp", renderer, settings, this, posX, posY, 13, 18, 0, -10); break;
			}

			settings->addEntityToLive(bomb);
		}
	}
};

