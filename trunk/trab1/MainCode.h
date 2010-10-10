#include "helicoptero.h"

const int TRUE  = 1;
const int FALSE = 0;

//declaracoes das camaras
int camera_select;
int camara3_x, camara3_y, camara3_z, camara3_ox, camara3_oy, camara3_oz;

// declaraçoes de luz
#define LIGHT0_ID 100
#define LIGHT1_ID 101
#define LIGHT2_ID 102
#define LIGHT3_ID 103
#define LIGHT4_ID 104
int light0_enabled;
int light1_enabled;
int light2_enabled;
int light3_enabled;
int light4_enabled;

//declaracoes para holofotes
float holofote_ambient[] =   {0.0, 0.0, 0.0, 1.0}; // sem componente ambiente
float holofote_diffuse[] =   {6.0, 6.0, 6.0, 1.0};
float holofote_specular[] =  {6.0, 6.0, 6.0, 1.0};
float holofote_kc = 0.0;
float holofote_kl = 0.1;
float holofote_kq = 0.0;
float ang=30.0;


// declaraces para a fonte de luz LIGHT0;
float light0_position[]  = {0.0, 3.0, 4.0, 1.0}; // nao necessaria...
float light0_ambient[] =   {0.0, 0.0, 0.0, 1.0}; // sem componente ambiente
float light0_diffuse[] =   {6.0, 6.0, 6.0, 1.0};
float light0_specular[] =  {6.0, 6.0, 6.0, 1.0};
float light0_kc = 0.0;
float light0_kl = 0.0;
float light0_kq = 0.0;
float light0_direction[] = {0.0, -1.0, -1.0, 1.0};
double light0x = 450.0;
double light0y = 150.0;
double light0z = 150.0;
double symb_light0_radius = 0.2;


int symb_light0_slices = 8;
int symb_light0_stacks = 8;

// fonte (global) de luz ambiente 
float light_ambient[] = {0.6, 0.6, 0.6, 1.0}; /* Set the background ambient lighting. */// era 0.6 nos primeiros 3

double poste_r = 3.0/2.0;
double poste_altura = 47.0;
double baseInf_r = 13.0/2.0;
double baseSup_r = 7.0/2.0;
double base_altura = 7.0;





