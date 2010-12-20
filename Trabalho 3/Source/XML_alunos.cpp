#include "SceneLoader.h"
//#include "Variaveis.h"
//#include "Picking.h"
//#include <winsock2.h>



using namespace std;

// dimensoes e localizacao da janela
#define DIMX 500
#define DIMY 500
#define INITIALPOS_X 200
#define INITIALPOS_Y 200

#define BUFSIZE 512
#define cube 1
float dim_cube=3.75;
float dim_Casa=4.0;
float alturaTab=4.5;

struct g_mouseState{
	bool leftButton;
	bool rightButton;
	bool middleButton;
	int x;
	int y;
} MouseState;

int window_w = DIMX;
int window_h = DIMY;
GLuint selectBuf[BUFSIZE];

#define LIGHT_ID 100

float xy_aspect;

// matriz de transf. geometrica utilizada pelo botao esferico
float view_rotate[16] =	{ 1,0,0,0,
						  0,1,0,0,
						  0,0,1,0,
						  0,0,0,1 };

// vector de posicao utilizado pelo botao de afastamento
float obj_pos[] = { 0.0, 0.0, 0.0 };
	
// declaracoes para o plano e caixa
float mat1_shininess[] = {128.0}; 

//float mat1_specular[] = {1.0,1.0,1.0};	/* specular reflection. */
float mat1_specular[] = {0.4, 0.4, 0.4, 1.0};	/* specular reflection. */
//float mat1_diffuse[] =  {0.0, 0.0, 0.0, 1.0};	/* diffuse reflection. */
float mat1_diffuse[] =  {0.6, 0.6, 0.6, 1.0};	/* diffuse reflection. */
float mat1_ambient[] =  {0.6, 0.6, 0.6, 1.0};	/* ambient reflection. */
double dimx= 6.0;
double dimy= 2.0;
double dimz=10.0;

float light0_kc=0.0;
float light0_kl=0.0;
float light0_kq=0.1;

GLUquadric* glQ;

// declarações para as stripes que formam o plano
double i,j;
double di, limi=dimx, divisoes_i = 60;	//60
double dj, limj=dimz, divisoes_j = 100;	//100

// declarações para a fonte de luz LIGHT0;
float light0_position[]  = {0.0, 3.0, 4.0, 1.0}; // nao necessaria...
float light0_ambient[] =   {0.0, 0.0, 0.0, 1.0}; // sem componente ambiente
//float light0_diffuse[] =   {1.0, 1.0, 0.0, 0.0};
float light0_diffuse[] =   {0.8, 0.8, 0.8, 1.0};
//float light0_specular[] =  {0.0, 0.0, 0.0, 0.0};
float light0_specular[] =  {0.8, 0.8, 0.8, 1.0};
double light0x = dimx/2.0;
double light0y = 1;
double light0z = dimz/4.0;
double symb_light0_radius = 1.2;	// esfera que
int symb_light0_slices = 8;			// simboliza a
int symb_light0_stacks =16;			// fonte de luz light0

// fonte (global) de luz ambiente 
//float light_ambient[] = {0.0, 0.0, 0.0, 1.0}; /* Set the background ambient lighting. */
float light_ambient[] = {0.2, 0.2, 0.2, 1.0}; /* Set the background ambient lighting. */

// variaveis para a janela
int main_window;
GLUI  *glui2;

// declarações para animacao
unsigned int mili_secs = 10;
#define RADIUS_SPEED  0.4  // unidades de comprimento por segundo
#define ANGULAR_SPEED 0.5  // rotacoes por segundo

typedef struct anim_data{
	double yi,yf,dy,y,dty,xi,xf,dx,x,dtx,zi,zf,dz,z,dtz;
	bool sobe, enabled, corre;
};

anim_data peca_anim;
anim_data move_anim;
bool peca_sel;
#define MOVE_ID 150 
#define SELECT_ID 151

RGBpixmap pixmap;


vector<SceneLoader *> cenas;
int cena_actual;

Jogo * jogo;


bool loadCenas(string filename)
{
	SceneLoader * cena;
	stringstream ss;
	unsigned int size;
	string linha;
	vector<string> v;
	ifstream myfile (filename.c_str());
	if(myfile.is_open())
	{
		getline(myfile, linha);
		ss<<linha;
		ss>>size;//primeira linha com numero de .sgx
		
		if(size>0)
		{
			for(unsigned int i=0; i<size; i++)
			{
				getline(myfile, linha);
				cena=new SceneLoader(linha.c_str());
				cenas.push_back(cena);
			}
			cout<<endl<<endl<<"Cenas importadas com sucesso!"<<endl<<endl;
		}
		else
		{
			cout<<"\nFicheiro de configuracao num formato desconhecido!\n";
			return false;
		}
		myfile.close();
		return true;
	}
	else
	{
		cout<<"Nao foi possivel abrir o ficheiro de configuracao "<<filename<<"!"<<endl<<endl;
	}
	return false;
}

void open_textures()
{
	char* fname;

	for(unsigned int i=0; i<cenas.at(cena_actual)->textures.size(); i++)
	{
		fname = const_cast<char*> (cenas.at(cena_actual)->textures[i]->file.c_str());
		pixmap.readBMPFile(fname);
		pixmap.setTexture(i+1);
		cenas.at(cena_actual)->textures[i]->n_texture = i+1;
	}
}

void drawScene(GLenum mode)
{
	//glFrustum( -xy_aspect*.04, xy_aspect*.04, -.04, .04, cenas.at(cena_actual)->view.near, cenas.at(cena_actual)->view.far);
	glFrustum( -xy_aspect*cenas.at(cena_actual)->view.axisscale, xy_aspect*cenas.at(cena_actual)->view.axisscale, -cenas.at(cena_actual)->view.axisscale, cenas.at(cena_actual)->view.axisscale, cenas.at(cena_actual)->view.near, cenas.at(cena_actual)->view.far);
	
	//inicializacoes da matriz de transformacoes geometricas
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();


	//glTranslatef( obj_pos[0], obj_pos[1], -obj_pos[2] );    
	glTranslatef( cenas.at(cena_actual)->view.trans.at(0)->getX(), cenas.at(cena_actual)->view.trans.at(0)->getY(), -obj_pos[2]+cenas.at(cena_actual)->view.trans.at(0)->getZ() );    

	// roda a cena para ficar em perspectiva
	//glRotated(20.0, 1.0,0.0,0.0 );		// 20 graus em torno de X
	//glRotated(-45.0, 0.0,1.0,0.0 );		//-45 graus em torno de Y

	for(unsigned int i=1; i<cenas.at(cena_actual)->view.trans.size(); i++)
		cenas.at(cena_actual)->view.trans.at(i)->apply();

	// aplica efeito do botao de rotacao
	glMultMatrixf( view_rotate );

	cenas.at(cena_actual)->root_object->draw();
	jogo->draw();
	//myCube(10);
	//sensores();

	if(mode==GL_SELECT)
		sensores();

}

