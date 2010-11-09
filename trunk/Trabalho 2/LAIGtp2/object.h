#ifndef OBJECT_H_
#define OBJECT_H_

#include "tinyxml.h"

#include <string>
using namespace std;

class Object
{
	string id;
	string type;

public:

	void loadObject(TiXmlElement* objectElement);
}

#endif
