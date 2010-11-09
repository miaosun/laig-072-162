#ifndef ILLUMINATION_H_
#define ILLUMINATION_H_

#include "tinyxml.h"
#include <string>
using namespace std;

class Illumination
{
	string id;
	double doublesided;
	double local;

public:
	void loadIllumination(TiXmlElement* illumElement);
}

#endif