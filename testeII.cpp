/**
   Bomberman 2.0
   Hugo Fernandes Brasil
   Algoritmos e Programação II
*/
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "config.h"

using namespace std;



void condicaoMorte(int mapa[25][25], int posicaoInimigoX, int posicaoInimigoY, bool verificInimigo, int jogX, int jogY, bool &jogoRodando){
            if (mapa[jogX][jogY] == 4 || (jogX == posicaoInimigoX && jogY == posicaoInimigoY && verificInimigo)){
            jogoRodando = false;
            system("cls");
            cout<<"\n ***************************";
            cout<<endl;
            cout<<"\n       VOCE MORREU!!!       \n";
            cout<<"             :(              "<<endl;
            cout<<"\n ***************************";
            Sleep(1000);
        }

}

void lacoJogo(COORD coord, bool &jogoRodando, Bomba bomba, Entradas entradas, Mapa mapa, Jogador jogador,Inimigo inimigo1, Inimigo inimigo2, bool temInimigo){
    while(jogoRodando){
        ///Posiciona a escrita no iicio do console
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);


        if (bomba.temBomba){
            entradas.iniciaTempo = clock();
            entradas.tempoTotal = (entradas.terminaTempo - entradas.iniciaTempo) / CLOCKS_PER_SEC;

            if (entradas.tempoTotal == 3){
                //cuidar da explosão da bomba
                mapa.mapaJogo[bomba.bombaX][bomba.bombaY] = 4;
                bomba.espalhaExplosao(mapa.mapaJogo, bomba.bombaX, bomba.bombaY);
            }
            if (entradas.tempoTotal == 4){
                //remove a explosão da bomba
                mapa.mapaJogo[bomba.bombaX][bomba.bombaY] = 0;
                bomba.removeExplosao(mapa.mapaJogo, bomba.bombaX, bomba.bombaY);
                entradas.tempoTotal = 0;
                bomba.temBomba = false;
            }
        }

        inimigo1.contadorInimigo++;
        if(inimigo1.contadorInimigo == 100){

            inimigo1.movimentoInimigo(inimigo1.inimigoX, inimigo1.inimigoY, mapa.mapaJogo, jogador.x,jogador.y);
            inimigo2.movimentoInimigo(inimigo2.inimigoX, inimigo2.inimigoY, mapa.mapaJogo, jogador.x,jogador.y);
            inimigo1.contadorInimigo = 0;
        }

        entradas.movimento(jogador, mapa, bomba);

        //condição de morte do inimigo
        if (mapa.mapaJogo[inimigo1.inimigoX][inimigo1.inimigoY] == 4){
            inimigo1.temInimigo = false;
        }
        //condição de morte do inimigo 2
        if (mapa.mapaJogo[inimigo2.inimigoX][inimigo2.inimigoY] == 4){
            inimigo2.temInimigo = false;
        }

        //condição de vitoria
        if (!temInimigo){
            jogoRodando = false;
            system("cls");
            cout<<"\n ***************************";
            cout<<endl;
            cout<<"\n   PARABENS!!! VOCE GANHOU  \n";
            cout<<"             :)              "<<endl;
            cout<<"\n ***************************";
            Sleep(1000);

        }
        condicaoMorte(mapa.mapaJogo, inimigo1.inimigoX, inimigo1.inimigoY, inimigo1.temInimigo, jogador.x, jogador.y, jogoRodando);
        condicaoMorte(mapa.mapaJogo, inimigo2.inimigoX, inimigo2.inimigoY, inimigo2.temInimigo, jogador.x, jogador.y, jogoRodando);

    }

}

void novoJogo(int &dificuldade,COORD coord, bool &jogoRodando, Bomba bomba, Entradas entradas, Mapa mapa, Jogador jogador,Inimigo inimigo1, Inimigo inimigo2, bool temInimigo){
    system("cls");
            cout<<"-------------------------\n\n";
            cout<<"  ESCOLHA A DIFICULDADE\n\n";
            cout<<"-------------------------\n\n";
            cout<<"(1) FACIL\n";
            cout<<"(2) MEDIO\n";
            cout<<"(3) DIFICIL\n";
            cin>>dificuldade;
            jogoRodando = true;
            lacoJogo(coord, jogoRodando, bomba, entradas, mapa, jogador, inimigo1, inimigo2, temInimigo);

}

int main(){
    ///ALERTA: NAO MODIFICAR O TRECHO DE CODIGO, A SEGUIR.
        //INICIO: COMANDOS PARA QUE O CURSOR NAO FIQUE PISCANDO NA TELA
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO     cursorInfo;
        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = false; // set the cursor visibility
        SetConsoleCursorInfo(out, &cursorInfo);
        //FIM: COMANDOS PARA QUE O CURSOR NAO FIQUE PISCANDO NA TELA
        //INICIO: COMANDOS PARA REPOSICIONAR O CURSOR NO INICIO DA TELA
        short int CX=0, CY=0;
        COORD coord;
        coord.X = CX;
        coord.Y = CY;
        //FIM: COMANDOS PARA REPOSICIONAR O CURSOR NO INICIO DA TELA
    ///ALERTA: NAO MODIFICAR O TRECHO DE CODIGO, ACIMA.

    Bomba bomba;
    Inimigo inimigo1(13, 13, true);
    Inimigo inimigo2(13,2, true);
    Mapa mapa;
    Jogador jogador;
    Entradas entradas;
    Menu menu;


    //opções de iniciar jogo
    int opcao;
    //dificuldade
    int dificuldade;
    //jogo rodando
    bool jogoRodando = false;
    //contador de passos inimigo 1
    int contadorInimigo = 0;
    //contador de passos inimigo 2
    int contadorInimigo2 = 0;
    //Posicao inicial do personagem no console
    int x=1, y=1;
    //Variavel para tecla precionada
    char tecla;
    //variavel para verificar se tem bomba
    bool temBomba = false;
    //variavel para verificar se tem inimigo
    bool temInimigo = true;
    //variavel para o menu rodando
    bool menuRodando = true;
    
    while (menuRodando){
        cout<<"-----------------------\n\n";
        cout<<"        BEM VINDO      \n\n";
        cout<<"-----------------------\n\n";
        cout<<"(1) INICIAR NOVO JOGO \n";
        cout<<"(2) CONTINUAR JOGO SALVO \n";
        cout<<"(3) TUTORIAL \n";
        cin>>opcao;

        switch (opcao){
        case 1: 
            novoJogo(dificuldade, coord, jogoRodando, bomba, entradas, mapa, jogador, inimigo1, inimigo2, temInimigo);
            break;    
        
        
        case 3: system("cls");
            cout<<"Para jogar";
            break;
            }
        
        
        
    }

    return 0;
} //fim main