void sinalisa_casa()
{
	glColor3f(0.0,1.0,0.0);		// cor vermelho
	glPushMatrix();
	glTranslated(0.0, 4.5, 0.0);
	glRotated(-90, 1.0, 0.0, 0.0); 
	glRectd(-dim_Casa/2, -dim_Casa/2, dim_Casa/2, dim_Casa/2);
	//gluSphere(glQ, symb_light0_radius, symb_light0_slices, symb_light0_stacks);
	glPopMatrix();
}


void display(void)
{
	// ****** declaracoes internas 'a funcao display() ******

	//GLUquadric* glQ;	// nec. p/ criar sup. quadraticas (cilindros, esferas...)

	// ****** fim de todas as declaracoes da funcao display() ******

	glQ = gluNewQuadric();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
	// inicializacoes da matriz de visualizacao
	
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	drawScene(GL_RENDER);

	// permissao de atribuicao directa de cores
	// para objectos ue nao tem material atribuido
	//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	// Actualizacao da posicao da fonte de luz
	for(unsigned int i=0; i<cenas.at(cena_actual)->lights.size(); i++)
	{
		// esferas que simboliza as fontes d luzes

		glLightfv(GL_LIGHT0+i, GL_POSITION, cenas.at(cena_actual)->lights[i]->position);

		glColor3f(1.0,1.0,0.0);		// cor amarela
		gluQuadricOrientation( glQ, GLU_INSIDE);
		glPushMatrix();
		glTranslated(cenas.at(cena_actual)->lights[i]->position[0],cenas.at(cena_actual)->lights[i]->position[1],cenas.at(cena_actual)->lights[i]->position[2]);
		gluSphere(glQ, symb_light0_radius, symb_light0_slices, symb_light0_stacks);
		glPopMatrix();

		gluQuadricOrientation(glQ, GLU_OUTSIDE);
	}

	// inibicao de atribuicao directa de cores
	glDisable(GL_COLOR_MATERIAL);

	show_jogador(jogo->Jactual);

	// define caracteristicas de cor do material do plano e da caixa
	/*glMaterialfv(GL_FRONT, GL_SHININESS, mat1_shininess);
	glMaterialfv(GL_FRONT, GL_SPECULAR,  mat1_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat1_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT,   mat1_ambient);*/

	// swapping the buffers causes the rendering above to be shown
	glutSwapBuffers();
   
	glFlush();
}

/* Mouse handling */
void processMouse(int button, int state, int x, int y)
{
	GLint hits;
	GLint viewport[4];

	//update our button state
	if (button == GLUT_LEFT_BUTTON)
	{
		if(state == GLUT_DOWN)
			MouseState.leftButton = true;
		else
			MouseState.leftButton = false;
	}

	if (button == GLUT_RIGHT_BUTTON)
	{	
		if(state == GLUT_DOWN)
			MouseState.rightButton = true;
		else
			MouseState.rightButton = false;
	}

	if(button == GLUT_MIDDLE_BUTTON)
	{
		if(state == GLUT_MIDDLE_BUTTON)
			MouseState.middleButton = true;
		else
			MouseState.middleButton = false;
	}
	
	// update our position so we know a delta when the mouse is moved
	MouseState.x = x;
	MouseState.y = y;
	
	if (MouseState.leftButton && !MouseState.rightButton && !MouseState.middleButton) {
		// obrigatorio para o picking 
		// obter o viewport actual
		glGetIntegerv(GL_VIEWPORT, viewport);

		glSelectBuffer (BUFSIZE, selectBuf);
		glRenderMode (GL_SELECT);

		// inicia processo de picking
		glInitNames();
		glMatrixMode (GL_PROJECTION);
		glPushMatrix ();

		//  cria uma região de 5x5 pixels em torno do click do rato para o processo de picking
		glLoadIdentity ();
		gluPickMatrix ((GLdouble) x, (GLdouble) (window_h - y), 1.0, 1.0, viewport);

		//tabuleiro(3.96, 3.96, GL_SELECT);
		//funcPicking(GL_SELECT);
		drawScene(GL_SELECT);

		glMatrixMode (GL_PROJECTION);
		glPopMatrix ();
		glFlush ();

		hits = glRenderMode(GL_RENDER);
		//cout<<"hits "<<hits<<"\n";
		processHits(hits, selectBuf);
	}

	//glutPostRedisplay();
	
}

void processMouseMoved(int x, int y)
{
	
	// pedido de refrescamento da janela
	//glutPostRedisplay();				

}

void processPassiveMouseMoved(int x, int y)
{

	// pedido de refrescamento da janela
	glutPostRedisplay();				
}

void reshape(int w, int h)
{
	int tx, ty, tw, th;

	window_w = w;	//variaveis globais; window_h e' usado em processMouse()
	window_h = h;

	GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
	glViewport( tx, ty, tw, th );
	xy_aspect = (float)tw / (float)th;

	glutPostRedisplay();

}


