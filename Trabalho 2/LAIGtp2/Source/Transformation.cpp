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

void Rotation::apply()
{
	if(this->axis=="x")
		glRotated(this->angle, 1.0, 0.0, 0.0);
	else if(this->axis=="y")
		glRotated(this->angle, 0.0, 1.0, 0.0);
	else if(this->axis=="z")
		glRotated(this->angle, 0.0, 0.0, 1.0);
	else
	{
		cout<<"erro na rotacao: eixo errado\n";
		system("pause");
	}
}

Translation::Translation(float x, float y, float z):Transformation("trans")
{
	this->x=x;
	this->y=y;
	this->z=z;
}

void Translation::apply()
{
	glTranslated(this->x, this->y, this->z);
}

Scale::Scale(float x, float y, float z):Transformation("scl")
{
	this->x=x;
	this->y=y;
	this->z=z;
}

void Scale::apply()
{
	glScaled(this->x, this->y, this->z);
}