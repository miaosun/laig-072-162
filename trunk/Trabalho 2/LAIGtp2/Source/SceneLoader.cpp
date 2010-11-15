#include "SceneLoader.h"

SceneLoader::SceneLoader(const char * fileName):
  doc(fileName)
{
  // Read string from file
	bool loadOkay = doc.LoadFile();

	if ( !loadOkay )
	{
	  // fazer subclassing ?classe exception para dar mais informações...
		cout<<"erro no load do xml\n";
		system("pause");
	}

	this->mat_base=new Material();

	this->mat_base->ambient[0]=0.6;
	this->mat_base->ambient[1]=0.6;
	this->mat_base->ambient[2]=0.6;
	this->mat_base->ambient[3]=1.0;
	this->mat_base->diffuse[0]=0.6;
	this->mat_base->diffuse[1]=0.6;
	this->mat_base->diffuse[2]=0.6;
	this->mat_base->diffuse[3]=1.0;
	this->mat_base->id="_base";
	this->mat_base->specular[0]=0.4;
	this->mat_base->specular[1]=0.4;
	this->mat_base->specular[2]=0.4;
	this->mat_base->specular[3]=1.0;
	this->mat_base->shininess[0]=128.0; 

	this->no_tex=new Texture();

	this->no_tex->id="NO_TEXTURE";

	this->root = doc.RootElement();
}

bool SceneLoader::loadGlobals()
{
	global.root = globalsElement->Attribute("root");
	
	if((globalsElement->QueryIntAttribute("maxlights", &global.maxlights)) == TIXML_SUCCESS &&
	 (globalsElement->QueryIntAttribute("maxmaterials", &global.maxmaterials)) == TIXML_SUCCESS &&
	 (globalsElement->QueryIntAttribute("maxtextures", &global.maxtextures)) == TIXML_SUCCESS &&
	 (globalsElement->QueryIntAttribute("maxobjects", &global.maxobjects)) == TIXML_SUCCESS)
	{
		cout<<"Global:\n\tMaxLights:"<<global.maxlights<<", MaxMaterials:"<<global.maxmaterials<<", MaxTextures:"<<global.maxtextures<<", MaxObjects:"<<global.maxobjects<<"\n\tRoot: "<<global.root<<endl<<endl;
		return true;
	} 
	else
		cout<<"Erro parsing global.\n";
	return false;
}

bool SceneLoader::loadView()
{
	if((viewElement->QueryFloatAttribute("near", &view.near)) == TIXML_SUCCESS &&
		(viewElement->QueryFloatAttribute("far", &view.far)) == TIXML_SUCCESS &&
		(viewElement->QueryFloatAttribute("axisscale", &view.axisscale)) == TIXML_SUCCESS)
	{
		cout<<"View:\n\tNear:"<<view.near<<", Far:"<<view.far<<", AxisScale:"<<view.axisscale<<endl; 
	} 
	else
	{
		cout<<"Erro parsing frustum."<<endl;
		return false;
	}

	float x, y, z, angle;
	string axis;
	Transformation * transf;


	transformationElement=viewElement->FirstChildElement();

	while(transformationElement)
	{
		if(strcmp(transformationElement->Value(),"translation")==0)
		{
			if(transformationElement->QueryFloatAttribute("x", &x) == TIXML_SUCCESS &&
				transformationElement->QueryFloatAttribute("y", &y) == TIXML_SUCCESS &&
				transformationElement->QueryFloatAttribute("z", &z) == TIXML_SUCCESS)
			{
				transf=new Translation(x, y, z);
				view.trans.push_back(transf);
				cout<<"\ttranslation: x:"<<view.trans.back()->getX()<<" y:"<<view.trans.back()->getY()<<" z:"<<view.trans.back()->getZ()<<endl;
			}
			else
			{
				cout<<"Erro parsing translation da view\n";
				system("pause");
				return false;
			}
		}
		else if(strcmp(transformationElement->Value(),"rotation")==0)
		{
			axis=transformationElement->Attribute("axis");
			if(transformationElement->QueryFloatAttribute("angle", &angle) == TIXML_SUCCESS)
			{
				transf = new Rotation(axis, angle);
				view.trans.push_back(transf);
				cout<<"\trotacao "<<view.trans.back()->getAxis()<<" ang:"<<view.trans.back()->getAngle()<<endl;
			}
			else
			{
				cout<<"Erro parsing rotation da view\n";
				system("pause");
				return false;
			}
		}
		else if(strcmp(transformationElement->Value(),"scale")==0)
		{
			if(transformationElement->QueryFloatAttribute("x", &x) == TIXML_SUCCESS &&
				transformationElement->QueryFloatAttribute("y", &y) == TIXML_SUCCESS &&
				transformationElement->QueryFloatAttribute("z", &z) == TIXML_SUCCESS)
			{
				transf = new Scale(x, y, z);
				view.trans.push_back(transf);
				cout<<"\tscale x:"<<view.trans.back()->getX()<<" y:"<<view.trans.back()->getY()<<" z:"<<view.trans.back()->getZ()<<endl;
			}
			else
			{
				cout<<"Erro parsing scale da view\n";
				system("pause");
				return false;
			}
		}
		else
		{
			cout<<"erro na tag da transformacao: tem que ser ou translation ou rotation ou scale\n";
			system("pause");
			return false;
		}
		transformationElement=transformationElement->NextSiblingElement();
	}	
	cout<<endl;
	return true;
}

