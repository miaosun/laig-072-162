#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "..\tinyxml.h"
#include <GL\glui.h>
#include <string>

using namespace std;

class Material
{
public:
	string id;
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float emission[4];
	float shininess[1];

	void loadMaterial(TiXmlElement *materialsElement);
}

#endif