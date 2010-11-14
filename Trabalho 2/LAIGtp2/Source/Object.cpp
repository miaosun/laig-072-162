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
	if(!transf.empty())
	{
		for(unsigned int i=0; i<this->transf.size(); i++)
			this->transf.at(i)->apply();
	}
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
		//cout<<"vai ser "<<objs.at(i)->type<<" "<<objs.at(i)->id<<endl;
		objs.at(i)->draw();
		//system("pause");
	}
	glPopMatrix();
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

	cout<<"  draw rectangle "<<this->id<<endl;
	glPushMatrix();
	aplicaTransformacoes();
	if((this->y2 > this->y1) && (this->x2 > this->x1))
	{
		glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,1.0);
			glTexCoord2f(0.0,0.0); glVertex3d(this->x1, this->y1, 0.0);
			glTexCoord2f((this->x2-this->x1)/tex->length_s,0.0); glVertex3d(this->x2, this->y1, 0.0);
			glTexCoord2f((this->x2-this->x1)/tex->length_s,(this->y2-this->y1)/tex->length_t); glVertex3d(this->x2, this->y2, 0.0);
			glTexCoord2f(0.0,(this->y2-this->y1)/tex->length_t); glVertex3d(this->x1, this->y2, 0.0);
		glEnd();
	}
	else if((this->y1 > this->y2) && (this->x1 > this-> x2))
	{
		glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,1.0);
			glTexCoord2f(0.0,0.0); glVertex3d(this->x2, this->y2, 0.0);
			glTexCoord2f((this->x1-this->x2)/tex->length_s,0.0); glVertex3d(this->x1, this->y2, 0.0);
			glTexCoord2f((this->x1-this->x2)/tex->length_s,(this->y1-this->y2)/tex->length_t); glVertex3d(this->x1, this->y1, 0.0);
			glTexCoord2f(0.0,(this->y1-this->y2)/tex->length_t); glVertex3d(this->x2, this->y1, 0.0);
		glEnd();
	}
	else if((this->y2 > this->y1) && (this->x1 > this-> x2))
	{
		glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,1.0);
			glTexCoord2f(0.0,0.0); glVertex3d(this->x2, this->y1, 0.0);
			glTexCoord2f((this->x1-this->x2)/tex->length_s,0.0); glVertex3d(this->x1, this->y1, 0.0);
			glTexCoord2f((this->x1-this->x2)/tex->length_s,(this->y2-this->y1)/tex->length_t); glVertex3d(this->x1, this->y2, 0.0);
			glTexCoord2f(0.0,(this->y2-this->y1)/tex->length_t); glVertex3d(this->x2, this->y2, 0.0);
		glEnd();
	}
	else if(this->y1 > this->y2 && this->x2 > this->x1)
	{
		glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,1.0);
			glTexCoord2f(0.0,0.0); glVertex3d(this->x1, this->y2,  0.0);
			glTexCoord2f((this->x2-this->x1)/tex->length_s,0.0); glVertex3d(this->x2, this->y2,  0.0);
			glTexCoord2f((this->x2-this->x1)/tex->length_s,(this->y1-this->y2)/tex->length_t); glVertex3d(this->x2, this->y1,  0.0);
			glTexCoord2f(0.0,(this->y1-this->y2)/tex->length_t); glVertex3d(this->x1, this->y1,  0.0);
		glEnd();
	}
	else
	{
		cout<<"erro RECTANGLE os pontos tem que ser opostos\n";
		system("pause");
	}
	glPopMatrix();
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
	cout<<"  draw triangle "<<this->id<<endl;
	glPushMatrix();
	aplicaTransformacoes();
		glBegin(GL_POLYGON);
		glNormal3d(this->n1,this->n2,this->n3);
			glVertex3d(this->x1, this->y1, this->z1);
			glVertex3d(this->x2, this->y2, this->z2);
			glVertex3d(this->x3, this->y3, this->z3);
		glEnd();
	glPopMatrix();
}

void Triangle::calcNorm()
{
	float a[3], b[3], nx, ny, nz, mod;
	
	a[0] = x3 - x1;
	a[1] = y3 - y1;
	a[2] = z3 - z1;

	b[0] = x2 - x1;
	b[1] = y2 - y1;
	b[2] = z2 - z1;

	nx = a[1]*b[2] - a[2]*b[1];
	ny = a[2]*b[0] - a[0]*b[2];
	nz = a[0]*b[1] - a[1]*b[0];

	mod = sqrt(nx*nx + ny*ny + nz*nz);

	if(mod != 0.0)
	{
		this->n1 = nx / mod;
		this->n2 = ny / mod;
		this->n3 = nz / mod;
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
	cout<<"  draw sphere "<<this->id<<endl;
	glPushMatrix();
	aplicaTransformacoes();
		gluSphere(glQ, this->radius, this->slices, this->stacks);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	gluQuadricTexture(glQ, GL_FALSE);
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
	cout<<"  draw cylinder "<<this->id<<endl;
	glPushMatrix();
	aplicaTransformacoes();
		gluCylinder(glQ, this->base, this->top, this->height, this->slices, this->stacks);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	gluQuadricTexture(glQ, GL_FALSE);
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
	cout<<"  draw disk "<<this->id<<endl;
	glPushMatrix();
	aplicaTransformacoes();
		gluDisk(glQ, this->inner, this->outer, this->slices, this->loops);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	gluQuadricTexture(glQ, GL_FALSE);
}