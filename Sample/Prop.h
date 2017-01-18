#pragma once

#include "EntityInanimate.h"

class Prop : public EntityInanimate{
public:

	Prop(std::string texturePath, SDL_Renderer* renderer, Settings* settings, int localX = DEFAULT_POS, int localY = DEFAULT_POS, 
		int width = DEFAULT_SIZE, int height = DEFAULT_SIZE) :
		EntityInanimate(texturePath, renderer, settings, localX, localY, width, height) {

	}


	void explode() {

	}
};

