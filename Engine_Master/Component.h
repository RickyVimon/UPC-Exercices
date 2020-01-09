#ifndef __COMPONENT__
#define __COMPONENT__

enum ComponentType
{
	Transform = 0,
	Mesh,
	Material,
	Camera
};

class GameObject;

class Component
{

public:
	Component() {};
	virtual ~Component() = default;
	virtual void Enable() { active = true; };
	virtual void Update() {};
	virtual void Disable() { active = false; };

public:
	ComponentType type;
	bool active;
	GameObject* myGameObject = nullptr; //IMPORTANT, THIS POINTER MUST BE SYNC WITH PARENTS CHILDREN, BE CAREFUL

};

#endif //__COMPONENT__