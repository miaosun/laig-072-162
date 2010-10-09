
double base1_r = 3.0/2.0;
double base2_r = 2.0/2.0;
double base1_lth = 24.0;
double base2_lth = 7.0;
int nslices = 23;
int nstacks = 1;

double cauda_r1 = 5.0;
double cauda_r2 = 3.0;
double cauda_length = 30;

double alpha = 15.0;
double belta = 25.0;
double distancia = -13;

double corpo_r = 12.0;

void apois_helicoptero()
{
	GLUquadric* glQ;
	glQ = gluNewQuadric();

	glPushMatrix();
	glTranslated(-base1_lth/2.0, 0.0, 0.0);
	glRotated(-90.0, 0.0, 1.0, 0.0);
	glRotated(180.0, 1.0, 0.0, 0.0);

	//base em plano (mais comprido)
	glPushMatrix();
	gluDisk(glQ, 0.0, base1_r, nslices, nstacks);
	gluCylinder(glQ, base1_r, base1_r, base1_lth, nslices, nstacks);   
	glTranslated(0.0, 0.0, base1_lth);
	gluDisk(glQ, 0.0, base1_r, nslices, nstacks);
	glPopMatrix();
	
	//base em horizontal (mais curto)
	glPushMatrix();
	glTranslated(0.0, 0.0, base2_lth);
	glRotated(90.0, 1.0, 0.0, 0.0);
	gluDisk(glQ, 0.0, base2_r, nslices, nstacks);
	gluCylinder(glQ, base1_r, base1_r, base2_lth, nslices, nstacks);   
	glTranslated(0.0, 0.0, base2_lth);
	gluDisk(glQ, 0.0, base1_r, nslices, nstacks);
	glPopMatrix();

	//base em horizontal (mais curto)
	glPushMatrix();
	glTranslated(0.0, 0.0, 17.0);
	glRotated(90.0, 1.0, 0.0, 0.0);
	gluDisk(glQ, 0.0, base2_r, nslices, nstacks);
	gluCylinder(glQ, base1_r, base1_r, base2_lth, nslices, nstacks);   
	glTranslated(0.0, 0.0, base2_lth);
	gluDisk(glQ, 0.0, base1_r, nslices, nstacks);
	glPopMatrix();

	glPopMatrix();
}

void base()
{
	glPushMatrix();
	glTranslated(0.0, 0.0, -distancia/2.0);
	glRotated(-alpha, 1.0, 0.0, 0.0);
	apois_helicoptero();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, 0.0, distancia/2.0);
	glRotated(alpha, 1.0, 0.0, 0.0);
	apois_helicoptero();
	glPopMatrix();
}


void triangulo1()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 6);
	glBegin(GL_POLYGON);
		glNormal3d(0.0,1.0,0.0);  // esta normal fica comum aos 4 vertices
		glTexCoord2f(0.0,0.0);  glVertex3d(0.0, 0.0, 0.0);
		glTexCoord2f(10.0,0.0); glVertex3d(9.0, 0.0, 2.5);
		glTexCoord2f(10.0,5.0); glVertex3d(9.0, 0.0, -2.5);		
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void triangulo2()
{
	glPushMatrix();
	glScaled(3.0, 0.0, 1.0/2.0);
	triangulo1();
	glPopMatrix();
}

void helice1()
{
	glPushMatrix();
	glRotated(-90.0, 1.0, 0.0, 0.0);

	triangulo1();

	glPushMatrix();
	glRotated(120.0, 0.0, 1.0, 0.0);
	triangulo1();
	glPopMatrix();

	glPushMatrix();
	glRotated(240.0, 0.0, 1.0, 0.0);
	triangulo1();
	glPopMatrix();

	glPopMatrix();
}

void cauda()
{
	GLUquadric* glQ;
	glQ = gluNewQuadric();

	glPushMatrix();
	glTranslated(corpo_r, corpo_r+base2_lth+base1_r, 0.0);
	glRotated(-90.0, 0.0, 1.0, 0.0);
	glRotated(20.0, 1.0, 0.0, 0.0);
	glTranslated(0.0, 0.0, -cauda_length);

	glPushMatrix();
	gluDisk(glQ, 0.0, cauda_r2, nslices, nstacks);
	gluCylinder(glQ, cauda_r2, cauda_r1, cauda_length, nslices, nstacks);   
	glTranslated(0.0, 0.0, cauda_length);
	gluDisk(glQ, 0.0, cauda_r1, nslices, nstacks);
	glPopMatrix();

	helice1();
	glPopMatrix();
}

void topo()
{
	GLUquadric* glQ;
	glQ = gluNewQuadric();

	glPushMatrix();
	glTranslated(0.0, 2*corpo_r+base2_lth, 0.0);

	triangulo2();

	glPushMatrix();
	glRotated(120.0, 0.0, 1.0, 0.0);
	triangulo2();
	glPopMatrix();

	glPushMatrix();
	glRotated(240.0, 0.0, 1.0, 0.0);
	triangulo2();
	glPopMatrix();

	glPushMatrix();
	glRotated(90.0, 1.0, 0.0, 0.0);
	gluDisk(glQ, 0.0, 2*base2_r, nslices, nstacks);
	gluCylinder(glQ, 2*base2_r, 2*base2_r, base2_lth, nslices, nstacks);   
	glTranslated(0.0, 0.0, base2_lth);
	gluDisk(glQ, 0.0, 2*base2_r, nslices, nstacks);
	glPopMatrix();

	glPopMatrix();
}


void corpo()
{
	GLUquadric* glQ;
	glQ = gluNewQuadric();

	glPushMatrix();	
		gluSphere(glQ,corpo_r,nslices,nstacks);
	glPopMatrix();
}

void helicoptero()
{
	base();
	cauda();
	topo();
	corpo();

}