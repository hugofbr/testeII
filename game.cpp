#include "game.h"
#include <conio.h>

void Jogador::mover(int novaPosX, int novaPosY)
{
    pos.x = novaPosX;
    pos.y = novaPosY;
}

bool Jogador::colisaoJogador(int mapa[25][25], int x, int y)
{
    if (mapa[x][y] == 0 || mapa[x][y] == 4 || mapa[x][y] == 5 || mapa[x][y] == 6)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Inimigo::inicializa(int x, int y, bool flag)
{
    pos.x = x;
    pos.y = y;
    vivo = flag;
    contPassos = 0;
}

void Inimigo::moverAleatoriamente(int mapa[25][25])
{
    int dir = rand() % 4;
    int novoX = pos.x;
    int novoY = pos.y;

    switch (dir)
    {
    case 0:
        novoX--;
        break;
    case 1:
        novoX++;
        break;
    case 2:
        novoY--;
        break;
    case 3:
        novoY++;
        break;
    }

    if (colisaoInimigo(mapa, novoX, novoY))
    {
        pos.x = novoX;
        pos.y = novoY;
    }
}

bool Inimigo::colisaoInimigo(int mapa[25][25], int x, int y)
{
    if (mapa[x][y] == 0 || mapa[x][y] == 4)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Mapa::inicializaMapa()
{
    int mapaInicial[25][25] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                               1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                               1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                               1, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                               1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                               1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1,
                               1, 1, 1, 1, 2, 2, 1, 0, 0, 1, 1, 1, 2, 2, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1,
                               1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1,
                               1, 0, 0, 0, 1, 1, 1, 2, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1,
                               1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1,
                               1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
                               1, 2, 2, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
                               1, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
                               1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
                               1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            mapaJogo[i][j] = mapaInicial[i][j];
        }
    }
}

void Mapa::imprimeMapa(const Jogador *jogador, const Inimigo &inimigo)
{
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            if (i == jogador->pos.x && j == jogador->pos.y && jogador->vivo)
            {
                cout << char(1); // jogador
            }
            else if (i == inimigo.pos.x && j == inimigo.pos.y && inimigo.vivo)
            {
                cout << char(5); // inimigo
            }
            else
            {
                switch (mapaJogo[i][j])
                {
                case 0:
                    cout << " ";
                    break; // caminho
                case 1:
                    cout << char(219);
                    break; // parede forte
                case 2:
                    cout << char(35);
                    break; // parede fraca
                case 3:
                    cout << char(64);
                    break; // bomba
                case 4:
                    cout << "*";
                    break; // explosão da bomba
                    // default: cout<<"-"; //erro
                } // fim switch
            }
        }
        cout << endl;
    }
}



// Entradas
char Entrada::opcaoMenu()
{
    if (_kbhit())
    {
        entradaMenu = _getch();
    }
    return entradaMenu;
}

void Entrada::movimentos(Jogador *jogador, Mapa &mapa, Bomba &bomba)
{
    if (_kbhit())
    {
        entradaMov = _getch();

        switch (entradaMov)
        {
        case 72:
        case 'w': /// cima
            if (jogador->colisaoJogador(mapa.mapaJogo, jogador->pos.x - 1, jogador->pos.y))
            {
                jogador->mover(jogador->pos.x - 1, jogador->pos.y);
            }
            break;
        case 80:
        case 's': /// baixo
            if (jogador->colisaoJogador(mapa.mapaJogo, jogador->pos.x + 1, jogador->pos.y))
            {
                jogador->mover(jogador->pos.x + 1, jogador->pos.y);
            }
            break;
        case 75:
        case 'a': /// esquerda
            if (jogador->colisaoJogador(mapa.mapaJogo, jogador->pos.x, jogador->pos.y - 1))
            {
                jogador->mover(jogador->pos.x, jogador->pos.y - 1);
            }
            break;
        case 77:
        case 'd': /// direita
            if (jogador->colisaoJogador(mapa.mapaJogo, jogador->pos.x, jogador->pos.y + 1))
            {
                jogador->mover(jogador->pos.x, jogador->pos.y + 1);
            }
            break;
        case 32:
            bomba.colocaBomba(mapa, jogador);
            break;
        }
    }
}
//bomba

void Bomba::espalhaExplosao(int mapa[25][25], int bombaX, int bombaY){
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

void Bomba::removeExplosao(int mapa[25][25], int bombaX, int bombaY){
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

void Bomba::logicaBomba(int mapa[25][25], Bomba &bomba){
     if (bomba.existeBomba){
            
            bomba.terminaTempo = clock();
            bomba.totalTempo = (bomba.terminaTempo - bomba.comecaTempo) / CLOCKS_PER_SEC;
            //cout<<bomba.totalTempo;
            if (bomba.totalTempo == 3){
                
                //cuidar da explosão da bomba
                mapa[bomba.pos.x][bomba.pos.y] = 4;
                bomba.espalhaExplosao(mapa, bomba.pos.x, bomba.pos.y);
            }
            if (bomba.totalTempo == 4){
                //remove a explosão da bomba
                mapa[bomba.pos.x][bomba.pos.y] = 0;
                bomba.removeExplosao(mapa, bomba.pos.x, bomba.pos.y);
                bomba.totalTempo = 0;
                bomba.existeBomba = false;
            }
        }

}

void Bomba::colocaBomba(Mapa &mapa, Jogador* jogador)
{   
    if (!existeBomba)
    {
        existeBomba = true;
        mapa.mapaJogo[jogador->pos.x][jogador->pos.y] = 3;
        comecaTempo = clock();
        pos.x = jogador->pos.x;
        pos.y = jogador->pos.y;
    }
}

void Menu::menuPrincipal()
{
    cout << "-----------------------\n\n";
    cout << "        BEM VINDO      \n\n";
    cout << "-----------------------\n\n";
    cout << "(1) INICIAR NOVO JOGO \n";
    cout << "(2) CONTINUAR JOGO SALVO \n";
    cout << "(3) TUTORIAL \n";
    cout << "(4) SAIR \n";
}

void Menu::menuDificuldade()
{
    cout << "-------------------------\n\n";
    cout << "  ESCOLHA A DIFICULDADE\n\n";
    cout << "-------------------------\n\n";
    cout << "(1) FACIL\n";
    cout << "(2) MEDIO\n";
    cout << "(3) DIFICIL\n";
}

// Definição do operador << para Posicao
ostream &operator<<(ostream &os, const Posicao &pos)
{
    os << "(" << pos.x << ", " << pos.y << ")";
    return os;
}

ostream &operator<<(ostream &os, const Inimigo &inimigo)
{
    os << "Posicao: " << inimigo.pos << ", Vivo: " << (inimigo.vivo ? "Sim" : "Nao") << ", Contador de Passos: " << inimigo.contPassos;
    return os;
}
