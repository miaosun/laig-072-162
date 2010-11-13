#include "Transformation.h"

using namespace std;


Transformation::Transformation(string type)
{
	this->type=type;
}

Rotation::Rotation(string axis, float angle):Transformation("rot")
{
	this->axis=axis;
	this->angle=angle;
}

Translation::Translation(float x, float y, float z):Transformation("trans")
{
	this->x=x;
	this->y=y;
	this->z=z;
}

Scale::Scale(float x, float y, float z):Transformation("scl")
{
	this->x=x;
	this->y=y;
	this->z=z;
}