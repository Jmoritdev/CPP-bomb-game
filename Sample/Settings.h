#pragma once


#include <vector>
#include <iostream>


class Entity;


class Settings {

private:

	int screenWidth;
	int screenHeight;

	std::vector<Entity*> entityList;

	//this list keeps track of all the entity's that will have to die this frame;
	std::vector<Entity*> toDieList;

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

	void addEntityToDie(Entity* entity) {
		toDieList.push_back(entity);
	}

	//void removeEntity(Entity* entity) {
	//	std::cout << "removing entity";

	//	for (iterator = entityList.begin(); iterator != entityList.end(); ++iterator) {
	//		
	//	}

	//	iterator = entityList.begin();
	//}

};

