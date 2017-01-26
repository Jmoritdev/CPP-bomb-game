#pragma once

#include "EntityInanimate.h"

class Explosion : public EntityInanimate {

protected:

	struct Circle {
		int x, y;
		int r;
	};

	Circle hitCircle;

public:

	Explosion(std::string texturePath, SDL_Renderer* renderer, Settings* settings, int blastRadius, int localX = DEFAULT_POS, int localY = DEFAULT_POS,
		int width = DEFAULT_SIZE, int height = DEFAULT_SIZE) :
		EntityInanimate(texturePath, renderer, settings, localX, localY, width, height) {

		hitCircle.r = blastRadius;
		hitCircle.x = localX;
		hitCircle.y = localY;

	}

	Circle* getHitCircle() {
		return &hitCircle;
	}

	//checks all entities to see if they are within the blastzone, if they are, they are going to die
	void checkCollision() {
		//a constant iterator for a vector that stores pointers to entitys
		std::vector<Entity*>::const_iterator iterator;

		//a pointer to a vector that stores pointers to all entities currently initialized
		std::vector<Entity*>* entityList = settings->getEntities();

		for (iterator = entityList->begin(); iterator != entityList->end(); ++iterator) {

			SDL_Rect* hitbox= (*iterator)->getHitbox();

			if ((*iterator) != this) {

				//Closest point on collision box
				int cX, cY;

				//Find closest x offset
				if (hitCircle.x < hitbox->x) {
					cX = hitbox->x;
				} else if (hitCircle.x > hitbox->x + hitbox->w) {
					cX = hitbox->x + hitbox->w;
				} else {
					cX = hitCircle.x;
				}

				//Find closest y offset
				if (hitCircle.y < hitbox->y) {
					cY = hitbox->y;
				} else if (hitCircle.y > hitbox->y + hitbox->h) {
					cY = hitbox->y + hitbox->h;
				} else {
					cY = hitCircle.y;
				}

				if (distanceSquared(hitCircle.x, hitCircle.y, cX, cY) < hitCircle.r * hitCircle.r) {
					//This box and the circle have collided
					if (!((*iterator)->isBorder())) {
						settings->addEntityToDie(*iterator);
					}
				}
			}
		}
	}

	double distanceSquared(int x1, int y1, int x2, int y2) {
		int deltaX = x2 - x1;
		int deltaY = y2 - y1;
		return deltaX*deltaX + deltaY*deltaY;
	}
};

