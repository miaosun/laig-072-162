#include "SceneLoader.h"
#include <iostream>

using namespace std;

///////////exemplo 2 do prof

// Apontadores para os principais grupos
// declarados aqui como globais por conveniencia
// idealmente tudo seria includo numa classe

TiXmlElement* initElement=NULL; 
TiXmlElement* matsElement=NULL;
TiXmlElement* textsElement=NULL;
TiXmlElement* leavesElement=NULL;
TiXmlElement* nodesElement=NULL;
TiXmlElement* graphElement=NULL;

//-------------------------------------------------------

TiXmlElement *findChildByAttribute(TiXmlElement *parent,const char * attr, const char *val)
// Funcao de pesquisa de um n?filho por comparacao de um atributo (normalmente um id) com um valor de referencia
// numa versao mais alto nivel seria utilizada uma expressao XPath
{
	TiXmlElement *child=parent->FirstChildElement();
	int found=0;

	while (child && !found)
		if (child->Attribute(attr) && strcmp(child->Attribute(attr),val)==0)
			found=1;
		else
			child=child->NextSiblingElement();

	return child;
}


//////////////////////////////////////////////////////////////////
void SceneLoader::loadSgx()
{

}

bool SceneLoader::loadGlobals()
{
	global.root = globalsElement->Attribute("root");

	if((globalsElement->QueryIntAttribute("maxlights", &global.maxlights)) == TIXML_SUCCESS &&
	 (globalsElement->QueryIntAttribute("maxmaterials", &global.maxmaterials)) == TIXML_SUCCESS &&
	 (globalsElement->QueryIntAttribute("maxtextures", &global.maxtextures)) == TIXML_SUCCESS &&
	 (globalsElement->QueryIntAttribute("maxobjects", &global.maxobjects)) == TIXML_SUCCESS)
	{
		cout<<"MaxLights:"<<global.maxlights<<", MaxMaterials:"<<global.maxmaterials<<", MaxTextures:"<<global.maxtextures<<", MaxObjects:"<<global.maxobjects<<endl<<"Root: "<<global.root<<endl;
		return true;
	} 
	else
		cout<<"Erro parsing global."<<endl;
	return false;
}

bool SceneLoader::loadView()
{
	

	if((viewElement->QueryFloatAttribute("near", &view.near)) == TIXML_SUCCESS &&
		(viewElement->QueryFloatAttribute("far", &view.far)) == TIXML_SUCCESS &&
		(viewElement->QueryFloatAttribute("axisscale", &view.axisscale)) == TIXML_SUCCESS)
	{
		cout<<"Near:"<<view.near<<", Far:"<<view.far<<", AxisScale:"<<view.axisscale<<endl; 
	} 
	else
	{
		cout<<"Erro parsing frustum."<<endl;
		return false;
	}

	translationElement=viewElement->FirstChildElement("translation");

	if(translationElement!=NULL)
	{
		if(translationElement->QueryFloatAttribute("x", &view.trans.x) == TIXML_SUCCESS &&
			translationElement->QueryFloatAttribute("y", &view.trans.y) == TIXML_SUCCESS &&
			translationElement->QueryFloatAttribute("z", &view.trans.z) == TIXML_SUCCESS)
			cout<<"translation: x:"<<view.trans.x<<" y:"<<view.trans.y<<" z:"<<view.trans.z<<endl;
		else
			cout<<"Erro parsing translation\n";
	}
	else
	{
		cout<<"problema com a translation"<<endl;
		return false;
	}

	rotationElement=viewElement->FirstChildElement("rotation");

	if(rotationElement!=NULL)
	{
		view.rots[0].axis=rotationElement->Attribute("axis");
		if(rotationElement->QueryFloatAttribute("angle", &view.rots[0].angle) != TIXML_SUCCESS)
			return false;
		cout<<"rotacao "<<view.rots[0].axis<<" ang:"<<view.rots[0].angle<<endl;
	}
	else
	{
		cout<<"problema com a rotation de x\n";
		return false;
	}

	rotationElement=rotationElement->NextSiblingElement("rotation");
	
	if(rotationElement!=NULL)
	{
		view.rots[1].axis=rotationElement->Attribute("axis");
		if(rotationElement->QueryFloatAttribute("angle", &view.rots[1].angle) != TIXML_SUCCESS)
			return false;
		cout<<"rotacao "<<view.rots[1].axis<<" ang:"<<view.rots[1].angle<<endl;
	}
	else
	{
		cout<<"problema com a rotation de y\n";
		return false;
	}

	rotationElement=rotationElement->NextSiblingElement("rotation");
	
	if(rotationElement!=NULL)
	{
		view.rots[2].axis=rotationElement->Attribute("axis");
		if(rotationElement->QueryFloatAttribute("angle", &view.rots[2].angle) != TIXML_SUCCESS)
			return false;
		cout<<"rotacao "<<view.rots[2].axis<<" ang:"<<view.rots[2].angle<<endl;
	}
	else
	{
		cout<<"problema com a rotation de z\n";
		return false;
	}

	scaleElement=rotationElement->NextSiblingElement("scale");

	if(scaleElement!=NULL)
	{
		if(scaleElement->QueryFloatAttribute("x", &view.scl.x) != TIXML_SUCCESS)
			return false;
		if(scaleElement->QueryFloatAttribute("y", &view.scl.y) != TIXML_SUCCESS)
			return false;
		if(scaleElement->QueryFloatAttribute("z", &view.scl.z) != TIXML_SUCCESS)
			return false;
		cout<<"scale x:"<<view.scl.x<<" y:"<<view.scl.y<<" z:"<<view.scl.z<<endl;
	}
	else
	{
		cout<<"problema com a scale\n";
		return false;
	}
	
	return true;
}

