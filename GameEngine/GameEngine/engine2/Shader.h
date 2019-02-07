#pragma once

#include "..//ogl/glm/glm.hpp"

#include <string>

class Shader
{
private:
	unsigned int programID;
public:
	Shader(const char* , const char*);
	void Use();
	
	void setFloat(const std::string &, const float &);
	void setVec3(const std::string &, const glm::vec3 &);
	void setMat4(const std::string &, const glm::mat4 &);

	unsigned int getProgramID();
};



