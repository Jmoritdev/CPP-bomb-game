#pragma once

#include <vector>
#include <iostream>

//normally including Entity caused some weird bugs, but this somehow fixed it.
class Entity;


class Settings {

private:

	int screenWidth;
	int screenHeight;

	std::vector<Entity*> entityList;

	//this list keeps track of all the entity's that will have to die this frame;
	std::vector<Entity*> toDieList;

	//this list keeps track of all the entity's that will have to be added to the main entitylist, but can't right now
	//the program is for example iterating over the entitylist
	std::vector<Entity*> toLiveList;

	bool vSync;

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

	void addEntity(Entity* entity) {
		entityList.push_back(entity);
	}

	std::vector<Entity*>* getEntities() {
		return &entityList;
	}

	bool getVSync() {
		return vSync;
	}

	void toggleVSync() {
		vSync = !vSync;
	}

	std::vector<Entity*>* getToDieList() {
		return &toDieList;
	}

	std::vector<Entity*>* getToAddList() {
		return &toLiveList;
	}

	void addEntityToDie(Entity* entity) {
		//check if the entity is already on the deathlist
		if (std::find(toDieList.begin(), toDieList.end(), entity) == toDieList.end()) {
			//if not on the list yet
			toDieList.push_back(entity);
		}
	}

	void addEntityToLive(Entity* entity) {
		//check if the entity is already on the toLiveList
		if (std::find(toLiveList.begin(), toLiveList.end(), entity) == toLiveList.end()) {
			//if not on the list yet
			toLiveList.push_back(entity);
		}
	}
};