void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
	  case 'q':
		light0y+= 0.1;
		cout << "light0y: " << light0y << endl; 
		break;
	  case 'a':
		light0y-= 0.1;
		cout << "light0y: " << light0y << endl; 
		break;
	  case 'i':
		light0_kc+=0.1;
		cout << "light0_kc: " << light0_kc << endl; 
		break;
	  case 'o':
		light0_kc-=0.1;
		cout << "light0_kc: " << light0_kc << endl; 
		break;
	  case 'k':
		light0_kl+=0.1;
		cout << "light0_kl: " << light0_kl << endl; 
		break;
	  case 'l':
		light0_kl-=0.1;
		cout << "light0_kl: " << light0_kl << endl; 
		break;
	  case 'n':
		light0_kq+=0.1;
		cout << "light0_kq: " << light0_kq << endl; 
		break;
	  case 'm':
		light0_kq-=0.1;
		cout << "light0_kq: " << light0_kq << endl; 
		break;
	  case 'z':
		divisoes_i+=3;
		cout << "div_i: " << divisoes_i <<endl;
		break;
	  case 'x':
		divisoes_i-=3;
		cout << "div_i: " << divisoes_i <<endl;
		break;
	  case 'c':
		divisoes_j+=5;
		cout << "div_j: " << divisoes_j <<endl;
		break;
	  case 'v':
		divisoes_j-=5;
		cout << "div_j: " << divisoes_j <<endl;
		break;

      case 27:		// tecla de escape termina o programa
         exit(0);
         break;
   }
}


void myGlutIdle( void )
{
  /* According to the GLUT specification, the current window is 
     undefined during an idle callback.  So we need to explicitly change
     it if necessary */
  if ( glutGetWindow() != main_window ) 
    glutSetWindow(main_window);  


  glutPostRedisplay();

  /****************************************************************/
  /*            This demonstrates GLUI::sync_live()               */
  /*   We change the value of a variable that is 'live' to some   */
  /*   control.  We then call sync_live, and the control          */
  /*   associated with that variable is automatically updated     */
  /*   with the new value.  This frees the programmer from having */
  /*   to always remember which variables are used by controls -  */
  /*   simply change whatever variables are necessary, then sync  */
  /*   the live ones all at once with a single call to sync_live  */
  /****************************************************************/

//  glui->sync_live();

}

void inicializacao()
{

	glFrontFace(GL_CCW);		/* Front faces defined using a counterclockwise rotation. */
	glDepthFunc(GL_LEQUAL);		/* Por defeito e GL_LESS */
	glEnable(GL_DEPTH_TEST);	/* Use a depth (z) buffer to draw only visible objects. */
	glEnable(GL_CULL_FACE);		/* Use face culling to improve speed. */
	glCullFace(GL_BACK);		/* Cull only back faces. */

	// por defeito a cor e de fundo e o preto
	glClearColor(cenas.at(cena_actual)->illumination.backgroud[0],cenas.at(cena_actual)->illumination.backgroud[1],cenas.at(cena_actual)->illumination.backgroud[2],cenas.at(cena_actual)->illumination.backgroud[3]);

	glLightModelf (GL_LIGHT_MODEL_TWO_SIDE, cenas.at(cena_actual)->illumination.doublesided);
	glLightModeli (GL_LIGHT_MODEL_LOCAL_VIEWER, cenas.at(cena_actual)->illumination.local);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, cenas.at(cena_actual)->illumination.ambient);  // define luz ambiente
	
	glEnable(GL_LIGHTING);
	for(unsigned int i=0; i<cenas.at(cena_actual)->lights.size(); i++)
	{
		// parametros de iluminacao
		glLightfv(GL_LIGHT0+i, GL_AMBIENT, cenas.at(cena_actual)->lights[i]->ambient);
		glLightfv(GL_LIGHT0+i, GL_DIFFUSE, cenas.at(cena_actual)->lights[i]->diffuse);
		glLightfv(GL_LIGHT0+i, GL_SPECULAR, cenas.at(cena_actual)->lights[i]->specular);

		//glLightfv(GL_LIGHT0+i, GL_POSITION, cenas.at(cena_actual)->lights[i]->position);

		if(cenas.at(cena_actual)->lights[i]->enabled)
			glEnable(GL_LIGHT0+i);
	}

	// a direccao e a posicao estao na rotina display()
	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90.0);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	//glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	open_textures();

	glShadeModel(GL_SMOOTH);				// GL_FLAT / GL_SMOOTH

	//glPolygonMode(GL_FRONT, GL_FILL);	// preence a face da frente dos poligonos
	//glPolygonMode(GL_FRONT, GL_LINE);	// desenha arestas dos poligonos

	glNewList(cube, GL_COMPILE);
		glPushMatrix();
		myCube(dim_cube);
		glPopMatrix();
	glEndList();

}

void ctr_light(int control)//funcao que liga e desliga as luzes em funcao dos checkboxes
{
	for(int i = 0; i < cenas.at(cena_actual)->lights.size(); i++)
	{
		if ( control == LIGHT_ID+i)
		{
			if ( !cenas.at(cena_actual)->lights[i]->enabled )
			{
				glEnable( GL_LIGHT0+i );
				cenas.at(cena_actual)->lights[i]->enabled = true;
			}
			else 
			{
				glDisable( GL_LIGHT0 +i); 
				cenas.at(cena_actual)->lights[i]->enabled = false;
			}
		}
	}
}

void ctr_camara(int control)
{
	if(control == 1)
	{
		gluLookAt(225.0, 500.0, -150.0, 225.0, 0.0, -150.0, 0.0, 0.0, -10.0);
	}
	
	if(control == 2)
	{
		gluLookAt(225.0, 250.0, -150.0, 225.0, 0.0, -150.0, 0.0, 0.0, -10.0);
	}
	
	if(control == 3)
	{
		gluLookAt(225.0, 180.0, 120.0, 225.0, 100.0, 300.0, 0.0, 1.0, 0.0);
	}
}


#include <winsock2.h>

SOCKET sock;
#define getCurrentTime GetTickCount

bool socketConnect() // Initialize Winsock.
{
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != NO_ERROR)
		printf("Client: Error at WSAStartup().\n");
    else
        printf("Client: WSAStartup() is OK.\n");

	// Create a socket.
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        printf("Client: socket() - Error at socket(): %ld\n", WSAGetLastError());
        WSACleanup();
        return false;
    }
	else
       printf("Client: socket() is OK.\n");

    // Connect to a server.
    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    // Just test using the localhost, you can try other IP address
    clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
    clientService.sin_port = htons(60070);

    if (connect(sock, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
        printf("Client: connect() - Failed to connect.\n");
        WSACleanup();
        return false;
    }
    else {
       printf("Client: connect() is OK.\n");
       printf("Client: Can start sending and receiving data...\n");
    }

    // Send and receive data.
	printf("Connected\n");
	return true;
}

