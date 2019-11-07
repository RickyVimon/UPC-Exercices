#pragma once
#include "Module.h"
#include "Libraries/MathGeoLib/include/Geometry/Frustum.h"
#include "GL/glew.h"
#include "Libraries/MathGeoLib/include/Math/float4x4.h"
#include "Libraries/MathGeoLib/include/Math/float3.h"


class ModuleCamera :
	public Module
{
public:
	ModuleCamera();
	virtual ~ModuleCamera();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	void ShowGrid();
	void ShowAxis();
	float4x4 LookAt(float3 eye, float3 target, float3 up);
	void SetFOV(float fov);

	void AdjustFOV();

	void Move(float3 movement);

public:
	bool flag_ground = false;
	bool flag_axis = false;
	Frustum frustum;
	float4x4 proj, view, model;
	float aspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
};

