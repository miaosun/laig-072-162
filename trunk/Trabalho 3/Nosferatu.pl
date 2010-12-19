%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%   Nosferatu em Prolog  %%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%  Gaspar Furtado  &  Miao Sun   %%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%  Grupo207  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%  PLOG  MIEIC 2010/2011  %%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

:-use_module(library(sockets)).
:-use_module(library(lists)).

%% Estado inicial do tabuleiro
% V representa estado vazio.
% 9 - espaço
% 0 - vazia
% 1 - aldeao
% 2 - vampiro
% 3 - nosferatu
estadoInicial([ [9,9,0,0,0,9,9],
                [9,0,0,0,0,0,9],
                [0,0,0,0,0,0,0],
                [0,0,0,0,0,0,0],
                [0,0,0,0,0,0,0],
                [9,0,0,0,0,0,9],
                [9,9,0,0,0,9,9]
               ]).

pecas_al([1,1,1,1,1,1,1,1,1,1,1,1]).
pecas_v([2,2,2,2,2,3]).


port(60070).

% launch me in sockets mode
server:-
	port(Port),
	socket_server_open(Port, Socket),
	socket_server_accept(Socket, _Client, Stream, [type(text)]),
	write('Accepted connection'), nl,
	serverLoop(Stream),
	socket_server_close(Socket).

% wait for commands
serverLoop(Stream) :-
	repeat,
	read(Stream, ClientMsg),
	write('Received: '), write(ClientMsg), nl,
	parse_input(ClientMsg, MyReply),
	format(Stream, '~q.~n', [MyReply]),
	write('Wrote: '), write(MyReply), nl,
	flush_output(Stream),
	(ClientMsg == quit; ClientMsg == end_of_file), !.

parse_input(casa_valida(X,Y,P,Tab), Answer) :-
		casa_valida(X,Y,P,Tab), Answer = 1, !.
parse_input(casa_valida(_,_,_,_), Answer) :-
		Answer = 0, !.
		
parse_input(pertence(J,X,Y,Tab), Answer) :-
		\+(pertence(J,X,Y,Tab)), Answer = 0, !.
parse_input(pertence(J,X,Y,Tab), Answer) :-
		pertence(J,X,Y,Tab), Answer = 1, !.
		
parse_input(movimento_valido(X,Y,Xf,Yf,Tab), Answer) :-
		\+(movimento_valido(X,Y,Xf,Yf,Tab)), Answer = 0, !.
parse_input(movimento_valido(X,Y,Xf,Yf,Tab), Answer) :-
		movimento_valido(X,Y,Xf,Yf,Tab), Answer = 1, !.
		
parse_input(exec_move(X,Y,Xf,Yf,Tab), Answer) :-
		exec_move(X,Y,Xf,Yf,Tab,Ntab), Answer = Ntab, !.
	
parse_input(quit, ok-bye) :- !.
		
	
	
	

%%% Inicio do programa
start(O):- welcome,
        %menu_start,
        load_simples(O,Tab,P_al,P_v),
        jogador(1,TipoJ),
        not(joga(1,TipoJ,P_al,P_v,Tab)).
        
load_simples(0,Tab,P_al,P_v):- menu_start,
                               estadoInicial(Tab),
                               pecas_al(P_al),
                               pecas_v(P_v).

load_simples(1,Tab,P_al,P_v):- tipo_jogo(1, Pl1, Pl2),
                             assert(jogador(1, Pl1)),
                             assert(jogador(2, Pl2)),
                             estadoInicial(Tab),
                             pecas_al(P_al),
                             pecas_v(P_v).
load_simples(2,Tab,P_al,P_v):- tipo_jogo(1, Pl1, Pl2),
                             assert(jogador(1, Pl1)),
                             assert(jogador(2, Pl2)),
                             estadoInicial_t(Tab),
                             pecas_al_t(P_al),
                             pecas_v_t(P_v).
load_simples(3,Tab,P_al,P_v):- tipo_jogo(1, Pl1, Pl2),
                             assert(jogador(1, Pl1)),
                             assert(jogador(2, Pl2)),
                             estadoInicial_t2(Tab),
                             pecas_al_t2(P_al),
                             pecas_v_t2(P_v).