void SceneLoader::loadIllumination()
{
	if((illuminationElement->QueryDoubleAttribute("doublesided", &illumination.doublesided)) == TIXML_SUCCESS &&
		(illuminationElement->QueryDoubleAttribute("local", &illumination.local) == TIXML_SUCCESS))
		cout<<"Illumination:\n\tDoubleSided: "<<illumination.doublesided<<", Local: "<<illumination.local<<endl;
	else
		cout<<"Erro parsing illumination\n";

	ambientElement = illuminationElement->FirstChildElement("ambient");

	float r, g, b, a;
	if(ambientElement)
	{
		if(ambientElement->QueryFloatAttribute("r", &r) == TIXML_SUCCESS &&
			ambientElement->QueryFloatAttribute("g", &g) == TIXML_SUCCESS &&
			ambientElement->QueryFloatAttribute("b", &b) == TIXML_SUCCESS &&
			ambientElement->QueryFloatAttribute("a", &a) == TIXML_SUCCESS)
			cout<<"\tAmbient R, G, B, A: "<<r<<", "<<g<<", "<<b<<", "<<a<<endl;
		else
			cout<<"Erro parsing ambiente de illumination\n";
	}
	else
		cout<<"problema com ambient de illumination\n";

	backgroundElement = illuminationElement->FirstChildElement("background");
	if(backgroundElement)
	{
		if(backgroundElement->QueryFloatAttribute("r", &r) == TIXML_SUCCESS &&
			backgroundElement->QueryFloatAttribute("g", &g) == TIXML_SUCCESS &&
			backgroundElement->QueryFloatAttribute("b", &b) == TIXML_SUCCESS &&
			backgroundElement->QueryFloatAttribute("a", &a) == TIXML_SUCCESS)
			cout<<"\tAmbient R, G, B, A: "<<r<<", "<<g<<", "<<b<<", "<<a<<endl;
		else
			cout<<"Erro parsing ambiente de illumination\n";
	}

	TiXmlElement *child=lightsElement->FirstChildElement();

	int nLights = 0;
	while(child)
	{
		if(nLights == global.maxlights)
			cout<<"Ja chegou limite de maxLights\n";
		else if(strcmp(child->Value(), "light") == 0)
			loadLight();
		else
			cout<<"Erro parsing light de lights de illumination\n";

		child = child->NextSiblingElement();
		nLights++;

	}
}

void SceneLoader::loadTexture()
{
	string id = texturesElement->Attribute("id");
	const string file = texturesElement->Attribute("file");
	float length_s, length_t;
	if(texturesElement->QueryFloatAttribute("length_s", &length_s) == TIXML_SUCCESS &&
		texturesElement->QueryFloatAttribute("length_t", &length_t) == TIXML_SUCCESS)
	{
		Texture* tex = new Texture(id, file, length_s, length_t);
		textures.push_back(tex);

		cout<<"Texture ID: "<<id<<", File: "<<file<<", Length_s: "<<length_s<<", Length_t: "<<length_t<<endl;
	}
	else
		cout<<"Erro parsing texture: "<<id<<endl;
}


