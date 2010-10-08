// G1_Ilum.cpp : Defines the entry point for the console application.
//

#include <glui.h>
#include <math.h>
#include "RGBpixmap.h"
#include "MainCode.h"

// dimensoes e localizacao da janela
#define DIMX 500
#define DIMY 500
#define INITIALPOS_X 200
#define INITIALPOS_Y 200

float xy_aspect;

// matriz de transf. geometrica utilizada pelo botao esferico
float view_rotate[16] = { 1,0,0,0,
                          0,1,0,0,
                          0,0,1,0,
                          0,0,0,1 };

// vector de posicao utilizado pelo botao de afastamento
float obj_pos[] = { 0.0, 0.0, 0.0 };

// declarações para os tres eixos (cilindros)
double axis_radius_begin =  0.2;
double axis_radius_end   =  0.0;
double axis_lenght       = 16.0;
int axis_nslices = 8;
int axis_nstacks = 1;

// declaracoes para as paredes
float mat1_shininess[] = {128.0}; 
float mat1_specular[] = {0.3, 0.3, 0.3, 1.0};	/* specular reflection. */
float mat1_diffuse[] =  {0.7, 0.7, 0.7, 1.0};	/* diffuse reflection. */
float mat1_ambient[] =  {0.7, 0.7, 0.7, 1.0};	/* ambient reflection. */

// declarações para a fonte de luz LIGHT0;
float light0_position[]  = {0.0, 3.0, 4.0, 1.0}; // nao necessaria...
float light0_ambient[] =   {0.0, 0.0, 0.0, 1.0}; // sem componente ambiente
float light0_diffuse[] =   {6.0, 6.0, 6.0, 1.0};
float light0_specular[] =  {6.0, 6.0, 6.0, 1.0};
float light0_kc = 0.0;
float light0_kl = 1.0;
float light0_kq = 0.0;
double light0x = 225.0;
double light0y = 150;
double light0z = 150.0;
double symb_light0_radius = 0.2;
int symb_light0_slices = 8;
int symb_light0_stacks =8;

// fonte (global) de luz ambiente 
float light_ambient[] = {1.0, 1.0, 1.0, 1.0}; /* Set the background ambient lighting. */// era 0.6 nos primeiros 3


// variaveis para a janela
int main_window;
GLUI  *glui2;


RGBpixmap pixmap;



