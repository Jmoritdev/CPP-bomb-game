#pragma once

#include "Entity.h"

class EntityInanimate : public Entity{
public:

	EntityInanimate(std::string texturePath, SDL_Renderer* renderer, Settings* settings, int localX = DEFAULT_POS, int localY = DEFAULT_POS, 
		int width = DEFAULT_SIZE, int height = DEFAULT_SIZE) :
		Entity(texturePath, renderer, settings, localX, localY, width, height) {

	}

	EntityInanimate() : Entity(){
		
	}
};