void SceneLoader::loadMaterial()
{
	string id = materialsElement->Attribute("id");
	float r, g, b, a, shininess;

	Material* mat = new Material(id);
	materiais.push_back(mat);

	cout<<"Material ID: "<<id<<endl;

	TiXmlElement* child = materialsElement->FirstChildElement();
	while(child)
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
				cout<<"Emission R, G, B, A: "<<r<<", "<<g<<", "<<b<<", "<<a<<endl;
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
				cout<<"Material Ambient R, G, B, A: "<<r<<", "<<g<<", "<<b<<", "<<a<<endl;
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
				cout<<"Material Diffuse R, G, B, A: "<<r<<", "<<g<<", "<<b<<", "<<a<<endl;
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
				cout<<"Material Specular R, G, B, A: "<<r<<", "<<g<<", "<<b<<", "<<a<<endl;
			} 
		}
		else if(strcmp(child->Value(), "shininess")==0)
		{
			if(child->QueryFloatAttribute("shininess", &shininess))
			{
				materiais.back()->shininess[0] = shininess;
				cout<<"Material Shininess: "<<shininess<<endl;
			}
		}
		else
			cout<<"Erro parsing material"<<endl;
		child=child->NextSiblingElement();

	}
}

void SceneLoader::loadLight()
{
	string id = lightsElement->Attribute("id");
	string enabled_s = lightsElement->Attribute("enabled");
	int enabled;
	if(enabled_s == "1")
		enabled = 1;
	else
		enabled = 0;
	float r, g, b, a, x, y, z, w;

	Light* light = new Light(id, enabled);
	lights.push_back(light);

	cout<<"Light ID: "<<id<<", Enabled: ";
	if(enabled==1)
		cout<<"Sim"<<endl;
	else
		cout<<"Nao"<<endl;

	TiXmlElement* child = lightsElement->FirstChildElement();
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
				cout<<"Light Ambient R, G, B, A: "<<r<<", "<<g<<", "<<b<<", "<<a<<endl;
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
				cout<<"Light Diffuse R, G, B, A: "<<r<<", "<<g<<", "<<b<<", "<<a<<endl;
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
				cout<<"Light Specular R, G, B, A: "<<r<<", "<<g<<", "<<b<<", "<<a<<endl;
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
				cout<<"Light Position X, Y, Z, W: "<<x<<", "<<y<<", "<<z<<", "<<w<<endl;
			} 
		}
		else
			cout<<"Erro parsing light"<<endl;
		child=child->NextSiblingElement();
	}
}
/////////////////////////////////////////////////




//-------------------------------------------------------

void processGraphNode(TiXmlElement *parent, int nivel)
// funcao recursiva de processamento do grafo
// ao encontrar um n? aplica as definicoes declaradas e itera sobre os seus descendentes
// nota: se um n?A, declarado em 'Nodes' aparecer instanciado uma vez no grafo com descendentes B e C
// e posteriormente o n?A for novamente instanciado, a relacao de descendencia com B e C nao ?impleita.
// Neste modelo o n??s?uma transformacao geometrica ou de atributos, nao uma definicao de um sub-grafo 
// com varios na que pode ser reinstanciado
{
	TiXmlElement *child=parent->FirstChildElement();

	// cria um prefixo de espacos para indentacao, apenas para visualizacao
	int prefixLen=nivel*2;
	char prefix[100];
	memset(prefix,' ',prefixLen);
	prefix[prefixLen]=0;

	while (child)
	{
		if (strcmp(child->Value(),"Node")==0)
		{
			// ?um n?
			printf("%s Nodo do tipo '%s' com id '%s'\n",prefix, child->Value(), child->Attribute("id"));
			// acede aos dados do n?e aplica materiais, texturas, transformacoes
			// para aceder ao n? existiriam varias alternativas
			// aqui implementa-se uma pesquisa beica
			TiXmlElement *node=findChildByAttribute(nodesElement,"id",child->Attribute("id"));

			if (node)
			{
				printf("%s     - Material id: '%s' \n", prefix, node->FirstChildElement("material")->Attribute("id"));
				printf("%s     - Texture id: '%s' \n", prefix, node->FirstChildElement("texture")->Attribute("id"));

				// repetir para outros detalhes do n?
			}


			// processa recursivamente os seus descendentes
			processGraphNode(child,nivel+1);
		}
		if (strcmp(child->Value(),"Leaf")==0)
		{
			// ?folha
			printf("%s Folha do tipo '%s' com id '%s'\n",prefix, child->Value(), child->Attribute("id"));

			// acede aos dados declarados na seccao Leaves
			TiXmlElement *leaf=findChildByAttribute(leavesElement,"id",child->Attribute("id"));

			if (leaf)
			{
				printf("%s     - tipo de folha: '%s' \n", prefix, leaf->Attribute("type"));
				// repetir para outros detalhes do n?
			}
			
			
			// e faz o render propriamente dito de acordo com o tipo de primitiva
			
		}

		child=child->NextSiblingElement();
	}

}

