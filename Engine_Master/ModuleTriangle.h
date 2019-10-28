#pragma once
#include "Module.h"
#include "GL/glew.h"
#include "MathGeoLib/include/Math/float4x4.h"
#include "MathGeoLib/include/Math/float3.h"

class ModuleTriangle :
	public Module
{
public:
	ModuleTriangle();
	virtual ~ModuleTriangle();
	bool Init();
	float4x4 LookAt(float3 target, float3 eye, float3 up);
	update_status Update();

private:
	GLuint vbo;
};

