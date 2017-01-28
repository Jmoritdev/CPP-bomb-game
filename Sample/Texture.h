#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include <SDL_ttf.h>

//used from the tutorial (http://lazyfoo.net/tutorials/SDL/index.php) and edited to work in a seperate class 
class Texture {

private:
	//The actual hardware texture
	SDL_Texture* texture;

	//Image dimensions
	int width;
	int height;

public:

	//Initializes variables
	Texture() {
		//Initialize
		texture = NULL;
		width = 0;
		height = 0;
	}

	//Deallocates memory
	~Texture() {
		//Deallocate
		free();
	}
	
	
	bool loadFromFile(std::string path, SDL_Renderer* renderer) {
		//Get rid of preexisting texture
		free();

		//The final texture
		SDL_Texture* newTexture = NULL;

		//Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		if (loadedSurface == NULL) {
			printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		} else {
			//Color key image
			SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

			//Create texture from surface pixels
			newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
			if (newTexture == NULL) {
				printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
			} else {
				//Get image dimensions
				width = loadedSurface->w;
				height = loadedSurface->h;
			}

			//Get rid of old loaded surface
			SDL_FreeSurface(loadedSurface);
		}

		//Return success
		texture = newTexture;
		return texture != NULL;
	}

	//Deallocates texture
	void free() {
		//Free texture if it exists
		if (texture != NULL) {
			SDL_DestroyTexture(texture);
			texture = NULL;
			width = 0;
			height = 0;
		}
	}

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue) {
		//Modulate texture rgb
		SDL_SetTextureColorMod(texture, red, green, blue);
	}

	//Set blending
	void setBlendMode(SDL_BlendMode blending) {
		//Set blending function
		SDL_SetTextureBlendMode(texture, blending);
	}

	//Set alpha modulation
	void setAlpha(Uint8 alpha) {
		//Modulate texture alpha
		SDL_SetTextureAlphaMod(texture, alpha);
	}

	//Renders texture at given point
	void render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) {
		//Set rendering space and render to screen
		SDL_Rect renderQuad = { x, y, width, height };

		//Set clip rendering dimensions
		if (clip != NULL) {
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}

		//Render to screen
		SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
	}

	//Gets image dimensions
	int getWidth() {
		return width;
	}

	int getHeight() {
		return height;
	}

	bool loadFromRenderedText(TTF_Font *font, std::string textureText, SDL_Color textColor, SDL_Renderer* renderer) {
		//Get rid of preexisting texture
		free();

		//Render text surface
		SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
		if (textSurface == NULL) {
			printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
		} else {
			//Create texture from surface pixels
			texture = SDL_CreateTextureFromSurface(renderer, textSurface);
			if (texture == NULL) {
				printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
			} else {
				//Get image dimensions
				width = textSurface->w;
				height = textSurface->h;
			}

			//Get rid of old surface
			SDL_FreeSurface(textSurface);
		}

		//Return success
		return texture != NULL;
	}

};