void display(void)
{
	// ****** declaracoes internas 'a funcao display() ******
	
	float temp;

	GLUquadric* glQ;	// nec. p/ criar sup. quadraticas (cilindros, esferas...)

	// ****** fim de todas as declaracoes da funcao display() ******

	glQ = gluNewQuadric();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
	// inicializacoes da matriz de visualizacao
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glFrustum( -xy_aspect*.04, xy_aspect*.04, -.04, .04, .1, 2500.0 );//alcance da camara

	//inicializacoes da matriz de transformacoes geometricas
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	
	// afasta a cena de 25 unidades mais a distância que...
	// ...decorre da utilizacao do botao de afastamento (pseudo-zoom)
    glTranslatef( obj_pos[0]-150, obj_pos[1], -obj_pos[2]-250 ); //era -25
		// tambem se poderia ter feito:
		//glTranslated(0.0,0.0,-25.0);
		//glTranslatef( obj_pos[0], obj_pos[1], -obj_pos[2] );

	// roda a cena para ficar em perspectiva	
	glRotated( 20.0, 1.0,0.0,0.0 );		// 20 graus em torno de X
	glRotated(0.0, 0.0,1.0,0.0 );		//-45 graus em torno de Y

	// roda a cena de acordo com o botao (esfera) de rotacao
	glMultMatrixf( view_rotate );

	// permissao de atribuicao directa de cores
	// para objectos que nao tem material atribuido, como
	// e' o caso dos eixos e da esfera que simboliza a fonte de luz...
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	// cilindro representativo do eixo X
	glColor3f(1.0,0.0,0.0);		// vermelho
	glPushMatrix();
	glRotated(90.0, 0.0,1.0,0.0 );
	gluCylinder(glQ, axis_radius_begin, axis_radius_end,
		             axis_lenght, axis_nslices, axis_nstacks);   // nao tem bases
	glPopMatrix();

	// cilindro representativo do eixo Y
	glColor3f(0.0,1.0,0.0);		// verde
	glPushMatrix();
	glRotated(-90.0, 1.0,0.0,0.0 );
	gluCylinder(glQ, axis_radius_begin, axis_radius_end,
		             axis_lenght, axis_nslices, axis_nstacks);   // nao tem bases
	glPopMatrix();
	
	// cilindro representativo do eixo Z
	glColor3f(0.0,0.0,1.0);		// azul
	glPushMatrix();
	// nao necessita rotacao... glRotated(...);
	gluCylinder(glQ, axis_radius_begin, axis_radius_end,
		             axis_lenght, axis_nslices, axis_nstacks);   // nao tem bases
	glPopMatrix();

	
	// Actualizacao da posicao da fonte de luz...
	light0_position[0] = light0x;	// por razoes de eficiencia, os restantes 
	light0_position[1] = light0y;	// parametros _invariaveis_ da LIGHT0 mantem os valores
	light0_position[2] = light0z;	// definidos na funcao de inicializacao
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	// ... e da esfera que a simboliza
	glColor3f(1.0,1.0,0.0);		// cor amarela
	gluQuadricOrientation( glQ, GLU_INSIDE);
	glPushMatrix();
	glTranslated(light0x,light0y,light0z);
	gluSphere(glQ, symb_light0_radius, symb_light0_slices, symb_light0_stacks);
    glPopMatrix();
	gluQuadricOrientation( glQ, GLU_OUTSIDE);



	// SEGUEM-SE ALGUNS EXEMPLOS DE UTILIZACAO DE OPENGL (GL, GLU, GLUT)

	// GLU: funcoes para desenhar Quadraticas
	//   Permitem desenhar alguns objectos: disco, cilindro/cone, esfera
	//   O parametro do tipo GLUquadric (variavel glQ, declarada acima) passa,
	//   em argumento da funcao de desenho respectiva, algumas propriedades
	//   que esta tem em conta durante o desenho (estilo de desenho, calculo e
	//   orientacao de normais, mapeamento de texturas...

	// Funcoes para definicao dessas propriedades em glQ
	gluQuadricDrawStyle(glQ, GLU_LINE);		// GLU_FILL, GLU_LINE, GLU_SILHOUETTE, GLU_POINT
	gluQuadricNormals(glQ, GLU_SMOOTH);		// GLU_NONE, GLU_FLAT, GLU_SMOOTH
	gluQuadricOrientation(glQ, GLU_OUTSIDE);	// GLU_OUTSIDE, GLU_INSIDE
	gluQuadricTexture(glQ, GL_FALSE);		// GL_TRUE, GL_FALSE
	//gluQuadricCallback(glQ, GLU_ERROR, <CallBackFunc>);

	// Funcoes de desenho de quadraticas
	// gluDisk(GLUquadric* quad, GLdouble inner, GLdouble outer,
	//			GLint slices, GLint loops )
	// gluPartialDisk(GLUquadric* quad, GLdouble inner, GLdouble outer,
	//			GLint slices, GLint loops, GLdouble start, GLdouble sweep )
	// gluCylinder(GLUquadric * quad, GLdouble base, GLdouble top, GLdouble height,
	//			GLint slices, GLint stacks );
	// gluSphere(GLUquadric* quad, GLdouble radius, GLint slices, GLint stacks )

/*	glColor3f(1.0,0.0,1.0);		// magenta
	gluSphere(glQ, 1.0, 8,8);

	glColor3f(0.0,1.0,1.0);		// ciano
	gluQuadricDrawStyle(glQ, GLU_FILL);
	gluPartialDisk(glQ, 3, 7, 16, 4, 45, 270);

	// Solidos, na GLUT: nao fazem mapeamento de texturas (excepto o Teapot)
	// glutSolidSphere(GLdouble radius, GLint slices, GLint stacks);
	// glutSolidCube(GLdouble size);
	// glutSolidCone(GLdouble base, GLdouble height, GLint slices, GLint stacks);
	// glutSolidTorus(GLdouble innerRadius, GLdouble outerRadius, GLint nsides, GLint rings);
	// glutSolidDodecahedron(void);
	// glutSolidOctahedron(void);
	// glutSolidTetrahedron(void);
	// glutSolidIcosahedron(void);
	// glutSolidTeapot(GLdouble size);


	// Texto 3D, GLUT
	// void glutStrokeCharacter(void *font, int character);	// GLUT_STROKE_ROMAN
	// int glutStrokeWidth(GLUTstrokeFont font, int character);

	glPushMatrix();
	glTranslatef(0,0,1);
	glScalef(0.05, 0.05, 0.05);
	glColor3f(0.0,0.0,1.0);		// azul
	glutStrokeCharacter(GLUT_STROKE_ROMAN, 'L');
	glutStrokeCharacter(GLUT_STROKE_ROMAN, 'A');
	glutStrokeCharacter(GLUT_STROKE_ROMAN, 'S');
	glPopMatrix();


	// Texto BitMap, GLUT
	// glRasterPos3f(x,y,z);
	// void glutBitmapCharacter(void *font, int character);	// valores varios...
	// int glutBitmapWidth(GLUTbitmapFont font, int character);

	glPushMatrix();
	glColor3f(1.0,1.0,0.0);		// amarelo
	glRasterPos3f(5,5,5);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '\'');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'm');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'a');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'o');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '!');
	glPopMatrix();
*/	
	// inibicao de atribuicao directa de cores; os objectos que se seguem DEVEM
	// possuir materiais associados
	glDisable(GL_COLOR_MATERIAL);



	// Definicao de material a usar daqui em diante (valores declarados acima)
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat1_shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  mat1_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   mat1_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   mat1_ambient);

