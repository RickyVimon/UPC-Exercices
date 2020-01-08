#ifndef __MODULESCENE_H__
#define __MODULESCENE_H__

#include "Module.h"
#include "GameObject.h"
#include <vector>

class ModuleScene :
	public Module
{
public:
	ModuleScene();
	void LoadDefaultScene(const char * path);
	virtual ~ModuleScene();

private:
	GameObject* CreateGameObject(const char * name);
	std::vector<GameObject*> game_objects;
};

#endif //__MODULESCENE__
