#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include<vector>


class ObjectManager
{
	bool marked;
	static std::vector<ObjectManager*> items;
public:
	ObjectManager(bool marked);
	virtual ~ObjectManager();
	void setMarked();
	void setUnMarked();
	static void clearUnmarkedObjects();
	static void clearAllObjects();
};

#endif // !OBJECTMANAGER_H