%% Welcome %%
welcome:-
       write('**********************************'),nl,
       write('*                                *'),nl,
       write('*     Bemvindo ao Nosferatu      *'),nl,
       write('*                                *'),nl,
       write('**********************************'),nl,nl.
%% menu inicial
menu_start:-
       write('**********************************'),nl,
       write('*                                *'),nl,
       write('*     Escolhe o mode do jogo:    *'),nl,
       write('*                                *'),nl,
       write('*       1.Humano VS Humano       *'),nl,
       write('*     2.Computador VS Humano     *'),nl,
       write('*     3.Humano VS Computador     *'),nl,
       write('*   4.Computador VS Computador   *'),nl,
       write('*                                *'),nl,
       write('**********************************'),nl,nl,
       repeat, write('faca a sua escolha: '), (get_code(Op), conv(Op,O),
       tipo_jogo(O, Pl1, Pl2)), !,
       assert(jogador(1, Pl1)),
       assert(jogador(2, Pl2)).

%% define o tipo de jogo
%% tipo_jogo(Op, Pl1, Pl2)
tipo_jogo(1, humano, humano).
tipo_jogo(2, computador, humano).
tipo_jogo(3, humano, computador).
%tipo_jogo(4, computador, computador).

menu_lvl:-
       write('**********************************'),nl,
       write('*                                *'),nl,
       write('*         Nivel do Jogo          *'),nl,
       write('*                                *'),nl,
       write('*            1.Easy              *'),nl,
       write('*           2.Normal             *'),nl,
       write('*            3.Hard              *'),nl,
       write('*                                *'),nl,
       write('**********************************'),nl,nl.


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%% METODOS AUXILIARES AO JOGO %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%pede casa
pede_casa(X,Y):- write('linha '), read(SY), Y is SY-1,
                 write('coluna '), get_code(SX), conv(SX,X).

conv(Let,Valor):- maiuscula(Let), Valor is Let-65.
conv(Let,Valor):- minuscula(Let), Valor is Let-97.
conv(Let,Valor):- numero(Let), Valor is Let-49.

maiuscula(Let):- Let>=65, Let=<72.
minuscula(Let):- Let>=97, Let=<104.
numero(Let):- Let>=48, Let=<56.

% posicao(X,Y,Valor,Tab) verifica o valor da casa X,Y
get_casa(X,0,Valor,[H|_]):- conteudo_casa_linha(X,Valor,H).
get_casa(X,Y,Valor,[_|T]):- Y>0, Y2 is Y-1, get_casa(X,Y2,Valor,T).

conteudo_casa_linha(0,Valor,[H|_]):- Valor is H.
conteudo_casa_linha(X,Valor,[_|T]):- X>0, X2 is X-1,
                                     conteudo_casa_linha(X2,Valor,T).

muda_tab(Pnov,X,Y,Tab,NovoTab):-
        muda_tab2(0,Pnov,X,Y,Tab,NovoTab),!.

muda_tab2(_,_,_,_,[],[]).
muda_tab2(Y,Pnov,X,Y,[Lin|Resto],[NovLin|Resto2]):-
        muda_linha(0,Pnov,X,Lin,NovLin),
        N2 is Y+1,
        muda_tab2(N2,Pnov,X,Y,Resto,Resto2).
muda_tab2(N,Pnov,X,Y,[Lin|Resto],[Lin|Resto2]):-
        N\=Y, N2 is N+1,
        muda_tab2(N2,Pnov,X,Y,Resto,Resto2).

muda_linha(_,_,_,[],[]).
muda_linha(X,Pnov,X,[_|Resto],[Pnov|Resto2]):-
        N2 is X+1,
        muda_linha(N2,Pnov,X,Resto,Resto2).
muda_linha(N,Pnov,X,[El|Resto],[El|Resto2]):-
        N\=X, N2 is N+1,
        muda_linha(N2,Pnov,X,Resto,Resto2).

% copia_tab(Tab,Ntab)
copia_tab([],[]).
copia_tab([Lin|Resto],[Lin|Nresto]):- copia_tab(Resto,Nresto).



