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

void Object::aplicaTransformacoes()
{
	for(unsigned int i=0; i<this->transf.size(); i++)
		this->transf.at(i)->apply();
}

Compound::Compound(string id, string mat_id, string tex_id, vector<Transformation *> transf, vector<string> s_objs):
Object(id, "compound", mat_id, tex_id, transf)
{
	this->s_objs=s_objs;
}

void Compound::draw()
{
	cout<<"vai desenhar compoud "<<this->id<<endl;
	glPushMatrix();
	aplicaTransformacoes();
	for(unsigned int i=0; i<this->objs.size(); i++)
	{
		if(!objs.at(i)->visited)
			objs.at(i)->draw();
	}
	glPopMatrix;
	this->visited=true;
}

Rectangle::Rectangle(string id, string mat_id, string tex_id, vector<Transformation *> transf, float x1, float y1, float x2, float y2):
Object(id, "rectangle", mat_id, tex_id, transf)
{
	this->x1=x1;
	this->x2=x2;
	this->y1=y1;
	this->y2=y2;
}

void Rectangle::draw()
{	
	if(this->tex->id!="NO_TEXTURE")
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, this->tex->n_texture);
	}

	if(this->mat!=NULL)
		mat->apply();
	
	if((this->y2 > this->y1) && (this->x2 > this->x1))
	{
		glPushMatrix();
		aplicaTransformacoes();
		glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,1.0);
			glTexCoord2f(0.0,0.0); glVertex3d(this->x1, this->y1,  0.0);
			glTexCoord2f((this->x2-this->x1)/tex->length_s,0.0); glVertex3d(this->x2, this->y1,  0.0);
			glTexCoord2f((this->x2-this->x1)/tex->length_s,(this->y2-this->y1)/tex->length_t); glVertex3d(this->x2, this->y2,  0.0);
			glTexCoord2f(0.0,(this->y2-this->y1)/tex->length_t); glVertex3d(this->x1, this->y2,  0.0);
		glEnd();
		glPopMatrix();
		cout<<"\tdesenhou rectangulo\n";
	}
	else if(y2<y1&&x2>x1)
	{
		glPushMatrix();
		aplicaTransformacoes();
		glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,1.0);
			glTexCoord2f(0.0,0.0); glVertex3d(this->x1, this->y1,  0.0);
			glTexCoord2f((this->x2-this->x1)/tex->length_s,0.0); glVertex3d(this->x1, this->y2,  0.0);
			glTexCoord2f((this->x2-this->x1)/tex->length_s,(this->y2-this->y1)/tex->length_t); glVertex3d(this->x2, this->y2,  0.0);
			glTexCoord2f(0.0,(this->y2-this->y1)/tex->length_t); glVertex3d(this->x2, this->y1,  0.0);
		glEnd();
		glPopMatrix();
		cout<<"\tdesenhou rectangulo\n";
	}
	else
	{
		cout<<"erro RECTANGLE os pontos tem que ser opostos\n";
		system("pause");
	}
	this->visited=true;
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

void Triangle::draw()
{

	//nao tem textura, para j?
	if(this->mat!=NULL)
		mat->apply();
	calcNorm();
	glPushMatrix();
	aplicaTransformacoes();
	glBegin(GL_POLYGON);
	glNormal3d(n1,n2,n3);
		glVertex3d(this->x1, this->y1, this->z1);
		glVertex3d(this->x2, this->y2, this->z2);
		glVertex3d(this->x3, this->y3, this->z3);
	glEnd();
	glPopMatrix();
	cout<<"\tdesenhou triangulo\n";
	this->visited=true;
}

void Triangle::calcNorm()
{
	float n[3];
	n[0] = this->y1*this->z2 - this->z1*this->y2;
	n[1] = this->z1*this->x2 - this->x1*this->z2;
	n[2] = this->x1*this->y2 - this->y1*this->x2;

	float mod = sqrt(n[0]*n[0] + n[1]*n[1] + n[2]*n[2]);

	if(mod != 0.0)
	{
		this->n1 = n[0] / mod;
		this->n2 = n[1] / mod;
		this->n3 = n[2] / mod;
	}
	else
		cout<<"erro ao calcular normal\n";
}

Sphere::Sphere(string id, string mat_id, string tex_id, vector<Transformation *> transf, float r, int slices, int stacks):
Object(id, "sphere", mat_id, tex_id, transf)
{
	this->radius=r;
	this->slices=slices;
	this->stacks=stacks;
}

void Sphere::draw()
{
	GLUquadric* glQ;
	glQ = gluNewQuadric();

	if(this->tex->id!="NO_TEXTURE")
	{
		gluQuadricTexture(glQ, GL_TRUE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, this->tex->n_texture);
	}
	if(this->mat!=NULL)
		mat->apply();

	glPushMatrix();
	aplicaTransformacoes();
	gluSphere(glQ, this->radius, this->slices, this->stacks);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluQuadricTexture(glQ, GL_FALSE);
	cout<<"\tdesenhou esfera\n";
	this->visited=true;
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

void Cylinder::draw()
{
	GLUquadric* glQ;
	glQ = gluNewQuadric();

	if(this->tex->id!="NO_TEXTURE")
	{
		gluQuadricTexture(glQ, GL_TRUE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, this->tex->n_texture);
	}
	if(this->mat!=NULL)
		mat->apply();

	glPushMatrix();
	aplicaTransformacoes();
	gluCylinder(glQ, this->base, this->top, this->height, this->slices, this->stacks);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	gluQuadricTexture(glQ, GL_FALSE);
	cout<<"\tdesenhou cilindro\n";
	this->visited=true;
}

Disk::Disk(string id, string mat_id, string tex_id, vector<Transformation *> transf, float inner, float outer, int slices, int loops):
Object(id, "disk", mat_id, tex_id, transf)
{
	this->inner=inner;
	this->outer=outer;
	this->slices=slices;
	this->loops=loops;
}

void Disk::draw()
{
	GLUquadric* glQ;
	glQ = gluNewQuadric();

	if(this->tex->id!="NO_TEXTURE")
	{
		gluQuadricTexture(glQ, GL_TRUE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, this->tex->n_texture);
	}
	if(this->mat!=NULL)
		mat->apply();

	glPushMatrix();
	aplicaTransformacoes();
	gluDisk(glQ, this->inner, this->outer, this->slices, this->loops);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	gluQuadricTexture(glQ, GL_FALSE);
	cout<<"\tdesenhou disco\n";
	this->visited=true;
}