void loadScene_exemplo2(void)
{

	// Read string from file

	TiXmlDocument doc( "cena.xml" );
	bool loadOkay = doc.LoadFile();

	if ( !loadOkay )
	{
		printf( "Could not load test file 'demotest.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc() );
		exit( 1 );
	}

	initElement = doc.FirstChildElement( "Init" );
	matsElement = doc.FirstChildElement( "Materials" );
	textsElement =  doc.FirstChildElement( "Textures" );
	leavesElement =  doc.FirstChildElement( "Leaves" );
	nodesElement =  doc.FirstChildElement( "Nodes" );

	graphElement =  doc.FirstChildElement( "Graph" );


	// Inicializacao
	// Um exemplo de um conjunto de na bem conhecidos e obrigatorios

	if (initElement == NULL)
		printf("Bloco Init não encontrado\n");
	else
	{
		printf("Processing init:\n");
		// frustum: exemplo para n?com parametros individuais
		TiXmlElement* frustumElement=initElement->FirstChildElement("frustum");
		if (frustumElement)
		{
			float near,far;

			if (frustumElement->QueryFloatAttribute("near",&near)==TIXML_SUCCESS && 
				frustumElement->QueryFloatAttribute("far",&far)==TIXML_SUCCESS
				)
				printf("  frustum attributes: %f %f\n", near, far);
			else
				printf("Error parsing frustum\n");
		}
		else
			printf("frustum not found\n");


		// translate: exemplo para um n?com um parifetro que aglutina varios floats
		TiXmlElement* translateElement=initElement->FirstChildElement("translate");
		if (translateElement)
		{
			char *valString=NULL;
			float x,y,z;

			valString=(char *) translateElement->Attribute("xyz");

			if(valString && sscanf(valString,"%f %f %f",&x, &y, &z)==3)
			{
				printf("  translate values (XYZ): %f %f %f\n", x, y, z);
			}
			else
				printf("Error parsing translate");
		}
		else
			printf("translate not found\n");		

		// repetir para cada uma das variaveis
	}

	// Validacao dos outros grupos seria feita aqui


	// render graph
	// iteracao recursiva
	processGraphNode(graphElement,0);

}




/////////////exempo 3 do prof


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
	sgxElement = doc.FirstChildElement( "sgx" );
	globalsElement = sgxElement->FirstChildElement( "globals" );
	viewElement = sgxElement->FirstChildElement( "view" );
	illuminationElement = sgxElement->FirstChildElement("illumination");

	pointsElement = doc.FirstChildElement( "Points" );
	polygonsElement = doc.FirstChildElement( "Polygons" );

	// Inicialização
	// Um exemplo de um conjunto de nós bem conhecidos e obrigatórios

	if(sgxElement == NULL) {
		cout << "Bloco sgx nao encontrado\n";
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
		return false;
	}

	if(illuminationElement != NULL)
		loadIllumination();
	else
	{
		cout<<"Bloco illumination nao econtrado\n";
		return false;
	}

	/*else if (pointsElement == NULL) {
		cout << "Bloco Points nao encontrado\n";
	}
	else if(polygonsElement == NULL) {
		cout << "Bloco Polygons nao encontrado\n";

	}*/
	return true;
}

//Carregar os pontos
void SceneLoader::loadPoints() {

	//Percorrer todos os elementos Point dentro do grupo Points do XML
	for(TiXmlElement *child(pointsElement->FirstChildElement()); child != NULL; child = child->NextSiblingElement())
	{
		const string name(child->Value());

		//Este bloco so pode conter tag's "Point"
		if(name == "Point") {

			point point_coord;
			
			//Ler o id do point
			const string point_name(child->Attribute("id"));

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