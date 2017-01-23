#pragma once

#include "EntityInanimate.h"

class Border : public EntityInanimate {
public:

	Border(std::string texturePath, SDL_Renderer* renderer, Settings* settings, int localX = DEFAULT_POS, int localY = DEFAULT_POS,
		int width = DEFAULT_SIZE, int height = DEFAULT_SIZE) :
		EntityInanimate(texturePath, renderer, settings, localX, localY, width, height) {

	}

	bool isBorder() {
		return true;
	}
};

