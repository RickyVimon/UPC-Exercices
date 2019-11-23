#pragma once
#include "Module.h"
#include "Libraries/MathGeoLib/include/Geometry/Frustum.h"
#include "GL/glew.h"
#include "Libraries/MathGeoLib/include/Math/float4x4.h"
#include "Libraries/MathGeoLib/include/Math/float3.h"

enum Axis {
	X,
	Y,
	Z
};

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
	void Move(Axis axis, float movement);
	void ZoomIn();
	void ZoomOut();
	void Rotate(Axis axis, float movement);
	void Orbit(Axis axis, float angle);
	bool Boost();
	void SetAspect();

	void FocusAt(const float3 target);

	void BackToZero();

public:
	float mov_speed = 0.1f;
	float rot_speed = 0.015f;
	float zoom_speed = 2;
	bool flag_ground = true;
	bool flag_axis = true;
	Frustum frustum;
	float4x4 proj, view, model;
	float3x3 rotation_matrix;
	float aspect;
	float3 initial_position = { -10, 5, -10 };
};

