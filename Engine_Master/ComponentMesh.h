#pragma once
#include "Component.h"
class ComponentMesh :
	public Component
{
public:
	ComponentMesh();
	~ComponentMesh();
	void Enable();
	void Disable();
	void Update();
};