void envia(char *s, int len) {
	int bytesSent = send(sock, s, len, 0);
	if(bytesSent == SOCKET_ERROR)
	{
		printf("Client: send() error %ld.\n", WSAGetLastError());
		throw ExcepcaoSocket();
	}
	cout<<s;
}

void recebe(char *ans) {
	int bytesRecv = SOCKET_ERROR;
	int pos = 0;
	while (true) {
		recv(sock, &ans[pos], 1, 0);
		if (ans[pos] == '\n')
			break;
		pos++;
	}
	ans[pos] = 0;
	cout << "prolog answered: " << ans << endl;
}

void quit() {
	cout << "Asking prolog to quit" << endl;
	char buff[] = "quit.\n";
	envia(buff, 6);
	char ans[128];
	recebe(ans);
}

void sock_end(int control)
{
	if(control==0)
		quit();
}

void undo(int control)
{
	bool actualiza=false;
	if(control==0 && !jogo->hist.empty())
	{
		jogo->sinal.clear();
		switch(jogo->fase)
		{
		case 0:
			jogo->tab=jogo->hist.back();
			jogo->hist.pop_back();
			if(jogo->Jactual==0)
				jogo->pecas_v.push_back(2);
			else
				jogo->pecas_al.push_back(1);
			actualiza=true;
			break;
		case 1:
			jogo->tab=jogo->hist.back();
			jogo->hist.pop_back();
			if(jogo->Jactual==0)
			{
				if(jogo->pecas_al.size()==6)
				{
					jogo->pecas_v.push_back(3);
					jogo->fase--;
					actualiza=true;
				}
			}
			else
			{
				jogo->pecas_al.push_back(1);
				actualiza=true;
			}
			break;
		case 2:
			jogo->tab=jogo->hist.back();
			jogo->hist.pop_back();
			break;
		}
		if(jogo->Jactual==0)
			jogo->Jactual=1;
		else
			jogo->Jactual=0;
		if(actualiza)
			jogo->procura_sinal(0);
	}
}

int main(int argc, char* argv[])
{
	cena_actual=0;

	Object * vampiro;
	Object * aldeao;
	Object * nosferatu;

	try
	{
		if(!loadCenas("config.dll"))
		{
			cout<<"problema a fazer load das cenas\n";
			system("pause");
			return 0;
		}
	}
	catch (Excepcao e)
	{
		cout<<"ficheiro de cena inexistente!\n";
		system("pause");
		return 0;
	}


	if(!cenas.at(cena_actual)->loadScene())
	{
		cout<<"nao fez load correctamente!\n";
		system("pause");
		return 0;
	}

	vampiro=cenas.at(cena_actual)->findObject("_vampiro");
	aldeao=cenas.at(cena_actual)->findObject("_aldeao");
	nosferatu=cenas.at(cena_actual)->findObject("_nosferatu");
	if(aldeao==NULL || vampiro==NULL || nosferatu==NULL)
	{
		cout<<"o conjunto de 3 pecas de jogo tem que ser definido!\n";
		system("pause");
		return false;
	}

	try
	{
		jogo=new Jogo(vampiro, aldeao, nosferatu, 0, 0);
	}
	catch (ExcepcaoSocket e)
	{
		cout<<"erro na abertura da socket \n";
		system("pause");
		return 0;
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize (DIMX, DIMY);
	glutInitWindowPosition (INITIALPOS_X, INITIALPOS_Y);
	main_window = glutCreateWindow (argv[0]);
 
   glutDisplayFunc(display);
   GLUI_Master.set_glutReshapeFunc(reshape);
   GLUI_Master.set_glutKeyboardFunc (keyboard);
   GLUI_Master.set_glutMouseFunc(processMouse);
   glutMotionFunc(processMouseMoved);
   glutPassiveMotionFunc(processPassiveMouseMoved);   
   GLUI_Master.set_glutSpecialFunc( NULL );

   glutTimerFunc(mili_secs, anim, 0);

	/*** Create the bottom subwindow ***/
	glui2 = GLUI_Master.create_glui_subwindow( main_window, GLUI_SUBWINDOW_BOTTOM );
	glui2->set_main_gfx_window( main_window );

	GLUI_Rotation *view_rot = glui2->add_rotation( "Rotacao", view_rotate );
	view_rot->set_spin( 1.0 );
	glui2->add_column( false );

	GLUI_Translation *trans_z = 
	glui2->add_translation( "Zoom", GLUI_TRANSLATION_Z, &obj_pos[2] );
	trans_z->set_speed( .02 );

	/////////list box para diferentes cenas
	glui2->add_column(true);
	GLUI_Listbox *cena;
	cena = glui2->add_listbox("escolhe cena: ");
	cena->add_item(1, "cena 1");
	cena->add_item(2, "cena 2");


	/////para desligar as sockets
	glui2->add_button("QuitSock", 0, sock_end);
	glui2->add_button("Undo", 0, undo);


	////////camaras
	glui2->add_column(false);
	GLUI_Panel *panel;
	panel = glui2->add_panel("Camaras");
	GLUI_RadioGroup *rb;
	rb = glui2->add_radiogroup_to_panel(panel, NULL, -1, ctr_camara);
	glui2->add_radiobutton_to_group(rb, "Camara 1");
	glui2->add_radiobutton_to_group(rb, "Camara 2");
	glui2->add_radiobutton_to_group(rb, "Camara 3");

	////////////////////////////////////////////////////////////////////////////////////////////////////
	//As fontes de luz devem poder ser alteradas por meio de controlos na r¨¦gua inferior de comandos.//
	////////////////////////////////////////////////////////////////////////////////////////////////////

	glui2->add_column(true);

	vector<int> light_enabled;
	for(int i = 0; i < cenas.at(cena_actual)->lights.size(); i++)
	{
		light_enabled.push_back(cenas.at(cena_actual)->lights[i]->enabled);
		glui2->add_checkbox(const_cast<char*> (cenas.at(cena_actual)->lights[i]->id.c_str()), &light_enabled[i],
				LIGHT_ID+i, ctr_light );
	}

	/* We register the idle callback with GLUI, not with GLUT */
	GLUI_Master.set_glutIdleFunc( myGlutIdle );
    
	inicializacao();
   
	glutMainLoop();

	return 0;
}


Jogo::Jogo(Object * vampiro, Object * aldeao, Object * nosferatu, int j1, int j2)
{
	this->vampiro=vampiro;
	this->aldeao=aldeao;
	this->nosferatu=nosferatu;
	this->jogadores.push_back(j1);
	this->jogadores.push_back(j2);
	for(unsigned int i=0; i<49; i++)
	{
		if(i<2||i==5||i==6||i==7||i==13||i==35||i==41||i==42||i==43||i>46)
			this->tab.push_back(9);
		else
			this->tab.push_back(0);
	}
	for(unsigned int i=0; i<12; i++)
		this->pecas_al.push_back(1);

	this->pecas_v.push_back(3);
	for(unsigned int i=0; i<5; i++)
		this->pecas_v.push_back(2);
	this->Jactual=0;
	this->fase=0;
	this->casa_sel=-1;
	move_anim.enabled=false;

	//iniciar variaveis da animacao

	if(!socketConnect())
		throw ExcepcaoSocket();

	this->procura_sinal(0);
}

void show_jogador(int jactual)
{
	//letras de identificacao do jogador
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);	
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluOrtho2D( 0.0, DIMX, 0.0, DIMY);
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glColor3f(1.0,1.0,0.0);	//amarelo
	glRasterPos2i(3, DIMY-25);

	switch(jactual)
	{
	case 0:
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'V');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'z');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'd');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 's');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'A');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'l');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'd');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 's');
		break;

	case 1:
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'V');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'z');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'd');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 's');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'V');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'm');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'p');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 's');
		break;
	}

	glDisable(GL_COLOR_MATERIAL);
}