bool SceneLoader::loadIllumination()
{
	int doublesided, local;
	if((illuminationElement->QueryIntAttribute("doublesided", &doublesided)) == TIXML_SUCCESS &&
		(illuminationElement->QueryIntAttribute("local", &local) == TIXML_SUCCESS))
	{
		if(doublesided==1)
			illumination.doublesided=true;
		else if(doublesided==0)
			illumination.doublesided=false;
		else
		{
			cout<<"erro: doublesided deve ter valor boleano!\n";
			system("pause");
			return false;
		}
		if(local==1)
			illumination.local=true;
		else if(local==0)
			illumination.local=false;
		else
		{
			cout<<"erro: local deve ter valor boleano!\n";
			system("pause");
			return false;
		}
		cout<<"Illumination:\n\tDoubleSided: "<<illumination.doublesided<<", Local: "<<illumination.local<<endl;
	}
	else
	{
		cout<<"Erro parsing illumination\n";
		system("pause");
		return false;
	}

	ambientElement = illuminationElement->FirstChildElement("ambient");

	if(ambientElement!=NULL)
	{
		if(ambientElement->QueryFloatAttribute("r", &illumination.ambient[0]) == TIXML_SUCCESS &&
			ambientElement->QueryFloatAttribute("g", &illumination.ambient[1]) == TIXML_SUCCESS &&
			ambientElement->QueryFloatAttribute("b", &illumination.ambient[2]) == TIXML_SUCCESS &&
			ambientElement->QueryFloatAttribute("a", &illumination.ambient[3]) == TIXML_SUCCESS)
			cout<<"\tAmbient R, G, B, A: "<<illumination.ambient[0]<<", "<<illumination.ambient[1]<<", "<<illumination.ambient[2]<<", "<<illumination.ambient[3]<<endl;
		else
		{
			cout<<"Erro parsing ambiente de illumination\n";
			system("pause");
			return false;
		}
	}
	else
	{
		cout<<"problema com ambient de illumination\n";
		system("pause");
		return false;
	}

	backgroundElement = illuminationElement->FirstChildElement("background");
	if(backgroundElement!=NULL)
	{
		if(backgroundElement->QueryFloatAttribute("r", &illumination.backgroud[0]) == TIXML_SUCCESS &&
			backgroundElement->QueryFloatAttribute("g", &illumination.backgroud[1]) == TIXML_SUCCESS &&
			backgroundElement->QueryFloatAttribute("b", &illumination.backgroud[2]) == TIXML_SUCCESS &&
			backgroundElement->QueryFloatAttribute("a", &illumination.backgroud[3]) == TIXML_SUCCESS)
			cout<<"\tBackground R, G, B, A: "<<illumination.backgroud[0]<<", "<<illumination.backgroud[1]
			<<", "<<illumination.backgroud[2]<<", "<<illumination.backgroud[3]<<endl;
		else
		{
			cout<<"Erro parsing background de illumination\n";
			system("pause");
			return false;
		}
	}
	else
	{
		cout<<"Erro parsing background de illumination\n";
		system("pause");
		return false;
	}	

	TiXmlElement *luzes=illuminationElement->FirstChildElement("lights");
	lightsElement=luzes->FirstChildElement("light");
	int nLights = 0;
	while(lightsElement!=NULL)
	{
		if(nLights == global.maxlights)
		{
			cout<<"Ja chegou limite de maxLights\n";
			system("pause");
			return false;
		}
		else if(strcmp(lightsElement->Value(), "light") == 0)
			loadLight();
		else
		{
			cout<<"Erro parsing light de lights de illumination\n";
			system("pause");
			return false;
		}

		lightsElement = lightsElement->NextSiblingElement();
		nLights++;
	}
	cout<<endl;
	return true;
}