/*	// desenha rectangulo paralelo ao plano XY, com texturas
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 1);	// activa a textura 1 (feup)
	temp = 2; // cinco repetições na direccao Z
	glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,1.0);  // esta normal fica comum aos 4 vertices
		glTexCoord2f(0.0,0.0);  glVertex3d(-1.0, 6.0, 10.0);	// associacao de
		glTexCoord2f(1.0,0.0);  glVertex3d(-1.0, 1.0, 10.0);	// coordenadas u,v
		glTexCoord2f(1.0,temp); glVertex3d(-1.0, 1.0,  1.0);	// das texturas, aos
		glTexCoord2f(0.0,temp); glVertex3d(-1.0, 6.0,  1.0);	// vertices 3D do poligono
	glEnd();

	// desenha rectangulo paralelo ao plano ZY, sem texturas
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_POLYGON);
		glNormal3d(1.0,0.0,0.0);  // esta normal fica comum aos 4 vertices
		glVertex3d( 1.0, 1.0,  -1.0);
		glVertex3d(10.0, 1.0,  -1.0);
		glVertex3d(10.0, 6.0,  -1.0);
		glVertex3d( 1.0, 6.0,  -1.0);
	glEnd();
*/
	//TODO
	//INICIO DO TRABALHO

	//Terreno e ¨¢rvores;
	glCallList(1);
	//Hospital (com telhado e letreiro inclu¨ªdos);
	glCallList(2);
	//Heliporto (¨¢rea de aterragem e holofotes).
	glCallList(3);

	hangar(); 
	torre();

	// swapping the buffers causes the rendering above to be shown
	glutSwapBuffers();
	glFlush();
}


/* Mouse handling */
void processMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{	 
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{	
	}
	
	glutPostRedisplay();
	
}

