#include "game.h"
#include <iostream>
#include <Windows.h>

using namespace std;

void loopJogo()
{
}

void novoJogo(bool &jogoRodando, COORD coord, Mapa &mapa, Jogador* jogador, Inimigo &inimigo, Entrada entrada, Bomba &bomba)
{
    system("cls");
    while (jogoRodando)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        inimigo.contPassos++;
        if (inimigo.contPassos == 50)
        {
            inimigo.moverAleatoriamente(mapa.mapaJogo);
            inimigo.contPassos = 0;
        }
        entrada.movimentos(jogador, mapa, bomba);
        bomba.logicaBomba(mapa.mapaJogo, bomba);
        mapa.imprimeMapa(jogador, inimigo);
    }
}

int main()
{
    /// ALERTA: NAO MODIFICAR O TRECHO DE CODIGO, A SEGUIR.
    // INICIO: COMANDOS PARA QUE O CURSOR NAO FIQUE PISCANDO NA TELA
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
    // FIM: COMANDOS PARA QUE O CURSOR NAO FIQUE PISCANDO NA TELA
    // INICIO: COMANDOS PARA REPOSICIONAR O CURSOR NO INICIO DA TELA
    short int CX = 0, CY = 0;
    COORD coord;
    coord.X = CX;
    coord.Y = CY;
    // FIM: COMANDOS PARA REPOSICIONAR O CURSOR NO INICIO DA TELA
    /// ALERTA: NAO MODIFICAR O TRECHO DE CODIGO, ACIMA.

    // Declarar structs
    Mapa mapa;
    mapa.inicializaMapa();

    Jogador* jogador = new Jogador;
    jogador->pos.x = 12;
    jogador->pos.y = 12;
    // Jogador jogador;
    // jogador.pos.x = 12;
    // jogador.pos.y = 12;

    Inimigo inimigo;
    inimigo.inicializa(5, 5, true);
    Inimigo inimigo2;
    inimigo2.inicializa(10, 10, true);
    Entrada entrada;

    Menu menu;

    Bomba bomba;

    bool menuRodando = true;
    bool jogoRodando = true;

    menu.menuPrincipal();

    // Loop principal jogo
    while (menuRodando)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        switch (entrada.opcaoMenu())
        {
        case '1':
            novoJogo(jogoRodando, coord, mapa, jogador, inimigo, entrada, bomba);
            break;
        case '2':
            system("cls");
            cout << "continua jogo";
            break;
        case '3':
            system("cls");
            cout << "sobre";
            break;
        case '4':
            system("cls");
            cout << "sair";
            menuRodando = false;
            cout << "obrigado por jogar";
            break;

        default:
            break;
        }
    }

    return 0;
}
