#include "helicoptero.h"

const int TRUE  = 1;
const int FALSE = 0;

double dimx1 = 150.0;
double dimx2 = 300.0;
double dimx3 = 450.0;
double dimy  =-300.0;

void chao(void)
{
	//rectangulo 1
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 5);
	glBegin(GL_POLYGON);
		glNormal3d(0.0,1.0,0.0);  // esta normal fica comum aos 4 vertices
		glTexCoord2f(0.0,0.0); glVertex3d( 0.0, 0.0,  0.0);
		glTexCoord2f(10.0,0.0); glVertex3d(dimx1, 0.0,  0.0);
		glTexCoord2f(10.0,5.0); glVertex3d(dimx1, 0.0,  dimy);
		glTexCoord2f(0.0,5.0); glVertex3d(0.0, 0.0,  dimy);		
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//rectangulo 2
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 7);
	glBegin(GL_POLYGON);
		glNormal3d(0.0,1.0,0.0);  // esta normal fica comum aos 4 vertices
		glTexCoord2f(0.0,0.0); glVertex3d(dimx1, 0.0,  0.0);
		glTexCoord2f(8.0,0.0); glVertex3d(dimx2, 0.0,  0.0);
		glTexCoord2f(8.0,4.0); glVertex3d(dimx2, 0.0,  dimy);
		glTexCoord2f(0.0,4.0); glVertex3d(dimx1, 0.0,  dimy);		
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//rectangulo 3
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 6);
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
	glBindTexture(GL_TEXTURE_2D, 6);
	glPushMatrix();
	glTranslated(x, 0.0, -y);
	glRotated(-90.0, 1.0,0.0,0.0 );
	gluCylinder(glQ, largura/10.0, 0.0, altura/2.0, 10.0, 5.0);   // nao tem bases
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//copa
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 5);
	glPushMatrix();
	glTranslated(x, altura/2.0, -y);
	glRotated(-90.0, 1.0,0.0,0.0 );
	gluCylinder(glQ, largura/2.0, 0.0, altura/2.0, 10.0, 5.0);   // nao tem bases
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void arvore_X(double x, double y, double altura, double largura)
{
	GLUquadric* glQ;
	glQ = gluNewQuadric();
	
	//tronco
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 6);
	glPushMatrix();
	glTranslated(x, 0.0, -y);
	glRotated(-90.0, 1.0,0.0,0.0 );
	gluCylinder(glQ, largura/10.0, 0.0, altura, 10.0, 5.0);   // nao tem bases
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	//copa
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 5);
	glPushMatrix();
	glTranslated(x, 0.0, -y);
	glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,1.0);  
		glVertex3d(-largura/2.0, altura/2.0,  0.0);
		glVertex3d(0.0, altura,  0.0);
		glVertex3d(largura/2.0, altura/2.0,  0.0);		
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(x, 0.0, -y);
	glRotated(180.0, 0.0,1.0,0.0 );
	glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,1.0);  
		glVertex3d(-largura/2.0, altura/2.0,  0.0);
		glVertex3d(0.0, altura,  0.0);
		glVertex3d(largura/2.0, altura/2.0,  0.0);		
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(x, 0.0, -y);
	glRotated(90.0, 0.0,1.0,0.0 );
	glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,1.0);  
		glVertex3d(-largura/2.0, altura/2.0,  0.0);
		glVertex3d(0.0, altura,  0.0);
		glVertex3d(largura/2.0, altura/2.0,  0.0);		
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslated(x, 0.0, -y);
	glRotated(-90.0, 0.0,1.0,0.0 );
	glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,1.0);  
		glVertex3d(-largura/2.0, altura/2.0,  0.0);
		glVertex3d(0.0, altura,  0.0);
		glVertex3d(largura/2.0, altura/2.0,  0.0);		
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

}

