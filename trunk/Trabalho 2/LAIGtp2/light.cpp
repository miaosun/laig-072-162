
#include "light.h"

void Light::loadLight(TiXmlElement* lightElement)
{
	this->id = lightElement->Attribute("id");
	lightElement->QueryIntAttribute("enabled", &this->enabled);
		
	//Ambiente
	TiXmlElement* ambientElement = lightElement->FirstChildElement("ambient");
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
		printf("Erro parsing bloco ambiente do light %s\n", this->id); 
	
	//Difusa
	TiXmlElement* diffuseElement = lightElement->FirstChildElement("diffuse");
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
		printf("Erro parsing bloco diffuse do light %s\n", this->id); 

	//Especular
	TiXmlElement* specularElement = lightElement->FirstChildElement("specular");
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
		printf("Erro parsing bloco specular do light %s\n", this->id); 


	//Posicao
	TiXmlElement* positionElement = lightElement->FirstChildElement("position");
	if( positionElement->QueryFloatAttribute("x", &position[0]) == TIXML_SUCCESS &&
		positionElement->QueryFloatAttribute("y", &position[1]) == TIXML_SUCCESS &&
		positionElement->QueryFloatAttribute("z", &position[2]) == TIXML_SUCCESS &&
		positionElement->QueryFloatAttribute("w", &position[3]) == TIXML_SUCCESS)
	{
		printf("Position R: %f\n", position[0]);
		printf("position G: %f\n", position[1]);
		printf("Position B: %f\n", position[2]);
		printf("Position A: %f\n", position[3]);
	} 
	else
		printf("Erro parsing bloco position do light %s\n", this->id); 
	
}
