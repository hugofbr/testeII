#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <ctime>

using namespace std;

struct Posicao
{
    int x;
    int y;

    // Sobrecarga do operador << para permitir a impressão de Posicao
    friend ostream &operator<<(ostream &os, const Posicao &pos);
};

struct Jogador
{
    Posicao pos;
    bool vivo;

    void mover(int novaPosX, int novaPosY);
    bool colisaoJogador(int mapa[25][25], int x, int y);
};

struct Inimigo
{
    Posicao pos;
    bool vivo;
    int contPassos;

    void inicializa(int x, int y, bool flag);

    void moverAleatoriamente(int mapa[25][25]);
    bool colisaoInimigo(int mapa[25][25], int x, int y);

    friend ostream &operator<<(ostream &os, const Inimigo &inimigo);
};

struct Mapa
{
    int mapaJogo[25][25];

    void inicializaMapa();

    void imprimeMapa(const Jogador *jogador, const Inimigo &inimigo);
};

struct Bomba
{
    Posicao pos;
    bool existeBomba;

    void removeExplosao();
    void espalhaExplosao();

    clock_t comecaTempo, terminaTempo, totalTempo;
    void colocaBomba(Mapa &mapa, Jogador *jogador);
};

struct Entrada
{
    char entradaMenu;
    char opcaoMenu();

    char entradaMov;
    void movimentos(Jogador *jogador, Mapa &mapa, Bomba &bomba);
};

struct Menu
{
    void menuPrincipal();
    void menuDificuldade();
};

#endif