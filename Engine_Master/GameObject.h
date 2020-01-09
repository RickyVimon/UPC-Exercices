#ifndef __GAMEOBJECT__
#define __GAMEOBJECT__

#include "Component.h"
#include <vector>

class GameObject
{
public:
	GameObject();
	GameObject(const char* name) : name(name) {
		CreateComponent(ComponentType::Transform);
	}
	virtual ~GameObject();

public:
	const char* name;
	GameObject* parent = nullptr;

private:
	Component* CreateComponent(ComponentType type);
	std::vector<Component*> components;

};

#endif //__GAMEOBJECT__