%%%%%%%%%%%%%%%%%%% INSERIR PEÇAS NO TABULEIRO %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
insere_peca(P,Tab,TabN):- repeat,
                              (write('Indique uma casa valida para inserir uma peca!\n'),
                              pede_casa(X,Y)), casa_valida(X,Y,P,Tab),
                              muda_tab(P,X,Y,Tab,TabN).
%insere_peca(_,_,_,_,_):- fail.

% 0 - Nordeste
% 1 - Sudeste
% 2 - Sudoeste
% 3 - Noroeste
direccao(Xi,Yi,Xf,Yf,Dir):- Xi<Xf, Yi>Yf, Dir is 0. %Nordeste
direccao(Xi,Yi,Xf,Yf,Dir):- Xi<Xf, Yi<Yf, Dir is 1. %Sudeste
direccao(Xi,Yi,Xf,Yf,Dir):- Xi>Xf, Yi<Yf, Dir is 2. %Sudoeste
direccao(Xi,Yi,Xf,Yf,Dir):- Xi>Xf, Yi>Yf, Dir is 3. %Noroeste

% vizinho(X,Y,Dir,Xf,Yf)
vizinho(X,Y,0,Xf,Yf):- (Y=:=0; X=:=6), Xf is 0, Yf is 0.
vizinho(X,Y,0,Xf,Yf):- Y=\=0, X=\=6, Xf is X+1, Yf is Y-1.  %Nordeste
vizinho(X,Y,1,Xf,Yf):- (Y=:=6; X=:=6), Xf is 0, Yf is 0.
vizinho(X,Y,1,Xf,Yf):- Y=\=6, X=\=6, Xf is X+1, Yf is Y+1.  %Sudeste
vizinho(X,Y,2,Xf,Yf):- (Y=:=6; X=:=0), Xf is 0, Yf is 0.
vizinho(X,Y,2,Xf,Yf):- Y=\=6, X=\=0, Xf is X-1, Yf is Y+1.  %Sudoeste
vizinho(X,Y,3,Xf,Yf):- (Y=:=0; X=:=0), Xf is 0, Yf is 0.
vizinho(X,Y,3,Xf,Yf):- Y=\=0, X=\=0, Xf is X-1, Yf is Y-1.  %Noroeste

e_vizinho(X,Y,Xf,Yf):- vizinho(X,Y,D,Xf,Yf).

esta_seguro(X,Y,Peca,Tab):- esta_seguro_aux(X,Y,Peca,Tab,0).
esta_seguro_aux(_,_,_,_,4).
esta_seguro_aux(X,Y,1,Tab,Dir):- Dir<4, vizinho(X,Y,Dir,X2,Y2),
                               get_casa(X2,Y2,V,Tab), V=\=2, V=\=3, !,
                               Dir2 is Dir+1,
                               esta_seguro_aux(X,Y,1,Tab,Dir2).
esta_seguro_aux(X,Y,1,Tab,Dir):- Dir<4, vizinho(X,Y,Dir,X2,Y2),
                               get_casa(X2,Y2,V,Tab), (V=:=3; V=:=2), oposto(Dir, Dir3),
                               vizinho(X,Y,Dir3,Xo,Yo), \+(casa_livre(Xo,Yo,Tab)), !,
                               Dir2 is Dir+1,
                               esta_seguro_aux(X,Y,1,Tab,Dir2).
esta_seguro_aux(X,Y,P,Tab,Dir):- P=\=1, Dir<4, vizinho(X,Y,Dir,X2,Y2),
                               get_casa(X2,Y2,V,Tab), V=\=1, !,
                               Dir2 is Dir+1,
                               esta_seguro_aux(X,Y,P,Tab,Dir2).
esta_seguro_aux(X,Y,P,Tab,Dir):- P=\=1, Dir<4, vizinho(X,Y,Dir,X2,Y2),
                               get_casa(X2,Y2,V,Tab), V=:=1, oposto(Dir, Dir3),
                               vizinho(X,Y,Dir3,Xo,Yo), \+(casa_livre(Xo,Yo,Tab)), !,
                               Dir2 is Dir+1,
                               esta_seguro_aux(X,Y,P,Tab,Dir2).

