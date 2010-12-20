
//#include <winsock2.h>
//#include <winsock.h>
//#include <windows.h>
//#include <stdlib.h>
#include <glui.h>
//#include <stdio.h>
#include <ctype.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <math.h>
#include <queue>

using namespace std;

// Apontadores para os principais grupos
// declarados aqui como globais por conveniência
// idealmente tudo seria incluido numa classe

class Excepcao{};
class Exit{};
class ExcepcaoSocket{};


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
		this->maxlights = 0;
		this->maxtextures = 0;
		this->maxmaterials = 0;
		this->maxobjects = 0;
		this->root = "";
	}
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

	float ambient[4];
	float backgroud[4];


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
	float shininess[1];

	Material(){};
	Material(string id)
	{
		this->id = id;
		this->shininess[0] = 0;
	}

	void apply()
	{
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, this->shininess);
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
