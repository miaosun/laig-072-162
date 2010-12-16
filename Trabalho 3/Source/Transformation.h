#include "globals.h"

using namespace std;

class Transformation
{
	string type;
public:
	Transformation(string type);
	virtual float getX()=0;
	virtual float getY()=0;
	virtual float getZ()=0;
	virtual float getAngle()=0;
	virtual string getAxis()=0;
	virtual void apply()=0;
};

class Translation:public Transformation
{
	float x;
	float y;
	float z;
public:
	Translation(float x, float y, float z);
	float getX() {return this->x;};
	float getY() {return this->y;};
	float getZ() {return this->z;};
	float getAngle() {return 0.0;};
	string getAxis() {return "";};
	void apply();
};

class Rotation:public Transformation
{
public:
	string axis;
	float angle;
	Rotation(string axis, float angle);
	float getX() {return 0.0;};
	float getY() {return 0.0;};
	float getZ() {return 0.0;};
	float getAngle() {return this->angle;};
	string getAxis() {return this->axis;};
	void apply();
};

class Scale:public Transformation
{
	float x;
	float y;
	float z;
public:
	Scale(float x, float y, float z);
	float getX() {return this->x;};
	float getY() {return this->y;};
	float getZ() {return this->z;};
	float getAngle() {return 0.0;};
	string getAxis() {return "";};
	void apply();
};