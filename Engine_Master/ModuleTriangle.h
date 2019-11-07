#pragma once
#include "Module.h"
#include "GL/glew.h"
#include "Libraries/MathGeoLib/include/Math/float4x4.h"
#include "Libraries/MathGeoLib/include/Math/float3.h"
#include "Libraries/MathGeoLib/include/Geometry/Frustum.h"

class ModuleTriangle :
	public Module
{
public:
	ModuleTriangle();
	virtual ~ModuleTriangle();
	bool Init();
	update_status Update();

private:
	GLuint vbo;
};