void chao(void)
{
	//rectangulo 1
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GrassTexture);
	glBegin(GL_POLYGON);
		glNormal3d(0.0,1.0,0.0);  // esta normal fica comum aos 4 vertices
		glTexCoord2f(0.0,0.0); glVertex3d( 0.0, 0.0,  0.0);
		glTexCoord2f(5.0,0.0); glVertex3d(dimx1, 0.0,  0.0);
		glTexCoord2f(5.0,10.0); glVertex3d(dimx1, 0.0,  dimy);
		glTexCoord2f(0.0,10.0); glVertex3d(0.0, 0.0,  dimy);		
	glEnd();
	glDisable(GL_TEXTURE_2D);


	// DECLARACOES RELACIONADAS COM OS "EVALUATORS"
	GLfloat ctrlpoints[4][3] = {	{dimx1, 0.0, 0.0},
									{dimx1, 0.0, dimy}, 
									{dimx2, 0.0, 0.0},
									{dimx2, 0.0, dimy} };

	GLfloat nrmlcompon[4][3] = {	{  0.0, 1.0, 0.0},
									{  0.0, 1.0, 0.0}, 
									{  0.0, 1.0, 0.0},
									{  0.0, 1.0, 0.0} };

	GLfloat textpoints[4][2] = {	{ 0.0, 0.0},
									{ 0.0, 4.0}, 
									{ 8.0, 0.0},
									{ 8.0, 4.0} };


	// INICIALIZACOES RELACIONADAS COM OS "EVALUATORS"
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 2,  0.0, 1.0, 6, 2,  &ctrlpoints[0][0]);
	glMap2f(GL_MAP2_NORMAL,   0.0, 1.0, 3, 2,  0.0, 1.0, 6, 2,  &nrmlcompon[0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2,  0.0, 1.0, 2, 2,  0.0, 1.0, 4, 2,  &textpoints[0][0]);

	// os interpoladores activam-se:
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_NORMAL);
	glEnable(GL_MAP2_TEXTURE_COORD_2);
	glMapGrid2f(300, 0.0,1.0, 150, 0.0,1.0); 

	//rectangulo 2
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, stone_texture);
	glEvalMesh2(GL_FILL, 0,300, 0,150);
	glDisable(GL_TEXTURE_2D);


	//rectangulo 3
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, wood_texture);
	glBegin(GL_POLYGON);
		glNormal3d(0.0,1.0,0.0);  // esta normal fica comum aos 4 vertices
		glTexCoord2f(0.0,0.0); glVertex3d(dimx2, 0.0,  0.0);
		glTexCoord2f(32.0,0.0); glVertex3d(dimx3, 0.0,  0.0);
		glTexCoord2f(32.0,16.0); glVertex3d(dimx3, 0.0,  dimy);
		glTexCoord2f(0.0,16.0); glVertex3d(dimx2, 0.0,  dimy);		
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void arvore_A(double x, double y, double altura, double largura)
{
	GLUquadric* glQ;
	glQ = gluNewQuadric();
	
	//tronco
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, wood_texture);
	glPushMatrix();
	glTranslated(x, 0.0, -y);
	glRotated(-90.0, 1.0,0.0,0.0 );
	gluCylinder(glQ, largura/10.0, 0.0, altura/2.0, nslices, nstacks);   // nao tem bases
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//copa
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GrassTexture);
	glPushMatrix();
	glTranslated(x, altura/2.0, -y);
	glRotated(-90.0, 1.0,0.0,0.0 );
	gluCylinder(glQ, largura/2.0, 0.0, altura/2.0, nslices, nstacks);   // nao tem bases
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

double folha_temp = 6.0;

void arvore_X(double x, double y, double altura, double largura)
{
	GLUquadric* glQ;
	glQ = gluNewQuadric();
	
	//tronco
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, wood_texture);
	glPushMatrix();
	glTranslated(x, 0.0, -y);
	glRotated(-90.0, 1.0,0.0,0.0 );
	gluCylinder(glQ, largura/10.0, 0.0, altura, nslices, nstacks);   // nao tem bases
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//copa
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, folha_texture);
	glPushMatrix();
	glTranslated(x, 0.0, -y);
	glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,1.0);  
		glTexCoord2f(0.0, 0.0); glVertex3d(-largura/2.0, altura/2.0,  0.0);
		glTexCoord2f(folha_temp, folha_temp); glVertex3d(0.0, altura,  0.0);
		glTexCoord2f(2*folha_temp, 0.0); glVertex3d(largura/2.0, altura/2.0,  0.0);		
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(x, 0.0, -y);
	glRotated(180.0, 0.0,1.0,0.0 );
	glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,-1.0);  
		glTexCoord2f(0.0, 0.0); glVertex3d(-largura/2.0, altura/2.0,  0.0);
		glTexCoord2f(folha_temp, folha_temp); glVertex3d(0.0, altura,  0.0);
		glTexCoord2f(2*folha_temp, 0.0); glVertex3d(largura/2.0, altura/2.0,  0.0);		
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(x, 0.0, -y);
	glRotated(90.0, 0.0,1.0,0.0 );
	glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,1.0);  
		glTexCoord2f(0.0, 0.0); glVertex3d(-largura/2.0, altura/2.0,  0.0);
		glTexCoord2f(folha_temp, folha_temp); glVertex3d(0.0, altura, 0.0);
		glTexCoord2f(2*folha_temp, 0.0); glVertex3d(largura/2.0, altura/2.0,  0.0);		
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(x, 0.0, -y);
	glRotated(-90.0, 0.0,1.0,0.0 );
	glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,-1.0);  
		glTexCoord2f(0.0, 0.0); glVertex3d(-largura/2.0, altura/2.0,  0.0);
		glTexCoord2f(folha_temp, folha_temp); glVertex3d(0.0, altura,  0.0);
		glTexCoord2f(2*folha_temp, 0.0); glVertex3d(largura/2.0, altura/2.0,  0.0);		
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}