oposto(Dir, Dir2):- Dir<3, Dir2 is Dir+2.
oposto(Dir, Dir2):- Dir>2, Dir2 is Dir-2.


casa_valida(X,Y,Peca,Tab):- casa_livre(X,Y,Tab),
                            esta_seguro(X,Y,Peca,Tab).
                            
casa_livre(X,Y,Tab):- get_casa(X,Y,P,Tab), P=:=0.

pertence(1,X,Y,Tab):- get_casa(X,Y,P,Tab), P=:=1.
pertence(2,X,Y,Tab):- get_casa(X,Y,P,Tab), (P=:=2; P=:=3).

escreve_vez(1):- write('Vez dos aldeoes\n\n').
escreve_vez(2):- write('Vez dos vampiros\n\n').

% para ver se as duas posicoes estao na mesma linha
na_linha_livre(X,Y,Xf,Yf,Tab):- direccao(X,Y,Xf,Yf,D),
                                na_linha_livre_aux(X,Y,Xf,Yf,D,Tab).

na_linha_livre_aux(X,Y,X,Y,_,_).
na_linha_livre_aux(X,Y,Xf,Yf,D,Tab):- vizinho(X,Y,D,X2,Y2),
                                      get_casa(X2,Y2,P,Tab),
                                      P=:=0,
                                      na_linha_livre_aux(X2,Y2,Xf,Yf,D,Tab).
                                      
na_linha_come_simples(X,Y,Xf,Yf,Tab):- direccao(X,Y,Xf,Yf,D),
                                       get_casa(X,Y,P,Tab),
                                       na_linha_come_simples_aux(P,X,Y,Xf,Yf,D,Tab).
na_linha_come_simples_aux(1,X,Y,Xf,Yf,D,Tab):- vizinho(X,Y,D,X2,Y2),
                                               get_casa(X2,Y2,P,Tab),
                                               (P=:=3; P=:=2),
                                               vizinho(X2,Y2,D,X3,Y3),
                                               X3=:=Xf, Y3=:=Yf.
na_linha_come_simples_aux(Peca,X,Y,Xf,Yf,D,Tab):- (Peca=:=3; Peca=:=2),
                                                  vizinho(X,Y,D,X2,Y2),
                                                  get_casa(X2,Y2,P,Tab),
                                                  P=:=1,
                                                  vizinho(X2,Y2,D,X3,Y3),
                                                  X3=:=Xf, Y3=:=Yf.
                                                  
na_linha_come_nosferatu(X,Y,Xf,Yf,Tab):- direccao(X,Y,Xf,Yf,D),
                                         na_linha_come_nosferatu_aux(X,Y,Xf,Yf,D,Tab).

na_linha_come_nosferatu_aux(X,Y,X,Y,_,_).
na_linha_come_nosferatu_aux(X,Y,Xf,Yf,D,Tab):- vizinho(X,Y,D,X2,Y2),
                                               get_casa(X2,Y2,P,Tab),
                                               P=:=0,
                                               na_linha_come_nosferatu_aux(X2,Y2,Xf,Yf,D,Tab).
na_linha_come_nosferatu_aux(X,Y,Xf,Yf,D,Tab):- vizinho(X,Y,D,X2,Y2),
                                               get_casa(X2,Y2,P,Tab),
                                               P=:=1,
                                               vizinho(X2,Y2,D,X3,Y3),
                                               get_casa(X3,Y3,P2,Tab),
                                               P2=:=0,
                                               na_linha_come_nosferatu_aux(X3,Y3,Xf,Yf,D,Tab).

escolhe_peca(J,X,Y,Tab):- repeat, (write('Escolha a peca que pretende mover\n'),
                          pede_casa(X,Y)), pertence(J,X,Y,Tab),!.
                          
escolhe_move(X,Y,Xf,Yf,Tab):- repeat, (write('Escolha a casa para onde pertende mover\n'),
                              pede_casa(Xf,Yf)), movimento_valido(X,Y,Xf,Yf,Tab),!.
                              
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%% JOGAR %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

troca(1,2).
troca(2,1).

