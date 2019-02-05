#include "objectManager.h"

std::vector<ObjectManager*> ObjectManager::items = std::vector<ObjectManager*>();


ObjectManager::ObjectManager(bool marked) {
	this->marked = marked;
	this->items.push_back(this);
}

ObjectManager::~ObjectManager() {
}

void ObjectManager::setMarked() {
	this->marked = true;
}

void ObjectManager::setUnMarked() {
	this->marked = false;
}

void ObjectManager::clearUnmarkedObjects() {
	ObjectManager* tmp = NULL;

	for (size_t i = 1; i < items.size() + 1; i++) {
		tmp = items[i - 1];
		if (tmp->marked == false) {
			items.erase(items.begin() + i - 1);
			--i;
			delete tmp;
		}
	}
}

void ObjectManager::clearAllObjects() {
	ObjectManager* tmp = NULL;

	while (items.size()) {
		tmp = items.back();
		items.pop_back();
		delete tmp;
	}
}