void janela(double dim)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, janela_texture);
	glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,1.0); 
		glTexCoord2f(0.0,0.0); glVertex3d(0.0, 0.0,  0.0);
		glTexCoord2f(1.0,0.0); glVertex3d(dim,0.0,  0.0);
		glTexCoord2f(1.0,1.0); glVertex3d(dim, dim, 0.0);
		glTexCoord2f(0.0,1.0); glVertex3d(0.0, dim, 0.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}


void holofote(int LIGHT)
{
	GLUquadric* glQ;
	glQ = gluNewQuadric();
	
	float luz;
	float holofote_pos[4], holofote_direction[4];

	glPushMatrix();
		glRotated(-90.0, 1.0,0.0,0.0 );
	
		//poste
		gluQuadricTexture(glQ, GL_TRUE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, holo_base_texture);

		glColor3f(1.0,0.0,0.0);	
		gluCylinder(glQ, poste_r, poste_r, poste_altura, nslices, nstacks);
		glPushMatrix();
			glTranslated(0.0, 0.0, poste_altura);
			gluDisk(glQ, 0.0, poste_r, nslices, nstacks);
		glPopMatrix();
	
		holofote_direction[0]=0.0;
		holofote_direction[1]=1.0;
		holofote_direction[2]=-1.0;
		holofote_direction[3]=1.0;

		holofote_pos[0]=0;
		holofote_pos[1]=5;
		holofote_pos[2]=poste_altura+2;
		holofote_pos[3]=1.0;
	
		glLightfv(LIGHT, GL_POSITION, holofote_pos);
		glLightfv(LIGHT, GL_SPOT_DIRECTION, holofote_direction);
		glLightfv(LIGHT, GL_AMBIENT, holofote_ambient);
		glLightfv(LIGHT, GL_DIFFUSE, holofote_diffuse);
		glLightfv(LIGHT, GL_SPECULAR, holofote_specular);
		glLightf(LIGHT, GL_CONSTANT_ATTENUATION,  holofote_kc);
		glLightf(LIGHT, GL_LINEAR_ATTENUATION,    holofote_kl);
		glLightf(LIGHT, GL_QUADRATIC_ATTENUATION, holofote_kq);
		glLightfv(LIGHT, GL_SPOT_CUTOFF, &ang);
	
		glTranslated(0.0, 2*baseSup_r, poste_altura);
		glRotated(45.0, 1.0, 0.0, 0.0);
		//abat-jour
		gluCylinder(glQ, baseInf_r, baseSup_r, base_altura, nslices, nstacks);
		glPushMatrix();
			glTranslated(0.0, 0.0, base_altura);	
			gluDisk(glQ, 0.0, baseSup_r, nslices, nstacks);

			glDisable(GL_TEXTURE_2D);	
			gluQuadricTexture(glQ, GL_FALSE);

		glPopMatrix();

		glPopMatrix();

	glPopMatrix();
}



