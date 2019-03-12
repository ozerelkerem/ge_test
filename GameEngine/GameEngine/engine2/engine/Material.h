#pragma once
#include <engine/Texture.h>
#include <limits>
#include <glm/glm.hpp>

#include <string>

#include <Api.h>

using MaterialID = uint16_t;


class Material
{
public:
	Material(std::string);
	~Material();

	static const MaterialID INVALID_MATERIAL_ID = std::numeric_limits<MaterialID>::max();

	std::string name;

	glm::vec3 ambientColor;
	Texture *ambientTexture;
	//Texture *normalTexture;

	void active();

	inline static void noMaterial() { 
		normalShader->setInt("material.hasTexture", 0);
		normalShader->setVec3("material.ambientColor", glm::vec3(1,0,1));
	}
};