bool SceneLoader::loadTexture()
{
	string id = texturesElement->Attribute("id");
	const string file = texturesElement->Attribute("file");
	float length_s, length_t;
	if(texturesElement->QueryFloatAttribute("length_s", &length_s) == TIXML_SUCCESS &&
		texturesElement->QueryFloatAttribute("length_t", &length_t) == TIXML_SUCCESS)
	{
		Texture* tex = new Texture(id, file, length_s, length_t);
		textures.push_back(tex);

		cout<<"\tTexture ID: "<<id<<", File: "<<file<<", Length_s: "<<length_s<<", Length_t: "<<length_t<<endl;
	}
	else
	{
		cout<<"Erro parsing texture: "<<id<<endl;
		system("pause");
		return false;
	}
	return true;
}

bool SceneLoader::loadTextures()
{
	texturesElement=texturesElement->FirstChildElement();
	cout<<"Textures:\n";
	int nTextures = 0;
	while(texturesElement)
	{
		if(nTextures == global.maxtextures)
		{
			cout<<"Ja chegou limite de maxTextures\n";
			system("pause");
			return false;
		}
		else if(strcmp(texturesElement->Value(), "texture") == 0)
		{
			if(!loadTexture())
				return false;
		}
		else
		{
			cout<<"Erro parsing texture de textures\n";
			system("pause");
			return false;
		}

		texturesElement = texturesElement->NextSiblingElement();
		nTextures++;
	}
	cout<<endl;
	return true;
}

bool SceneLoader::loadMaterial()
{
	string id = materialElement->Attribute("id");
	float r, g, b, a, shininess;

	Material* mat = new Material(id);
	materiais.push_back(mat);

	cout<<"\tMaterial ID: "<<id<<endl;

	TiXmlElement* child = materialElement->FirstChildElement();
	while(child != NULL)
	{
		if(strcmp(child->Value(), "emission")==0)
		{
			if(child->QueryFloatAttribute("r", &r) == TIXML_SUCCESS &&
				child->QueryFloatAttribute("g", &g) == TIXML_SUCCESS &&
				child->QueryFloatAttribute("b", &b) == TIXML_SUCCESS &&
				child->QueryFloatAttribute("a", &a) == TIXML_SUCCESS)
			{
				materiais.back()->emission[0] = r;
				materiais.back()->emission[1] = g;
				materiais.back()->emission[2] = b;
				materiais.back()->emission[3] = a;
				cout<<"\t\tEmission R, G, B, A: "<<r<<", "<<g<<", "<<b<<", "<<a<<endl;
			} 
			else
			{
				cout<<"Erro parsing emission de material\n";
				system("pause");
				return false;
			}
		}
		else if(strcmp(child->Value(), "ambient")==0)
		{
			if(child->QueryFloatAttribute("r", &r) == TIXML_SUCCESS &&
				child->QueryFloatAttribute("g", &g) == TIXML_SUCCESS &&
				child->QueryFloatAttribute("b", &b) == TIXML_SUCCESS &&
				child->QueryFloatAttribute("a", &a) == TIXML_SUCCESS)
			{
				materiais.back()->ambient[0] = r;
				materiais.back()->ambient[1] = g;
				materiais.back()->ambient[2] = b;
				materiais.back()->ambient[3] = a;
				cout<<"\t\tAmbient R, G, B, A: "<<r<<", "<<g<<", "<<b<<", "<<a<<endl;
			} 
			else
			{
				cout<<"Erro parsing ambient de material\n";
				system("pause");
				return false;
			}
		}
		else if(strcmp(child->Value(), "diffuse")==0)
		{
			if(child->QueryFloatAttribute("r", &r) == TIXML_SUCCESS &&
				child->QueryFloatAttribute("g", &g) == TIXML_SUCCESS &&
				child->QueryFloatAttribute("b", &b) == TIXML_SUCCESS &&
				child->QueryFloatAttribute("a", &a) == TIXML_SUCCESS)
			{
				materiais.back()->diffuse[0] = r;
				materiais.back()->diffuse[1] = g;
				materiais.back()->diffuse[2] = b;
				materiais.back()->diffuse[3] = a;
				cout<<"\t\tDiffuse R, G, B, A: "<<r<<", "<<g<<", "<<b<<", "<<a<<endl;
			} 
			else
			{
				cout<<"Erro parsing diffuse de material\n";
				system("pause");
				return false;
			}
		}
		else if(strcmp(child->Value(), "specular")==0)
		{
			if(child->QueryFloatAttribute("r", &r) == TIXML_SUCCESS &&
				child->QueryFloatAttribute("g", &g) == TIXML_SUCCESS &&
				child->QueryFloatAttribute("b", &b) == TIXML_SUCCESS &&
				child->QueryFloatAttribute("a", &a) == TIXML_SUCCESS)
			{
				materiais.back()->specular[0] = r;
				materiais.back()->specular[1] = g;
				materiais.back()->specular[2] = b;
				materiais.back()->specular[3] = a;
				cout<<"\t\tSpecular R, G, B, A: "<<r<<", "<<g<<", "<<b<<", "<<a<<endl;
			} 
			else
			{
				cout<<"Erro parsing specular de material\n";
				system("pause");
				return false;
			}
		}
		else if(strcmp(child->Value(), "shininess")==0)
		{
			if(child->QueryFloatAttribute("value", &shininess) == TIXML_SUCCESS)
			{
				materiais.back()->shininess[0] = shininess;
				cout<<"\t\tShininess: "<<shininess<<endl;
			}
			else
			{
				cout<<"Erro parsing shininess de material\n";
				system("pause");
				return false;
			}
		}
		else
		{
			cout<<"Erro parsing material\n";
			system("pause");
			return false;
		}
		child=child->NextSiblingElement();
	}
	return true;
}

