#pragma once
#include "Component.h"
class ComponentMaterial :
	public Component
{
public:
	ComponentMaterial();
	~ComponentMaterial();
	void Enable();
	void Disable();
	void Update();
};

