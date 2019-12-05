#ifndef _MESH_H_
#define _MESH_H_	
#include "Globals.h"
#include "Module.h"
#include <string>
#include <vector>
#include "MathGeoLib/include/Math/float3.h"
#include "MathGeoLib/include/Math/float2.h"

struct Texture {
	unsigned int id;
	char*  type;
	const char* name;
	int width;
	int height;
	unsigned char *data;
};

struct Vertex 
{
	float3 Position;
	float3 Normal;
	float2 TexCoords;
	float3 Tangent;
	float3 Bitangent;
};

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures);
	~Mesh();
	void Init();
	void Draw(unsigned int program) const;

private:
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};

#endif __Mesh_H__