%% para quando todos jogam
joga(J,humano,[],[],Tab):- mostra_tabuleiro(Tab),
                           escreve_vez(J),
                           escolhe_peca(J,X,Y,Tab),
                           escolhe_move(X,Y,Xf,Yf,Tab),
                           exec_move(X,Y,Xf,Yf,Tab,TabN),
                           troca(J,J2),
                           not(verifica_fim(TabN)), !,
                           joga(J2,humano,[],[],TabN).
joga(J,computador,[],[],Tab):- mostra_tabuleiro(Tab),
                           escreve_vez(J),
                           lista_jogadas(J,Tab,Lista),
                           escolhe_jogada(Lista,X,Y,Xf,Yf),
                           exec_move(X,Y,Xf,Yf,Tab,TabN),
                           troca(J,J2),
                           jogador(J2,TipoJ),
                           not(verifica_fim(TabN)), !,
                           joga(J2,TipoJ,[],[],TabN).

%% para quando os vampiros jogam e os aldeoes inserem pecas
joga(2,humano,P_al,[],Tab):- mostra_tabuleiro(Tab),
                             escreve_vez(2),
                          escolhe_peca(2,X,Y,Tab),
                          escolhe_move(X,Y,Xf,Yf,Tab),
                          exec_move(X,Y,Xf,Yf,Tab,TabN),
                          not(verifica_fim(TabN)), !,
                          jogador(1,TipoJ),
                          joga(1,TipoJ,P_al,[],TabN).
joga(2,computador,P_al,[],Tab):- mostra_tabuleiro(Tab),
                             escreve_vez(2),
                          lista_jogadas(2,Tab,Lista),
                          escolhe_jogada(Lista,X,Y,Xf,Yf),
                          exec_move(X,Y,Xf,Yf,Tab,TabN),
                          not(verifica_fim(TabN)), !,
                          jogador(1,TipoJ),
                          joga(1,TipoJ,P_al,[],TabN).
joga(1,humano,[Peca|Resto],[],Tab):- mostra_tabuleiro(Tab),
                                     escreve_vez(1),
                                     insere_peca(Peca,Tab,TabN),
                                     jogador(2,TipoJ),
                                     joga(2,TipoJ,Resto,[],TabN).
joga(1,computador,[Peca|Resto],[],Tab):- mostra_tabuleiro(Tab),
                                         escreve_vez(1),
                                         lista_casas(Peca,Tab,Lista),
                                         escolhe_casa(Lista,X,Y),
                                         muda_tab(Peca,X,Y,Tab,Ntab),
                                         jogador(2,TipoJ),
                                         joga(2,TipoJ,Resto,[],Ntab).

%% para quando todos inserem pecas
joga(1,humano,[Peca|Resto],L_v,Tab):- mostra_tabuleiro(Tab),
                                      escreve_vez(1),
                                      insere_peca(Peca,Tab,TabN),
                                      jogador(2,TipoJ),
                                      joga(2,TipoJ,Resto,L_v,TabN).
joga(2,humano,P_al,[Peca|Resto],Tab):- mostra_tabuleiro(Tab),
                                       escreve_vez(2),
                                       insere_peca(Peca,Tab,TabN),
                                       jogador(1,TipoJ),
                                       joga(1,TipoJ,P_al,Resto,TabN).
joga(1,computador,[Peca|Resto],L_v,Tab):- mostra_tabuleiro(Tab),
                                          escreve_vez(1),
                                          lista_casas(Peca,Tab,Lista),
                                          escolhe_casa(Lista,X,Y),
                                          muda_tab(Peca,X,Y,Tab,Ntab),
                                          jogador(2,TipoJ),
                                          joga(2,TipoJ,Resto,L_v,Ntab).
joga(2,computador,P_al,[Peca|Resto],Tab):- mostra_tabuleiro(Tab),
                                          escreve_vez(2),
                                          lista_casas(Peca,Tab,Lista),
                                          escolhe_casa(Lista,X,Y),
                                          muda_tab(Peca,X,Y,Tab,Ntab),
                                          jogador(1,TipoJ),
                                          joga(1,TipoJ,P_al,Resto,Ntab).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%% PARA CALCULO DAS JOGADAS DO COMPUTADOR %%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

lista_casas(Peca,Tab,Lista):- findall((X,Y),casa_valida(X,Y,Peca,Tab),Lista).