void Jogo::posicao(bool tabuleiro, int pos)//a partir da origem
{
	int linha=pos/7;
	int coluna= pos%7;

	if(tabuleiro)
		glTranslated(-3*dim_Casa+coluna*dim_Casa, alturaTab+2.0, -3*dim_Casa+linha*dim_Casa);
	else
	{
		if(pos<3)
			glTranslated(-4*dim_Casa+pos*dim_Casa, alturaTab, -3*dim_Casa);
		else if(pos>12&&pos<16)
			glTranslated(2*dim_Casa+(pos-13)*dim_Casa, alturaTab, -3*dim_Casa);
		else if(pos==3||pos==4)
			glTranslated(-4*dim_Casa+(pos-3)*dim_Casa, alturaTab, -2*dim_Casa);
		else if(pos==16||pos==17)
			glTranslated(3*dim_Casa+(pos-16)*dim_Casa, alturaTab, -2*dim_Casa);
		else if(pos==5)
			glTranslated(-4*dim_Casa, alturaTab, -dim_Casa);
		else if(pos==18)
			glTranslated(4*dim_Casa, alturaTab, -dim_Casa);
		else if(pos==6)
			glTranslated(-4*dim_Casa, alturaTab, 0.0);
		else if(pos==19)
			glTranslated(4*dim_Casa, alturaTab, 0.0);
		else if(pos==7)
			glTranslated(-4*dim_Casa, alturaTab, dim_Casa);
		else if(pos==20)
			glTranslated(4*dim_Casa, alturaTab, dim_Casa);
		else if(pos==8||pos==9)
			glTranslated(-4*dim_Casa+(pos-8)*dim_Casa, alturaTab, 2*dim_Casa);
		else if(pos==21||pos==22)
			glTranslated(3*dim_Casa+(pos-21)*dim_Casa, alturaTab, 2*dim_Casa);
		else if(pos>9&&pos<13)
			glTranslated(-4*dim_Casa+(pos-10)*dim_Casa, alturaTab, 3*dim_Casa);
		else if(pos>22)
			glTranslated(2*dim_Casa+(pos-23)*dim_Casa, alturaTab, 3*dim_Casa);
	}
}

void peca_anim_init()
{
	peca_anim.yi=0;
	peca_anim.y=peca_anim.yi;
	peca_anim.yf=5.0;
	peca_anim.dty=1.0;
	peca_anim.sobe=true;
	peca_anim.dy=(peca_anim.yf-peca_anim.yi)/((1000.0*peca_anim.dty)/mili_secs);
}

void move_anim_init(int casa)
{
	int linha_i=jogo->casa_sel/7;
	int coluna_i=jogo->casa_sel%7;
	int linha_f=casa/7;
	int coluna_f=casa%7;

	move_anim.yi=alturaTab+2.0;
	move_anim.y=peca_anim.yi;
	move_anim.yf=alturaTab+7.0;
	move_anim.dty=1.0;
	move_anim.sobe=true;
	move_anim.dy=(move_anim.yf-move_anim.yi)/((1000.0*move_anim.dty)/mili_secs);
	
	move_anim.xi=-3*dim_Casa+coluna_i*dim_Casa;
	move_anim.x=peca_anim.xi;
	move_anim.xf=-3*dim_Casa+coluna_f*dim_Casa;
	move_anim.dtx=2.0;
	move_anim.dx=(move_anim.xf-move_anim.xi)/((1000.0*move_anim.dtx)/mili_secs);

	move_anim.zi=-3*dim_Casa+linha_i*dim_Casa;
	move_anim.z=peca_anim.zi;
	move_anim.zf=-3*dim_Casa+linha_f*dim_Casa;
	move_anim.dtz=2.0;
	move_anim.dz=(move_anim.zf-move_anim.zi)/((1000.0*move_anim.dtz)/mili_secs);

	move_anim.enabled=true;
	move_anim.corre=false;
}

