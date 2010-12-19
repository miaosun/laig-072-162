
#include "Object.h"
//#include <WinSock2.h>

class Jogo
{
public:
	vector<int> pecas_al;
	vector<int> pecas_v;

	vector<int> tab;

	Object * vampiro;
	Object * aldeao;
	Object * nosferatu;

	vector<int> jogadores;

	Jogo(Object * vampiro, Object * aldeao, Object * nosferatu, int j1, int j2);
	void draw();
	void posicao(bool tabuleiro, int pos);
};

void myCube(GLfloat lado);

void sensores();
void reverte(Object * obj);

void pickingAction(GLuint answer);

// processa os hits no picking
void processHits (GLint hits, GLuint buffer[]);
