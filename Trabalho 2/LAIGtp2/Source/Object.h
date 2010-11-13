#include "Transformation.h"

using namespace std;

class Object
{
public:
	string id;
	string type;
	string mat;
	string tex;
	bool visited;
	vector<Transformation *> transf;
	Object(string id, string type, string mat, string tex, vector<Transformation *> transf);

	//funcoes
	virtual vector<Object *> getObjs()=0;
	virtual float getX1()=0;
	virtual float getX2()=0;
	virtual float getX3()=0;
	virtual float getY1()=0;
	virtual float getY2()=0;
	virtual float getY3()=0;
	virtual float getZ1()=0;
	virtual float getZ2()=0;
	virtual float getZ3()=0;
	virtual int getSlices()=0;
	virtual int getStacks()=0;
	virtual float getRadius()=0;
	virtual float getBase()=0;
	virtual float getTop()=0;
	virtual float getHeight()=0;
	virtual float getInner()=0;
	virtual float getOuter()=0;
};

class Compound:public Object
{
public:
	vector<Object *> objs;
	Compound(string id, string mat, string tex, vector<Transformation *> transf, vector<Object *> objs);

	//funcoes
	vector<Object *> getObjs(){return this->objs;};
};

class Rectangle:public Object
{
public:
	float x1, x2, y1, y2;
	Rectangle(string id, string mat, string tex, vector<Transformation *> transf, float x1, float y1, float x2, float y2);

	//funcoes
	float getX1(){return this->x1;};
	float getX2(){return this->x2;};
	float getY1(){return this->y1;};
	float getY2(){return this->y2;};
};

class Triangle:public Object
{
public:
	float x1, x2, x3, y1, y2, y3, z1, z2, z3;
	Triangle(string id, string mat, string tex, vector<Transformation *> transf, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3);

	//funcoes
	float getX1(){return this->x1;};
	float getX2(){return this->x2;};
	float getX3(){return this->x3;};
	float getY1(){return this->y1;};
	float getY2(){return this->y2;};
	float getY3(){return this->y3;};
	float getZ1(){return this->z1;};
	float getZ2(){return this->z2;};
	float getZ3(){return this->z3;};

};

class Sphere:public Object
{
public:
	float radius;
	int slices, stacks;
	Sphere(string id, string mat, string tex, vector<Transformation *> transf, float r, int slices, int stacks);

	//funcoes
	int getSlices(){return this->slices;};
	int getStacks(){return this->stacks;};
	float getRadius(){return this->radius;};
};

class Cylinder:public Object
{
public:
	float base, top, height;
	int slices, stacks;
	Cylinder(string id, string mat, string tex, vector<Transformation *> transf, float base, float top, float height, int slices, int stacks);

	//funcoes
	int getSlices(){return this->slices;};
	int getStacks(){return this->stacks;};
	float getBase(){return this->base;};
	float getTop(){return this->top;};
	float getHeight(){return this->height;};
};

class Disk:public Object
{
public:
	float inner, outer;
	int slices, loops;
	Disk(string id, string mat, string tex, vector<Transformation *> transf, float inner, float outer, int slices, int loops);

	//funcoes
	int getSlices(){return this->slices;};
	int getStacks(){return this->loops;};
	float getInner(){return this->inner;};
	float getOuter(){return this->outer;};
};