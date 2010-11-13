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
	virtual vector<Object *> * getObjs()=0;
	virtual vector<string> * getSObjs()=0;
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
	vector<string> s_objs;
	Compound(string id, string mat, string tex, vector<Transformation *> transf, vector<string> s_objs);

	//funcoes
	vector<Object *> * getObjs(){return &this->objs;};
	vector<string> * getSObjs(){return &this->s_objs;};
	float getX1(){return NULL;};
	float getX2(){return NULL;};
	float getX3(){return NULL;};
	float getY1(){return NULL;};
	float getY2(){return NULL;};
	float getY3(){return NULL;};
	float getZ1(){return NULL;};
	float getZ2(){return NULL;};
	float getZ3(){return NULL;};
	int getSlices(){return NULL;};
	int getStacks(){return NULL;};
	float getRadius(){return NULL;};
	float getBase(){return NULL;};
	float getTop(){return NULL;};
	float getHeight(){return NULL;};
	float getInner(){return NULL;};
	float getOuter(){return NULL;};
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
	float getX3(){return NULL;};
	float getY3(){return NULL;};
	float getZ1(){return NULL;};
	float getZ2(){return NULL;};
	float getZ3(){return NULL;};
	int getSlices(){return NULL;};
	int getStacks(){return NULL;};
	float getRadius(){return NULL;};
	float getBase(){return NULL;};
	float getTop(){return NULL;};
	float getHeight(){return NULL;};
	float getInner(){return NULL;};
	float getOuter(){return NULL;};
	vector<Object *> * getObjs(){return NULL;};
	vector<string> * getSObjs(){return NULL;};
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
	int getSlices(){return NULL;};
	int getStacks(){return NULL;};
	float getRadius(){return NULL;};
	float getBase(){return NULL;};
	float getTop(){return NULL;};
	float getHeight(){return NULL;};
	float getInner(){return NULL;};
	float getOuter(){return NULL;};
	vector<Object *> * getObjs(){return NULL;};
	vector<string> * getSObjs(){return NULL;};
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
	float getX1(){return NULL;};
	float getX2(){return NULL;};
	float getX3(){return NULL;};
	float getY1(){return NULL;};
	float getY2(){return NULL;};
	float getY3(){return NULL;};
	float getZ1(){return NULL;};
	float getZ2(){return NULL;};
	float getZ3(){return NULL;};
	float getBase(){return NULL;};
	float getTop(){return NULL;};
	float getHeight(){return NULL;};
	float getInner(){return NULL;};
	float getOuter(){return NULL;};
	vector<Object *> * getObjs(){return NULL;};
	vector<string> * getSObjs(){return NULL;};
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
	float getX1(){return NULL;};
	float getX2(){return NULL;};
	float getX3(){return NULL;};
	float getY1(){return NULL;};
	float getY2(){return NULL;};
	float getY3(){return NULL;};
	float getZ1(){return NULL;};
	float getZ2(){return NULL;};
	float getZ3(){return NULL;};
	float getInner(){return NULL;};
	float getOuter(){return NULL;};
	vector<Object *> * getObjs(){return NULL;};
	vector<string> * getSObjs(){return NULL;};
	float getRadius(){return NULL;};
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
	float getX1(){return NULL;};
	float getX2(){return NULL;};
	float getX3(){return NULL;};
	float getY1(){return NULL;};
	float getY2(){return NULL;};
	float getY3(){return NULL;};
	float getZ1(){return NULL;};
	float getZ2(){return NULL;};
	float getZ3(){return NULL;};
	float getBase(){return NULL;};
	float getTop(){return NULL;};
	float getHeight(){return NULL;};
	vector<Object *> * getObjs(){return NULL;};
	vector<string> * getSObjs(){return NULL;};
	float getRadius(){return NULL;};
};