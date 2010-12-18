
#include "Variaveis.h"

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
	glTranslated(0.0, 0.0, 0.0);
		
	glPushName(0);
		
		glPushMatrix();
		glTranslated(-dimCasa-dimCasa/2+(dimCasa-dimcube)/2, 0.0, -2*dimCasa-dimCasa/2);
		glCallList(cube);
		glPopMatrix();
		for(int i=1; i<3; i++)
		{
			glLoadName(i);
			glPushMatrix();
			glTranslated(-dimCasa-dimCasa/2+i*dimCasa+(dimCasa-dimcube)/2, 0.0, -2*dimCasa-dimCasa/2);
			glCallList(cube);
			glPopMatrix();

		}
		
		for(int i=0; i<5; i++)
		{
			glLoadName(i+3);
			glPushMatrix();
			glTranslated(-2*dimCasa-dimCasa/2+i*dimCasa+(dimCasa-dimcube)/2, 0.0, -dimCasa-dimCasa/2);
			glCallList(cube);
			glPopMatrix();
		}
		
		for(int i=0; i<7; i++)
		{
			glLoadName(i+8);
			glPushMatrix();
			glTranslated(-3*dimCasa-dimCasa/2+i*dimCasa+(dimCasa-dimcube)/2, 0.0, -dimCasa/2);
			glCallList(cube);
			glPopMatrix();
		}

		for(int i=0; i<7; i++)
		{
			glLoadName(i+15);
			glPushMatrix();
			glTranslated(-3*dimCasa-dimCasa/2+i*dimCasa+(dimCasa-dimcube)/2, 0.0, dimCasa/2);
			glCallList(cube);
			glPopMatrix();
		}

		for(int i=0; i<7; i++)
		{
			glLoadName(i+22);
			glPushMatrix();
			glTranslated(-3*dimCasa-dimCasa/2+i*dimCasa+(dimCasa-dimcube)/2, 0.0, dimCasa+dimCasa/2);
			glCallList(cube);
			glPopMatrix();
		}

		for(int i=0; i<5; i++)
		{
			glLoadName(i+29);
			glPushMatrix();
			glTranslated(-2*dimCasa-dimCasa/2+i*dimCasa+(dimCasa-dimcube)/2, 0.0, 2*dimCasa+dimCasa/2);
			glCallList(cube);
			glPopMatrix();
		}
		
		for(int i=0; i<3; i++)
		{
			glLoadName(i+34);
			glPushMatrix();
			glTranslated(-dimCasa-dimCasa/2+i*dimCasa+(dimCasa-dimcube)/2, 0.0, 3*dimCasa+dimCasa/2);
			glCallList(cube);
			glPopMatrix();
		}
	glPopMatrix();
}

void pickingAction(GLuint answer) {
	printf("%d\n", answer);
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

struct g_mouseState{
	bool leftButton;
	bool rightButton;
	bool middleButton;
	int x;
	int y;
} MouseState;