void processMouseMoved(int x, int y)
{
	
	// pedido de refrescamento da janela
	glutPostRedisplay();				

}

void processPassiveMouseMoved(int x, int y)
{

	// pedido de refrescamento da janela
	glutPostRedisplay();				
}

void reshape(int w, int h)
{
	int tx, ty, tw, th;

	GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
	glViewport( tx, ty, tw, th );
	xy_aspect = (float)tw / (float)th;

	glutPostRedisplay();

}


void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
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

}

void inicializacao()
{

	glFrontFace(GL_CCW);		// Front faces defined using a counterclockwise rotation
	glDepthFunc(GL_LEQUAL);		// Por defeito e GL_LESS
	glEnable(GL_DEPTH_TEST);	// Use a depth (z) buffer to draw only visible objects


	// Face Culling para aumentar a velocidade
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);		// GL_FRONT, GL_BACK, GL_FRONT_AND_BACK


	// Define que modelo de iluminacao utilizar; consultar o manual de referencia
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);  // define luz ambiente
	glLightModelf (GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glLightModeli (GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
	
	// por defeito a cor de fundo e o preto
	// glClearColor(1.0,1.0,1.0,1.0);    // cor de fundo a branco


	// declaracoes para a fonte luz GL_LIGHT0
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,  light0_kc);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION,    light0_kl);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, light0_kq);

	// NOTA: a direccao e a posicao de GL_LIGHT0 estao na rotina display(), pelo
	//       que as isntrucoes seguntes nao sao necessarias
	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90.0);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	//glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	// Permitir calculos de iluminacao
	glEnable(GL_LIGHTING);
	// "Acender" a fonte de luz GL_LIGHT0
	glEnable(GL_LIGHT0);


	// Declaracoe para shading
	glShadeModel(GL_SMOOTH);			// GL_FLAT / GL_SMOOTH
	glPolygonMode(GL_FRONT, GL_FILL);	// preence a face da frente dos poligonos
	// glPolygonMode(GL_FRONT, GL_LINE);	// desenha arestas dos poligonos


	// Texturas a utilizar (ver classe RGBpixmap)
	pixmap.readBMPFile("feup.bmp");
	pixmap.setTexture(1);

	pixmap.readBMPFile("tile.bmp");
	pixmap.setTexture(2);

	pixmap.readBMPFile("clamp.bmp");
	pixmap.setTexture(3);

	pixmap.readBMPFile("mandril.bmp");
	pixmap.setTexture(4);

	pixmap.readBMPFile("GrassTexture.bmp");
	pixmap.setTexture(5);

	pixmap.readBMPFile("wood_texture.bmp");
	pixmap.setTexture(6);

	pixmap.readBMPFile("stone.bmp");
	pixmap.setTexture(7);

	pixmap.readBMPFile("janela.bmp");
	pixmap.setTexture(8);

//criar display lists

	//Terreno e ¨¢rvores
	glNewList(1,GL_COMPILE);
		chao();
		arvore_A(30.0, 30.0, 70.0, 40.0);
		arvore_A(100.0, 100.0, 50.0, 30.0);
		arvore_X(30.0, 150.0, 50.0, 30.0);
		arvore_X(100.0, 200.0, 70.0, 40.0);
	glEndList();

	//Hospital (com telhado e letreiro inclu¨ªdos)
	glNewList(2, GL_COMPILE);
		hospital();
	glEndList();

	//Heliporto (¨¢rea de aterragem e holofotes)
	glNewList(3, GL_COMPILE);
		heliporto();
	glEndList();
}



int main(int argc, char* argv[])
{
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
	GLUI_Translation *trans_z = glui2->add_translation( "Zoom", GLUI_TRANSLATION_Z, &obj_pos[2] );
	trans_z->set_speed( .02 );


	/* We register the idle callback with GLUI, not with GLUT */
	GLUI_Master.set_glutIdleFunc( myGlutIdle );
   
	inicializacao();
   
	glutMainLoop();

	return 0;
}