escolhe_casa([(X,Y)|_],X2,Y2):- X2 is X, Y2 is Y.

lista_jogadas(J,Tab,Lista):-
            findall((X,Y,Xf,Yf),movimento_valido_aux(J,X,Y,Xf,Yf,Tab),Lista).

escolhe_jogada([(X,Y,Xf,Yf)|_],X2,Y2,X3,Y3):- X2 is X, Y2 is Y, X3 is Xf, Y3 is Yf.

movimento_valido_aux(J,X,Y,Xf,Yf,Tab):- pertence(J,X,Y,Tab),
                                        movimento_valido(X,Y,Xf,Yf,Tab).
                                        
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% verifica se algum jogador ganhou
verifica_fim(Tab):- ganhou(Jg,Tab), Jg=:=1, mostra_tabuleiro(Tab),
                    write('Ganharam os Aldeoes!').
verifica_fim(Tab):- ganhou(Jg,Tab), Jg=:=2, mostra_tabuleiro(Tab),
                    write('Ganharam os Vampiros!').

% apenas movimentos simples
movimento_valido(X,Y,Xf,Yf,Tab):- casa_livre(Xf,Yf,Tab),
                                  e_vizinho(X,Y,Xf,Yf).
% movimentos simples do nosferatu
movimento_valido(X,Y,Xf,Yf,Tab):- casa_livre(Xf,Yf,Tab),
                                  get_casa(X,Y,P,Tab), P=:=3,
                                  na_linha_livre(X,Y,Xf,Yf,Tab).
% movimento come peça simples
movimento_valido(X,Y,Xf,Yf,Tab):- casa_livre(Xf,Yf,Tab),
                                  na_linha_come_simples(X,Y,Xf,Yf,Tab).
% movimento come do nosferatu
movimento_valido(X,Y,Xf,Yf,Tab):- casa_livre(Xf,Yf,Tab),
                                  get_casa(X,Y,P,Tab), P=:=3,
                                  na_linha_come_nosferatu(X,Y,Xf,Yf,Tab).


% movimento simples de uma casa
exec_move(X,Y,Xf,Yf,Tab,TabN):- e_vizinho(X,Y,Xf,Yf),
                                get_casa(X,Y,P,Tab),
                                muda_tab(0,X,Y,Tab,NTab),
                                muda_tab(P,Xf,Yf,NTab,TabN).
% movimento simples com come
exec_move(X,Y,Xf,Yf,Tab,TabN):- \+(e_vizinho(X,Y,Xf,Yf)),
                                get_casa(X,Y,P,Tab),
                                P=\=3,
                                direccao(X,Y,Xf,Yf,D),
                                vizinho(X,Y,D,X2,Y2),
                                muda_tab(0,X2,Y2,Tab,Ntab),
                                muda_tab(0,X,Y,Ntab,NTab2),
                                muda_tab(P,Xf,Yf,NTab2,TabN).
                                
exec_move(X,Y,Xf,Yf,Tab,TabN):- na_linha_come_nosferatu(X,Y,Xf,Yf,Tab),
                                repeat,
                                (write('Que pretende fazer com a(s) peça(s) que capturou?\n'),
                                write('1-Comer\n2-Transformar em vampiro\n\nOpcao: '),
                                read(O)), (O=:=1; O=:=2),
                                direccao(X,Y,Xf,Yf,D),
                                limpa_linha(O,X,Y,Xf,Yf,D,Tab,Ntab),
                                muda_tab(0,X,Y,Ntab,Ntab2),
                                muda_tab(3,Xf,Yf,Ntab2,TabN).

limpa_linha(_,X,Y,X,Y,_,Tab,Ntab):- copia_tab(Tab,Ntab).
limpa_linha(1,X,Y,Xf,Yf,D,Tab,Ntab):- vizinho(X,Y,D,X2,Y2),
                                      get_casa(X2,Y2,P,Tab),
                                      P=:=1,
                                      muda_tab(0,X2,Y2,Tab,Ntab2),
                                      limpa_linha(1,X2,Y2,Xf,Yf,D,Ntab2,Ntab).
