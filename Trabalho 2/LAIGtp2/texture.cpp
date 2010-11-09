
#include "texture.h"

void Texture::loadTexture(TiXmlElement* textsElement)
{
	this->id = textsElement->Attribute("id");
	this->file = textsElement->Attribute("file");
	if(textsElement->QueryFloatAttribute("length_s", &length_s) == TIXML_SUCCESS &&
		textsElement->QueryFloatAttribute("length_t", &length_t) == TIXML_SUCCESS)
	{
		printf("Texture id: %f\n", this->id);
		printf("File: %s\n", this->file);
		printf("Length_S: %f\n", this->length_s);
		printf("Length_T: %f\n", this->length_t);
	} else{
		printf("Erro parsing texture: %s\n", this->id);
	}
}