void heliporto(void)
{

	// DECLARACOES RELACIONADAS COM OS "EVALUATORS"
	GLfloat ctrlpoints[4][3] = {	{dimx1+heliporto_x1, 0.5, heliporto_y1},
									{dimx1+heliporto_x1, 0.5, heliporto_y2}, 
									{dimx1+heliporto_x2, 0.5, heliporto_y1},
									{dimx1+heliporto_x2, 0.5, heliporto_y2} };

	GLfloat nrmlcompon[4][3] = {	{  0.0, 1.0, 0.0},
									{  0.0, 1.0, 0.0}, 
									{  0.0, 1.0, 0.0},
									{  0.0, 1.0, 0.0} };

	GLfloat textpoints[4][2] = {	{ 0.0, 0.0},
									{ 0.0, 1.0}, 
									{ 1.0, 0.0},
									{ 1.0, 1.0} };


	// INICIALIZACOES RELACIONADAS COM OS "EVALUATORS"
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 2,  0.0, 1.0, 6, 2,  &ctrlpoints[0][0]);
	glMap2f(GL_MAP2_NORMAL,   0.0, 1.0, 3, 2,  0.0, 1.0, 6, 2,  &nrmlcompon[0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2,  0.0, 1.0, 2, 2,  0.0, 1.0, 4, 2,  &textpoints[0][0]);

	// os interpoladores activam-se:
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_NORMAL);
	glEnable(GL_MAP2_TEXTURE_COORD_2);
	glMapGrid2f(200, 0.0,1.0, 150, 0.0,1.0); 

	//meu comeca aqui
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, heliporto_texture);
	glEvalMesh2(GL_FILL, 0,200, 0,150);
	glDisable(GL_TEXTURE_2D);


	//canto inferior esquerdo	
	glPushMatrix();
		glTranslated(dimx1+heliporto_x1+poste_r, 0.0, heliporto_y1-poste_r);
		glRotated(-45.0, 0.0, 1.0, 0.0);
		holofote(GL_LIGHT1);
	glPopMatrix();

	//canto superior esquerdo
	glPushMatrix();
		glTranslated(dimx1+heliporto_x1+poste_r, 0.0,heliporto_y2+poste_r);
		glRotated(-135.0, 0.0, 1.0, 0.0);
		holofote(GL_LIGHT2);
	glPopMatrix();

	//canto superior direito	
	glPushMatrix();
		glTranslated(dimx1+heliporto_x2-poste_r, 0.0, heliporto_y2+poste_r);
		glRotated(135.0, 0.0, 1.0, 0.0);
		holofote(GL_LIGHT3);
	glPopMatrix();

	//canto inferior direito
	glPushMatrix();
		glTranslated(dimx1+heliporto_x2-poste_r, 0.0, heliporto_y1-poste_r);
		glRotated(45.0, 0.0, 1.0, 0.0);
		holofote(GL_LIGHT4);
	glPopMatrix();

}

