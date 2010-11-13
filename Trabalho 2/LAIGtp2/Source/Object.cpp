#include "Object.h"

using namespace std;

Object::Object(string id, string type, string mat, string tex, vector<Transformation *> transf)
{
	this->id=id;
	this->type=type;
	this->mat=mat;
	this->tex=tex;
	this->transf=transf;
	this->visited=false;
}

Compound::Compound(string id, string mat, string tex, vector<Transformation *> transf, vector<string> s_objs):
Object(id, "compound", mat, tex, transf)
{
	this->s_objs=s_objs;
}



Rectangle::Rectangle(string id, string mat, string tex, vector<Transformation *> transf, float x1, float y1, float x2, float y2):
Object(id, "rectangle", mat, tex, transf)
{
	this->x1=x1;
	this->x2=x2;
	this->y1=y1;
	this->y2=y2;
}

Triangle::Triangle(string id, string mat, string tex, vector<Transformation *> transf, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3):
Object(id, "triangle", mat, tex, transf)
{
	this->x1=x1;
	this->x2=x2;
	this->x3=x3;
	this->y1=y1;
	this->y2=y2;
	this->y3=y3;
	this->z1=z1;
	this->z2=z2;
	this->z3=z3;
}

Sphere::Sphere(string id, string mat, string tex, vector<Transformation *> transf, float r, int slices, int stacks):
Object(id, "sphere", mat, tex, transf)
{
	this->radius=r;
	this->slices=slices;
	this->stacks=stacks;
}

Cylinder::Cylinder(string id, string mat, string tex, vector<Transformation *> transf, float base, float top, float height, int slices, int stacks):
Object(id, "cylinder", mat, tex, transf)
{
	this->base=base;
	this->top=top;
	this->height=height;
	this->slices=slices;
	this->stacks=stacks;
}

Disk::Disk(string id, string mat, string tex, vector<Transformation *> transf, float inner, float outer, int slices, int loops):
Object(id, "disk", mat, tex, transf)
{
	this->inner=inner;
	this->outer=outer;
	this->slices=slices;
	this->loops=loops;
}