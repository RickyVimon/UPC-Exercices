#ifndef _COMPONENTMATERIAL_H_
#define _COMPONENTMATERIAL_H_
#include "Mesh.h"
#include "MathGeoLib/include/Math/float4.h"

enum texture_type{
	diffuse,
	specular,
	normal,
	height
};

class ComponentMaterial
{
public:
	ComponentMaterial();
	~ComponentMaterial();

	std::vector<Texture*> textures;
	std::vector<float> alpha;
	std::vector<float4> color;

};

#endif //_COMPONENTMATERIAL_H_

