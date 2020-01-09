#include "GameObject.h"



GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

Component * GameObject::CreateComponent(ComponentType type)
{
	if (type == ComponentType::Transform) {
		//components.push_back(new ComponentTransform(this));
	}

	Component *newComponent;
	switch (type)
	{
	case ComponentType::Camera:
		//components.push_back(new Camera());
		break;

	case ComponentType::Material:
		//components.push_back(new Material());
		break;

	case ComponentType::Mesh:
		//components.push_back(new Mesh());
		break;
	default:
		return nullptr;
	}

	//newComponent->owner = this;
	components.push_back(newComponent);

	return newComponent;
}