void anim(int dummy)
{
	if(jogo->casa_sel>0 && !move_anim.enabled)
	{
		//cout<<"entrou\n";
		if(peca_anim.sobe && (peca_anim.y<peca_anim.yf))
			peca_anim.y+=peca_anim.dy;
		else if(peca_anim.sobe && (peca_anim.y>=peca_anim.yf))
			peca_anim.sobe=false;
		else if(!peca_anim.sobe && (peca_anim.y>peca_anim.yi))
			peca_anim.y-=peca_anim.dy;
		else if(!peca_anim.sobe && (peca_anim.y<=peca_anim.yi))
			peca_anim.sobe=true;
	}
	if(move_anim.enabled)
	{
		if(move_anim.sobe && (move_anim.y<move_anim.yf))
			move_anim.y+=move_anim.dy;
		else if(move_anim.sobe && (move_anim.y>=move_anim.yf))
		{
			move_anim.sobe=false;
			move_anim.corre=true;
		}
		else if(move_anim.corre && move_anim.z!=move_anim.zf && move_anim.x!=move_anim.xf)
		{
			move_anim.x+=move_anim.dx;
			move_anim.z+=move_anim.dz;
		}
		else if(move_anim.corre && move_anim.z==move_anim.zf && move_anim.x==move_anim.xf && !move_anim.sobe && move_anim.y>move_anim.yi)
			move_anim.y+=move_anim.dy;
		else
			move_anim.enabled=false;
	}

	glutTimerFunc(mili_secs,anim, 0);
}

void Jogo::procura_sinal(int fase)
{
	this->sinal.clear();
	for(unsigned int i=0; i<49; i++)
	{
		if(fase==0)
		{
			if(casa_valida(i))
				this->sinal.push_back(i);
		}
		else
		{
			if(mov_valido(i))
				this->sinal.push_back(i);
		}
	}
}

void Jogo::sinaliza_casa(int casa)
{
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.0,0.86,0.67);	
	glPushMatrix();
	posicao(true, casa);
	glTranslated(0.0, 0.01, 0.0);
	glRotated(-90, 1.0, 0.0, 0.0); 
	glRectd(-dim_Casa/2, -dim_Casa/2, dim_Casa/2, dim_Casa/2);
	glPopMatrix();
	glDisable(GL_COLOR_MATERIAL);
}

void Jogo::draw()
{
	//cout<<"a desenhar\n";
	for(unsigned int i=0; i<this->tab.size(); i++)
	{
		glPushMatrix();
		if(i==jogo->casa_sel && !move_anim.enabled)
		{
			posicao(true, i);
			glTranslated(0.0, peca_anim.y, 0.0);
		}
		else if(move_anim.enabled && i==jogo->casa_sel)
			glTranslated(move_anim.x, move_anim.y, move_anim.z);
		else
			posicao(true, i);
		switch(this->tab.at(i))
		{
		case 1:
			this->aldeao->draw();
			break;
		case 2:
			this->vampiro->draw();
			break;
		case 3:
			this->nosferatu->draw();
			break;
		}
		glPopMatrix();
	}
	for(unsigned int i=0; i<this->pecas_al.size();i++)
	{
		switch(this->pecas_al.at(i))
		{
		case 1:
			glPushMatrix();
			posicao(false, i);
			//reverte(this->aldeao);
			this->aldeao->draw();
			glPopMatrix();
			//cout<<"desenhou aldeao fora\n";
			break;
		default:
			return;
		}
	}
	for(unsigned int i=0; i<this->pecas_v.size(); i++)
	{
		switch(this->pecas_v.at(i))
		{
		case 2:
			glPushMatrix();
			posicao(false, i+13);
			//reverte(this->vampiro);
			this->vampiro->draw();
			glPopMatrix();
			//cout<<"desenhou vampiro fora\n";
			break;
		case 3:
			glPushMatrix();
			posicao(false, i+13);
			//reverte(this->nosferatu);
			this->nosferatu->draw();
			glPopMatrix();
			//cout<<"desenhou nosferatu fora\n";
			break;
		default:
			return;
		}
	}
	for(unsigned int i=0; i<this->sinal.size(); i++)
		this->sinaliza_casa(this->sinal.at(i));
}

void myCube(GLfloat lado)
{
	//frente
	glRectd(0.0, 0.0, lado, lado);

	//base
	glPushMatrix();	
	glTranslated(0.0, 0.0, -lado);
	glRotated(90.0, 1.0, 0.0, 0.0);
		glRectd(0.0, 0.0, lado, lado);
	glPopMatrix();

	//lado esq
	glPushMatrix();	
	glTranslated(0.0, 0.0, -lado);
	glRotated(-90.0, 0.0, 1.0, 0.0);
		glRectd(0.0, 0.0, lado, lado);
	glPopMatrix();

	//lado dir
	glPushMatrix();	
	glTranslated(lado, 0.0, 0.0);
	glRotated(90.0, 0.0, 1.0, 0.0);
		glRectd(0.0, 0.0, lado, lado);
	glPopMatrix();

	//topo
	glPushMatrix();	
	glTranslated(0.0, lado, 0.0);
	glRotated(-90.0, 1.0, 0.0, 0.0);
		glRectd(0.0, 0.0, lado, lado);
	glPopMatrix();

	//tras
	glPushMatrix();	
	glTranslated(lado, 0.0, -lado);
	glRotated(180.0, 0.0, 1.0, 0.0);
		glRectd(0.0, 0.0, lado, lado);
	glPopMatrix();
}

