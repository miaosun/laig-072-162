#ifndef LIGHT_H_
#define LIGHT_H_

#include "tinyxml.h"
#include <string>
using namespace std;

class Light
{
public:
	string id;
	int enabled;
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float position[4];
	TiXmlElement* lightElement;
	void loadLight();
}


#endif