#pragma once
#include "Component.h"
#include "Component.h"
#include "MathGeoLib/include/MathGeoLib.h"
#include "assimp/matrix4x4.h"

class ComponentTransform :
	public Component
{
public:
	float3 scaling = float3::zero;
	float3 position = float3::zero;
	Quat rotation = Quat::identity;
	float4x4 localTransform = float4x4::identity;
	float4x4 worldTransform = float4x4::identity;

public:
	ComponentTransform() {}
	//ComponentTransform(GameObject* myGameObject) : ComponentTransform(myGameObject, ComponentType::Transform) { }
	virtual ~ComponentTransform() {}
public:
	void DrawView();
	void CalculateWorldTransform(const float4x4&);
	void SetTransform(const aiMatrix4x4&);
};