void hospital(void)
{
	glPushMatrix();
	glTranslated(167.5, 0.0, -190.0);
	
		glEnable(GL_TEXTURE_2D);
		//paredes
		glBindTexture(GL_TEXTURE_2D, wall_texture);

		glBegin(GL_POLYGON);
			glNormal3d(0.0,0.0,1.0);  
			glTexCoord2f(0.0, 0.0); glVertex3d(0.0, 0.0,  0.0);
			glTexCoord2f(5.0, 0.0); glVertex3d(115.0, 0.0,  0.0);
			glTexCoord2f(5.0, 5.0); glVertex3d(115.0, 115.0,  0.0);	
			glTexCoord2f(0.0, 5.0); glVertex3d(0.0, 115.0,  0.0);
		glEnd();

		glPushMatrix();
		glTranslated(115.0, 0.0, -70.0);
		glRotated(180.0, 0.0,1.0,0.0 );
		glBegin(GL_POLYGON);
			glNormal3d(0.0,0.0,1.0);  
			glTexCoord2f(0.0, 0.0); glVertex3d(0.0, 0.0,  0.0);
			glTexCoord2f(5.0, 0.0); glVertex3d(115.0, 0.0,  0.0);
			glTexCoord2f(5.0, 5.0); glVertex3d(115.0, 115.0,  0.0);	
			glTexCoord2f(0.0, 5.0); glVertex3d(0.0, 115.0,  0.0);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslated(0.0, 0.0, -70.0);
		glRotated(-90.0, 0.0,1.0,0.0 );
		glBegin(GL_POLYGON);
			glNormal3d(0.0,0.0,1.0);  
			glTexCoord2f(0.0, 0.0); glVertex3d(0.0, 0.0,  0.0);
			glTexCoord2f(3.0, 0.0); glVertex3d(70.0, 0.0,  0.0);
			glTexCoord2f(3.0, 5.0); glVertex3d(70.0, 115.0,  0.0);	
			glTexCoord2f(0.0, 5.0); glVertex3d(0.0, 115.0,  0.0);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslated(115.0, 0.0, 0.0);
		glRotated(90.0, 0.0,1.0,0.0 );
		glBegin(GL_POLYGON);
			glNormal3d(0.0,0.0,1.0);  
			glTexCoord2f(0.0, 0.0); glVertex3d(0.0, 0.0,  0.0);
			glTexCoord2f(3.0, 0.0); glVertex3d(70.0, 0.0,  0.0);
			glTexCoord2f(3.0, 5.0); glVertex3d(70.0, 115.0,  0.0);	
			glTexCoord2f(0.0, 5.0); glVertex3d(0.0, 115.0,  0.0);
		glEnd();
		glPopMatrix();

		//telhado
		glBindTexture(GL_TEXTURE_2D, roof_texture);

		glPushMatrix();
		glTranslated(-7.5, 115.0, -77.5);
		glRotated(90.0, 1.0,0.0,0.0 );
		glBegin(GL_POLYGON);
			glNormal3d(0.0,0.0,1.0);  
			glVertex3d(0.0, 0.0,  0.0);
			glVertex3d(130.0, 0.0,  0.0);
			glVertex3d(130.0, 85.0,  0.0);	
			glVertex3d(0.0, 85.0,  0.0);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslated(-7.5, 115.0, 7.5);
		glBegin(GL_POLYGON);
			glNormal3d(0.0,0.0,1.0); //ver normal 
			glTexCoord2f(0.0, 0.0); glVertex3d(0.0, 0.0,  0.0);
			glTexCoord2f(5.0, 0.0); glVertex3d(130.0, 0.0,  0.0);
			glTexCoord2f(3.0, 3.0); glVertex3d(97.5, 10.0, -42.5);	
			glTexCoord2f(0.0, 3.0); glVertex3d(32.5, 10.0,  -42.5);
		glEnd();
		glPopMatrix();
	
		glPushMatrix();
		glTranslated(122.5, 115.0, -77.5);
		glRotated(180.0, 0.0,1.0,0.0);
		glBegin(GL_POLYGON);
			glNormal3d(0.0,0.0,1.0);  //ver normal 
			glTexCoord2f(5.0, 0.0); glVertex3d(0.0, 0.0,  0.0);
			glTexCoord2f(0.0, 0.0); glVertex3d(130.0, 0.0,  0.0);
			glTexCoord2f(0.0, 3.0); glVertex3d(97.5, 10.0, -42.5);	
			glTexCoord2f(3.0, 0.0); glVertex3d(32.5, 10.0,  -42.5);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslated(-7.5, 115.0, 7.5);
		glBegin(GL_POLYGON);
			glNormal3d(0.0,0.0,1.0); //ver normal 
			glTexCoord2f(0.0, 0.0); glVertex3d(0.0, 0.0,  0.0);
			glTexCoord2f(5.0, 0.0); glVertex3d(32.5, 10.0,  -42.5);
			glTexCoord2f(10.0, 3.0); glVertex3d(0.0, 0.0, -85);
		glEnd();
		glPopMatrix();

		glPushMatrix(); 
		glTranslated(122.5, 115.0, -77.5);
		glRotated(180.0, 0.0,1.0,0.0);
		glBegin(GL_POLYGON);
			glNormal3d(0.0,0.0,1.0); //ver normal 
			glTexCoord2f(0.0, 0.0); glVertex3d(0.0, 0.0,  0.0);
			glTexCoord2f(5.0, 0.0); glVertex3d(32.5, 10.0,  -42.5);
			glTexCoord2f(10.0, 3.0); glVertex3d(0.0, 0.0, -85);
		glEnd();
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);

		//janelas

			//frente
			glPushMatrix();
			glTranslated(3.0, 0.0, 0.0);	

				glPushMatrix();
				glTranslated(9.0, 9.0, 0.1);
				janela(18.0);
				glPopMatrix();

				glPushMatrix();
				glTranslated(9.0, 45.0, 0.1);
				janela(18.0);
				glPopMatrix();

				glPushMatrix();
				glTranslated(9.0, 81.0, 0.1);
				janela(18.0);
				glPopMatrix();

				glPushMatrix();
				glTranslated(45.0, 45.0, 0.1);
				janela(18.0);
				glPopMatrix();

				glPushMatrix();
				glTranslated(45.0, 81.0, 0.1);
				janela(18.0);
				glPopMatrix();

				glPushMatrix();
				glTranslated(81.0, 9.0, 0.1);
				janela(18.0);
				glPopMatrix();

				glPushMatrix();
				glTranslated(81.0, 45.0, 0.1);
				janela(18.0);
				glPopMatrix();

				glPushMatrix();
				glTranslated(81.0, 81.0, 0.1);
				janela(18.0);
				glPopMatrix();

			glPopMatrix();

			//tras
			glPushMatrix();
			glTranslated(115.0, 0.0, -72.0);
			glRotated(180.0, 0.0, 1.0, 0.0);

				glPushMatrix();
				glTranslated(9.0, 9.0, 0.1);
				janela(18.0);
				glPopMatrix();

				glPushMatrix();
				glTranslated(9.0, 45.0, 0.1);
				janela(18.0);
				glPopMatrix();

				glPushMatrix();
				glTranslated(9.0, 81.0, 0.1);
				janela(18.0);
				glPopMatrix();

				glPushMatrix();
				glTranslated(45.0, 9.0, 0.1);
				janela(18.0);
				glPopMatrix();

				glPushMatrix();
				glTranslated(45.0, 45.0, 0.1);
				janela(18.0);
				glPopMatrix();

				glPushMatrix();
				glTranslated(45.0, 81.0, 0.1);
				janela(18.0);
				glPopMatrix();

				glPushMatrix();
				glTranslated(81.0, 9.0, 0.1);
				janela(18.0);
				glPopMatrix();

				glPushMatrix();
				glTranslated(81.0, 45.0, 0.1);
				janela(18.0);
				glPopMatrix();

				glPushMatrix();
				glTranslated(81.0, 81.0, 0.1);
				janela(18.0);
				glPopMatrix();

			glPopMatrix();

			//esq
			glPushMatrix();
			glTranslated(0.0, 0.0, -71.0);
			glRotated(-90.0, 0.0, 1.0, 0.0);

				glPushMatrix();
				glTranslated(9.0, 9.0, 0.1);
				janela(18.0);
				glPopMatrix();

				glPushMatrix();
				glTranslated(9.0, 45.0, 0.1);
				janela(18.0);
				glPopMatrix();

				glPushMatrix();
				glTranslated(9.0, 81.0, 0.1);
				janela(18.0);
				glPopMatrix();

				glPushMatrix();
				glTranslated(45.0, 9.0, 0.1);
				janela(18.0);
				glPopMatrix();

				glPushMatrix();
				glTranslated(45.0, 45.0, 0.1);
				janela(18.0);
				glPopMatrix();

				glPushMatrix();
				glTranslated(45.0, 81.0, 0.1);
				janela(18.0);
				glPopMatrix();

			glPopMatrix();

			//dir
			glPushMatrix();
			glTranslated(117.0, 0.0, 0.0);
			glRotated(90.0, 0.0, 1.0, 0.0);

				glPushMatrix();
				glTranslated(9.0, 9.0, 0.1);
				janela(18.0);
				glPopMatrix();

				glPushMatrix();
				glTranslated(9.0, 45.0, 0.1);
				janela(18.0);
				glPopMatrix();

				glPushMatrix();
				glTranslated(9.0, 81.0, 0.1);
				janela(18.0);
				glPopMatrix();

				glPushMatrix();
				glTranslated(45.0, 9.0, 0.1);
				janela(18.0);
				glPopMatrix();

				glPushMatrix();
				glTranslated(45.0, 45.0, 0.1);
				janela(18.0);
				glPopMatrix();

				glPushMatrix();
				glTranslated(45.0, 81.0, 0.1);
				janela(18.0);
				glPopMatrix();

			glPopMatrix();

		//porta
		glPushMatrix();
		glTranslated(45.5, 0.0, 0.1);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, wood_texture);
			glBegin(GL_POLYGON);
				glNormal3d(0.0,0.0,1.0); 
				glTexCoord2f(0.0,0.0); glVertex3d(0.0, 0.0,  0.0);
				glTexCoord2f(1.0,0.0); glVertex3d(24.0,0.0,  0.0);
				glTexCoord2f(1.0,1.0); glVertex3d(24.0, 36.0, 0.0);
				glTexCoord2f(0.0,1.0); glVertex3d(0.0, 36.0, 0.0);
			glEnd();
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		//letreiro
		
		glPushMatrix();
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);
		glTranslatef(20.0,120.0,-7.5);
		glScalef(0.3, 0.3, 0.3);
		glColor3f(1.0,1.0,0.0);		// amarelo
		glLineWidth(5.0);
		glutStrokeCharacter(GLUT_STROKE_ROMAN, 'H');
		glutStrokeCharacter(GLUT_STROKE_ROMAN, 'S');	
		glutStrokeCharacter(GLUT_STROKE_ROMAN, 'J');
		glColor3f(1.0,1.0,1.0);	
		glDisable(GL_COLOR_MATERIAL);
		
		glPopMatrix();
	glPopMatrix();

}

