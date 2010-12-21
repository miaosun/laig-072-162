
#include "Object.h"
//#include <WinSock2.h>

class Jogo
{
public:
	vector<int> pecas_al;
	vector<int> pecas_v;


	vector<vector<int>> hist_tabs;
	vector<vector<int>> hist_moves;
	vector<vector<int>> hist_pecas_al;
	vector<vector<int>> hist_pecas_v;
	vector<int> hist_insert;

	vector<int> tab;
	vector<int> sinal;
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
	void sinaliza_casa(int casa);
	vector<int> parse_tab(char * buf);
	void procura_sinal();
};

void myCube(GLfloat lado);
void open_textures();

void sensores();
void anim(int dummy);
void peca_anim_init();
void move_anim_init(int casa);
void filme(int dummy);
void filme_vars();

void sock_end(int control);
void undo(int control);

void pickingAction(GLuint answer);

// processa os hits no picking
void processHits (GLint hits, GLuint buffer[]);

void show_jogador(int jactual);

