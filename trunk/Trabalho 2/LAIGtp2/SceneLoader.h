#ifndef SCENE_LOADER
#define SCENE_LOADER

#include "tinyxml.h"
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

class SceneLoader {

public:
	map<string, point> pointsMap;
	map<string, vector<string>> polygonsMap;
	SceneLoader(const char * fileName);
	bool loadScene();

private:
  
	TiXmlElement* objectsElement;
	TiXmlElement* objectElement;
	TiXmlElement* materialElement;
	TiXmlElement* polygonsElement;
	TiXmlElement *root;
	TiXmlElement *objects;
	TiXmlDocument doc;

	void loadObjects();
	void loadMaterial();
	void loadGeometry();
	void loadPolygons();
};

#endif