bool SceneLoader::loadMaterials()
{
	materialElement=materialsElement->FirstChildElement();
	cout<<"Materials:\n";
	int nMaterials = 0;
	while(materialElement)
	{
		if(nMaterials == global.maxmaterials)
		{
			cout<<"Ja chegou limite de maxMaterials\n";
			system("pause");
			return false;
		}
		else if(strcmp(materialElement->Value(), "material") == 0)
		{
			if(!loadMaterial())
				return false;
		}
		else
		{
			cout<<"Erro parsing material de materials\n";
			system("pause");
			return false;
		}

		materialElement = materialElement->NextSiblingElement();
		nMaterials++;
	}
	cout<<endl;
	return true;

}

bool SceneLoader::loadLight()
{
	int i_enabled;
	bool enabled;
	string id = lightsElement->Attribute("id");
	lightsElement->QueryIntAttribute("enabled", &i_enabled);
	float r, g, b, a, x, y, z, w;

	if(i_enabled==1)
		enabled=true;
	else if(i_enabled==0)
		enabled=false;
	else
	{
		cout<<"enabled deve ser um valor boleano!\n";
		system("pause");
		return false;
	}

	Light* light = new Light(id, enabled);
	lights.push_back(light);

	cout<<"\tLight ID: "<<id<<", Enabled: ";
	if(enabled)
		cout<<"Sim"<<endl;
	else
		cout<<"Nao"<<endl;


	TiXmlElement* child = lightsElement->FirstChildElement("position");

	while(child)
	{
		if(strcmp(child->Value(), "ambient")==0)
		{
			if(child->QueryFloatAttribute("r", &r) == TIXML_SUCCESS &&
				child->QueryFloatAttribute("g", &g) == TIXML_SUCCESS &&
				child->QueryFloatAttribute("b", &b) == TIXML_SUCCESS &&
				child->QueryFloatAttribute("a", &a) == TIXML_SUCCESS)
			{
				lights.back()->ambient[0] = r;
				lights.back()->ambient[1] = g;
				lights.back()->ambient[2] = b;
				lights.back()->ambient[3] = a;
				cout<<"\t\tAmbient R, G, B, A: "<<r<<", "<<g<<", "<<b<<", "<<a<<endl;
			} 
			else
			{
				cout<<"erro na definicao ambient de "<<id<<endl;
				system("pause");
				return false;
			}
		}
		else if(strcmp(child->Value(), "diffuse")==0)
		{
			if(child->QueryFloatAttribute("r", &r) == TIXML_SUCCESS &&
				child->QueryFloatAttribute("g", &g) == TIXML_SUCCESS &&
				child->QueryFloatAttribute("b", &b) == TIXML_SUCCESS &&
				child->QueryFloatAttribute("a", &a) == TIXML_SUCCESS)
			{
				lights.back()->diffuse[0] = r;
				lights.back()->diffuse[1] = g;
				lights.back()->diffuse[2] = b;
				lights.back()->diffuse[3] = a;
				cout<<"\t\tDiffuse R, G, B, A: "<<r<<", "<<g<<", "<<b<<", "<<a<<endl;
			} 
			else
			{
				cout<<"erro na definicao diffuse de "<<id<<endl;
				system("pause");
				return false;
			}
		}
		else if(strcmp(child->Value(), "specular")==0)
		{
			if(child->QueryFloatAttribute("r", &r) == TIXML_SUCCESS &&
				child->QueryFloatAttribute("g", &g) == TIXML_SUCCESS &&
				child->QueryFloatAttribute("b", &b) == TIXML_SUCCESS &&
				child->QueryFloatAttribute("a", &a) == TIXML_SUCCESS)
			{
				lights.back()->specular[0] = r;
				lights.back()->specular[1] = g;
				lights.back()->specular[2] = b;
				lights.back()->specular[3] = a;
				cout<<"\t\tSpecular R, G, B, A: "<<r<<", "<<g<<", "<<b<<", "<<a<<endl;
			} 
			else
			{
				cout<<"erro na definicao specular de "<<id<<endl;
				system("pause");
				return false;
			}
		}
		else if(strcmp(child->Value(), "position")==0)
		{
			if(child->QueryFloatAttribute("x", &x) == TIXML_SUCCESS &&
				child->QueryFloatAttribute("y", &y) == TIXML_SUCCESS &&
				child->QueryFloatAttribute("z", &z) == TIXML_SUCCESS &&
				child->QueryFloatAttribute("w", &w) == TIXML_SUCCESS)
			{
				lights.back()->position[0] = x;
				lights.back()->position[1] = y;
				lights.back()->position[2] = z;
				lights.back()->position[3] = w;
				cout<<"\t\tPosition X, Y, Z, W: "<<x<<", "<<y<<", "<<z<<", "<<w<<endl;
			} 
			else
			{
				cout<<"erro na definicao position de "<<id<<endl;
				system("pause");
				return false;
			}
		}
		else
		{
			cout<<"Erro parsing light id: "<<id<<endl;
			system("pause");
			return false;
		}
		child=child->NextSiblingElement();
	}
	return true;
}

