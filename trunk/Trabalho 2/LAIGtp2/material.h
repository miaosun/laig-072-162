#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "tinyxml.h"
#include <GL\glui.h>
#include <string>

class Material
{
	std::string id;
	float ambiente[4];
	float diffuse[4];
	float specular[4];
	float emission[4];
	float shininess[1];
public:
	std::string getId();
	Material* loadAttributes(TiXmlElement *materialsElement);
}

#endif