void sensores()
{

	glPushMatrix();
	glTranslated(0.0, alturaTab+2.0, 0.0);
		
	glPushName(2);
		
		glPushMatrix();
		glTranslated(-dim_Casa-dim_Casa/2+(dim_Casa-dim_cube)/2, 0.0, -2*dim_Casa-dim_Casa/2);
		if(jogo->tab.at(2)==0)
		{
			glRotated(-90.0, 1.0, 0.0, 0.0);
			glRectd(0.0, 0.0, dim_cube, dim_cube);
		}
		else
			glCallList(cube);
		glPopMatrix();
		for(int i=1; i<3; i++)
		{
			glLoadName(i+2);
			glPushMatrix();
			glTranslated(-dim_Casa-dim_Casa/2+i*dim_Casa+(dim_Casa-dim_cube)/2, 0.0, -2*dim_Casa-dim_Casa/2);
			if(jogo->tab.at(i+2)==0)
			{
				glRotated(-90.0, 1.0, 0.0, 0.0);
				glRectd(0.0, 0.0, dim_cube, dim_cube);
			}
			else
				glCallList(cube);
			glPopMatrix();

		}
		
		for(int i=0; i<5; i++)
		{
			glLoadName(i+8);
			glPushMatrix();
			glTranslated(-2*dim_Casa-dim_Casa/2+i*dim_Casa+(dim_Casa-dim_cube)/2, 0.0, -dim_Casa-dim_Casa/2);
			if(jogo->tab.at(i+8)==0)
			{
				glRotated(-90.0, 1.0, 0.0, 0.0);
				glRectd(0.0, 0.0, dim_cube, dim_cube);
			}
			else
				glCallList(cube);
			glPopMatrix();
		}
		
		for(int i=0; i<7; i++)
		{
			glLoadName(i+14);
			glPushMatrix();
			glTranslated(-3*dim_Casa-dim_Casa/2+i*dim_Casa+(dim_Casa-dim_cube)/2, 0.0, -dim_Casa/2);
			if(jogo->tab.at(i+14)==0)
			{
				glRotated(-90.0, 1.0, 0.0, 0.0);
				glRectd(0.0, 0.0, dim_cube, dim_cube);
			}
			else
				glCallList(cube);
			glPopMatrix();
		}

		for(int i=0; i<7; i++)
		{
			glLoadName(i+21);
			glPushMatrix();
			glTranslated(-3*dim_Casa-dim_Casa/2+i*dim_Casa+(dim_Casa-dim_cube)/2, 0.0, dim_Casa/2);
			if(jogo->tab.at(i+21)==0)
			{
				glRotated(-90.0, 1.0, 0.0, 0.0);
				glRectd(0.0, 0.0, dim_cube, dim_cube);
			}
			else
				glCallList(cube);
			glPopMatrix();
		}

		for(int i=0; i<7; i++)
		{
			glLoadName(i+28);
			glPushMatrix();
			glTranslated(-3*dim_Casa-dim_Casa/2+i*dim_Casa+(dim_Casa-dim_cube)/2, 0.0, dim_Casa+dim_Casa/2);
			if(jogo->tab.at(i+28)==0)
			{
				glRotated(-90.0, 1.0, 0.0, 0.0);
				glRectd(0.0, 0.0, dim_cube, dim_cube);
			}
			else
				glCallList(cube);
			glPopMatrix();
		}

		for(int i=0; i<5; i++)
		{
			glLoadName(i+36);
			glPushMatrix();
			glTranslated(-2*dim_Casa-dim_Casa/2+i*dim_Casa+(dim_Casa-dim_cube)/2, 0.0, 2*dim_Casa+dim_Casa/2);
			if(jogo->tab.at(i+36)==0)
			{
				glRotated(-90.0, 1.0, 0.0, 0.0);
				glRectd(0.0, 0.0, dim_cube, dim_cube);
			}
			else
				glCallList(cube);
			glPopMatrix();
		}
		
		for(int i=0; i<3; i++)
		{
			glLoadName(i+44);
			glPushMatrix();
			glTranslated(-dim_Casa-dim_Casa/2+i*dim_Casa+(dim_Casa-dim_cube)/2, 0.0, 3*dim_Casa+dim_Casa/2);
			if(jogo->tab.at(i+44)==0)
			{
				glRotated(-90.0, 1.0, 0.0, 0.0);
				glRectd(0.0, 0.0, dim_cube, dim_cube);
			}
			else
				glCallList(cube);
			glPopMatrix();
		}
	glPopMatrix();
}

void pickingAction(GLuint answer) 
{
	int peca;
	try
	{
		if(!move_anim.enabled)
		{
			switch(jogo->fase)
			{
			case 0://quando todos inserem
				if(jogo->casa_valida(answer))//insere peca e decrementa peice pool
				{
					if(jogo->Jactual==0)
					{
						jogo->hist.push_back(jogo->tab);
						peca=jogo->pecas_al.back();
						jogo->pecas_al.pop_back();
						jogo->tab.at(answer)=peca;
						jogo->Jactual=1;
						jogo->procura_sinal(0);
					}
					else
					{
						jogo->hist.push_back(jogo->tab);
						peca=jogo->pecas_v.back();
						jogo->pecas_v.pop_back();
						if(jogo->pecas_v.empty())
							jogo->fase++;
						jogo->tab.at(answer)=peca;
						jogo->Jactual=0;
						jogo->procura_sinal(0);
					}
				}
				break;
			case 1://quando os aldeoes inserem e os vampiros jogam
				switch(jogo->Jactual)
				{
				case 0:
					if(jogo->casa_valida(answer))
					{
						jogo->hist.push_back(jogo->tab);
						peca=jogo->pecas_al.back();
						jogo->pecas_al.pop_back();
						if(jogo->pecas_al.empty())
							jogo->fase++;
						jogo->tab.at(answer)=peca;
						jogo->Jactual=1;
						jogo->sinal.clear();
					}
					break;
				case 1:
					if(jogo->pertence(answer))
					{
						peca_anim_init();
						jogo->casa_sel=answer;
						jogo->fase_ant=jogo->fase;
						jogo->fase=3;
						jogo->procura_sinal(1);
						//cout<<"pertence\n";
					}
					break;
				}
				break;
			case 2://quando todos jogam
				if(jogo->pertence(answer))
				{
					peca_anim_init();
					jogo->casa_sel=answer;
					jogo->fase_ant=jogo->fase;
					jogo->fase=3;
					jogo->procura_sinal(1);
					//cout<<"pertence\n";
				}
				break;
			case 3://quando se seleccionou uma casa e se tenta seleccionar a outra
				if(jogo->mov_valido(answer))
				{
					move_anim_init(answer);
					jogo->exec_move(answer);
					if(jogo->Jactual==0)
						jogo->Jactual=1;
					else
						jogo->Jactual=0;
					jogo->casa_sel=-1;
					jogo->fase=jogo->fase_ant;
					jogo->sinal.clear();
					if(jogo->fase==1)
						jogo->procura_sinal(0);
				}
				break;
			}
		}
	}
	catch (ExcepcaoSocket e)
	{
		cout<<"erro na comunicacao com o prolog\n";
		system("pause");
	}

	//printf("%d\n", answer);
}

