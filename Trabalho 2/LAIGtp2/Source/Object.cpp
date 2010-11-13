#include "Object.h"

Object::Object(string id, string type, string mat_id, string tex_id, vector<Transformation *> transf)
{
	this->id=id;
	this->type=type;
	this->mat_id=mat_id;
	this->tex_id=tex_id;
	this->transf=transf;
	this->visited=false;
}


Compound::Compound(string id, string mat_id, string tex_id, vector<Transformation *> transf, vector<string> s_objs):
Object(id, "compound", mat_id, tex_id, transf)
{
	this->s_objs=s_objs;
}

void Compound::draw(){};


Rectangle::Rectangle(string id, string mat_id, string tex_id, vector<Transformation *> transf, float x1, float y1, float x2, float y2):
Object(id, "rectangle", mat_id, tex_id, transf)
{
	this->x1=x1;
	this->x2=x2;
	this->y1=y1;
	this->y2=y2;
}

Triangle::Triangle(string id, string mat_id, string tex_id, vector<Transformation *> transf, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3):
Object(id, "triangle", mat_id, tex_id, transf)
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

Sphere::Sphere(string id, string mat_id, string tex_id, vector<Transformation *> transf, float r, int slices, int stacks):
Object(id, "sphere", mat_id, tex_id, transf)
{
	this->radius=r;
	this->slices=slices;
	this->stacks=stacks;
}

Cylinder::Cylinder(string id, string mat_id, string tex_id, vector<Transformation *> transf, float base, float top, float height, int slices, int stacks):
Object(id, "cylinder", mat_id, tex_id, transf)
{
	this->base=base;
	this->top=top;
	this->height=height;
	this->slices=slices;
	this->stacks=stacks;
}

Disk::Disk(string id, string mat_id, string tex_id, vector<Transformation *> transf, float inner, float outer, int slices, int loops):
Object(id, "disk", mat_id, tex_id, transf)
{
	this->inner=inner;
	this->outer=outer;
	this->slices=slices;
	this->loops=loops;
}



void Rectangle::draw()
{
	/////////falta material e textura
	
	if(this->tex != NULL && this->tex_id != "clear")
	{
		glEnable(GL_TEXTURE_2D);
	//	glBindTexture(GL_TEXTURE_2D, //Gluint);
	}

	if(this->mat != NULL && this->mat_id != "null")
	{

	}
	

	
	if(this->y2 > this->y1 && this->x2 > this->x1)
	{
		glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,1.0);
		glTexCoord2f(0.0,0.0); glVertex3d(this->x1, this->y1,  0.0);
		glTexCoord2f((this->x2-this->x1)/tex->length_s,0.0); glVertex3d(this->x2, this->y1,  0.0);
		glTexCoord2f((this->x2-this->x1)/tex->length_s,(this->y2-this->y1)/tex->length_t); glVertex3d(this->x2, this->y2,  0.0);
		glTexCoord2f(0.0,(this->y2-this->y1)/tex->length_t); glVertex3d(this->x1, this->y2,  0.0);
		glEnd();
	}
	else
	{
		cout<<"y2 tem que ser maior que y1, e x2 maior x1\n";
	}
	
}

void Triangle::draw()
{

}

void Sphere::draw()
{
	GLUquadric* glQ;
	glQ = gluNewQuadric();

	if(this->tex != NULL && this->tex->id != "clear")
	{
		gluQuadricTexture(glQ, GL_TRUE);
		glEnable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D, //Gluint);
	}
	if(this->mat != NULL && this->mat->id != "null")
	{

	}

	glPushMatrix();
	////////////matrix d transformacao
	gluSphere(glQ, this->radius, this->slices, this->stacks);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluQuadricTexture(glQ, GL_FALSE);
}

void Cylinder::draw()
{
	GLUquadric* glQ;
	glQ = gluNewQuadric();

	if(this->tex != NULL && this->tex->id != "clear")
	{
		gluQuadricTexture(glQ, GL_TRUE);
		glEnable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D, //Gluint);
	}
	if(this->mat != NULL && this->mat->id != "null")
	{

	}

	glPushMatrix();
	////////////matrix d transformacao
	gluCylinder(glQ, this->base, this->top, this->height, this->slices, this->stacks);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	gluQuadricTexture(glQ, GL_FALSE);
}

void Disk::draw()
{

}