
#include "view.h"

View::View(double near, double far, double axisscale, string id)
{
	this->near = near;
	this->far = far;
	this->axisscale = axisscale;
	this->id = id;
}

void View::loadView(TiXmlElement *viewElement)
{
	if((viewElement->QueryFloatAttribute("near", &(this->near))) == TIXML_SUCCESS &&
		(viewElement->QueryFloatAttribute("far", &(this->far))) == TIXML_SUCCESS &&
		(viewElement->QueryFloatAttribute("axisscale", &(this->axisscale))) == TIXML_SUCCESS)
	{
		printf("Near: %f\n", this->near);
		printf("Far: %f\n", this->far);
		printf("axisScale: %f\n", this->axisscale);
	} else{
		printf("Erro parsing frustum\n");
	}
}