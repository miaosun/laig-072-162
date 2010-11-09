
#include "tinyxml.h"

#include <string>
using namespace std;

class View
{
	float near;
	float far;
	float axisscale;
	string id;
public:
	
	View(double near, double far, double axisscale, string id);
	void loadView(TiXmlElement *viewElement);

}