limpa_linha(2,X,Y,Xf,Yf,D,Tab,Ntab):- vizinho(X,Y,D,X2,Y2),
                                      get_casa(X2,Y2,P,Tab),
                                      P=:=1,
                                      muda_tab(2,X2,Y2,Tab,Ntab2),
                                      limpa_linha(2,X2,Y2,Xf,Yf,D,Ntab2,Ntab).
limpa_linha(O,X,Y,Xf,Yf,D,Tab,Ntab):- vizinho(X,Y,D,X2,Y2),
                                      get_casa(X2,Y2,P,Tab),
                                      P=:=0,
                                      muda_tab(0,X2,Y2,Tab,Ntab2),
                                      limpa_linha(O,X2,Y2,Xf,Yf,D,Ntab2,Ntab).


ganhou(_,[]).
ganhou(1,[H|R]):-ganhou_aux(1,H), ganhou(1,R).
ganhou(2,[H|R]):-ganhou_aux(2,H), ganhou(2,R).
ganhou_aux(_,[]).
ganhou_aux(1,[H|T]):-H=\=3, ganhou_aux(1,T).
ganhou_aux(2,[H|T]):-H=\=1, ganhou_aux(2,T).



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%% VISUALIZAÇÃO DO TABULEIRO %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


mostra_tabuleiro(Tab):- write('    A   B   C   D   E   F   G '),nl,
                 linhas(1,Tab),
                 write('    A   B   C   D   E   F   G '),nl,nl,!.

linhas(_,[]):-!.
%primeira linha
linhas(N,[H|T]):- N=:=1, lim(1), write(N), write('  '),
                  linha(H),
                  write(' '), write(N), nl,
                  N2 is N+1,
                  linhas(N2, T).
%segunda linha
linhas(N,[H|T]):- N=:=2, lim(2), write(N), write('  '),
                  linha(H),
                  write(' '), write(N), nl,
                  N2 is N+1,
                  linhas(N2, T).
%linhas do meio
linhas(N,[H|T]):- N>2, N<6, lim(3), write(N), write(' |'),
                  linha(H),
                  write(' '), write(N), nl,
                  N2 is N+1,
                  linhas(N2, T).
%penultima linha
linhas(N,[H|T]):- N=:=6, lim(3), write(N), write('  '),
                  linha(H),
                  write(' '), write(N), nl,
                  N2 is N+1,
                  linhas(N2, T).
%ultima linha
linhas(N,[H|T]):- N=:=7, lim(2), write(N), write('  '),
                  linha(H),
                  write(' '), write(N), nl, lim(1),
                  N2 is N+1,
                  linhas(N2, T).

linha([]):-!.
linha([9|[9|T]]):- write('    '), linha([9|T]).
linha([9|[H|T]]):- H=\=9, write('   |'), linha([H|T]).
linha([9|T]):- write('    '), linha(T).
linha([H|T]):- H=\=9, escreve(H), linha(T).


lim(1):- write('          +---+---+---+'), nl.
lim(2):- write('      +---+---+---+---+---+'), nl.
lim(3):- write('  +---+---+---+---+---+---+---+'), nl.

%escreve(N)
escreve(0):-write('   |').   %vazia
escreve(1):-write(' o |').   %aldeao
escreve(2):-write(' $ |').   %vampiro
escreve(3):-write(' N |').   %nosferatu

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%% PARA EFEITOS DE TESTE %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

estadoInicial_t([ [9,9,1,0,0,9,9],
                  [9,1,1,0,0,2,9],
                  [1,1,0,0,0,2,2],
                  [1,0,0,0,0,0,2],
                  [0,0,0,0,0,0,2],
                  [9,0,0,0,0,3,9],
                  [9,9,0,0,0,9,9]
               ]).

pecas_al_t([1,1,1,1,1,1]).
pecas_v_t([]).

estadoInicial_t2([ [9,9,1,1,1,9,9],
                   [9,1,1,0,0,2,9],
                   [1,1,0,0,1,2,2],
                   [1,0,0,1,0,0,2],
                   [1,0,0,0,0,0,2],
                   [9,1,0,0,0,3,9],
                   [9,9,0,0,0,9,9]
                 ]).

pecas_al_t2([]).
pecas_v_t2([]).