bool SceneLoader::loadObject()
{
	Object *o;
	string id, type, axis, mat, tex;
	vector<Transformation *> transf_v;
	vector<string> s_id;
	Transformation * transf;
	float x, y, z, angle, x1, x2, x3, y1, y2, y3, z1, z2, z3, base, top, height, radius, inner, outer;
	int slices, stacks;

	id=objectElement->Attribute("id");
	type=objectElement->Attribute("type");
	cout<<"objecto "<<id<<endl;

	transformationElement=objectElement->FirstChildElement("transformations");
	transformationElement=transformationElement->FirstChildElement();
	while(transformationElement)
	{
		if(strcmp(transformationElement->Value(),"translation")==0)
		{
			if(transformationElement->QueryFloatAttribute("x", &x) == TIXML_SUCCESS &&
				transformationElement->QueryFloatAttribute("y", &y) == TIXML_SUCCESS &&
				transformationElement->QueryFloatAttribute("z", &z) == TIXML_SUCCESS)
			{
				transf=new Translation(x, y, z);
				transf_v.push_back(transf);
				cout<<"\t\ttranslation: x:"<<transf_v.back()->getX()<<" y:"<<transf_v.back()->getY()<<" z:"<<transf_v.back()->getZ()<<endl;
			}
			else
			{
				cout<<"Erro parsing translation do objecto "<<id<<endl;
				system("pause");
				return false;
			}
		}
		else if(strcmp(transformationElement->Value(),"rotation")==0)
		{
			axis=transformationElement->Attribute("axis");
			if(transformationElement->QueryFloatAttribute("angle", &angle) == TIXML_SUCCESS)
			{
				transf = new Rotation(axis, angle);
				transf_v.push_back(transf);
				cout<<"\t\trotacao "<<transf_v.back()->getAxis()<<" ang:"<<transf_v.back()->getAngle()<<endl;
			}
			else
			{
				cout<<"Erro parsing rotation do objecto "<<id<<endl;
				system("pause");
				return false;
			}
		}
		else if(strcmp(transformationElement->Value(),"scale")==0)
		{
			if(transformationElement->QueryFloatAttribute("x", &x) == TIXML_SUCCESS &&
				transformationElement->QueryFloatAttribute("y", &y) == TIXML_SUCCESS &&
				transformationElement->QueryFloatAttribute("z", &z) == TIXML_SUCCESS)
			{
				transf = new Scale(x, y, z);
				transf_v.push_back(transf);
				cout<<"\t\tscale x:"<<transf_v.back()->getX()<<" y:"<<transf_v.back()->getY()<<" z:"<<transf_v.back()->getZ()<<endl;
			}
			else
			{
				cout<<"Erro parsing scale do objecto "<<id<<endl;
				system("pause");
				return false;
			}
		}
		else
		{
			cout<<"erro na tag da transformacao: tem que ser ou translation ou rotation ou scale. do objecto "<<id<<endl;
			system("pause");
			return false;
		}
		transformationElement=transformationElement->NextSiblingElement();
	}

	TiXmlElement* material=objectElement->FirstChildElement("material");
	if(material)
		mat=material->Attribute("id");
	else
	{
		cout<<"o objecto "<<id<<" nao tem material definido\n";
		system("pause");
		return false;
	}

	TiXmlElement* texture=objectElement->FirstChildElement("texture");
	if(texture)
		tex=texture->Attribute("id");
	else
	{
		cout<<"o objecto "<<id<<" nao tem textura definida\n";
		system("pause");
		return false;
	}

	if(type=="simple")
	{
		TiXmlElement* geometry=objectElement->FirstChildElement("geometry");
		if(geometry)
		{
			if(strcmp(geometry->Attribute("type"),"rectangle")==0)
			{
				if(geometry->QueryFloatAttribute("x1", &x1) == TIXML_SUCCESS &&
					geometry->QueryFloatAttribute("x2", &x2) == TIXML_SUCCESS &&
					geometry->QueryFloatAttribute("y1", &y1) == TIXML_SUCCESS &&
					geometry->QueryFloatAttribute("y2", &y2) == TIXML_SUCCESS)
				{
					o=new Rectangle(id, mat, tex, transf_v, x1, y1, x2, y2);
					objs.push_back(o);
					cout<<"\t\trectangulo x1:"<<objs.back()->getX1()<<" y1:"<<objs.back()->getY1()<<" x2:"<<objs.back()->getX2()<<" y2:"<<objs.back()->getY2()<<endl;
				}
				else
				{
					cout<<"problema na declaracao de rectangle do objecto "<<id<<endl;
					system("pause");
					return false;
				}
			}
			else if(strcmp(geometry->Attribute("type"),"triangle")==0)
			{
				if(geometry->QueryFloatAttribute("x1", &x1) == TIXML_SUCCESS &&
					geometry->QueryFloatAttribute("x2", &x2) == TIXML_SUCCESS &&
					geometry->QueryFloatAttribute("x3", &x3) == TIXML_SUCCESS &&
					geometry->QueryFloatAttribute("y1", &y1) == TIXML_SUCCESS &&
					geometry->QueryFloatAttribute("y2", &y2) == TIXML_SUCCESS &&
					geometry->QueryFloatAttribute("y3", &y3) == TIXML_SUCCESS &&
					geometry->QueryFloatAttribute("z1", &z1) == TIXML_SUCCESS &&
					geometry->QueryFloatAttribute("z2", &z2) == TIXML_SUCCESS &&
					geometry->QueryFloatAttribute("z3", &z3) == TIXML_SUCCESS)
				{
					o=new Triangle(id, mat, tex, transf_v, x1, y1, z1, x2, y2, z2, x3, y3, z3);
					objs.push_back(o);
					cout<<"\t\tTriangulo x1:"<<objs.back()->getX1()<<" y1:"<<objs.back()->getY1()<<" z1:"<<objs.back()->getZ1()
						<<"\n\t\t  x2:"<<objs.back()->getX2()<<" y2:"<<objs.back()->getY2()<<" z2:"<<objs.back()->getZ2()
						<<"\n\t\t  x3:"<<objs.back()->getX3()<<" y3:"<<objs.back()->getY3()<<" z3:"<<objs.back()->getZ3()<<endl;
				}
				else
				{
					cout<<"problema na declaracao de triangle do objecto "<<id<<endl;
					system("pause");
					return false;
				}
			}
			else if(strcmp(geometry->Attribute("type"),"cylinder")==0)
			{
				if(geometry->QueryFloatAttribute("base", &base) == TIXML_SUCCESS &&
					geometry->QueryFloatAttribute("top", &top) == TIXML_SUCCESS &&
					geometry->QueryFloatAttribute("height", &height) == TIXML_SUCCESS &&
					geometry->QueryIntAttribute("slices", &slices) == TIXML_SUCCESS &&
					geometry->QueryIntAttribute("stacks", &stacks) == TIXML_SUCCESS)
				{
					o=new Cylinder(id, mat, tex, transf_v, base, top, height, slices, stacks);
					objs.push_back(o);
					cout<<"\n\tCilindro base:"<<objs.back()->getBase()<<" topo:"<<objs.back()->getTop()<<" altura:"
						<<objs.back()->getHeight()<<" stacks:"<<objs.back()->getStacks()<<" slices:"<<objs.back()->getSlices()<<endl;
				}
				else
				{
					cout<<"problema na declaracao de cylinder do objecto "<<id<<endl;
					system("pause");
					return false;
				}

			}
			else if(strcmp(geometry->Attribute("type"),"sphere")==0)
			{
				if(geometry->QueryFloatAttribute("radius", &radius) == TIXML_SUCCESS &&
					geometry->QueryIntAttribute("slices", &slices) == TIXML_SUCCESS &&
					geometry->QueryIntAttribute("stacks", &stacks) == TIXML_SUCCESS)
				{
					o=new Sphere(id, mat, tex, transf_v, radius, slices, stacks);
					objs.push_back(o);
					cout<<"\n\tEsfera raio:"<<objs.back()->getRadius()<<" slices:"<<objs.back()->getSlices()<<" stacks:"<<objs.back()->getStacks()<<endl;
				}
				else
				{
					cout<<"problema na declaracao de sphere do objecto "<<id<<endl;
					system("pause");
					return false;
				}
			}
			else if(strcmp(geometry->Attribute("type"),"disk")==0)
			{
				if(geometry->QueryFloatAttribute("inner", &inner) == TIXML_SUCCESS &&
					geometry->QueryFloatAttribute("outer", &outer) == TIXML_SUCCESS &&
					geometry->QueryIntAttribute("slices", &slices) == TIXML_SUCCESS &&
					geometry->QueryIntAttribute("loops", &stacks) == TIXML_SUCCESS)
				{
					o=new Disk(id, mat, tex, transf_v, inner, outer, slices, stacks);
					objs.push_back(o);
					cout<<"\n\tDisco inner:"<<objs.back()->getInner()<<" outer:"<<objs.back()->getOuter()<<" slices:"<<objs.back()->getSlices()<<" loops:"<<objs.back()->getStacks()<<endl;
				}
				else
				{
					cout<<"problema na declaracao de disk do objecto "<<id<<endl;
					system("pause");
					return false;
				}
			}
			else
			{
				cout<<"tipo geometrico nao contemplado no objecto "<<id<<endl;
				system("pause");
				return false;
			}
		}
		else
		{
			cout<<"bloco geometry inexistente no objecto "<<id<<endl;
			system("pause");
			return false;
		}	
	}
	else if(type=="compound")
	{
		TiXmlElement* child=objectElement->FirstChildElement("children");
		if(child)
		{
			cout<<"\n\tCompound:"<<id<<endl;
			child=child->FirstChildElement();
			while(child)
			{
				if(strcmp(child->Value(), "objectref")==0)
				{
					s_id.push_back(child->Attribute("id"));
					cout<<"\tobjref: "<<s_id.back()<<endl;
				}
				else
				{
					cout<<"tag do tipo objectref incorrecta\n";
					system("pause");
					return false;
				}
				child=child->NextSiblingElement();
			}
			o=new Compound(id, mat, tex, transf_v, s_id);
			objs.push_back(o);
		}
		else
		{
			cout<<"bloco children inexistente no objecto compound "<<id<<endl;
			system("pause");
			return false;
		}	
	}
	else
	{
		cout<<"problema no tipo no objecto: "<<id<<endl;
		system("pause");
		return false;
	}
	return true;
}

