#include "SceneLoader.h"
#include "Picking.h"

#include <math.h>

using namespace std;

RGBpixmap pixmap;
vector<SceneLoader *> cenas;
int cena_actual;

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

	// define caracteristicas de cor do material do plano e da caixa
	/*glMaterialfv(GL_FRONT, GL_SHININESS, mat1_shininess);
	glMaterialfv(GL_FRONT, GL_SPECULAR,  mat1_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat1_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT,   mat1_ambient);*/

	cenas.at(cena_actual)->root_object->draw();

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

		drawScene(GL_SELECT);

		glMatrixMode (GL_PROJECTION);
		glPopMatrix ();
		glFlush ();

		hits = glRenderMode(GL_RENDER);
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

	glPolygonMode(GL_FRONT, GL_FILL);	// preence a face da frente dos poligonos
	//glPolygonMode(GL_FRONT, GL_LINE);	// desenha arestas dos poligonos
	
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
   

	/*** Create the bottom subwindow ***/
	glui2 = GLUI_Master.create_glui_subwindow( main_window, GLUI_SUBWINDOW_BOTTOM );
	glui2->set_main_gfx_window( main_window );

	GLUI_Rotation *view_rot = glui2->add_rotation( "Rotacao", view_rotate );
	view_rot->set_spin( 1.0 );
	glui2->add_column( false );

	GLUI_Translation *trans_z = 
	glui2->add_translation( "Zoom", GLUI_TRANSLATION_Z, &obj_pos[2] );
	trans_z->set_speed( .02 );

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
