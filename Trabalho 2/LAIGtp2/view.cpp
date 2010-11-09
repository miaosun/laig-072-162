#ifndef VIEW_H_
#define VIEW_H_

#include "view.h"

View::View(double near, double far, double axisscale, string id)
{
	this->near = near;
	this->far = far;
	this->axisscale = axisscale;
	this->id = id;
}

#endif