void Jogo::anexa_tab(char * buf)
{
	int i=0;
	char buf2[BUFSIZE];

	//linha 0
	sprintf(buf2, "[[%i,%i,%i,%i,%i,%i,%i],", tab.at(i*7+0), tab.at(i*7+1), tab.at(i*7+2), tab.at(i*7+3), tab.at(i*7+4), tab.at(i*7+5), tab.at(i*7+6));
	strcat(buf, buf2);
	//linha 1
	i++;
	sprintf(buf2, "[%i,%i,%i,%i,%i,%i,%i],", tab.at(i*7+0), tab.at(i*7+1), tab.at(i*7+2), tab.at(i*7+3), tab.at(i*7+4), tab.at(i*7+5), tab.at(i*7+6));
	strcat(buf, buf2);
	//linha 2
	i++;
	sprintf(buf2, "[%i,%i,%i,%i,%i,%i,%i],", tab.at(i*7+0), tab.at(i*7+1), tab.at(i*7+2), tab.at(i*7+3), tab.at(i*7+4), tab.at(i*7+5), tab.at(i*7+6));
	strcat(buf, buf2);
	//linha 3
	i++;
	sprintf(buf2, "[%i,%i,%i,%i,%i,%i,%i],", tab.at(i*7+0), tab.at(i*7+1), tab.at(i*7+2), tab.at(i*7+3), tab.at(i*7+4), tab.at(i*7+5), tab.at(i*7+6));
	strcat(buf, buf2);
	//linha 4
	i++;
	sprintf(buf2, "[%i,%i,%i,%i,%i,%i,%i],", tab.at(i*7+0), tab.at(i*7+1), tab.at(i*7+2), tab.at(i*7+3), tab.at(i*7+4), tab.at(i*7+5), tab.at(i*7+6));
	strcat(buf, buf2);
	//linha 5
	i++;
	sprintf(buf2, "[%i,%i,%i,%i,%i,%i,%i],", tab.at(i*7+0), tab.at(i*7+1), tab.at(i*7+2), tab.at(i*7+3), tab.at(i*7+4), tab.at(i*7+5), tab.at(i*7+6));
	strcat(buf, buf2);
	//linha 6
	i++;
	sprintf(buf2, "[%i,%i,%i,%i,%i,%i,%i]]).\n", tab.at(i*7+0), tab.at(i*7+1), tab.at(i*7+2), tab.at(i*7+3), tab.at(i*7+4), tab.at(i*7+5), tab.at(i*7+6));
	strcat(buf, buf2);
}

bool Jogo::casa_valida(int casa)
{
	vector<int> pos = conv_casa(casa);
	
	char buf[BUFSIZE];

	if(this->Jactual==0)
		sprintf(buf, "casa_valida(%i,%i,%i,", pos.at(0), pos.at(1), this->pecas_al.back());
	else
		sprintf(buf, "casa_valida(%i,%i,%i,", pos.at(0), pos.at(1), this->pecas_v.back());
	anexa_tab(buf);

	//cout<<buf;
	//system("pause");
	
	envia(buf, strlen(buf));

	recebe(buf);

	int res=atoi(buf);
	//cout<<res<<endl;

	//quit();

	if(res==1)
		return true;
	else
		return false;
}	

bool Jogo::pertence(int casa)
{
	vector<int> pos = conv_casa(casa);
	char buf[BUFSIZE];

	sprintf(buf, "pertence(%i,%i,%i,", this->Jactual+1, pos.at(0), pos.at(1));
	anexa_tab(buf);

	envia(buf, strlen(buf));

	recebe(buf);

	int res=atoi(buf);

	if(res==1)
		return true;
	else
		return false;
}

bool Jogo::mov_valido(int casa)
{
	vector<int> posi = conv_casa(this->casa_sel);
	vector<int> posf = conv_casa(casa);
	char buf[BUFSIZE];

	sprintf(buf, "movimento_valido(%i,%i,%i,%i,", posi.at(0), posi.at(1), posf.at(0), posf.at(1));
	anexa_tab(buf);

	envia(buf, strlen(buf));

	recebe(buf);

	int res=atoi(buf);

	if(res==1)
		return true;
	else
		return false;
}

void Jogo::exec_move(int casa)
{
	vector<int> posi = conv_casa(this->casa_sel);
	vector<int> posf = conv_casa(casa);
	char buf[BUFSIZE];

	sprintf(buf, "exec_move(%i,%i,%i,%i,", posi.at(0), posi.at(1), posf.at(0), posf.at(1));
	anexa_tab(buf);

	envia(buf, strlen(buf));

	recebe(buf);

	this->hist.push_back(this->tab);
	this->tab=parse_tab(buf);

}

vector<int> Jogo::parse_tab(char * buf)
{
	vector<int> nums;
	int num;
	char c;
	for(unsigned int j=0; j<7; j++)
	{
		for(unsigned int i=0; i<7; i++)
		{
			buf+=2;
			num=atoi(buf);
			nums.push_back(num);
		}
		buf+=2;
	}
	
	
	//cout<<nums.size()<<endl;
	return nums;
}

vector<int> Jogo::conv_casa(int casa)
{
	vector<int> pos;
	int aux=casa/7;
	//pos.push_back(aux);
	pos.push_back(casa%7);
	pos.push_back(aux);
	return pos;
}

// processa os hits no picking
void processHits (GLint hits, GLuint buffer[]) {
	GLuint *ptr = buffer;
	GLuint mindepth = 0xFFFFFFFF;
	GLuint *answer=NULL;
	GLuint nn;

	for (int i=0;i<hits;i++) {
		int num = *ptr; ptr++;
		GLuint z1 = *ptr; ptr++;
		ptr++;
		if (z1 < mindepth && num>0 ) 
		{
			//cout<<"entrou num\n";
			mindepth = z1;
			answer = ptr;
			nn=num;

		}
		for (int j=0; j < num; j++) 
			ptr++;
	}

	//cout<<"precoessa\n";
	
	// existe uma resposta
	if (answer!=NULL) 
		pickingAction(*answer);
	//else
		//cout<<"nao tem resposta\n";
	
}