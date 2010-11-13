#ifndef SCENE_LOADER
#define SCENE_LOADER

#include "../tinyxml.h"
#include "Object.h"
#include <map>
#include <string>
#include <vector>

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
	float shininess;

	Material(){};
	Material(string id)
	{
		this->id = id;
		this->shininess = 0;
	}
};


class Texture
{
public:
	string id;
	string file;
	float length_s;
	float length_t;

	Texture(){};
	Texture(string id, string file, float length_s, float length_t)
	{
		this->id = id;
		this->file = file;
		this->length_s = length_s;
		this->length_t = length_t;
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
	vector<Transformation *> trans;


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
	vector<Object *> objs;

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
		materialElement = NULL;
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
	TiXmlElement* materialElement;
	TiXmlElement* materialsElement;
	TiXmlElement* texturesElement;
	TiXmlElement* pointsElement;
	//transformacoes
	TiXmlElement* transformationElement;



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
	bool loadLight();
	bool loadMaterial();
	bool loadMaterials();
	bool loadTexture();
	bool loadTextures();

	bool loadCompound();
	bool loadObject();
	bool loadObjects();
	
	bool loadGeometry();
};

void loadScene_exemplo2(void);



#endif