void janela(double dim)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 8);
	glBegin(GL_POLYGON);
		glNormal3d(0.0,0.0,1.0); 
		glTexCoord2f(0.0,0.0); glVertex3d(0.0, 0.0,  0.0);
		glTexCoord2f(1.0,0.0); glVertex3d(dim,0.0,  0.0);
		glTexCoord2f(1.0,1.0); glVertex3d(dim, dim, 0.0);
		glTexCoord2f(0.0,1.0); glVertex3d(0.0, dim, 0.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

double poste_r = 3.0/2.0;
double poste_altura = 47.0;
double baseInf_r = 13.0/2.0;
double baseSup_r = 7.0/2.0;
double base_altura = 7.0;

void holofote(int tipo)
{
	GLUquadric* glQ;
	glQ = gluNewQuadric();
		
	glPushMatrix();
	glRotated(-90.0, 1.0,0.0,0.0 );
	
	//poste
	glColor3f(1.0,0.0,0.0);	
	gluCylinder(glQ, poste_r, poste_r, poste_altura, nslices, nstacks);
	glPushMatrix();
	glTranslated(0.0, 0.0, poste_altura);
	gluDisk(glQ, 0.0, poste_r, nslices, nstacks);
	glPopMatrix();
	

	glPushMatrix();
	switch (tipo)
	{
	case 1://canto inferior esquerdo	
		glRotated(-45.0, 0.0, 0.0, 1.0);		
		break;
	case 2://canto superior esquerdo			
		glRotated(-135.0, 0.0, 0.0, 1.0);
		break;
	case 3://canto superior direito	
		glRotated(135.0, 0.0, 0.0, 1.0);
		break;
	case 4://canto inferior direito	
		glRotated(45.0, 0.0, 0.0, 1.0);
		break;
	default:
		break;
	}
	glTranslated(0.0, baseSup_r, poste_altura);
	glRotated(45.0, 1.0, 0.0, 0.0);
    //abat-jour
	gluCylinder(glQ, baseInf_r, baseSup_r, base_altura, nslices, nstacks);
	glPushMatrix();
	glTranslated(0.0, 0.0, base_altura);
	gluDisk(glQ, 0.0, baseSup_r, nslices, nstacks);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
}

double heliporto_x1 = 45.0/2.0;
double heliporto_x2 = heliporto_x1+105.0;
double heliporto_y1 = -75.0/2.0;
double heliporto_y2 = heliporto_y1-75.0;

void heliporto(void)
{

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 5);
	glBegin(GL_POLYGON);
		glNormal3d(0.0,1.0,0.0);  // esta normal fica comum aos 4 vertices
		glTexCoord2f(0.0,0.0);  glVertex3d(dimx1+heliporto_x1, 0.5, heliporto_y1);
		glTexCoord2f(10.0,0.0); glVertex3d(dimx1+heliporto_x2, 0.5, heliporto_y1);
		glTexCoord2f(10.0,5.0); glVertex3d(dimx1+heliporto_x2, 0.5, heliporto_y2);
		glTexCoord2f(0.0,5.0);  glVertex3d(dimx1+heliporto_x1, 0.5, heliporto_y2);		
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//canto inferior esquerdo	
	glPushMatrix();
	glTranslated(dimx1+heliporto_x1+poste_r, 0.0, heliporto_y1-poste_r);
	holofote(1);
	glPopMatrix();

	//canto superior esquerdo
	glPushMatrix();
	glTranslated(dimx1+heliporto_x1+poste_r, 0.0,heliporto_y2+poste_r);
	holofote(2);
	glPopMatrix();

	//canto superior direito	
	glPushMatrix();
	glTranslated(dimx1+heliporto_x2-poste_r, 0.0, heliporto_y2+poste_r);
	holofote(3);
	glPopMatrix();

	//canto inferior direito
	glPushMatrix();
	glTranslated(dimx1+heliporto_x2-poste_r, 0.0, heliporto_y1-poste_r);
	holofote(4);
	glPopMatrix();

}

void hospital(void)
{
	glPushMatrix();
	glTranslated(167.5, 0.0, -190.0);
	
		//paredes
		glBegin(GL_POLYGON);
			glNormal3d(0.0,0.0,1.0);  
			glVertex3d(0.0, 0.0,  0.0);
			glVertex3d(115.0, 0.0,  0.0);
			glVertex3d(115.0, 115.0,  0.0);	
			glVertex3d(0.0, 115.0,  0.0);
		glEnd();
		glPushMatrix();
		glTranslated(115.0, 0.0, -70.0);
		glRotated(180.0, 0.0,1.0,0.0 );
		glBegin(GL_POLYGON);
			glNormal3d(0.0,0.0,1.0);  
			glVertex3d(0.0, 0.0,  0.0);
			glVertex3d(115.0, 0.0,  0.0);
			glVertex3d(115.0, 115.0,  0.0);	
			glVertex3d(0.0, 115.0,  0.0);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		glTranslated(0.0, 0.0, -70.0);
		glRotated(-90.0, 0.0,1.0,0.0 );
		glBegin(GL_POLYGON);
			glNormal3d(0.0,0.0,1.0);  
			glVertex3d(0.0, 0.0,  0.0);
			glVertex3d(70.0, 0.0,  0.0);
			glVertex3d(70.0, 115.0,  0.0);	
			glVertex3d(0.0, 115.0,  0.0);
		glEnd();
		glPopMatrix();
		glPushMatrix();
		glTranslated(115.0, 0.0, 0.0);
		glRotated(90.0, 0.0,1.0,0.0 );
		glBegin(GL_POLYGON);
			glNormal3d(0.0,0.0,1.0);  
			glVertex3d(0.0, 0.0,  0.0);
			glVertex3d(70.0, 0.0,  0.0);
			glVertex3d(70.0, 115.0,  0.0);	
			glVertex3d(0.0, 115.0,  0.0);
		glEnd();
		glPopMatrix();

		//telhado
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
			glVertex3d(0.0, 0.0,  0.0);
			glVertex3d(130.0, 0.0,  0.0);
			glVertex3d(97.5, 10.0, -42.5);	
			glVertex3d(32.5, 10.0,  -42.5);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslated(122.5, 115.0, -77.5);
		glRotated(180.0, 0.0,1.0,0.0);
		glBegin(GL_POLYGON);
			glNormal3d(0.0,0.0,1.0);  //ver normal 
			glVertex3d(0.0, 0.0,  0.0);
			glVertex3d(130.0, 0.0,  0.0);
			glVertex3d(97.5, 10.0, -42.5);	
			glVertex3d(32.5, 10.0,  -42.5);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslated(-7.5, 115.0, 7.5);
		glBegin(GL_POLYGON);
			glNormal3d(0.0,0.0,1.0); //ver normal 
			glVertex3d(0.0, 0.0,  0.0);
			glVertex3d(32.5, 10.0,  -42.5);
			glVertex3d(0.0, 0.0, -85);
		glEnd();
		glPopMatrix();

		glPushMatrix();
		glTranslated(122.5, 115.0, -77.5);
		glRotated(180.0, 0.0,1.0,0.0);
		glBegin(GL_POLYGON);
			glNormal3d(0.0,0.0,1.0); //ver normal 
			glVertex3d(0.0, 0.0,  0.0);
			glVertex3d(32.5, 10.0,  -42.5);
			glVertex3d(0.0, 0.0, -85);
		glEnd();
		glPopMatrix();

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
			glBindTexture(GL_TEXTURE_2D, 6);
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
		glTranslatef(20.0,115.0,-7.5);
		glScalef(0.3, 0.3, 0.3);
		glColor3f(0.0,1.0,0.0);		// azul
		glutStrokeCharacter(GLUT_STROKE_ROMAN, 'H');
		glutStrokeCharacter(GLUT_STROKE_ROMAN, 'S');
		glutStrokeCharacter(GLUT_STROKE_ROMAN, 'J');
		glPopMatrix();
		
	glPopMatrix();
}

