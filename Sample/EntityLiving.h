#pragma once

#include "EntityMoving.h"
#include "Projectile.h"

class EntityLiving : public EntityMoving{

protected:
	
	int health;

	//keeps track of all the projectiles the player shot
	std::vector<Entity*> projectileList;

public:
	static const int DEFAULT_HEALTH = 100;
	static const int DEFAULT_VELOCITY = 10;

	EntityLiving() : EntityMoving(){
		this->health = DEFAULT_HEALTH;
	}

	EntityLiving(std::string texturePath, SDL_Renderer* renderer, Settings* settings, int localX = DEFAULT_POS, int localY = DEFAULT_POS, 
				 int width = DEFAULT_SIZE, int height = DEFAULT_SIZE,int localVelX = 0, int localVelY = 0, int health = DEFAULT_HEALTH) :
		EntityMoving(texturePath, renderer, settings, localX, localY, width, height, localVelX, localVelY){
		
		this->health = health;

	}

	~EntityLiving() {
		
	}

	void shootBomb(int endPointX, int endPointY) {
		int bombVelX = (endPointX - posX);
		int bombVelY = (endPointY - posY);

		Entity* bomb = new Projectile("Sprites/bomb.bmp", renderer, settings, this, posX, posY, 20, 20, 5, 5);
		settings->addEntity(bomb);
		projectileList.push_back(bomb);
	}

	std::vector<Entity*>* getProjectileList() {
		if (projectileList.empty()) {
			return NULL;
		}
		return &projectileList;
	}



};