void hangar()
{
	int slices = 12;
	int smooth = TRUE;
	double radius = 93.0/2.0;
	double height = -145.0;

	const double pi = acos(-1.0);
	double delta= pi/slices;
	double alfa=0, beta=0;
	double norm_x, norm_y, norm_x1, norm_y1;	//coordenadas x e y do vector normal ?superficie

	glDisable(GL_CULL_FACE);

	// DECLARACOES RELACIONADAS COM OS "EVALUATORS"
	GLfloat ctrlpoints[4][4][3] = { { {0.0, 0.0, 0.0}, {radius/2, radius*sin(pi/3.0), 0.0}, {93-radius/2, radius*sin(pi/3.0), 0.0}, {93, 0.0, 0.0} },
		{ {0.0, 0.0, height/4}, {radius/2, radius*sin(pi/3.0), height/4}, {93-radius/2, radius*sin(pi/3.0), height/4}, {93, 0.0, height/4} },
		{ {0.0, 0.0, height/2}, {radius/2, radius*sin(pi/3.0), height/2}, {93-radius/2, radius*sin(pi/3.0), height/2}, {93, 0.0, height/2} },
		{ {0.0, 0.0, height}, {radius/2, radius*sin(pi/3.0), height}, {93-radius/2, radius*sin(pi/3.0), height}, {93, 0.0, height} } };

	GLfloat nrmlcompon[4][4][3] = { { {-1.0, 0.0, 0.0}, {-0.5, sin(pi/3.0), 0.0}, {0.5, sin(pi/3.0), 0.0}, {1.0, 0.0, 0.0} }, 
		{ {-1.0, 0.0, 0.0}, {-0.5, sin(pi/3.0), 0.0}, {0.5, sin(pi/3.0), 0.0}, {1.0, 0.0, 0.0} },
		{ {-1.0, 0.0, 0.0}, {-0.5, sin(pi/3.0), 0.0}, {0.5, sin(pi/3.0), 0.0}, {1.0, 0.0, 0.0} },
		{ {-1.0, 0.0, 0.0}, {-0.5, sin(pi/3.0), 0.0}, {0.5, sin(pi/3.0), 0.0}, {1.0, 0.0, 0.0} } };

	// INICIALIZACOES RELACIONADAS COM OS "EVALUATORS"
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 2,  0.0, 1.0, 6, 2,  &ctrlpoints[0][0][0]);
	glMap2f(GL_MAP2_NORMAL,   0.0, 1.0, 3, 2,  0.0, 1.0, 6, 2,  &nrmlcompon[0][0][0]);
	
	// os interpoladores activam-se:
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_NORMAL);

	glMapGrid2f(20, 0.0,1.0, 30, 0.0,1.0);

	glShadeModel(GL_SMOOTH);

	//meu comeca aqui
	glEvalMesh2(GL_FILL, 0,20, 0,30);

	
	glPushMatrix();
	glTranslated(307.0+93.0/2.0, 0.0, -125.0);
	/*
	while(slices > 0)
	{
		beta= alfa+delta - (delta/2);	//ângulo auxiliar para calcular o vector normal ao plano

		norm_x= cos(beta)/ sqrt(cos(beta)*cos(beta)+sin(beta)*sin(beta));	//
		norm_y= sin(beta)/ sqrt(cos(beta)*cos(beta)+sin(beta)*sin(beta));

		//construçao de uma face do prisma
		
		//normal da 1?aresta
		norm_x= cos(alfa)/ sqrt(cos(alfa)*cos(alfa)+sin(alfa)*sin(alfa));
		norm_y= sin(alfa)/ sqrt(cos(alfa)*cos(alfa)+sin(alfa)*sin(alfa));
		//normal da 2?aresta
		norm_x1= cos(alfa+delta)/ sqrt(cos(alfa+delta)*cos(alfa+delta)+sin(alfa+delta)*sin(alfa+delta));
		norm_y1= sin(alfa+delta)/ sqrt(cos(alfa+delta)*cos(alfa+delta)+sin(alfa+delta)*sin(alfa+delta));

			//construção da face j?com smooth shading
			glBegin(GL_POLYGON);								
				glNormal3d(norm_x1, norm_y1, 0.0);	//normal da 2?aresta
				glVertex3d(radius*cos(alfa+delta),	radius*sin(alfa+delta),	-height);
				glVertex3d(radius*cos(alfa+delta),	radius*sin(alfa+delta),	0.0);
				glNormal3d(norm_x, norm_y, 0.0);	//normal da 1?aresta.
				glVertex3d(radius*cos(alfa),		radius*sin(alfa),		0.0);
				glVertex3d(radius*cos(alfa),		radius*sin(alfa),		-height);
			glEnd();


		--slices;
		alfa += delta;	//proximo angulo
	}*/
	glEnable(GL_CULL_FACE);
		glPopMatrix();

}

