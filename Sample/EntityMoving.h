#pragma once

#include "Entity.h"

class EntityMoving : public Entity{

protected:

	int velX, velY;

public:

	EntityMoving() {

	}

	EntityMoving(std::string texturePath, SDL_Renderer* renderer, Settings* settings, int localX = DEFAULT_POS, int localY = DEFAULT_POS,
		int width = DEFAULT_SIZE, int height = DEFAULT_SIZE, int localVelX = 0, int localVelY = 0) :
		Entity(texturePath, renderer, settings, localX, localY, width, height) {

		this->velX = localVelX;
		this->velY = localVelY;

	}

	~EntityMoving() {
	}

	void move() {

		//if you dont move, you dont have to do anything within this if statement
		if (velX != 0) {

			//move left or right
			posX += velX;
			hitbox.x += velX;

			//check for collision with borders  //getScreenWidth returns a pointer, so dereference before comparing
			if ((posX < 0) || (posX + width > *(settings->getScreenWidth())) || isColliding()) {
				
				//does nothing unless 'this' is an enemy
				this->startShooting();

				if (this->isProjectile()) {
					settings->addEntityToDie(this);
				}
				//Move back
				posX -= velX;
				hitbox.x -= velX;
			}

		}

		//if you dont move, you dont have to do anything within this if statement
		if (velY != 0) {

			//Move up or down
			posY += velY;
			hitbox.y += velY;

			//check for collision with borders 	//same here for height
			if ((posY < 0) || (posY + height > *(settings->getScreenHeight())) || isColliding()) {

				//does nothing unless 'this' is an enemy
				this->startShooting();

				if (this->isProjectile()) {
					settings->addEntityToDie(this);
				}
				//Move back
				posY -= velY;
				hitbox.y -= velY;
			}

		}
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
				(*iterator)->getShooter() != this && this->getShooter() != (*iterator)) {

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
};

