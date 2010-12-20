
#include "Object.h"
//#include <WinSock2.h>

class Jogo
{
public:
	vector<int> pecas_al;
	vector<int> pecas_v;


	vector<vector<int>> hist;
	vector<int> tab;
	int fase;
	int fase_ant;
	int Jactual;
	int casa_sel;

	Object * vampiro;
	Object * aldeao;
	Object * nosferatu;

	vector<int> jogadores;

	Jogo(Object * vampiro, Object * aldeao, Object * nosferatu, int j1, int j2);
	void draw();
	void posicao(bool tabuleiro, int pos);
	bool casa_valida(int casa);
	vector<int> conv_casa(int casa);
	void anexa_tab(char * buf);
	bool pertence(int casa);
	bool mov_valido(int casa);
	void exec_move(int casa);
	void move_peca();
	vector<int> parse_tab(char * buf);
};

void myCube(GLfloat lado);

void sensores();
void anim(int dummy);
void peca_anim_init();

void pickingAction(GLuint answer);

// processa os hits no picking
void processHits (GLint hits, GLuint buffer[]);

void show_jogador(int jactual);
void sinalisa_casa();
