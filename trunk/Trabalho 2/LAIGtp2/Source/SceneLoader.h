#ifndef SCENE_LOADER
#define SCENE_LOADER

#include "..\tinyxml.h"
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

class View
{
public:
	string id;
	float near;
	float far;
	float axisscale;

	View(string id, float near, float far, float axisscalse)
	{
		this->id = id;
		this->near = near;
		this->far = far;
		this->axisscale = axisscale;
	}
};

class Illumination
{
public:
	string id;
	double doublesided;
	double local;

	Illumination(string id, double doublesided, double local)
	{
		this->id = id;
		this->doublesided = doublesided;
		this->local = local;
	}
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





class SceneLoader {

public:
	map<string, point> pointsMap;
	map<string, vector<string>> polygonsMap;

	vector<View *> views;
	vector<Material *> materiais;
	vector<Texture *> textures;
	vector<Light *> lights;
	
	SceneLoader(const char * fileName);
	bool loadScene();
  
	TiXmlElement* viewsElement;
	TiXmlElement* objectsElement;
	TiXmlElement* objectElement;
	TiXmlElement* lightsElement;
	TiXmlElement* materiaisElement;
	TiXmlElement* texturesElement;
	TiXmlElement* pointsElement;
	TiXmlElement* polygonsElement;
	TiXmlElement *root;
	TiXmlElement *objects;
	TiXmlDocument doc;

	void loadView(TiXmlElement* viewsElement);
	void loadLight(TiXmlElement* lightsElement);
	void loadMaterial(TiXmlElement* materialElement);
	void loadTexture(TiXmlElement* textureElement);
	void loadGeometry();
	//void loadObjects();
	void loadPoints();
	void loadPolygons();
};

#endif
