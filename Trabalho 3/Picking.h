
#include "Variaveis.h"


void drawScene(GLenum mode)
{
	glFrustum( -xy_aspect*.04, xy_aspect*.04, -.04, .04, .1, 50.0 );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glTranslated(0.0,0.0,-30.0);
	glRotated(45.0, 1.0,0.0,0.0 );
    glTranslatef( obj_pos[0], obj_pos[1], -obj_pos[2] ); 
	glMultMatrixf( view_rotate );
	
	// tabuleiro
	if (mode == GL_SELECT)
		glPushName(0);

	glCallList(tableList);

	// esfera 1
	if (mode == GL_SELECT) 
		glLoadName (1);
	
	// define caracteristicas do material da esfera 1
	glMaterialfv(GL_FRONT, GL_SHININESS, mat1_shininess);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat1_specular);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat1_diffuse);

	glPushMatrix();

	glTranslated(0.0,1.0,0.0);
	gluSphere(glQ, 0.5, 16, 8);
	glPopMatrix();

	// fim de esfera 1

	// esfera 2
	if (mode == GL_SELECT)
		glLoadName (2);
	
	glColorMaterial(GL_FRONT_AND_BACK,GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.0,1.0,0.0);
	glPushMatrix();

	glTranslated(2.5,1.0,-1.0);
	gluSphere(glQ, 0.5, 16, 8);
	glPopMatrix();

	// fim da esfera


	// teapot
	
	if (mode == GL_SELECT)
		glLoadName (3);
	
	glColor3f(1.0,1.0,0.0);
	glPushMatrix();

	glTranslated(1.0,1.0,2.0);
	glutSolidTeapot(0.80);
	// fim teapot

	glDisable(GL_COLOR_MATERIAL);

	glPopName();
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
		if (z1 < mindepth && num>0) {
			mindepth = z1;
			answer = ptr;
			nn=num;
		}
		for (int j=0; j < num; j++) 
			ptr++;
	}
	
	// existe uma resposta
	if (answer!=NULL) 
		pickingAction(*answer);
	
}

struct g_mouseState{
	bool leftButton;
	bool rightButton;
	bool middleButton;
	int x;
	int y;
} MouseState;