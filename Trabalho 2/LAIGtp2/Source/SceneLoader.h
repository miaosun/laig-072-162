#ifndef SCENE_LOADER
#define SCENE_LOADER

#include "../tinyxml.h"
#include <map>
#include <string>
#include <vector>

using namespace std;

// Apontadores para os principais grupos
// declarados aqui como globais por conveniência
// idealmente tudo seria incluído numa classe

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

struct Translation
{
	float x;
	float y;
	float z;
};

struct Rotation
{
	string axis;
	float angle;
};

struct Scale
{
	float x;
	float y;
	float z;
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
	int enabled;
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float position[4];

	Light(string id, int enabled)
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

	vector<Light *> lights;

	Illumination(){};
	Illumination(double doublesided, double local)
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

	Material(string id)
	{
		this->id = id;
	}
};


class Texture
{
public:
	string id;
	string file;
	float length_s;
	float length_t;

	Texture(string id, string file, float length_s, float length_t)
	{
		this->id = id;
		this->file = file;
		this->length_s = length_s;
		this->length_t = length_t;
	}
};

class Object
{
public:
	string id;
	string type;

	Object(string id, string type)
	{
		this->id = id;
		this->type = type;
	}
};



class View
{
public:
	string id;
	float near;
	float far;
	float axisscale;
	//transformacoes
	Translation trans;
	Rotation rots[3];
	Scale scl;


	View(){};
	View(string id, float near, float far, float axisscalse)
	{
		this->id = id;
		this->near = near;
		this->far = far;
		this->axisscale = axisscale;
	}
};
///////////////////////////////////


class SceneLoader {

public:
	map<string, point> pointsMap;
	map<string, vector<string>> polygonsMap;

	////////////adiconado
	vector<Material *> materiais;
	vector<Texture *> textures;
	vector<Light *> lights;

	Global global;
	View view;
	Illumination illumination;

	SceneLoader()
	{
		sgxElement = NULL;
		globalsElement = NULL;
		viewElement = NULL;
		illuminationElement = NULL;

		ambientElement = NULL;
		backgroundElement = NULL;

		objectsElement = NULL;
		lightsElement = NULL;
		materialsElement = NULL;
		texturesElement = NULL;
		pointsElement = NULL;
		polygonsElement = NULL;


	}


	////////////////

	SceneLoader(const char * fileName);
	bool loadScene();

private:
  
	//////////////////
	TiXmlElement* sgxElement;
	TiXmlElement* globalsElement;
	TiXmlElement* viewElement;
	TiXmlElement* illuminationElement;

	TiXmlElement* ambientElement;
	TiXmlElement* backgroundElement;

	TiXmlElement* objectsElement;
	TiXmlElement* objectElement;
	TiXmlElement* lightsElement;
	TiXmlElement* materialsElement;
	TiXmlElement* texturesElement;
	TiXmlElement* pointsElement;
	//transformacoes
	TiXmlElement* translationElement;
	TiXmlElement* rotationElement;
	TiXmlElement* scaleElement;




	//////////////////


	TiXmlElement* polygonsElement;
	TiXmlElement *root;
	TiXmlDocument doc;

	void loadPoints();
	void loadPolygons();


	////////adicionado
	void loadSgx();
	bool loadGlobals();
	bool loadView();
	bool loadIllumination();
	void loadLight();
	void loadMaterial();
	void loadTexture();
	void loadGeometry();
};

void loadScene_exemplo2(void);



#endif
