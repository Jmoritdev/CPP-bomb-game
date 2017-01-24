#pragma once

#include "EntityMoving.h"
#include "Projectile.h"

class EntityLiving : public EntityMoving{

protected:
	
	int health;


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


	bool collideWithBorder() {
		return true;
	}

};