void hangar()
{
	/*glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 2,  0.0, 1.0, 6, 2,  &ctrlpoints[0][0]);
	glMap2f(GL_MAP2_NORMAL,   0.0, 1.0, 3, 2,  0.0, 1.0, 6, 2,  &nrmlcompon[0][0]);
	glMap2f(GL_MAP2_COLOR_4,  0.0, 1.0, 4, 2,  0.0, 1.0, 8, 2,  &colorpoints[0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2,  0.0, 1.0, 2, 2,  0.0, 1.0, 4, 2,  &textpoints[0][0]);

	// os interpoladores activam-se:
	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_NORMAL);
	glEnable(GL_MAP2_COLOR_4);
	glEnable(GL_MAP2_TEXTURE_COORD_2);

	// para este conjunto de interpoladores:
	//    na direccao U, serao efectuadas divisoes em 40 passos
	//        quando a vari�vel U varia de 0 a 1
	//    na direccao V, serao efectuadas divisoes em 60 passos
	//        quando a vari�vel U varia de 0 a 1
	glMapGrid2f(40, 0.0,1.0, 60, 0.0,1.0); */

	int slices = 12;
	int smooth = TRUE;
	double radius = 93.0/2.0;
	double height = 145.0;

	const double pi = acos(-1.0);
	double delta= pi/slices;
	double alfa=0, beta=0;
	double norm_x, norm_y, norm_x1, norm_y1;	//coordenadas x e y do vector normal ?superficie
	glPushMatrix();
	glTranslated(307.0+93.0/2.0, 0.0, -125.0);

	while(slices > 0)
	{
		beta= alfa+delta - (delta/2);	//�ngulo auxiliar para calcular o vector normal ao plano

		norm_x= cos(beta)/ sqrt(cos(beta)*cos(beta)+sin(beta)*sin(beta));	//
		norm_y= sin(beta)/ sqrt(cos(beta)*cos(beta)+sin(beta)*sin(beta));

		//constru�ao de uma face do prisma
		
		//normal da 1?aresta
		norm_x= cos(alfa)/ sqrt(cos(alfa)*cos(alfa)+sin(alfa)*sin(alfa));
		norm_y= sin(alfa)/ sqrt(cos(alfa)*cos(alfa)+sin(alfa)*sin(alfa));
		//normal da 2?aresta
		norm_x1= cos(alfa+delta)/ sqrt(cos(alfa+delta)*cos(alfa+delta)+sin(alfa+delta)*sin(alfa+delta));
		norm_y1= sin(alfa+delta)/ sqrt(cos(alfa+delta)*cos(alfa+delta)+sin(alfa+delta)*sin(alfa+delta));

			//constru��o da face j?com smooth shading
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
	}
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
	glPushMatrix();
	glTranslated(415.0+25.0/2,0.0,-220.0-torre_r);
	glRotated(-90.0, 1.0,0.0,0.0 );
	gluCylinder(glQ, torre_r, torre_r, torre_altura, nslices, nstacks);   
	glPopMatrix();

	//plataforma
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

	double clip_sphere[]={0.0,0.0,1.0,0.0}; 

	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CLIP_PLANE1);
	glPushMatrix();	
		
		glTranslatef(415.0+torre_r,torre_altura+plataforma_altura,-220.0-torre_r);
		glRotated(-90.0,1.0,0.0,0.0);
		glClipPlane(GL_CLIP_PLANE1,clip_sphere);
		gluSphere(glQ,plataforma_r,33.0,10.0);
	glPopMatrix();
	glDisable(GL_CLIP_PLANE1);
	glDisable (GL_BLEND);
}
