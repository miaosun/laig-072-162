
#include "material.h"


void Material::loadMaterial(TiXmlElement *materialsElement)
{
	this->id = materialsElement->Attribute("id"); 
	printf("Material id: %s\n", this->id);

	//Emission
	TiXmlElement* emissionElement = materialsElement->FirstChildElement("emission");
	if(emissionElement->QueryFloatAttribute("r", &emission[0]) == TIXML_SUCCESS &&
		emissionElement->QueryFloatAttribute("g", &emission[1]) == TIXML_SUCCESS &&
		emissionElement->QueryFloatAttribute("b", &emission[2]) == TIXML_SUCCESS &&
		emissionElement->QueryFloatAttribute("a", &emission[3]) == TIXML_SUCCESS)
	{
		printf("Emission R: %f\n", emission[0]);
		printf("Emission G: %f\n", emission[1]);
		printf("Emission B: %f\n", emission[2]);
		printf("Emission A: %f\n", emission[3]);
	} 
	else 
		printf("Erro parsing bloco emission do material: %s\n", this->id);
	
	
	//Ambiente
	TiXmlElement* ambientElement = materialsElement->FirstChildElement("ambient");
	if(ambientElement->QueryFloatAttribute("r", &ambient[0]) == TIXML_SUCCESS &&
		ambientElement->QueryFloatAttribute("g", &ambient[1]) == TIXML_SUCCESS &&
		ambientElement->QueryFloatAttribute("b", &ambient[2]) == TIXML_SUCCESS &&
		ambientElement->QueryFloatAttribute("a", &ambient[3]) == TIXML_SUCCESS)
	{
		printf("Ambient R: %f\n", ambient[0]);
		printf("Ambient G: %f\n", ambient[1]);
		printf("Ambient B: %f\n", ambient[2]);
		printf("Ambient A: %f\n", ambient[3]);
	}
	else 
		printf("Erro parsing bloco ambient do material: %s\n", this->id);
	

	//Difusa
	TiXmlElement* diffuseElement = materialsElement->FirstChildElement("diffuse");
	if(diffuseElement->QueryFloatAttribute("r", &diffuse[0]) == TIXML_SUCCESS &&
		diffuseElement->QueryFloatAttribute("g", &diffuse[1]) == TIXML_SUCCESS &&
		diffuseElement->QueryFloatAttribute("b", &diffuse[2]) == TIXML_SUCCESS &&
		diffuseElement->QueryFloatAttribute("a", &diffuse[3]) == TIXML_SUCCESS)
	{
		printf("Diffuse R: %f\n", diffuse[0]);
		printf("Diffuse G: %f\n", diffuse[1]);
		printf("Diffuse B: %f\n", diffuse[2]);
		printf("Diffuse A: %f\n", diffuse[3]);
	} 
	else 
		printf("Erro parsing bloco diffuese do material: %s\n", this->id);
	

	//Especular
	TiXmlElement* specularElement = materialsElement->FirstChildElement("specular");
	if(specularElement->QueryFloatAttribute("r", &specular[0]) == TIXML_SUCCESS &&
		specularElement->QueryFloatAttribute("g", &specular[1]) == TIXML_SUCCESS &&
		specularElement->QueryFloatAttribute("b", &specular[2]) == TIXML_SUCCESS &&
		specularElement->QueryFloatAttribute("a", &specular[3]) == TIXML_SUCCESS)
	{
		printf("Specular R: %f\n", specular[0]);
		printf("Specular G: %f\n", specular[1]);
		printf("Specular B: %f\n", specular[2]);
		printf("Specular A: %f\n", specular[3]);
	} 
	else 
		printf("Erro parsing bloco specular do material: %s\n", this->id);
	

	//Shininess
	TiXmlElement* shininessElement = materialsElement->FirstChildElement("shininess");
	if(shininessElement->QueryFloatAttribute("value", &shininess[0]) == TIXML_SUCCESS)
		printf("Shininess: %f\n", shininess[0]);
	else
		printf("Erro parsing Shininess do material: %s\n", this->id);

}