#ifndef __GAMEOBJECT__
#define __GAMEOBJECT__

class GameObject
{
public:
	GameObject();
	GameObject(const char* name);
	virtual ~GameObject();

private:
	//Component* CreateComponent(ComponentType);
};

#endif //__GAMEOBJECT__


