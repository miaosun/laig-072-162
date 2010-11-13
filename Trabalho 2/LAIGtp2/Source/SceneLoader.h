#ifndef SCENE_LOADER
#define SCENE_LOADER

#include "../tinyxml.h"
#include "Object.h"
#include <map>
#include <string>
#include <vector>

using namespace std;

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
	Object * root_object;

	Material * mat_base;
	Texture * no_tex;

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
	Texture * findTexture(string id);
	Material * findMaterial(string id);
	Object * findObject(string id);
	bool aplicaMaterials(Object * o, Material * mat);
	bool aplicaTextures(Object * o, Texture * tex);
	
	bool loadGeometry();
};

void loadScene_exemplo2(void);



#endif
