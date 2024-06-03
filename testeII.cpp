/**
   Bomberman 2.0
   Hugo Fernandes Brasil
   Algoritmos e Programação II
*/
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>

using namespace std;

struct Inimigo {
    int inimigoX, inimigoY;
    bool temInimigo;
    Inimigo(int x, int y, bool flag) {
        inimigoX = x;
        inimigoY = y;
        temInimigo = flag;
    }
};

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


bool colisaoPlayer(int mapa[25][25], int x, int y){
    if (mapa[x][y] == 0 || mapa[x][y] == 4){
        return true;
    } else {
        return false;
    }

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

void movimentoInimigo2(int &inimigo2X, int &inimigo2Y, int mapa[25][25], int x, int y){
    int dir = rand() % 4; //escolhe uma direção aleatoria
    int passos = rand() % 3 + 1; //escolhe quantos passos ele vai dar aleatoriamente
    for (int i = 0; i < passos; i++){ //verifica o numero de passos e anda conforme
        if (dir == 0 && (mapa[inimigo2X-1][inimigo2Y]==0 || mapa[inimigo2X-1][inimigo2Y] == mapa[x][y])){inimigo2X--;}
        if (dir == 1 && (mapa[inimigo2X+1][inimigo2Y]==0|| mapa[inimigo2X+1][inimigo2Y] == mapa[x][y])){inimigo2X++;}
        if (dir == 2 && (mapa[inimigo2X][inimigo2Y+1]==0|| mapa[inimigo2X][inimigo2Y+1] == mapa[x][y])){inimigo2Y++;}
        if (dir == 3 && (mapa[inimigo2X][inimigo2Y-1]==0|| mapa[inimigo2X][inimigo2Y-1] == mapa[x][y])){inimigo2Y--;}

    }
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

    int mapa[25][25]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
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



    //opções de iniciar jogo
    int opcao;
    //dificuldade
    int dificuldade;
    //jogo rodando
    bool jogoRodando = false;
    //posições da bomba
    int bombaX = 0, bombaY = 0;
    //contador pra bomba estourar
    clock_t iniciaTempo, terminaTempo, tempoTotal;
    //contador de passos inimigo 1
    int contadorInimigo = 0;
    //contador de passos inimigo 2
    int contadorInimigo2 = 0;
    //posição inicial do inimigo 1
    Inimigo inimigo1(13, 13, true);
    //posição inicial do inimigo 2
    Inimigo inimigo2(13,2, true);
    //Posicao inicial do personagem no console
    int x=1, y=1;
    //Variavel para tecla precionada
    char tecla;
    //variavel para verificar se tem bomba
    bool temBomba = false;
    //variavel para verificar se tem inimigo
    bool temInimigo = true;
    
    
    
    cout<<"-----------------------\n\n";
    cout<<"        BEM VINDO      \n\n";
    cout<<"-----------------------\n\n";
    cout<<"(1) INICIAR NOVO JOGO \n";
    cout<<"(2) CONTINUAR JOGO SALVO \n";
    cout<<"(3) TUTORIAL \n";
    cin>>opcao;

    switch (opcao){
    case 1: system("cls");
            cout<<"-------------------------\n\n";
            cout<<"  ESCOLHA A DIFICULDADE\n\n";
            cout<<"-------------------------\n\n";
            cout<<"(1) FACIL\n";
            cout<<"(2) MEDIO\n";
            cout<<"(3) DIFICIL\n";
            cin>>dificuldade;
            jogoRodando = true;
            break;    
    case 3: system("cls");
        cout<<"Para jogar";
        break;
        }
    
    
    
    
    while(jogoRodando){
        ///Posiciona a escrita no iicio do console
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);


        if (temBomba){
            terminaTempo = clock();
            tempoTotal = (terminaTempo - iniciaTempo) / CLOCKS_PER_SEC;

            if (tempoTotal == 3){
                //cuidar da explosão da bomba
                mapa[bombaX][bombaY] = 4;
                espalhaExplosao(mapa, bombaX, bombaY);
            }
            if (tempoTotal == 4){
                //remove a explosão da bomba
                mapa[bombaX][bombaY] = 0;
                removeExplosao(mapa, bombaX, bombaY);
                tempoTotal = 0;
                temBomba = false;
            }
        }

    

        ///Imprime o jogo: mapa e personagem.
        for(int i=0;i<25;i++){
            for(int j=0;j<25;j++){
                if(i==x && j==y){
                    cout<<char(1); //personagem
                } else if ((i==inimigo1.inimigoX && j==inimigo1.inimigoY) && inimigo1.temInimigo){
                    cout<<char(5); //inimigo
                   } else if ((i == inimigo2.inimigoX && j == inimigo2.inimigoY) && inimigo2.temInimigo){
                        cout<<char(5); //inimigo 2
                    } else {
                    switch (mapa[i][j]){
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

        contadorInimigo++;
        if(contadorInimigo == 100){

            movimentoInimigo(inimigo1.inimigoX, inimigo1.inimigoY, mapa, x, y);
            contadorInimigo = 0;
        }

         contadorInimigo2++;
        if(contadorInimigo2 == 100){

            movimentoInimigo2(inimigo2.inimigoX, inimigo2.inimigoY, mapa, x, y);
            contadorInimigo2 = 0;
        }


        ///executa os movimentos e posiciona a bomba
         if ( _kbhit() ){
            tecla = getch();
            switch(tecla)
            {
                case 72: case 'w': ///cima
                  if (colisaoPlayer(mapa, x-1, y)){ //sem função == if (mapa[x-1][y]==0){x--} ((ele verifica se o proximo espaço da matriz é um espaço onde o jogador possa andar))
                    x--;
                    }
                break;
                case 80: case 's': ///baixo
                   if (colisaoPlayer(mapa, x+1, y)){
                    x++;
                   }
                break;
                case 75:case 'a': ///esquerda
                    if (colisaoPlayer(mapa, x, y-1)){
                    y--;
                    }
                break;
                case 77: case 'd': ///direita
                    if (colisaoPlayer(mapa, x, y+1)){
                    y++;
                    }
                break;
                case 32: //bomba
                    if (temBomba == false){ //poderia ser if(!temBomba) ! == negação
                    mapa[x][y] = 3;
                    temBomba = true;
                    iniciaTempo = clock();
                    bombaX = x;
                    bombaY = y;
                    }
                break;

            }
        }
        //condição de morte do inimigo
        if (mapa[inimigo1.inimigoX][inimigo1.inimigoY] == 4){
            inimigo1.temInimigo = false;
        }
        //condição de morte do inimigo 2
        if (mapa[inimigo2.inimigoX][inimigo2.inimigoY] == 4){
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
        condicaoMorte(mapa, inimigo1.inimigoX, inimigo1.inimigoY, inimigo1.temInimigo, x, y, jogoRodando);
        condicaoMorte(mapa, inimigo2.inimigoX, inimigo2.inimigoY, inimigo2.temInimigo, x, y, jogoRodando);

    } //fim do laco do jogo

    return 0;
} //fim main
