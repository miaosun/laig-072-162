#include "SceneLoader.h"
#include <iostream>

using namespace std;

SceneLoader::SceneLoader(const char * fileName):
  doc(fileName)
{
  // Read string from file
	bool loadOkay = doc.LoadFile();

	if ( !loadOkay )
	{
	  // fazer subclassing ?classe exception para dar mais informações...
	  throw exception();
	}
	
	this->root = doc.RootElement();
}

//-------------------------------------------------------

bool SceneLoader::loadScene()
{ 
	objectsElement = root->FirstChildElement( "objects" );

	// Inicialização
	// Um exemplo de um conjunto de nós bem conhecidos e obrigatórios

	if (objectsElement == NULL) {
		cout << "Bloco objects nao encontrado\n";
		return false;
	}

	else {
		loadObjects();

		return true;
	}
}

void SceneLoader::loadMaterial()
{
	vector<string> mats;
	for(TiXmlElement *child(objectElement->FirstChildElement()); child!=NULL; child=child->NextSiblingElement())
	{
		const string name(child->Value());
		if(name=="material")
		{
			const string mat1(child->Attribute("id"));
			mats.push_back(mat1);
		}
	}
}

void SceneLoader::loadGeometry()
{
	vector<string> geos;
	for(TiXmlElement *child(objectElement->FirstChildElement()); child!=NULL; child=child->NextSiblingElement())
	{
		const string tag_geo(child->Value());
		if(tag_geo=="geometry")
		{
			const string geo(child->Attribute("id"));
			geos.push_back(geo);
		}
	}
}

void SceneLoader::loadObjects()
{
	materialElement = objects->FirstChildElement( "material" );

	if (materialElement == NULL) {
		cout << "Bloco material nao encontrado\n";
	}
	else {
		loadObject();
	}

	//Percorrer todos os elementos Point dentro do grupo Points do XML
	for(TiXmlElement *child(objectsElement->FirstChildElement()); child != NULL; child = child->NextSiblingElement())
	{
		vector<string> objs;
		const string tag_objects(child->Value());

		//Este bloco so pode conter tag's "Point"
		if(tag_objects == "object") {

			point point_coord;
			
			//Ler o id do point
			const string object_name(child->Attribute("id"));
			if(object_name=="tampa")
			{
				objs.push_back(object_name);
			}
			//Ler os valor x,y,z do point
			if(child->QueryFloatAttribute("x", &point_coord.x) == TIXML_SUCCESS &&
				child->QueryFloatAttribute("y", &point_coord.y) == TIXML_SUCCESS &&
				child->QueryFloatAttribute("z", &point_coord.z) == TIXML_SUCCESS)
			{
				//Guarda-los no map de points
				pointsMap[point_name]=point_coord;
			}
		}
		else {
			//Erro
			return;
		}
	}
}


//Carregar os poligonos
void SceneLoader::loadPolygons(){
	
	//Percorrer todos os elementos Polygon dentro do grupo Polygons do XML
	for(TiXmlElement *polygon(polygonsElement->FirstChildElement()); polygon != NULL; polygon = polygon->NextSiblingElement())
	{
		const string tag_polygon(polygon->Value());

		vector<string> vec_temp;

		//Este bloco so pode conter tag's "Polygon"
		if(tag_polygon == "Polygon") {

			//Ler o id do poligono
			const string polygon_name(polygon->Attribute("id"));

			//Ler todos os pontos que fazem parte desse poligono.
			for(TiXmlElement *points(polygon->FirstChildElement()); points != NULL; points = points->NextSiblingElement()) {
				const string tag_point(points->Value());

				if(tag_point == "Point") {

					//Ler o nome do ponto actual e guarda-lo no vector de pontos do poligono.
					const string point_name(points->Attribute("id"));

					vec_temp.push_back(point_name);
				}
				else return;
			}

			//Guardar o novo poligono no map de poligonos.
			polygonsMap[polygon_name] = vec_temp;
		}
		else {
			//Erro
			return;
		}
	}
}