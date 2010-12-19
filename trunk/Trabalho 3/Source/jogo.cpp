#include "jogo.h"
//#include "Variaveis.h"
//#include <winsock2.h>

/*Jogo::Jogo(Object * vampiro, Object * aldeao, Object * nosferatu, Jogador * j1, Jogador * j2)
{
	this->vampiro=vampiro;
	this->aldeao=aldeao;
	this->nosferatu=nosferatu;
	this->jogadores.push_back(j1);
	this->jogadores.push_back(j2);
	for(unsigned int i=0; i<49; i++)
	{
		if(i<2||i==5||i==6||i==7||i==13||i==35||i==41||i==42||i==43||i>46)
			this->tab.push_back(9);
		else
			this->tab.push_back(0);
	}
	if(!socketConnect())
		throw ExcepcaoSocket();

}*/

/*bool Jogo::socketConnect() // Initialize Winsock.
{
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != NO_ERROR)
		printf("Client: Error at WSAStartup().\n");
    else
        printf("Client: WSAStartup() is OK.\n");

	// Create a socket.
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        printf("Client: socket() - Error at socket(): %ld\n", WSAGetLastError());
        WSACleanup();
        return false;
    }
	else
       printf("Client: socket() is OK.\n");

    // Connect to a server.
    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    // Just test using the localhost, you can try other IP address
    clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
    clientService.sin_port = htons(60070);

    if (connect(sock, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
        printf("Client: connect() - Failed to connect.\n");
        WSACleanup();
        return false;
    }
    else {
       printf("Client: connect() is OK.\n");
       printf("Client: Can start sending and receiving data...\n");
    }

    // Send and receive data.
	printf("Connected\n");
	return true;
}*/

/*Jogador::Jogador(int tipo)
{
	this->tipo=tipo;
}

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

void sensores(float dim_Casa, float dim_cube, int _cube)
{
	glPushMatrix();
	glTranslated(0.0, 4.0, 0.0);//?
		
	glPushName(0);
		
		glPushMatrix();
		glTranslated(-dim_Casa-dim_Casa/2+(dim_Casa-dim_cube)/2, 0.0, -2*dim_Casa-dim_Casa/2);
		glCallList(_cube);
		glPopMatrix();
		for(int i=1; i<3; i++)
		{
			glLoadName(i);
			glPushMatrix();
			glTranslated(-dim_Casa-dim_Casa/2+i*dim_Casa+(dim_Casa-dim_cube)/2, 0.0, -2*dim_Casa-dim_Casa/2);
			glCallList(_cube);
			glPopMatrix();

		}
		
		for(int i=0; i<5; i++)
		{
			glLoadName(i+3);
			glPushMatrix();
			glTranslated(-2*dim_Casa-dim_Casa/2+i*dim_Casa+(dim_Casa-dim_cube)/2, 0.0, -dim_Casa-dim_Casa/2);
			glCallList(_cube);
			glPopMatrix();
		}
		
		for(int i=0; i<7; i++)
		{
			glLoadName(i+8);
			glPushMatrix();
			glTranslated(-3*dim_Casa-dim_Casa/2+i*dim_Casa+(dim_Casa-dim_cube)/2, 0.0, -dim_Casa/2);
			glCallList(_cube);
			glPopMatrix();
		}

		for(int i=0; i<7; i++)
		{
			glLoadName(i+15);
			glPushMatrix();
			glTranslated(-3*dim_Casa-dim_Casa/2+i*dim_Casa+(dim_Casa-dim_cube)/2, 0.0, dim_Casa/2);
			glCallList(_cube);
			glPopMatrix();
		}

		for(int i=0; i<7; i++)
		{
			glLoadName(i+22);
			glPushMatrix();
			glTranslated(-3*dim_Casa-dim_Casa/2+i*dim_Casa+(dim_Casa-dim_cube)/2, 0.0, dim_Casa+dim_Casa/2);
			glCallList(_cube);
			glPopMatrix();
		}

		for(int i=0; i<5; i++)
		{
			glLoadName(i+29);
			glPushMatrix();
			glTranslated(-2*dim_Casa-dim_Casa/2+i*dim_Casa+(dim_Casa-dim_cube)/2, 0.0, 2*dim_Casa+dim_Casa/2);
			glCallList(_cube);
			glPopMatrix();
		}
		
		for(int i=0; i<3; i++)
		{
			glLoadName(i+34);
			glPushMatrix();
			glTranslated(-dim_Casa-dim_Casa/2+i*dim_Casa+(dim_Casa-dim_cube)/2, 0.0, 3*dim_Casa+dim_Casa/2);
			glCallList(_cube);
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
	
}*/