double torre_r = 25.0/2.0;
double torre_altura = 95.0;
double plataforma_r = 90.0/2.0;
double plataforma_altura = 7.0;

void torre()
{
	GLUquadric* glQ;
	glQ = gluNewQuadric();

	//base
	gluQuadricTexture(glQ, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, torre_base_texture);

	glPushMatrix();
	glTranslated(415.0+25.0/2,0.0,-220.0-torre_r);
	glRotated(-90.0, 1.0,0.0,0.0 );
	gluCylinder(glQ, torre_r, torre_r, torre_altura, nslices, nstacks);   
	glPopMatrix();

	//plataforma
	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, plataform_texture);
	glPushMatrix();
	glTranslated(415.0+torre_r,torre_altura,-220.0-torre_r);
	glRotated(-90.0, 1.0,0.0,0.0 );
	glPushMatrix();
	glRotated(180.0, 1.0,0.0,0.0 );
	gluDisk(glQ, 0.0, plataforma_r, nslices, nstacks);
	glPopMatrix();
	gluCylinder(glQ, plataforma_r, plataforma_r, plataforma_altura, nslices, nstacks);   
	gluDisk(glQ, 0.0, plataforma_r, nslices, nstacks);   
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);	
	gluQuadricTexture(glQ, GL_FALSE);
	//Cupula semi-esferica
	double clip_sphere[]={0.0,0.0,1.0,0.0}; 

	material2();

	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CLIP_PLANE1);
	glPushMatrix();			
		glTranslatef(415.0+torre_r,torre_altura+plataforma_altura,-220.0-torre_r);
		glRotated(-90.0,1.0,0.0,0.0);
		glClipPlane(GL_CLIP_PLANE1,clip_sphere);
		gluSphere(glQ,plataforma_r,nslices,nstacks);
	glPopMatrix();
	glDisable(GL_CLIP_PLANE1);
	glDisable (GL_BLEND);

	material1();
}
