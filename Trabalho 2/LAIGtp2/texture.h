#ifndef TEXTURE_H_
#define TEXTURE_H_


#include "tinyxml.h"

#include <string>
using namespace std;

class Texture
{
	string id;
	string file;
	float length_s;
	float length_t;

public:
	TiXmlElement* textsElement;
	void loadTexture();
}

#endif