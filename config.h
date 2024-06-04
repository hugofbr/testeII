#include <iostream>
#include <time.h>
#include <conio.h>
using namespace std;

struct Jogador {
    int x, y;

    bool colisaoPlayer(int mapa[25][25], int x, int y){
        if (mapa[x][y] == 0 || mapa[x][y] == 4){
            return true;
        } else {
            return false;
        }

    }   

};

struct Inimigo {
    int inimigoX, inimigoY, contadorInimigo;
    bool temInimigo;
    Inimigo(int x, int y, bool flag) {
        inimigoX = x;
        inimigoY = y;
        temInimigo = flag;
    }

    void movimentoInimigo(int &inimigoX, int &inimigoY, int mapa[25][25], int x, int y){
        int dir = rand() % 4; //escolhe uma direção aleatoria
        int passos = rand() % 3 + 1; //escolhe quantos passos ele vai dar aleatoriamente
        for (int i = 0; i < passos; i++){ //verifica o numero de passos e anda conforme
            if (dir == 0 && (mapa[inimigoX-1][inimigoY]==0 || mapa[inimigoX-1][inimigoY] == mapa[x][y])){inimigoX--;}
            if (dir == 1 && (mapa[inimigoX+1][inimigoY]==0|| mapa[inimigoX+1][inimigoY] == mapa[x][y])){inimigoX++;}
            if (dir == 2 && (mapa[inimigoX][inimigoY+1]==0|| mapa[inimigoX][inimigoY+1] == mapa[x][y])){inimigoY++;}
            if (dir == 3 && (mapa[inimigoX][inimigoY-1]==0|| mapa[inimigoX][inimigoY-1] == mapa[x][y])){inimigoY--;}

        }

    }
};

struct Mapa{
    int mapaJogo[25][25]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
                    1,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,2,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
                    1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,
                    1,1,1,1,2,2,1,0,0,1,1,1,2,2,1,1,0,0,0,1,0,0,0,0,1,
                    1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1,1,1,1,0,1,
                    1,0,0,0,1,1,1,2,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,
                    1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,
                    1,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
                    1,2,2,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
                    1,0,0,0,0,0,0,0,1,2,2,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
                    1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
                    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    void imprimeMapa(Inimigo inimigo1, Inimigo inimigo2, Jogador jogador){
        for(int i=0;i<25;i++){
            for(int j=0;j<25;j++){
                if(i==jogador.x && j==jogador.y){
                    cout<<char(1); //personagem
                } else if ((i==inimigo1.inimigoX && j==inimigo1.inimigoY) && inimigo1.temInimigo){
                    cout<<char(5); //inimigo
                   } else if ((i == inimigo2.inimigoX && j == inimigo2.inimigoY) && inimigo2.temInimigo){
                        cout<<char(5); //inimigo 2
                    } else {
                    switch (mapaJogo[i][j]){
                        case 0: cout<<" "; break; //caminho
                        case 1: cout<<char(219); break; //parede forte
                        case 2: cout<<char(35); break; //parede fraca
                        case 3: cout<<char(64); break; //bomba
                        case 4: cout<<"*"; break; //explosão da bomba
                        //default: cout<<"-"; //erro
                    } //fim switch
                }
            }
            cout<<"\n";
        } //fim for mapa

    }
};



struct Bomba {
    int bombaX, bombaY;
    bool temBomba;


    void removeExplosao(int mapa[25][25], int bombaX, int bombaY){
        //remove vertical
        int raio = 1;
        for (int i = 1; i <= raio; i++){
            if (mapa[bombaX - i][bombaY] == 4){
                mapa[bombaX - i][bombaY] = 0;
            }
        }

        for (int i = 1; i <= raio; i++){
            if (mapa[bombaX + i][bombaY] == 4){
                mapa[bombaX + i][bombaY] = 0;
            }
        }

        //remove horizontal
        for (int i = 1; i <= raio; i++){
            if (mapa[bombaX][bombaY - i] == 4){
                mapa[bombaX][bombaY - i] = 0;
            }
        }

        for (int i = 1; i <= raio; i++){
            if (mapa[bombaX][bombaY + i] ==4){
                mapa[bombaX][bombaY + i] = 0;
            }
        }

    }


    void espalhaExplosao(int mapa[25][25], int bombaX, int bombaY){
        //espalha vertical
        int raio = 1;
        for (int i = 1; i <= raio; i++){
            if (mapa[bombaX - i][bombaY] == 0 || mapa[bombaX - i][bombaY] == 2){
                mapa[bombaX - i][bombaY] = 4;
            }
        }

        for (int i = 1; i <= raio; i++){
            if (mapa[bombaX + i][bombaY] == 0 || mapa[bombaX + i][bombaY] == 2){
                mapa[bombaX + i][bombaY] = 4;
            }
        }

        //espalha horizontal
            for (int i = 1; i <= raio; i++){
            if (mapa[bombaX][bombaY - i] == 0 || mapa[bombaX][bombaY - i] == 2){
                mapa[bombaX][bombaY - i] = 4;
            }
        }

        for (int i = 1; i <= raio; i++){
            if (mapa[bombaX][bombaY + i] == 0 || mapa[bombaX][bombaY + i] == 2){
                mapa[bombaX][bombaY + i] = 4;
            }
        }

    }



};

struct Entradas {
    char tecla;
    clock_t iniciaTempo, terminaTempo, tempoTotal;
    void movimento(Jogador jogador, Mapa mapa, Bomba bomba){

        if ( _kbhit() ){
            tecla = getch();
            switch(tecla)
            {
                case 72: case 'w': ///cima
                if (jogador.colisaoPlayer(mapa.mapaJogo, jogador.x-1, jogador.y)){ //sem função == if (mapa.mapaJogox-1][jogador.y]==0){jogador.x--} ((ele verifica se o proximo espaço da matriz é um espaço onde o jogador possa andar))
                    jogador.x--;
                    }
                break;
                case 80: case 's': ///baixo
                if (jogador.colisaoPlayer(mapa.mapaJogo, jogador.x+1, jogador.y)){
                    jogador.x++;
                }
                break;
                case 75:case 'a': ///esquerda
                    if (jogador.colisaoPlayer(mapa.mapaJogo, jogador.x, jogador.y-1)){
                    jogador.y--;
                    }
                break;
                case 77: case 'd': ///direita
                    if (jogador.colisaoPlayer(mapa.mapaJogo, jogador.x, jogador.y+1)){
                    jogador.y++;
                    }
                break;
                case 32: //bomba
                    if (bomba.temBomba == false){ //poderia ser if(!temBomba) ! == negação
                    mapa.mapaJogo[jogador.x][jogador.y] = 3;
                    bomba.temBomba = true;
                    iniciaTempo = clock();
                    bomba.bombaX = jogador.x;
                    bomba.bombaY = jogador.y;
                    }
                break;

            }
        }
    }
};

struct Menu {


};