bool SceneLoader::loadObjects()
{
	int nObjects=0;
	objectElement=objectsElement->FirstChildElement("object");
	cout<<"Objects:";

	while(objectElement)
	{
		if(nObjects==global.maxobjects)
		{
			cout<<"Ja chegou limite de objectos\n";
			system("pause");
			return false;
		}
		else if(strcmp(objectElement->Value(), "object") == 0)
		{
			if(!loadObject())
				return false;
		}
		else
		{
			cout<<"Erro na tag objecto na "<<nObjects<<endl;
			system("pause");
			return false;
		}
		objectElement=objectElement->NextSiblingElement();
		nObjects++;
	}
	cout<<endl;
	return true;
}

bool SceneLoader::loadScene()
{ 
	sgxElement = doc.FirstChildElement( "sgx" );
	globalsElement = sgxElement->FirstChildElement( "globals" );
	viewElement = sgxElement->FirstChildElement( "view" );
	illuminationElement = sgxElement->FirstChildElement("illumination");
	texturesElement = sgxElement->FirstChildElement("textures");
	objectsElement = sgxElement->FirstChildElement("objects");
	materialsElement = sgxElement->FirstChildElement("materials");

	Material * mat;
	Texture * tex;


	// Inicialização
	// Um exemplo de um conjunto de nós bem conhecidos e obrigatórios

	if(sgxElement == NULL) {
		cout << "Bloco sgx nao encontrado\n";
		system("pause");
		return false;
	}
	
	if(globalsElement != NULL)
	{
		if(!loadGlobals())
			return false;
	}
	else
	{
		cout<<"Bloco globals nao encontrado\n";
		system("pause");
		return false;
	}

	if (viewElement != NULL) 
	{
		if(!loadView())
			return false;
	}
	else
	{
		cout << "Bloco view nao encontrado\n";
		system("pause");
		return false;
	}

	if(illuminationElement != NULL)
	{
		if(!loadIllumination())
			return false;
	}
	else
	{
		cout<<"Bloco illumination nao econtrado\n";
		system("pause");
		return false;
	}
	
	if(texturesElement != NULL)
	{
		if(!loadTextures())
			return false;
	}
	else
	{
		cout<<"Bloco textures nao econtrado\n";
		system("pause");
		return false;
	}
	if(materialsElement != NULL)
	{
		if(!loadMaterials())
			return false;
	}
	else
	{
		cout<<"Bloco materials nao econtrado\n";
		system("pause");
		return false;
	}
	if(objectsElement!=NULL)
	{
		if(!loadObjects())
			return false;
		if(!loadCompound())
			return false;
		root_object=findObject(global.root);
		if(root_object==NULL)
			return false;
		if(root_object->mat_id=="null")
			mat=this->mat_base;
		else
		{
			mat=findMaterial(root_object->mat_id);
			if(mat==NULL)
				return false;
		}
		if(!aplicaMaterials(root_object, mat))
			return false;

		if(root_object->tex_id=="null"||root_object->tex_id=="clear")
			tex=this->no_tex;
		else
		{
			tex=findTexture(root_object->tex_id);
			if(tex==NULL)
				return false;
		}
		if(!aplicaTextures(root_object, tex))
			return false;
	}
	else
	{
		cout<<"Bloco objects nao econtrado\n";
		system("pause");
		return false;
	}

	return true;
}

