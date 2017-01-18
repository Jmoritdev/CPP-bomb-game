#pragma once


#include <vector>
#include <iostream>
class Entity;


class Settings {

private:

	int screenWidth;
	int screenHeight;
	bool vSync;
	std::vector<Entity*> entityList;

public:

	Settings() {
		screenHeight = 480;
		screenWidth = 640;
		vSync = true;
	}

	int* getScreenWidth() {
		return &screenWidth;
	}

	int* getScreenHeight() {
		return &screenHeight;
	}

	void setScreenWidth(int width) {
		screenWidth = width;
	}

	void setScreenHeight(int height) {
		screenHeight = height;
	}

	void toggleVSync() {
		vSync = !vSync;
	}

	bool getVSync() {
		return vSync;
	}

	void addEntity(Entity* entity) {
		entityList.push_back(entity);
	}

	std::vector<Entity*>* getEntities() {
		return &entityList;
	}

};

