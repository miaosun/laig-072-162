#include <string>
#include <vector>
#include <glui.h>

using namespace std;

// Apontadores para os principais grupos
// declarados aqui como globais por conveniência
// idealmente tudo seria incluido numa classe

struct point {
	float x;
	float y;
	float z;
};


///////////////////
/////adcionado/////
///////////////////
class Global
{
public:
	int maxlights;
	int maxtextures;
	int maxmaterials;
	int maxobjects;
	string root;

	Global()
	{
		this->maxlights = maxlights;
		this->maxtextures = maxtextures;
		this->maxmaterials = maxmaterials;
		this->maxobjects = maxobjects;
		this->root = root;
	}
};

struct Ambient
{
	float r;
	float g;
	float b;
	float a;
};

struct Background
{
	float r;
	float g;
	float b;
	float a;
};

class Light
{
public:
	string id;
	bool enabled;
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float position[4];

	Light(string id, bool enabled)
	{
		this->id = id;
		this->enabled = enabled;
	}
};

class Illumination
{
public:
	bool doublesided;
	bool local;

	Ambient ambient;
	Background backgroud;


	Illumination(){};
	Illumination(bool doublesided, bool local)
	{
		this->doublesided = doublesided;
		this->local = local;
	}
};

class Material
{
public:
	string id;
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float emission[4];
	GLfloat shininess;

	Material(){};
	Material(string id)
	{
		this->id = id;
		this->shininess = 0;
	}

	void apply()
	{
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &this->shininess);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, this->specular);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, this->diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, this->ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, this->emission);
	}
};


class Texture
{
public:
	string id;
	string file;
	float length_s;
	float length_t;
	int n_texture;

	Texture(){};
	Texture(string id, string file, float length_s, float length_t)
	{
		this->id = id;
		this->file = file;
		this->length_s = length_s;
		this->length_t = length_t;
	}
};