bool SceneLoader::loadCompound()
{
	for(unsigned int i=0; i<objs.size(); i++)
	{
		if(objs.at(i)->type=="compound")
		{
			cout<<"Compound object "<<objs.at(i)->id<<endl;
			objs.at(i)->visited=true;
			for(unsigned int ii=0; ii<objs.at(i)->getSObjs()->size();ii++)
			{
				for(unsigned int j=0; j<objs.size(); j++)
				{
					if(objs.at(i)->getSObjs()->at(ii)==objs.at(j)->id)
					{
						cout<<"encontrou o objecto "<<objs.at(i)->getSObjs()->at(ii)<<endl;
						objs.at(j)->visited=true;
						objs.at(i)->getObjs()->push_back(objs.at(j));
					}
				}
			}
			if(objs.at(i)->getObjs()->size() !=objs.at(i)->getSObjs()->size())
			{
				cout<<"nao encontrou todos os objectos referenciados em "<<objs.at(i)->id<<endl;
				system("pause");
				return false;
			}
		}
	}
	for(unsigned int i=0; i<objs.size(); i++)
	{
		if(!objs.at(i)->visited)
		{
			cout<<"folha solta, objecto: "<<objs.at(i)->id<<endl;
			system("pause");
			return false;
		}
		objs.at(i)->visited=false;
	}
	return true;
}

Texture * SceneLoader::findTexture(string id)
{
	for(unsigned int i=0; i<textures.size(); i++)
	{
		if(textures.at(i)->id==id)
			return textures.at(i);
	}
	cout<<"texture "<<id<<" nao encontrada\n";
	system("pause");
	return NULL;
}

Material * SceneLoader::findMaterial(string id)
{
	for(unsigned int i=0; i<materiais.size(); i++)
	{
		if(materiais.at(i)->id==id)
			return materiais.at(i);
	}
	cout<<"material "<<id<<" nao encontrado\n";
	system("pause");
	return NULL;
}

Object * SceneLoader::findObject(string id)
{
	for(unsigned int i=0; i<objs.size(); i++)
	{
		if(objs.at(i)->id==id)
			return objs.at(i);
	}
	cout<<"nao foi possivel encontrar o objecto "<<id<<endl;
	system("pause");
	return NULL;
}

bool SceneLoader::aplicaMaterials(Object * o, Material * mat)
{
	Material * mat2;

	if(o->mat_id=="null")
		o->mat=mat;
	else
	{
		mat2=findMaterial(o->mat_id);
		if(mat2==NULL)
			return false;
		o->mat=mat2;
	}

	if(o->type=="compound")
	{
		for(unsigned int i=0; i<o->getObjs()->size(); i++)
		{
			if(!aplicaMaterials(o->getObjs()->at(i), o->mat))
				return false;
		}
	}
	return true;
}

bool SceneLoader::aplicaTextures(Object * o, Texture * tex)
{
	Texture * tex2;

	if(o->tex_id=="null")
		o->tex=tex;
	else if(o->tex_id=="clear")
		o->tex=this->no_tex;
	else
	{
		tex2=findTexture(o->tex_id);
		if(tex2==NULL)
			return false;
		o->tex=tex2;
	}

	if(o->type=="compound")
	{
		for(unsigned int i=0; i<o->getObjs()->size(); i++)
		{
			if(!aplicaTextures(o->getObjs()->at(i), o->tex))
				return false;
		}
	}
	return true;
}

