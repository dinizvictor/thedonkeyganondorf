#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define TELA_H 480
#define TELA_W 640
#define GANON_H 58
#define GANON_W 74
#define MAGIA_H 18
#define MAGIA_W 20

void transparencia(SDL_Surface* surface){

    SDL_SetColorKey(surface, SDL_SRCCOLORKEY, SDL_MapRGB(surface->format, 0, 64, 128));

}

bool verificaSurface(SDL_Surface* surface){

    if(!surface)
    return 0;
    else
    return 1;

}

int colisao( SDL_Rect A, SDL_Rect B )
{
    //lados dos retangulos
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //calcula os lados do rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    //calcula os lados do rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    //Se nao colidir
    if( bottomA <= topB )
    {
        return 0;
    }

    if( topA >= bottomB )
    {
        return 0;
    }

    if( rightA <= leftB )
    {
        return 0;
    }

    if( leftA >= rightB )
    {
        return 0;
    }

    //Se colidir
    return 1;
}

int calculoScore(SDL_Rect link, SDL_Rect magia, int pisoLink, int pisoMagia, int sizeLink, int sizeMagia, int orientacao){


    if(orientacao == 0 && link.x + sizeLink > magia.x && link.x < magia.x + sizeMagia && !colisao(link,magia) && pisoMagia == pisoLink){

        return 1;

    }

    else if(orientacao == 1 && link.x < magia.x + sizeMagia && link.x + sizeLink > magia.x && !colisao(link,magia) && pisoMagia == pisoLink){

        return 1;

    }

    else

        return 0;

}


typedef struct{

    SDL_Rect rectSRC;
    SDL_Rect rectSprite[12];
    SDL_Surface* surface;
    SDL_Surface* spriteSurface;

} Personagem;

typedef struct{

    char nome[3];
    int pontos;

} Pontuacao;

int main(int argc, char** argv){

    Personagem link;
    Personagem ganondorf;

    //Superficie que cria a tela.
    SDL_Surface* tela = SDL_SetVideoMode(TELA_W, TELA_H, 16,SDL_HWSURFACE|SDL_DOUBLEBUF);
    if(!verificaSurface(tela)){
        printf("Erro: Tela");
        return 1;
    }
    //Colocando Título
    SDL_WM_SetCaption("The Donkey Ganondorf","The Legend of Zelda - The Donkey Ganondorf");
    //Recebendo a imagem.
    link.surface = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/LinkParado.bmp");
    if(!verificaSurface(link.surface)){
        printf("Erro: Link Surface");
        return 1;
    }
    transparencia(link.surface);
    //Recebendo a imagem.
    link.spriteSurface = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/LinkAndando.bmp");
    if(!verificaSurface(link.spriteSurface)){
        printf("Erro: Link Sprite");
        return 1;
    }
    transparencia(link.spriteSurface);

    link.rectSRC.h = link.surface->h;
    link.rectSRC.w = link.surface->w;

    for(int l=0;l<12;l++){

        (l<6) ? (link.rectSprite[l].x = l * link.surface->w): (link.rectSprite[l].x = (l-6) * link.surface->w);
        (l<6) ? (link.rectSprite[l].y = 0): (link.rectSprite[l].y = link.surface->h);

        link.rectSprite[l].w = link.surface->w;
        link.rectSprite[l].h = link.surface->h;
    }

    SDL_Surface* spriteGiroEspada = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/espadaGiro.bmp");
    if(!verificaSurface(spriteGiroEspada)){
        printf("Erro: Sprite Espada");
        return 1;
    }
    transparencia(spriteGiroEspada);

    SDL_Rect giroEspadaRect;
    giroEspadaRect.w = 61;
    giroEspadaRect.h = 48;

    SDL_Rect spriteGiroEspadaRect[8];

    for(int l=0;l<8;l++){

        spriteGiroEspadaRect[l].x = l * 61;
        spriteGiroEspadaRect[l].y = 0;
        spriteGiroEspadaRect[l].w = 61;
        spriteGiroEspadaRect[l].h = 48;

    }

    SDL_Surface* zeldaCaida = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/Zelda1.bmp");
    if(!verificaSurface(zeldaCaida)){
        printf("Erro: Sprite Zelda Caida");
        return 1;
    }
    transparencia(zeldaCaida);

    SDL_Surface* zelda = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/Zelda2.bmp");
    if(!verificaSurface(zelda)){
        printf("Erro: Sprite Zelda");
        return 1;
    }
    transparencia(zelda);

    SDL_Surface* coracao = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/coracao.bmp");
    if(!verificaSurface(coracao)){
        printf("Erro: Sprite Coracao");
        return 1;
    }
    transparencia(coracao);

    SDL_Rect zeldaCaidaRect;
    zeldaCaidaRect.w = 64;
    zeldaCaidaRect.h = 30;
    zeldaCaidaRect.x = 81;
    zeldaCaidaRect.y = 67;

    SDL_Rect zeldaRect;
    zeldaRect.w = 22;
    zeldaRect.h = 47;
    zeldaRect.x = 145;
    zeldaRect.y = 47;

    SDL_Rect coracaoRect;
    coracaoRect.w = 30;
    coracaoRect.h = 28;
    coracaoRect.x = 167;
    coracaoRect.y = 26;

    SDL_Rect linkFinalRect;
    linkFinalRect.w = 27;
    linkFinalRect.h = 57;
    linkFinalRect.x = 197;
    linkFinalRect.y = 37;

    ganondorf.surface = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/GanondorfParado.bmp");
    if(!verificaSurface(ganondorf.surface)){
        printf("Erro: Ganondorf Surface");
        return 1;
    }
    transparencia(ganondorf.surface);

    ganondorf.rectSRC.h = ganondorf.surface->h;
    ganondorf.rectSRC.w = ganondorf.surface->w;

    ganondorf.spriteSurface = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/GanondorfMagia.bmp");
    if(!verificaSurface(ganondorf.spriteSurface)){
        printf("Erro: Ganondorf Sprite");
        return 1;
    }
    transparencia(ganondorf.spriteSurface);

    for(int l=0;l<4;l++){

        ganondorf.rectSprite[l].x = l * GANON_W;
        ganondorf.rectSprite[l].y = 0;
        ganondorf.rectSprite[l].w = GANON_W;
        ganondorf.rectSprite[l].h = GANON_H;
    }

    //Magia de Ataque

    SDL_Surface* magiaGanon = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/Magia2.bmp");
    if(!verificaSurface(magiaGanon)){
        printf("Erro: Magia");
        return 1;
    }
    transparencia(magiaGanon);

    SDL_Surface* escada = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/Escada2.bmp");
    if(!verificaSurface(escada)){
        printf("Erro: Escada");
        return 1;
    }
    transparencia(escada);

    SDL_Surface* piso = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/Piso.bmp");
    if(!verificaSurface(piso)){
        printf("Erro: Piso");
        return 1;
    }
    transparencia(piso);

    SDL_Rect escadaRect,escadaRect2,escadaRect3,escadaRect4,escadaRect5,escadaRect6;
    escadaRect.h = escadaRect2.h = escadaRect3.h = escadaRect4.h = escadaRect5.h = escadaRect6.h = escada->h;
    escadaRect.w = escadaRect2.w = escadaRect3.w = escadaRect4.w = escadaRect5.w = escadaRect6.w = escada->w;

    SDL_Surface* imgFundo = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/fundo.bmp");
    if(!verificaSurface(imgFundo)){
        printf("Erro: %s",SDL_GetError());
        return 1;
    }

    SDL_Surface* entrada1 = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/Entrada1.bmp");
    if(!verificaSurface(entrada1)){
        printf("Erro: %s",SDL_GetError());
        return 1;
    }

    SDL_Surface* entrada2 = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/Entrada2.bmp");
    if(!verificaSurface(entrada2)){
        printf("Erro: %s",SDL_GetError());
        return 1;
    }

    SDL_Surface* menu = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/Menu.bmp");
    if(!verificaSurface(menu)){
        printf("Erro: %s",SDL_GetError());
        return 1;
    }

    SDL_Surface* menu1 = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/Menu1.bmp");
    if(!verificaSurface(menu1)){
        printf("Erro: %s",SDL_GetError());
        return 1;
    }

    SDL_Surface* menu2 = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/Menu2.bmp");
    if(!verificaSurface(menu2)){
        printf("Erro: %s",SDL_GetError());
        return 1;
    }

    SDL_Surface* menu3 = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/Menu3.bmp");
    if(!verificaSurface(menu3)){
        printf("Erro: %s",SDL_GetError());
        return 1;
    }

    SDL_Surface* menu4 = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/Menu4.bmp");
    if(!verificaSurface(menu4)){
        printf("Erro: %s",SDL_GetError());
        return 1;
    }

    SDL_Surface* menu5 = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/Menu5.bmp");
    if(!verificaSurface(menu5)){
        printf("Erro: %s",SDL_GetError());
        return 1;
    }

    SDL_Surface* comoJogar1 = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/ComoJogar1.bmp");
    if(!verificaSurface(comoJogar1)){
        printf("Erro: %s",SDL_GetError());
        return 1;
    }

    SDL_Surface* comoJogar2 = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/ComoJogar2.bmp");
    if(!verificaSurface(comoJogar2)){
        printf("Erro: %s",SDL_GetError());
        return 1;
    }

    SDL_Surface* recordes1 = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/Recordes1.bmp");
    if(!verificaSurface(recordes1)){
        printf("Erro: %s",SDL_GetError());
        return 1;
    }

    SDL_Surface* recordes2 = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/Recordes2.bmp");
    if(!verificaSurface(recordes2)){
        printf("Erro: %s",SDL_GetError());
        return 1;
    }

    SDL_Surface* creditos1 = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/Creditos1.bmp");
    if(!verificaSurface(creditos1)){
        printf("Erro: %s",SDL_GetError());
        return 1;
    }

    SDL_Surface* creditos2 = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/Creditos2.bmp");
    if(!verificaSurface(creditos2)){
        printf("Erro: %s",SDL_GetError());
        return 1;
    }

    SDL_Surface* sair = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/Sair.bmp");
    if(!verificaSurface(sair)){
        printf("Erro: %s",SDL_GetError());
        return 1;
    }

    SDL_Surface* gameOver = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/GameOver.bmp");
    if(!verificaSurface(gameOver)){
        printf("Erro: %s",SDL_GetError());
        return 1;
    }

    SDL_Surface* gameOver1 = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/GameOver1.bmp");
    if(!verificaSurface(gameOver1)){
        printf("Erro: %s",SDL_GetError());
        return 1;
    }

    SDL_Surface* gameOver2 = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/GameOver2.bmp");
    if(!verificaSurface(gameOver2)){
        printf("Erro: %s",SDL_GetError());
        return 1;
    }

    SDL_Surface* venceu = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/Venceu.bmp");
    if(!verificaSurface(venceu)){
        printf("Erro: %s",SDL_GetError());
        return 1;
    }

    SDL_Surface* venceu1 = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/Venceu1.bmp");
    if(!verificaSurface(venceu1)){
        printf("Erro: %s",SDL_GetError());
        return 1;
    }

    SDL_Surface* venceu2 = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/Venceu2.bmp");
    if(!verificaSurface(venceu2)){
        printf("Erro: %s",SDL_GetError());
        return 1;
    }

    SDL_Surface* vidas1 = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/vidas1.bmp");
    if(!verificaSurface(vidas1)){
        printf("Erro: %s",SDL_GetError());
        return 1;
    }
    transparencia(vidas1);

    SDL_Surface* vidas2 = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/vidas2.bmp");
    if(!verificaSurface(vidas2)){
        printf("Erro: %s",SDL_GetError());
        return 1;
    }
    transparencia(vidas2);

    SDL_Surface* vidas3 = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/vidas3.bmp");
    if(!verificaSurface(vidas3)){
        printf("Erro: %s",SDL_GetError());
        return 1;
    }
    transparencia(vidas3);

    SDL_Surface* espada = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/espadaMestre.bmp");
    if(!verificaSurface(espada)){
        printf("Erro: %s",SDL_GetError());
        return 1;
    }
    transparencia(espada);

    SDL_Surface* giroEspada = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/espadaGiro.bmp");
    if(!verificaSurface(giroEspada)){
        printf("Erro: %s",SDL_GetError());
        return 1;
    }
    transparencia(giroEspada);


    SDL_Rect fundoRect;
    fundoRect.x = 0;
    fundoRect.y = 0;

    SDL_Rect entradaRect;
    entradaRect.x = 0;
    entradaRect.y = 0;

    SDL_Rect espadaRect;
    espadaRect.h = 19;
    espadaRect.w = 19;
    espadaRect.x = 553;
    espadaRect.y = 47;

    //Botoes do Menu

    SDL_Rect btJogar;
    btJogar.w = 82;
    btJogar.h = 46;
    btJogar.x = 280;
    btJogar.y = 219;

   SDL_Rect btComoJogar;
    btComoJogar.w = 147;
    btComoJogar.h = 42;
    btComoJogar.x = 247;
    btComoJogar.y = 266;

    SDL_Rect btRecordes;
    btRecordes.w = 119;
    btRecordes.h = 42;
    btRecordes.x = 261;
    btRecordes.y = 309;

    SDL_Rect btCreditos;
    btCreditos.w = 108;
    btCreditos.h = 42;
    btCreditos.x = 266;
    btCreditos.y = 352;

    SDL_Rect btSair;
    btSair.w = 57;
    btSair.h = 42;
    btSair.x = 292;
    btSair.y = 395;

    SDL_Rect btVoltar;
    btVoltar.w = 80;
    btVoltar.h = 39;
    btVoltar.x = 554;
    btVoltar.y = 427;

    SDL_Rect btJogarNov;
    btJogarNov.w = 210;
    btJogarNov.h = 43;
    btJogarNov.x = 8;
    btJogarNov.y = 431;

    SDL_Rect btMenu;
    btMenu.w = 64;
    btMenu.h = 43;
    btMenu.x = 570;
    btMenu.y = 431;

    SDL_Rect nomeRect;
    nomeRect.w = 52;
    nomeRect.h = 43;
    nomeRect.x = 205;
    nomeRect.y = 152;

    SDL_Rect pontoRect;
    pontoRect.w = 100;
    pontoRect.h = 43;
    pontoRect.x = 205;
    pontoRect.y = 275;

    SDL_Rect primeiroRect;
    primeiroRect.w = 88;
    primeiroRect.h = 38;
    primeiroRect.x = 128;
    primeiroRect.y = 207;

    SDL_Rect nomePrimeiroRect;
    nomePrimeiroRect.w = 43;
    nomePrimeiroRect.h = 38;
    nomePrimeiroRect.x = 227;
    nomePrimeiroRect.y = 207;

    SDL_Rect segundoRect;
    segundoRect.w = 88;
    segundoRect.h = 38;
    segundoRect.x = 128;
    segundoRect.y = 245;

    SDL_Rect nomeSegundoRect;
    nomeSegundoRect.w = 43;
    nomeSegundoRect.h = 38;
    nomeSegundoRect.x = 227;
    nomeSegundoRect.y = 245;

    SDL_Rect terceiroRect;
    terceiroRect.w = 88;
    terceiroRect.h = 38;
    terceiroRect.x = 128;
    terceiroRect.y = 283;

    SDL_Rect nomeTerceiroRect;
    nomeTerceiroRect.w = 43;
    nomeTerceiroRect.h = 38;
    nomeTerceiroRect.x = 227;
    nomeTerceiroRect.y = 283;

    SDL_Rect vidasRect;
    vidasRect.w = 74;
    vidasRect.h = 27;
    vidasRect.x = 6;
    vidasRect.y = 0;

    SDL_Rect scoreShowRect;
    scoreShowRect.w = 70;
    scoreShowRect.h = 31;
    scoreShowRect.x = 570;
    scoreShowRect.y = 0;

    SDL_Rect palavraScoreRect;
    palavraScoreRect.w = 59;
    palavraScoreRect.h = 31;
    palavraScoreRect.x = 511;
    palavraScoreRect.y = 0;


    link.rectSRC.x = piso->w - link.surface->w;
    link.rectSRC.y = ((tela->h - piso->h)-link.surface->h)+4;

    SDL_Rect pisoRect1[3][15], pisoRect2[3][14];
    int i, posX = 0, posY = 1;

    //Primeiro Piso.
    for(i=0;i<15;i++){
        if(i<7){
            pisoRect1[0][i].y = tela->h - piso->h;
            pisoRect1[0][i].x = posX;
            posX = posX + piso->w;
        }
        else{

            pisoRect1[0][i].y = (tela->h - piso->h)-posY;
            pisoRect1[0][i].x = posX;
            posX = posX + piso->w;
            posY++;
        }
    }

    posX = 0;
    posY = 1;
    //Segundo Piso.
    for(i=0;i<14;i++){

        pisoRect2[0][i].y =(((tela->h - piso->h)-link.surface->h)-25)+posY;
        pisoRect2[0][i].x = posX;
        posX = posX + piso->w;
        posY++;
    }

    posX = piso->w;
    posY = 1;
    //Terceiro Piso.
    for(i=0;i<15;i++){

        pisoRect1[1][i].y =(((tela->h - (6 * piso->h))-link.surface->h)-40)-posY;
        pisoRect1[1][i].x = posX;
        posX = posX + piso->w;
        posY++;

    }

    posX = 0;
    posY = 1;
    //Quarto Piso.
    for(i=0;i<14;i++){

        pisoRect2[1][i].y =(((tela->h - (16 * piso->h))-link.surface->h)-40)+posY;
        pisoRect2[1][i].x = posX;
        posX = posX + piso->w;
        posY++;

    }

    posX = piso->w;
    posY = 1;
    //Quinto Piso.
    for(i=0;i<15;i++){

        pisoRect1[2][i].y =(((tela->h - (23 * piso->h))-link.surface->h)-40)-posY;
        pisoRect1[2][i].x = posX;
        posX = posX + piso->w;
        posY++;

    }

    posX = 0;
    posY = 1;
    //Sexto Piso
    for(i=0;i<14;i++){

        if(i<10){
            pisoRect2[2][i].y = (((tela->h - (32 * piso->h))-link.surface->h)-45);
            pisoRect2[2][i].x = posX;
            posX = posX + piso->w;
        }
        else{

            pisoRect2[2][i].y = (((tela->h - (32 * piso->h))-link.surface->h)-45)+posY;
            pisoRect2[2][i].x = posX;
            posX = posX + piso->w;
            posY++;
        }

    }

    //Rects das escadas
    escadaRect.x = (piso->w) * 12;
    escadaRect.y = ((tela->h - escada->h) - piso->h);

    escadaRect2.x = (piso->w) * 2;
    escadaRect2.y = pisoRect2[0][1].y - escada->h;

    escadaRect3.x = (piso->w) * 12;
    escadaRect3.y = pisoRect1[1][11].y - escada->h;

    escadaRect4.x = (piso->w) * 2;
    escadaRect4.y = pisoRect2[1][1].y - escada->h;

    escadaRect5.x = (piso->w) * 12;
    escadaRect5.y = pisoRect1[2][12].y - escada->h;

    ganondorf.rectSRC.x = pisoRect2[2][4].x;
    ganondorf.rectSRC.y = (pisoRect2[2][1].y - ganondorf.surface->h) + 5;
    //Sprites magia.
    SDL_Rect spriteMagiaRect[15],magiaRect[2];
    int cont;
    for(cont = 0; cont<15; cont++){

        spriteMagiaRect[cont].h = magiaGanon->h;
        spriteMagiaRect[cont].w = magiaGanon->w;
        spriteMagiaRect[cont].x = pisoRect2[2][4].x + 45;
        spriteMagiaRect[cont].y = pisoRect2[2][4].y - magiaGanon->h;

    }

    magiaRect[0].h = MAGIA_H;
    magiaRect[0].w = MAGIA_W;
    magiaRect[0].x = 0;
    magiaRect[0].y = 0;

    magiaRect[1].h = MAGIA_H;
    magiaRect[1].w = MAGIA_W;
    magiaRect[1].x = MAGIA_W;
    magiaRect[1].y = 0;

    //Variáveis de Auxilio ou Contagem

    SDL_Event event; //Um evento enviado pela SDL.

    int quitMenu = 0, quit = 0;// quitMenu = 0; //Devemos encerrar o jogo?

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO | SDL_INIT_TIMER); //Inicializar a SDL.

    TTF_Init();

    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
    Mix_Music* MenuPrincipalMusic = Mix_LoadMUS("/home/victor/Área de Trabalho/Jogo/Jogo/Temas/MenuPrincipal.wav");
    if(MenuPrincipalMusic == NULL){

        printf("Não foi possivel abrir o audio!\n");
        return 1;

    }

    Mix_Music* JogoMusic = Mix_LoadMUS("/home/victor/Área de Trabalho/Jogo/Jogo/Temas/MusicaJogo.wav");
    if(JogoMusic == NULL){

        printf("Não foi possivel abrir o audio!\n");
        return 1;

    }

    Mix_Chunk* ColisaoMusic = Mix_LoadWAV("/home/victor/Área de Trabalho/Jogo/Jogo/Temas/destroiMagia.wav");
    if(ColisaoMusic == NULL){

        printf("Não foi possivel abrir o audio!\n");
        return 1;

    }

    Mix_Chunk* SelecaoMusic = Mix_LoadWAV("/home/victor/Área de Trabalho/Jogo/Jogo/Temas/selecao.wav");
    if(SelecaoMusic == NULL){

        printf("Não foi possivel abrir o audio!\n");
        return 1;

    }

    Mix_Music* GameOverMusic = Mix_LoadMUS("/home/victor/Área de Trabalho/Jogo/Jogo/Temas/GameOver.wav");
    if(GameOverMusic == NULL){

        printf("Não foi possivel abrir o audio!\n");
        return 1;

    }

    Mix_Music* VenceuMusic = Mix_LoadMUS("/home/victor/Área de Trabalho/Jogo/Jogo/Temas/Ganhou.wav");
    if(VenceuMusic == NULL){

        printf("Não foi possivel abrir o audio!\n");
        return 1;

    }

    //Menu
    int tempoEntrada = 0, quitLoopMenu = 0, quitLoopComoJogar = 0,
        quitLoopRecordes = 0, quitLoopCreditos = 0, quitLoopSair = 0, quitTelaGameOver = 0,
        quitTelaVenceu = 0;
    SDL_Surface* surfaceAtual = menu;
    //Teclas.
    bool a[6] = {0,0,0,0,0};
    bool enter = 0;
    //Piso atual.
    int pisoAtual = 1;
    //Chave da posição do sprite.
    int key = 0, keyMagia = 0, contMagia = 0, keyGanon = 0;
    //Controlador de Velocidade de Animação
    const int FPS = 25; //19
    Uint32 start;
    float frame = 0;

    //Pulo
    int tempo = 0, pular = 0, descer = 0;

    //Posição da magia
    int pisoMagia[15],contPiso;

    for(contPiso=0;contPiso<15;contPiso++)
        pisoMagia[contPiso] = 6;

    //Parâmetros Jogador
    int vidas = 3, naEscada = 0, preScore = 0, score = 0, orientacao = 0, pegouEspada = 0, keyGiroEspada = 0, tempoAnimaGiro = 0, ganhou = 0;

    //Parâmetros Magia
    int magiaVel = 4, ataqueGanon = 0, tempoMagia = 0, magiaAtiva[8] = {1,1,1,1,1,1,1,1}; //4

    //Texto
    FILE* sco;
    Pontuacao primeiroLugar, segundoLugar, terceiroLugar;

    SDL_Surface* message = NULL; //Fim De Jogo
    SDL_Surface* message2 = NULL;

    SDL_Surface* message3 = NULL; //Recordes
    SDL_Surface* message4 = NULL;
    SDL_Surface* message5 = NULL;
    SDL_Surface* message6 = NULL;
    SDL_Surface* message7 = NULL;
    SDL_Surface* message8 = NULL;

    SDL_Surface* message9 = NULL; //Info Jogador
    SDL_Surface* message10 = NULL;

    TTF_Font *font = NULL;
    TTF_Font *font2 = NULL;
    TTF_Font *font3 = NULL;

    SDL_Color corTexto = {43, 169, 200};

    font = TTF_OpenFont("AgencyFB.ttf", 35);

    font2 = TTF_OpenFont("AgencyFB.ttf", 30);

    font3 = TTF_OpenFont("AgencyFB.ttf", 24);

    if(font == NULL){

        printf("Erro: Fonte não encontrada.\n");
        return 1;

    }

    //Info Jogador

    char showScore[7];

    do{ //Loop do Menu

        while(SDL_PollEvent(&event)){

            switch(event.type){
                    //caso escolha sair (x) termina a execuçao
                    case SDL_QUIT:
                        SDL_Quit();
                        TTF_Quit();
                        Mix_Quit();
                        return 0;
                        break;

                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym){

                            case SDLK_RETURN:
                                enter = 1;
                                break;

                            default:
                                enter = 0;
                                break;

                        }
                        break;

                    case SDL_KEYUP:
                        switch(event.key.keysym.sym){

                            case SDLK_RETURN:
                                enter = 0;
                                break;

                            default:
                                enter = 0;
                                break;

                        }
                        break;
                }

        }

        if(enter){
            Mix_PlayChannel( -1, SelecaoMusic, 0 );
            while(tempoEntrada < 6){

                SDL_BlitSurface(entrada2,NULL,tela,&entradaRect);
                SDL_Flip(tela);
                SDL_Delay(10);
                SDL_BlitSurface(entrada1,NULL,tela,&entradaRect);
                SDL_Flip(tela);
                tempoEntrada++;
            }

            while(!quitLoopMenu){ //Menu Principal

                if(Mix_PlayingMusic() == 0){
                        //Play the music
                        if( Mix_PlayMusic(MenuPrincipalMusic, -1) == -1 ){
                            return 1;
                        }
                }

                while(SDL_PollEvent(&event)){

                    switch(event.type){ //Acender Opções

                        case SDL_QUIT:
                            SDL_Quit();
                            TTF_Quit();
                            Mix_Quit();
                            return 0;
                            break;

                        case SDL_MOUSEMOTION:
                            if((event.motion.x > btJogar.x && event.motion.x < btJogar.x + btJogar.w) && (event.motion.y > btJogar.y && event.motion.y < btJogar.y + btJogar.h)){

                                surfaceAtual = menu1;

                            }
                            else if((event.motion.x > btComoJogar.x && event.motion.x < btComoJogar.x + btComoJogar.w) && (event.motion.y > btComoJogar.y && event.motion.y < btComoJogar.y + btComoJogar.h)){

                                surfaceAtual = menu2;

                            }
                            else if((event.motion.x > btRecordes.x && event.motion.x < btRecordes.x + btRecordes.w) && (event.motion.y > btRecordes.y && event.motion.y < btRecordes.y + btRecordes.h)){

                                surfaceAtual = menu3;

                            }
                            else if((event.motion.x > btCreditos.x && event.motion.x < btCreditos.x + btCreditos.w) && (event.motion.y > btCreditos.y && event.motion.y < btCreditos.y + btCreditos.h)){

                                surfaceAtual = menu4;

                            }
                            else if((event.motion.x > btSair.x && event.motion.x < btSair.x + btSair.w) && (event.motion.y > btSair.y && event.motion.y < btSair.y + btSair.h)){

                                surfaceAtual = menu5;

                            }

                            else{

                                surfaceAtual = menu;

                            }
                            break;

                        case SDL_MOUSEBUTTONDOWN: //Verificar Clique
                            if(event.button.button == SDL_BUTTON_LEFT){

                                if((event.motion.x > btJogar.x && event.motion.x < btJogar.x + btJogar.w) && (event.motion.y > btJogar.y && event.motion.y < btJogar.y + btJogar.h)){
                                     tempoEntrada = 0;
                                     quit = 0;
                                     vidas = 3;
                                     ganhou = 0;

                                     link.rectSRC.x = piso->w - link.surface->w;
                                     link.rectSRC.y = ((tela->h - piso->h)-link.surface->h)+4;

                                     pegouEspada = 0;
                                     Mix_HaltMusic(); // Para a Musica do Menu
                                     Mix_PlayChannel( -1, SelecaoMusic, 0 );
                                     for(int l = 0;l < 8;l++){

                                        magiaAtiva[l] = 1;
                                        pisoMagia[l] = 6;

                                     }
                                     a[0] = a[1] = a[2] = a[3] = a[4] = a[5] = 0;
                                     while(tempoEntrada < 6){

                                        SDL_BlitSurface(menu,NULL,tela,&entradaRect);
                                        SDL_Flip(tela);
                                        SDL_Delay(10);
                                        SDL_BlitSurface(menu1,NULL,tela,&entradaRect);
                                        SDL_Flip(tela);

                                        SDL_FillRect(tela, 0, SDL_MapRGB(tela->format,0,0,0));
                                        tempoEntrada++;

                                     }
                                     do{ //Inicio do loop do jogo

                                        if(Mix_PlayingMusic() == 0){
                                        //Play the music
                                            if( Mix_PlayMusic(JogoMusic, -1) == -1 ){
                                                return 1;
                                            }
                                        }

                                        start = SDL_GetTicks();

                                        surfaceAtual = menu;

                                        tempoMagia++;

                                        while(SDL_PollEvent(&event)){ //Checar eventos.

                                           switch(event.type)
                                            {
                                                //caso escolha sair (x) termina a execuçao
                                                case SDL_QUIT:
                                                    SDL_Quit();
                                                    TTF_Quit();
                                                    Mix_Quit();
                                                    return 0;
                                                    break;

                                                //caso Tecla Esteja pressionada
                                                case SDL_KEYDOWN:
                                                    switch(event.key.keysym.sym)
                                                    {
                                                        case SDLK_DOWN: //Baixo
                                                            a[0] = 1;
                                                            break;
                                                        case SDLK_RIGHT: //Direita
                                                            a[1] = 1;
                                                            break;
                                                        case SDLK_LEFT: //Esquerda
                                                            a[2] = 1;
                                                            break;
                                                        case SDLK_UP: //Cima
                                                            a[3] = 1;
                                                            break;
                                                        case SDLK_SPACE: //Espaço-Pular
                                                            if(!naEscada && !pegouEspada)
                                                                a[4] = 1;
                                                            break;
                                                        case SDLK_x: //X-Atacar
                                                            a[5] = 1;
                                                            break;
                                                        default:
                                                            a[0] = 0;
                                                            a[1] = 0;
                                                            a[2] = 0;
                                                            a[3] = 0;
                                                            a[5] = 0;
                                                            break;

                                                    }
                                                    break;

                                                //caso Tecla Não Esteja pressionada
                                                case SDL_KEYUP:
                                                    switch(event.key.keysym.sym)
                                                    {
                                                        case SDLK_DOWN: //Baixo
                                                            a[0] = 0;
                                                            break;
                                                        case SDLK_RIGHT: //Direita
                                                            a[1] = 0;
                                                            break;
                                                        case SDLK_LEFT: //Esquerda
                                                            a[2] = 0;
                                                            break;
                                                        case SDLK_UP: //Cima
                                                            a[3] = 0;
                                                            break;
                                                        case SDLK_x: //X-Atacar
                                                            a[5] = 0;
                                                            break;
                                                        default:
                                                            a[0] = 0;
                                                            a[1] = 0;
                                                            a[2] = 0;
                                                            a[3] = 0;
                                                            a[5] = 0;
                                                            break;

                                                    }
                                                    break;
                                            }
                                        }

                                        SDL_FillRect(tela, 0, SDL_MapRGB(tela->format,0,0,0)); //Limpar a tela.

                                        //Desenhar imagem de fundo
                                        SDL_BlitSurface(imgFundo,NULL,tela,&fundoRect);

                                        //Desenhar escadas
                                        SDL_BlitSurface(escada,NULL,tela,&escadaRect);
                                        SDL_BlitSurface(escada,NULL,tela,&escadaRect2);
                                        SDL_BlitSurface(escada,NULL,tela,&escadaRect3);
                                        SDL_BlitSurface(escada,NULL,tela,&escadaRect4);
                                        SDL_BlitSurface(escada,NULL,tela,&escadaRect5);

                                        //Desenhar os pisos.
                                        int j;

                                        for(i=0;i<3;i++){
                                            for(j=0;j<15;j++){

                                                SDL_BlitSurface(piso,NULL,tela,&pisoRect1[i][j]);

                                            }
                                        }

                                        for(i=0;i<3;i++){
                                            for(j=0;j<14;j++){

                                                SDL_BlitSurface(piso,NULL,tela,&pisoRect2[i][j]);

                                            }
                                        }

                                        //Descer escadas

                                        if(a[0] && !pegouEspada){

                                            if(pisoAtual == 1 || pisoAtual == 2){

                                                if(link.rectSRC.x >= pisoRect1[0][12].x && link.rectSRC.x + link.surface->w <= pisoRect1[0][12].x + piso->w){


                                                    if(link.rectSRC.y + link.surface->h <= pisoRect1[0][12].y + 3)
                                                        link.rectSRC.y+=3;

                                                    if(link.rectSRC.y + link.surface->h > 406 && link.rectSRC.y + link.surface->h < 469)
                                                        naEscada = 1;

                                                    if(link.rectSRC.y + link.surface->h >= 469){
                                                        pisoAtual = 1;
                                                        naEscada = 0;
                                                    }

                                                }

                                            }

                                            if(pisoAtual == 2 || pisoAtual == 3){

                                                if(link.rectSRC.x >= pisoRect2[0][2].x && link.rectSRC.x + link.surface->w <= pisoRect2[0][2].x + piso->w){


                                                    if(link.rectSRC.y + link.surface->h <= pisoRect2[0][2].y + 3)
                                                        link.rectSRC.y+=3;

                                                    if(link.rectSRC.y + link.surface->h > 330 && link.rectSRC.y + link.surface->h < 394)
                                                        naEscada = 1;

                                                    if(link.rectSRC.y + link.surface->h >= 394){
                                                        pisoAtual = 2;
                                                        naEscada = 0;
                                                    }

                                                }

                                            }

                                             if(pisoAtual == 3 || pisoAtual == 4){

                                                if(link.rectSRC.x >= pisoRect1[1][11].x && link.rectSRC.x + link.surface->w <= pisoRect1[1][11].x + piso->w){


                                                    if(link.rectSRC.y + link.surface->h <= pisoRect1[1][11].y + 2)
                                                        link.rectSRC.y+=3;

                                                    if(link.rectSRC.y + link.surface->h > 255 && link.rectSRC.y + link.surface->h < 318)
                                                        naEscada = 1;

                                                    if(link.rectSRC.y + link.surface->h >= 318){
                                                        pisoAtual = 3;
                                                        naEscada = 0;
                                                    }

                                                }

                                            }

                                             if(pisoAtual == 4 || pisoAtual == 5){

                                                if(link.rectSRC.x >= pisoRect2[1][2].x && link.rectSRC.x + link.surface->w <= pisoRect2[1][2].x + piso->w){


                                                    if(link.rectSRC.y + link.surface->h <= pisoRect2[1][2].y + 3)
                                                        link.rectSRC.y+=3;

                                                    if(link.rectSRC.y + link.surface->h > 178 && link.rectSRC.y + link.surface->h < 244)
                                                        naEscada = 1;

                                                    if(link.rectSRC.y + link.surface->h >= 244){
                                                        pisoAtual = 4;
                                                        naEscada = 0;
                                                    }

                                                }

                                            }

                                             if(pisoAtual == 5 || pisoAtual == 6){

                                                if(link.rectSRC.x >= pisoRect1[2][11].x && link.rectSRC.x + link.surface->w <= pisoRect1[2][11].x + piso->w){


                                                    if(link.rectSRC.y + link.surface->h <= pisoRect1[2][11].y + 3)
                                                        link.rectSRC.y+=3;

                                                    if(link.rectSRC.y + link.surface->h > 109 && link.rectSRC.y + link.surface->h < 165)
                                                        naEscada = 1;

                                                    if(link.rectSRC.y + link.surface->h >= 165){
                                                        pisoAtual = 5;
                                                        naEscada = 0;
                                                    }

                                                }

                                            }

                                        }

                                        //Subir escadas

                                        if(a[3] && !pegouEspada){

                                            if(pisoAtual == 1 || pisoAtual == 2){

                                                if(link.rectSRC.x >= pisoRect1[0][12].x && link.rectSRC.x + link.surface->w < pisoRect1[0][12].x + piso->w){

                                                    if(link.rectSRC.y + link.surface->h >= pisoRect2[0][12].y + 7)
                                                        link.rectSRC.y-=3;

                                                    if(link.rectSRC.y + link.surface->h > 404 && link.rectSRC.y + link.surface->h < 470)
                                                        naEscada = 1;

                                                    if(link.rectSRC.y + link.surface->h <= 407){
                                                        pisoAtual = 2;
                                                        naEscada = 0;
                                                    }

                                                }

                                            }

                                             if(pisoAtual == 2 || pisoAtual == 3){

                                                if(link.rectSRC.x >= pisoRect2[0][2].x && link.rectSRC.x + link.surface->w <= pisoRect2[0][2].x + piso->w){


                                                    if(link.rectSRC.y + link.surface->h >= pisoRect1[1][1].y + 3)
                                                        link.rectSRC.y-=3;

                                                    if(link.rectSRC.y + link.surface->h > 330 && link.rectSRC.y + link.surface->h < 394)
                                                        naEscada = 1;

                                                    if(link.rectSRC.y + link.surface->h <= 330 && link.rectSRC.y + link.surface->h > 325){
                                                        pisoAtual = 3;
                                                        naEscada = 0;
                                                    }

                                                }

                                            }

                                            if(pisoAtual == 3 || pisoAtual == 4){

                                                if(link.rectSRC.x >= pisoRect1[1][11].x && link.rectSRC.x + link.surface->w <= pisoRect1[1][11].x + piso->w){


                                                    if(link.rectSRC.y + link.surface->h >= pisoRect2[1][12].y + 3)
                                                        link.rectSRC.y-=3;

                                                    if(link.rectSRC.y + link.surface->h > 255 && link.rectSRC.y + link.surface->h < 318)
                                                        naEscada = 1;

                                                    if(link.rectSRC.y + link.surface->h <= 255){
                                                        pisoAtual = 4;
                                                        naEscada = 0;
                                                    }

                                                }

                                            }

                                            if(pisoAtual == 4 || pisoAtual == 5){

                                                if(link.rectSRC.x >= pisoRect2[1][2].x && link.rectSRC.x + link.surface->w <= pisoRect2[1][2].x + piso->w){


                                                    if(link.rectSRC.y + link.surface->h >= pisoRect1[2][1].y + 3)
                                                        link.rectSRC.y-=3;

                                                    if(link.rectSRC.y + link.surface->h > 178 && link.rectSRC.y + link.surface->h < 244)
                                                        naEscada = 1;

                                                    if(link.rectSRC.y + link.surface->h <= 178){
                                                        pisoAtual = 5;
                                                        naEscada = 0;
                                                    }

                                                }

                                            }

                                            if(pisoAtual == 5 || pisoAtual == 6){

                                                if(link.rectSRC.x >= pisoRect1[2][11].x && link.rectSRC.x + link.surface->w <= pisoRect1[2][11].x + piso->w){


                                                    if(link.rectSRC.y + link.surface->h >= pisoRect2[2][13].y + 3)
                                                        link.rectSRC.y-=3;

                                                    if(link.rectSRC.y + link.surface->h > 109 && link.rectSRC.y + link.surface->h < 165)
                                                        naEscada = 1;

                                                    if(link.rectSRC.y + link.surface->h <= 109){
                                                        pisoAtual = 6;
                                                        naEscada = 0;
                                                    }

                                                }

                                            }

                                        }

                                        //Pulo

                                        if(a[4]){

                                            tempo++;

                                        }
                                        if(tempo > 0){

                                            pular = 1;
                                            descer = 0;

                                        }

                                        if(tempo > 10){

                                            pular = 0;
                                            descer = 1;

                                        }

                                        if(tempo > 20){

                                            pular = 0;
                                            descer = 0;
                                            tempo = 0;
                                            a[4] = 0;

                                            if(pisoAtual == 1){

                                                if(link.rectSRC.x + link.rectSRC.w < piso->w*7)
                                                    link.rectSRC.y = ((tela->h - piso->h)-link.surface->h)+4;
                                                if(link.rectSRC.x + link.rectSRC.w >= piso->w*7 && link.rectSRC.x + link.rectSRC.w < piso->w*8)
                                                    link.rectSRC.y = (pisoRect1[0][7].y + 4) - link.rectSRC.h;
                                                if(link.rectSRC.x + link.rectSRC.w >= piso->w*8 && link.rectSRC.x + link.rectSRC.w < piso->w*9)
                                                    link.rectSRC.y = (pisoRect1[0][8].y + 4) - link.rectSRC.h;
                                                if(link.rectSRC.x + link.rectSRC.w >= piso->w*9 && link.rectSRC.x + link.rectSRC.w < piso->w*10)
                                                    link.rectSRC.y = (pisoRect1[0][9].y + 4) - link.rectSRC.h;
                                                if(link.rectSRC.x + link.rectSRC.w >= piso->w*10 && link.rectSRC.x + link.rectSRC.w < piso->w*11)
                                                    link.rectSRC.y = (pisoRect1[0][10].y + 4) - link.rectSRC.h;
                                                if(link.rectSRC.x + link.rectSRC.w >= piso->w*11 && link.rectSRC.x + link.rectSRC.w < piso->w*12)
                                                    link.rectSRC.y = (pisoRect1[0][11].y + 4) - link.rectSRC.h;
                                                if(link.rectSRC.x + link.rectSRC.w >= piso->w*12 && link.rectSRC.x + link.rectSRC.w < piso->w*13)
                                                    link.rectSRC.y = (pisoRect1[0][12].y + 4) - link.rectSRC.h;
                                                if(link.rectSRC.x + link.rectSRC.w >= piso->w*13 && link.rectSRC.x + link.rectSRC.w < piso->w*14)
                                                    link.rectSRC.y = (pisoRect1[0][13].y + 4) - link.rectSRC.h;
                                                if(link.rectSRC.x + link.rectSRC.w >= piso->w*14 && link.rectSRC.x + link.rectSRC.w < piso->w*15)
                                                    link.rectSRC.y = (pisoRect1[0][14].y + 4) - link.rectSRC.h;
                                            }

                                            if(pisoAtual == 2){

                                                if(link.rectSRC.x >= 0 && link.rectSRC.x < piso->w)
                                                    link.rectSRC.y = (pisoRect2[0][0].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w && link.rectSRC.x < piso->w*2)
                                                    link.rectSRC.y = (pisoRect2[0][1].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*2 && link.rectSRC.x < piso->w*3)
                                                    link.rectSRC.y = (pisoRect2[0][2].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*3 && link.rectSRC.x < piso->w*4)
                                                    link.rectSRC.y = (pisoRect2[0][3].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*4 && link.rectSRC.x < piso->w*5)
                                                    link.rectSRC.y = (pisoRect2[0][4].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*5 && link.rectSRC.x < piso->w*6)
                                                    link.rectSRC.y = (pisoRect2[0][5].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*6 && link.rectSRC.x < piso->w*7)
                                                    link.rectSRC.y = (pisoRect2[0][6].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*7 && link.rectSRC.x < piso->w*8)
                                                    link.rectSRC.y = (pisoRect2[0][7].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*8 && link.rectSRC.x < piso->w*9)
                                                    link.rectSRC.y = (pisoRect2[0][8].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*9 && link.rectSRC.x < piso->w*10)
                                                    link.rectSRC.y = (pisoRect2[0][9].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*10 && link.rectSRC.x < piso->w*11)
                                                    link.rectSRC.y = (pisoRect2[0][10].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*11 && link.rectSRC.x < piso->w*12)
                                                    link.rectSRC.y = (pisoRect2[0][11].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*12 && link.rectSRC.x < piso->w*13)
                                                    link.rectSRC.y = (pisoRect2[0][12].y - link.surface->h) + 2;

                                            }

                                            if(pisoAtual == 3){

                                                if(link.rectSRC.x >= piso->w && link.rectSRC.x < piso->w*2)
                                                    link.rectSRC.y = (pisoRect1[1][0].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*2 && link.rectSRC.x < piso->w*3)
                                                    link.rectSRC.y = (pisoRect1[1][1].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*3 && link.rectSRC.x < piso->w*4)
                                                    link.rectSRC.y = (pisoRect1[1][3].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*4 && link.rectSRC.x < piso->w*5)
                                                    link.rectSRC.y = (pisoRect1[1][4].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*5 && link.rectSRC.x < piso->w*6)
                                                    link.rectSRC.y = (pisoRect1[1][5].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*6 && link.rectSRC.x < piso->w*7)
                                                    link.rectSRC.y = (pisoRect1[1][6].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*7 && link.rectSRC.x < piso->w*8)
                                                    link.rectSRC.y = (pisoRect1[1][7].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*8 && link.rectSRC.x < piso->w*9)
                                                    link.rectSRC.y = (pisoRect1[1][8].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*9 && link.rectSRC.x < piso->w*10)
                                                    link.rectSRC.y = (pisoRect1[1][9].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*10 && link.rectSRC.x < piso->w*11)
                                                    link.rectSRC.y = (pisoRect1[1][10].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*11 && link.rectSRC.x < piso->w*12)
                                                    link.rectSRC.y = (pisoRect1[1][11].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*12 && link.rectSRC.x < piso->w*13)
                                                    link.rectSRC.y = (pisoRect1[1][12].y - link.surface->h) + 2;

                                            }

                                            if(pisoAtual == 4){

                                                if(link.rectSRC.x >= 0 && link.rectSRC.x < piso->w)
                                                    link.rectSRC.y = (pisoRect2[1][0].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w && link.rectSRC.x < piso->w*2)
                                                    link.rectSRC.y = (pisoRect2[1][1].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*2 && link.rectSRC.x < piso->w*3)
                                                    link.rectSRC.y = (pisoRect2[1][2].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*3 && link.rectSRC.x < piso->w*4)
                                                    link.rectSRC.y = (pisoRect2[1][3].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*4 && link.rectSRC.x < piso->w*5)
                                                    link.rectSRC.y = (pisoRect2[1][4].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*5 && link.rectSRC.x < piso->w*6)
                                                    link.rectSRC.y = (pisoRect2[1][5].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*6 && link.rectSRC.x < piso->w*7)
                                                    link.rectSRC.y = (pisoRect2[1][6].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*7 && link.rectSRC.x < piso->w*8)
                                                    link.rectSRC.y = (pisoRect2[1][7].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*8 && link.rectSRC.x < piso->w*9)
                                                    link.rectSRC.y = (pisoRect2[1][8].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*9 && link.rectSRC.x < piso->w*10)
                                                    link.rectSRC.y = (pisoRect2[1][9].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*10 && link.rectSRC.x < piso->w*11)
                                                    link.rectSRC.y = (pisoRect2[1][10].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*11 && link.rectSRC.x < piso->w*12)
                                                    link.rectSRC.y = (pisoRect2[1][11].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*12 && link.rectSRC.x < piso->w*13)
                                                    link.rectSRC.y = (pisoRect2[1][12].y - link.surface->h) + 2;

                                            }

                                            if(pisoAtual == 5){

                                                if(link.rectSRC.x >= piso->w && link.rectSRC.x < piso->w*2)
                                                    link.rectSRC.y = (pisoRect1[2][0].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*2 && link.rectSRC.x < piso->w*3)
                                                    link.rectSRC.y = (pisoRect1[2][1].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*3 && link.rectSRC.x < piso->w*4)
                                                    link.rectSRC.y = (pisoRect1[2][3].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*4 && link.rectSRC.x < piso->w*5)
                                                    link.rectSRC.y = (pisoRect1[2][4].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*5 && link.rectSRC.x < piso->w*6)
                                                    link.rectSRC.y = (pisoRect1[2][5].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*6 && link.rectSRC.x < piso->w*7)
                                                    link.rectSRC.y = (pisoRect1[2][6].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*7 && link.rectSRC.x < piso->w*8)
                                                    link.rectSRC.y = (pisoRect1[2][7].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*8 && link.rectSRC.x < piso->w*9)
                                                    link.rectSRC.y = (pisoRect1[2][8].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*9 && link.rectSRC.x < piso->w*10)
                                                    link.rectSRC.y = (pisoRect1[2][9].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*10 && link.rectSRC.x < piso->w*11)
                                                    link.rectSRC.y = (pisoRect1[2][10].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*11 && link.rectSRC.x < piso->w*12)
                                                    link.rectSRC.y = (pisoRect1[2][11].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*12 && link.rectSRC.x < piso->w*13)
                                                    link.rectSRC.y = (pisoRect1[2][12].y - link.surface->h) + 2;

                                            }

                                            if(pisoAtual == 6){

                                                if(link.rectSRC.x < piso->w*10)
                                                    link.rectSRC.y = (pisoRect2[2][0].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*10 && link.rectSRC.x < piso->w*11)
                                                    link.rectSRC.y = (pisoRect2[2][10].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*11 && link.rectSRC.x < piso->w*12)
                                                    link.rectSRC.y = (pisoRect2[2][11].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*12 && link.rectSRC.x < piso->w*13)
                                                    link.rectSRC.y = (pisoRect2[2][12].y - link.surface->h) + 2;

                                            }


                                        }
                                        //Pulo
                                        if(pular && !naEscada){
                                            link.rectSRC.y -= 4;
                                            //SDL_BlitSurface(link.surface,NULL,tela,&link.rectSRC);
                                        }
                                        if(descer && !naEscada){
                                            link.rectSRC.y += 4;
                                            //SDL_BlitSurface(link.surface,NULL,tela,&link.rectSRC);
                                        }

                                        //Caso RIGHT pressionado incrementa 3 a X
                                        if(a[1] && !naEscada){
                                            //Colisão
                                            orientacao = 0;
                                            if(pisoAtual == 1 && !a[4]){
                                                if(link.rectSRC.x + link.rectSRC.w < piso->w*7)
                                                    link.rectSRC.y = ((tela->h - piso->h)-link.surface->h)+4;
                                                if(link.rectSRC.x + link.rectSRC.w >= piso->w*7 && link.rectSRC.x + link.rectSRC.w < piso->w*8)
                                                    link.rectSRC.y = (pisoRect1[0][7].y + 4) - link.rectSRC.h;
                                                if(link.rectSRC.x + link.rectSRC.w >= piso->w*8 && link.rectSRC.x + link.rectSRC.w < piso->w*9)
                                                    link.rectSRC.y = (pisoRect1[0][8].y + 4) - link.rectSRC.h;
                                                if(link.rectSRC.x + link.rectSRC.w >= piso->w*9 && link.rectSRC.x + link.rectSRC.w < piso->w*10)
                                                    link.rectSRC.y = (pisoRect1[0][9].y + 4) - link.rectSRC.h;
                                                if(link.rectSRC.x + link.rectSRC.w >= piso->w*10 && link.rectSRC.x + link.rectSRC.w < piso->w*11)
                                                    link.rectSRC.y = (pisoRect1[0][10].y + 4) - link.rectSRC.h;
                                                if(link.rectSRC.x + link.rectSRC.w >= piso->w*11 && link.rectSRC.x + link.rectSRC.w < piso->w*12)
                                                    link.rectSRC.y = (pisoRect1[0][11].y + 4) - link.rectSRC.h;
                                                if(link.rectSRC.x + link.rectSRC.w >= piso->w*12 && link.rectSRC.x + link.rectSRC.w < piso->w*13)
                                                    link.rectSRC.y = (pisoRect1[0][12].y + 4) - link.rectSRC.h;
                                                if(link.rectSRC.x + link.rectSRC.w >= piso->w*13 && link.rectSRC.x + link.rectSRC.w < piso->w*14)
                                                    link.rectSRC.y = (pisoRect1[0][13].y + 4) - link.rectSRC.h;
                                                if(link.rectSRC.x + link.rectSRC.w >= piso->w*14 && link.rectSRC.x + link.rectSRC.w < piso->w*15)
                                                    link.rectSRC.y = (pisoRect1[0][14].y + 4) - link.rectSRC.h;

                                            }

                                            if(pisoAtual == 2 && !a[4]){

                                                if(link.rectSRC.x >= 0 && link.rectSRC.x < piso->w)
                                                    link.rectSRC.y = (pisoRect2[0][0].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w && link.rectSRC.x < piso->w*2)
                                                    link.rectSRC.y = (pisoRect2[0][1].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*2 && link.rectSRC.x < piso->w*3)
                                                    link.rectSRC.y = (pisoRect2[0][2].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*3 && link.rectSRC.x < piso->w*4)
                                                    link.rectSRC.y = (pisoRect2[0][3].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*4 && link.rectSRC.x < piso->w*5)
                                                    link.rectSRC.y = (pisoRect2[0][4].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*5 && link.rectSRC.x < piso->w*6)
                                                    link.rectSRC.y = (pisoRect2[0][5].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*6 && link.rectSRC.x < piso->w*7)
                                                    link.rectSRC.y = (pisoRect2[0][6].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*7 && link.rectSRC.x < piso->w*8)
                                                    link.rectSRC.y = (pisoRect2[0][7].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*8 && link.rectSRC.x < piso->w*9)
                                                    link.rectSRC.y = (pisoRect2[0][8].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*9 && link.rectSRC.x < piso->w*10)
                                                    link.rectSRC.y = (pisoRect2[0][9].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*10 && link.rectSRC.x < piso->w*11)
                                                    link.rectSRC.y = (pisoRect2[0][10].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*11 && link.rectSRC.x < piso->w*12)
                                                    link.rectSRC.y = (pisoRect2[0][11].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*12 && link.rectSRC.x < piso->w*13)
                                                    link.rectSRC.y = (pisoRect2[0][12].y - link.surface->h) + 2;

                                            }

                                            if(pisoAtual == 3 && !a[4]){

                                                if(link.rectSRC.x >= piso->w && link.rectSRC.x < piso->w*2)
                                                    link.rectSRC.y = (pisoRect1[1][0].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*2 && link.rectSRC.x < piso->w*3)
                                                    link.rectSRC.y = (pisoRect1[1][1].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*3 && link.rectSRC.x < piso->w*4)
                                                    link.rectSRC.y = (pisoRect1[1][3].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*4 && link.rectSRC.x < piso->w*5)
                                                    link.rectSRC.y = (pisoRect1[1][4].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*5 && link.rectSRC.x < piso->w*6)
                                                    link.rectSRC.y = (pisoRect1[1][5].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*6 && link.rectSRC.x < piso->w*7)
                                                    link.rectSRC.y = (pisoRect1[1][6].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*7 && link.rectSRC.x < piso->w*8)
                                                    link.rectSRC.y = (pisoRect1[1][7].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*8 && link.rectSRC.x < piso->w*9)
                                                    link.rectSRC.y = (pisoRect1[1][8].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*9 && link.rectSRC.x < piso->w*10)
                                                    link.rectSRC.y = (pisoRect1[1][9].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*10 && link.rectSRC.x < piso->w*11)
                                                    link.rectSRC.y = (pisoRect1[1][10].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*11 && link.rectSRC.x < piso->w*12)
                                                    link.rectSRC.y = (pisoRect1[1][11].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*12 && link.rectSRC.x < piso->w*13)
                                                    link.rectSRC.y = (pisoRect1[1][12].y - link.surface->h) + 2;

                                            }

                                            if(pisoAtual == 4 && !a[4]){

                                                if(link.rectSRC.x >= 0 && link.rectSRC.x < piso->w)
                                                    link.rectSRC.y = (pisoRect2[1][0].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w && link.rectSRC.x < piso->w*2)
                                                    link.rectSRC.y = (pisoRect2[1][1].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*2 && link.rectSRC.x < piso->w*3)
                                                    link.rectSRC.y = (pisoRect2[1][2].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*3 && link.rectSRC.x < piso->w*4)
                                                    link.rectSRC.y = (pisoRect2[1][3].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*4 && link.rectSRC.x < piso->w*5)
                                                    link.rectSRC.y = (pisoRect2[1][4].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*5 && link.rectSRC.x < piso->w*6)
                                                    link.rectSRC.y = (pisoRect2[1][5].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*6 && link.rectSRC.x < piso->w*7)
                                                    link.rectSRC.y = (pisoRect2[1][6].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*7 && link.rectSRC.x < piso->w*8)
                                                    link.rectSRC.y = (pisoRect2[1][7].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*8 && link.rectSRC.x < piso->w*9)
                                                    link.rectSRC.y = (pisoRect2[1][8].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*9 && link.rectSRC.x < piso->w*10)
                                                    link.rectSRC.y = (pisoRect2[1][9].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*10 && link.rectSRC.x < piso->w*11)
                                                    link.rectSRC.y = (pisoRect2[1][10].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*11 && link.rectSRC.x < piso->w*12)
                                                    link.rectSRC.y = (pisoRect2[1][11].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*12 && link.rectSRC.x < piso->w*13)
                                                    link.rectSRC.y = (pisoRect2[1][12].y - link.surface->h) + 2;

                                            }

                                            if(pisoAtual == 5 && !a[4]){

                                                if(link.rectSRC.x >= piso->w && link.rectSRC.x < piso->w*2)
                                                    link.rectSRC.y = (pisoRect1[2][0].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*2 && link.rectSRC.x < piso->w*3)
                                                    link.rectSRC.y = (pisoRect1[2][1].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*3 && link.rectSRC.x < piso->w*4)
                                                    link.rectSRC.y = (pisoRect1[2][3].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*4 && link.rectSRC.x < piso->w*5)
                                                    link.rectSRC.y = (pisoRect1[2][4].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*5 && link.rectSRC.x < piso->w*6)
                                                    link.rectSRC.y = (pisoRect1[2][5].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*6 && link.rectSRC.x < piso->w*7)
                                                    link.rectSRC.y = (pisoRect1[2][6].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*7 && link.rectSRC.x < piso->w*8)
                                                    link.rectSRC.y = (pisoRect1[2][7].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*8 && link.rectSRC.x < piso->w*9)
                                                    link.rectSRC.y = (pisoRect1[2][8].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*9 && link.rectSRC.x < piso->w*10)
                                                    link.rectSRC.y = (pisoRect1[2][9].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*10 && link.rectSRC.x < piso->w*11)
                                                    link.rectSRC.y = (pisoRect1[2][10].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*11 && link.rectSRC.x < piso->w*12)
                                                    link.rectSRC.y = (pisoRect1[2][11].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*12 && link.rectSRC.x < piso->w*13)
                                                    link.rectSRC.y = (pisoRect1[2][12].y - link.surface->h) + 2;

                                            }

                                            if(pisoAtual == 6 && !a[4]){

                                                if(link.rectSRC.x < piso->w*10)
                                                    link.rectSRC.y = (pisoRect2[2][0].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*10 && link.rectSRC.x < piso->w*11)
                                                    link.rectSRC.y = (pisoRect2[2][10].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*11 && link.rectSRC.x < piso->w*12)
                                                    link.rectSRC.y = (pisoRect2[2][11].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*12 && link.rectSRC.x < piso->w*13)
                                                    link.rectSRC.y = (pisoRect2[2][12].y - link.surface->h) + 2;

                                            }

                                            if(pisoAtual == 1 && link.rectSRC.x + link.rectSRC.w <= pisoRect1[0][14].x + piso->w)
                                                link.rectSRC.x+=3;

                                            if(pisoAtual == 2 && link.rectSRC.x + link.rectSRC.w <= pisoRect1[0][14].x)
                                                link.rectSRC.x+=3;

                                            if(pisoAtual == 3 && link.rectSRC.x + link.rectSRC.w <= pisoRect1[0][14].x + piso->w)
                                                link.rectSRC.x+=3;

                                            if(pisoAtual == 4 && link.rectSRC.x + link.rectSRC.w <= pisoRect1[0][14].x)
                                                link.rectSRC.x+=3;

                                            if(pisoAtual == 5 && link.rectSRC.x + link.rectSRC.w <= pisoRect1[0][14].x + piso->w)
                                                link.rectSRC.x+=3;

                                            if(pisoAtual == 6 && link.rectSRC.x + link.rectSRC.w <= pisoRect1[0][14].x)
                                                link.rectSRC.x+=3;

                                            key++;
                                            if (key>5)
                                                key = 0;

                                            link.surface = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/LinkParado.bmp");
                                            transparencia(link.surface);


                                        }

                                        //case LEFT pressionado decrementa 3 a X
                                        if(a[2] && !naEscada){
                                            orientacao = 1;
                                            //Colisão
                                            if(pisoAtual == 1 && !a[4]){
                                                if(link.rectSRC.x + link.rectSRC.w < piso->w*7)
                                                    link.rectSRC.y = ((tela->h - piso->h)-link.surface->h)+4;
                                                if(link.rectSRC.x + link.rectSRC.w >= piso->w*7 && link.rectSRC.x + link.rectSRC.w < piso->w*8)
                                                    link.rectSRC.y = (pisoRect1[0][7].y + 4) - link.rectSRC.h;
                                                if(link.rectSRC.x + link.rectSRC.w >= piso->w*8 && link.rectSRC.x + link.rectSRC.w < piso->w*9)
                                                    link.rectSRC.y = (pisoRect1[0][8].y + 4) - link.rectSRC.h;
                                                if(link.rectSRC.x + link.rectSRC.w >= piso->w*9 && link.rectSRC.x + link.rectSRC.w < piso->w*10)
                                                    link.rectSRC.y = (pisoRect1[0][9].y + 4) - link.rectSRC.h;
                                                if(link.rectSRC.x + link.rectSRC.w >= piso->w*10 && link.rectSRC.x + link.rectSRC.w < piso->w*11)
                                                    link.rectSRC.y = (pisoRect1[0][10].y + 4) - link.rectSRC.h;
                                                if(link.rectSRC.x + link.rectSRC.w >= piso->w*11 && link.rectSRC.x + link.rectSRC.w < piso->w*12)
                                                    link.rectSRC.y = (pisoRect1[0][11].y + 4) - link.rectSRC.h;
                                                if(link.rectSRC.x + link.rectSRC.w >= piso->w*12 && link.rectSRC.x + link.rectSRC.w < piso->w*13)
                                                    link.rectSRC.y = (pisoRect1[0][12].y + 4) - link.rectSRC.h;
                                                if(link.rectSRC.x + link.rectSRC.w >= piso->w*13 && link.rectSRC.x + link.rectSRC.w < piso->w*14)
                                                    link.rectSRC.y = (pisoRect1[0][13].y + 4) - link.rectSRC.h;
                                                if(link.rectSRC.x + link.rectSRC.w >= piso->w*14 && link.rectSRC.x + link.rectSRC.w < piso->w*15)
                                                    link.rectSRC.y = (pisoRect1[0][14].y + 4) - link.rectSRC.h;
                                            }


                                            if(pisoAtual == 2 && !a[4]){

                                                if(link.rectSRC.x >= 0 && link.rectSRC.x < piso->w)
                                                    link.rectSRC.y = (pisoRect2[0][0].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w && link.rectSRC.x < piso->w*2)
                                                    link.rectSRC.y = (pisoRect2[0][1].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*2 && link.rectSRC.x < piso->w*3)
                                                    link.rectSRC.y = (pisoRect2[0][2].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*3 && link.rectSRC.x < piso->w*4)
                                                    link.rectSRC.y = (pisoRect2[0][3].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*4 && link.rectSRC.x < piso->w*5)
                                                    link.rectSRC.y = (pisoRect2[0][4].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*5 && link.rectSRC.x < piso->w*6)
                                                    link.rectSRC.y = (pisoRect2[0][5].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*6 && link.rectSRC.x < piso->w*7)
                                                    link.rectSRC.y = (pisoRect2[0][6].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*7 && link.rectSRC.x < piso->w*8)
                                                    link.rectSRC.y = (pisoRect2[0][7].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*8 && link.rectSRC.x < piso->w*9)
                                                    link.rectSRC.y = (pisoRect2[0][8].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*9 && link.rectSRC.x < piso->w*10)
                                                    link.rectSRC.y = (pisoRect2[0][9].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*10 && link.rectSRC.x < piso->w*11)
                                                    link.rectSRC.y = (pisoRect2[0][10].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*11 && link.rectSRC.x < piso->w*12)
                                                    link.rectSRC.y = (pisoRect2[0][11].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*12 && link.rectSRC.x < piso->w*13)
                                                    link.rectSRC.y = (pisoRect2[0][12].y - link.surface->h) + 2;

                                            }

                                            if(pisoAtual == 3 && !a[4]){

                                                if(link.rectSRC.x >= piso->w && link.rectSRC.x < piso->w*2)
                                                    link.rectSRC.y = (pisoRect1[1][0].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*2 && link.rectSRC.x < piso->w*3)
                                                    link.rectSRC.y = (pisoRect1[1][1].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*3 && link.rectSRC.x < piso->w*4)
                                                    link.rectSRC.y = (pisoRect1[1][3].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*4 && link.rectSRC.x < piso->w*5)
                                                    link.rectSRC.y = (pisoRect1[1][4].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*5 && link.rectSRC.x < piso->w*6)
                                                    link.rectSRC.y = (pisoRect1[1][5].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*6 && link.rectSRC.x < piso->w*7)
                                                    link.rectSRC.y = (pisoRect1[1][6].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*7 && link.rectSRC.x < piso->w*8)
                                                    link.rectSRC.y = (pisoRect1[1][7].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*8 && link.rectSRC.x < piso->w*9)
                                                    link.rectSRC.y = (pisoRect1[1][8].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*9 && link.rectSRC.x < piso->w*10)
                                                    link.rectSRC.y = (pisoRect1[1][9].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*10 && link.rectSRC.x < piso->w*11)
                                                    link.rectSRC.y = (pisoRect1[1][10].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*11 && link.rectSRC.x < piso->w*12)
                                                    link.rectSRC.y = (pisoRect1[1][11].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*12 && link.rectSRC.x < piso->w*13)
                                                    link.rectSRC.y = (pisoRect1[1][12].y - link.surface->h) + 2;

                                            }

                                            if(pisoAtual == 4 && !a[4]){

                                                if(link.rectSRC.x >= 0 && link.rectSRC.x < piso->w)
                                                    link.rectSRC.y = (pisoRect2[1][0].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w && link.rectSRC.x < piso->w*2)
                                                    link.rectSRC.y = (pisoRect2[1][1].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*2 && link.rectSRC.x < piso->w*3)
                                                    link.rectSRC.y = (pisoRect2[1][2].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*3 && link.rectSRC.x < piso->w*4)
                                                    link.rectSRC.y = (pisoRect2[1][3].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*4 && link.rectSRC.x < piso->w*5)
                                                    link.rectSRC.y = (pisoRect2[1][4].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*5 && link.rectSRC.x < piso->w*6)
                                                    link.rectSRC.y = (pisoRect2[1][5].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*6 && link.rectSRC.x < piso->w*7)
                                                    link.rectSRC.y = (pisoRect2[1][6].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*7 && link.rectSRC.x < piso->w*8)
                                                    link.rectSRC.y = (pisoRect2[1][7].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*8 && link.rectSRC.x < piso->w*9)
                                                    link.rectSRC.y = (pisoRect2[1][8].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*9 && link.rectSRC.x < piso->w*10)
                                                    link.rectSRC.y = (pisoRect2[1][9].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*10 && link.rectSRC.x < piso->w*11)
                                                    link.rectSRC.y = (pisoRect2[1][10].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*11 && link.rectSRC.x < piso->w*12)
                                                    link.rectSRC.y = (pisoRect2[1][11].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*12 && link.rectSRC.x < piso->w*13)
                                                    link.rectSRC.y = (pisoRect2[1][12].y - link.surface->h) + 2;

                                            }

                                            if(pisoAtual == 5 && !a[4]){

                                                if(link.rectSRC.x >= piso->w && link.rectSRC.x < piso->w*2)
                                                    link.rectSRC.y = (pisoRect1[2][0].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*2 && link.rectSRC.x < piso->w*3)
                                                    link.rectSRC.y = (pisoRect1[2][1].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*3 && link.rectSRC.x < piso->w*4)
                                                    link.rectSRC.y = (pisoRect1[2][3].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*4 && link.rectSRC.x < piso->w*5)
                                                    link.rectSRC.y = (pisoRect1[2][4].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*5 && link.rectSRC.x < piso->w*6)
                                                    link.rectSRC.y = (pisoRect1[2][5].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*6 && link.rectSRC.x < piso->w*7)
                                                    link.rectSRC.y = (pisoRect1[2][6].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*7 && link.rectSRC.x < piso->w*8)
                                                    link.rectSRC.y = (pisoRect1[2][7].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*8 && link.rectSRC.x < piso->w*9)
                                                    link.rectSRC.y = (pisoRect1[2][8].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*9 && link.rectSRC.x < piso->w*10)
                                                    link.rectSRC.y = (pisoRect1[2][9].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*10 && link.rectSRC.x < piso->w*11)
                                                    link.rectSRC.y = (pisoRect1[2][10].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*11 && link.rectSRC.x < piso->w*12)
                                                    link.rectSRC.y = (pisoRect1[2][11].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*12 && link.rectSRC.x < piso->w*13)
                                                    link.rectSRC.y = (pisoRect1[2][12].y - link.surface->h) + 2;

                                            }

                                            if(pisoAtual == 6 && !a[4]){

                                                if(link.rectSRC.x < piso->w*10)
                                                    link.rectSRC.y = (pisoRect2[2][0].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*10 && link.rectSRC.x < piso->w*11)
                                                    link.rectSRC.y = (pisoRect2[2][10].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*11 && link.rectSRC.x < piso->w*12)
                                                    link.rectSRC.y = (pisoRect2[2][11].y - link.surface->h) + 2;
                                                if(link.rectSRC.x >= piso->w*12 && link.rectSRC.x < piso->w*13)
                                                    link.rectSRC.y = (pisoRect2[2][12].y - link.surface->h) + 2;

                                            }

                                            if(pisoAtual == 1 && link.rectSRC.x + link.rectSRC.w >= pisoRect1[0][0].x)
                                                link.rectSRC.x-=3;

                                            if(pisoAtual == 2 && link.rectSRC.x + link.rectSRC.w >= pisoRect1[0][0].x)
                                                link.rectSRC.x-=3;

                                            if(pisoAtual == 3 && link.rectSRC.x >= pisoRect1[0][0].x + piso->w)
                                                link.rectSRC.x-=3;

                                            if(pisoAtual == 4 && link.rectSRC.x + link.rectSRC.w >= pisoRect1[0][0].x)
                                                link.rectSRC.x-=3;

                                            if(pisoAtual == 5 && link.rectSRC.x >= pisoRect1[0][0].x + piso->w)
                                                link.rectSRC.x-=3;

                                            if(pisoAtual == 6 && link.rectSRC.x + link.rectSRC.w >= pisoRect1[0][0].x)
                                                link.rectSRC.x-=3;



                                            key--;
                                            if (key<6)
                                            key = 11;
                                            link.surface = SDL_LoadBMP("/home/victor/Área de Trabalho/Jogo/Jogo/Imagens/LinkParado2.bmp");
                                            transparencia(link.surface);


                                        }
                                        //Score

                                        if(!calculoScore(link.rectSRC,spriteMagiaRect[0],pisoAtual,pisoMagia[0],
                                                         link.surface->w,spriteMagiaRect[0].w,orientacao)
                                        && !calculoScore(link.rectSRC,spriteMagiaRect[1],pisoAtual,pisoMagia[1],
                                                         link.surface->w,spriteMagiaRect[1].w,orientacao)
                                        && !calculoScore(link.rectSRC,spriteMagiaRect[2],pisoAtual,pisoMagia[2],
                                                         link.surface->w,spriteMagiaRect[2].w,orientacao)
                                        && !calculoScore(link.rectSRC,spriteMagiaRect[3],pisoAtual,pisoMagia[3],
                                                         link.surface->w,spriteMagiaRect[3].w,orientacao)
                                        && !calculoScore(link.rectSRC,spriteMagiaRect[4],pisoAtual,pisoMagia[4],
                                                         link.surface->w,spriteMagiaRect[4].w,orientacao)
                                        && !calculoScore(link.rectSRC,spriteMagiaRect[5],pisoAtual,pisoMagia[5],
                                                         link.surface->w,spriteMagiaRect[5].w,orientacao)
                                        && !calculoScore(link.rectSRC,spriteMagiaRect[6],pisoAtual,pisoMagia[6],
                                                         link.surface->w,spriteMagiaRect[6].w,orientacao)
                                        && !calculoScore(link.rectSRC,spriteMagiaRect[7],pisoAtual,pisoMagia[7],
                                                         link.surface->w,spriteMagiaRect[7].w,orientacao))
                                            preScore = 0;

                                        //Magia 0
                                        preScore += calculoScore(link.rectSRC,spriteMagiaRect[0],pisoAtual,pisoMagia[0],
                                                 link.surface->w,spriteMagiaRect[0].w,orientacao);


                                        if(preScore == 6 && !colisao(link.rectSRC,spriteMagiaRect[0])){

                                            score += 100;
                                            preScore = 0;

                                        }


                                        if(preScore > 6 && colisao(link.rectSRC,spriteMagiaRect[0])){

                                            score -= 100;

                                        }

                                        //Magia 1
                                        preScore += calculoScore(link.rectSRC,spriteMagiaRect[1],pisoAtual,pisoMagia[1],
                                                 link.surface->w,spriteMagiaRect[1].w,orientacao);

                                        if(preScore == 6 && !colisao(link.rectSRC,spriteMagiaRect[1])){

                                            score += 100;
                                            preScore = 0;

                                        }
                                        if(preScore > 6 && colisao(link.rectSRC,spriteMagiaRect[1])){

                                            score -= 100;

                                        }

                                        //Magia 2
                                        preScore += calculoScore(link.rectSRC,spriteMagiaRect[2],pisoAtual,pisoMagia[2],
                                                 link.surface->w,spriteMagiaRect[2].w,orientacao);

                                        if(preScore == 6 && !colisao(link.rectSRC,spriteMagiaRect[2])){

                                            score += 100;
                                            preScore = 0;

                                        }
                                        if(preScore > 6 && colisao(link.rectSRC,spriteMagiaRect[2])){

                                            score -= 100;

                                        }

                                        //Magia 3
                                        preScore += calculoScore(link.rectSRC,spriteMagiaRect[3],pisoAtual,pisoMagia[3],
                                                 link.surface->w,spriteMagiaRect[3].w,orientacao);

                                        if(preScore == 6 && !colisao(link.rectSRC,spriteMagiaRect[3])){

                                            score += 100;
                                            preScore = 0;

                                        }
                                        if(preScore > 6 && colisao(link.rectSRC,spriteMagiaRect[3])){

                                            score -= 100;

                                        }

                                        //Magia 4
                                        preScore += calculoScore(link.rectSRC,spriteMagiaRect[4],pisoAtual,pisoMagia[4],
                                                 link.surface->w,spriteMagiaRect[4].w,orientacao);

                                        if(preScore == 6 && !colisao(link.rectSRC,spriteMagiaRect[4])){

                                            score += 100;
                                            preScore = 0;

                                        }
                                        if(preScore > 6 && colisao(link.rectSRC,spriteMagiaRect[4])){

                                            score -= 100;

                                        }

                                        //Magia 5
                                        preScore += calculoScore(link.rectSRC,spriteMagiaRect[5],pisoAtual,pisoMagia[5],
                                                 link.surface->w,spriteMagiaRect[5].w,orientacao);

                                        if(preScore == 6 && !colisao(link.rectSRC,spriteMagiaRect[5])){

                                            score += 100;
                                            preScore = 0;

                                        }
                                        if(preScore > 6 && colisao(link.rectSRC,spriteMagiaRect[5])){

                                            score -= 100;

                                        }

                                        //Magia 6
                                        preScore += calculoScore(link.rectSRC,spriteMagiaRect[6],pisoAtual,pisoMagia[6],
                                                 link.surface->w,spriteMagiaRect[6].w,orientacao);

                                        if(preScore == 6 && !colisao(link.rectSRC,spriteMagiaRect[6])){

                                            score += 100;
                                            preScore = 0;

                                        }
                                        if(preScore > 6 && colisao(link.rectSRC,spriteMagiaRect[6])){

                                            score -= 100;

                                        }

                                        //Magia 7
                                        preScore += calculoScore(link.rectSRC,spriteMagiaRect[7],pisoAtual,pisoMagia[7],
                                                 link.surface->w,spriteMagiaRect[7].w,orientacao);

                                        if(preScore == 6 && !colisao(link.rectSRC,spriteMagiaRect[7])){

                                            score += 100;
                                            preScore = 0;

                                        }
                                        if(preScore > 6 && colisao(link.rectSRC,spriteMagiaRect[7])){

                                            score -= 100;

                                        }

                                        //Desenha Zelda
                                        if(!ganhou)
                                            SDL_BlitSurface(zeldaCaida,NULL,tela,&zeldaCaidaRect);


                                        else{

                                            SDL_BlitSurface(zelda,NULL,tela,&zeldaRect);
                                            SDL_BlitSurface(coracao,NULL,tela,&coracaoRect); //Desenha Coracao

                                        }



                                        //Desenha espada

                                        if(pegouEspada == 0){

                                            SDL_BlitSurface(espada,NULL,tela,&espadaRect);

                                        }

                                        //Desenha info
                                        //Mostrar Vidas
                                        if(vidas == 3){

                                            SDL_BlitSurface(vidas1,NULL,tela,&vidasRect);

                                        }
                                        else if(vidas == 2){

                                            SDL_BlitSurface(vidas2,NULL,tela,&vidasRect);

                                        }
                                        else if(vidas == 1){

                                            SDL_BlitSurface(vidas3,NULL,tela,&vidasRect);

                                        }
                                        //Mostrar Score
                                        sprintf(showScore,"%d",score);

                                        message9 = TTF_RenderText_Solid(font3, "Score:", corTexto);
                                        message10 = TTF_RenderText_Solid(font3, showScore, corTexto);

                                        SDL_BlitSurface(message9,NULL,tela,&palavraScoreRect);
                                        SDL_BlitSurface(message10,NULL,tela,&scoreShowRect);

                                        //Desenha Magia
                                        if(magiaAtiva[0] && !ganhou)
                                            SDL_BlitSurface(magiaGanon,&magiaRect[keyMagia],tela,&spriteMagiaRect[0]);
                                        if(magiaAtiva[1] && !ganhou)
                                            SDL_BlitSurface(magiaGanon,&magiaRect[keyMagia],tela,&spriteMagiaRect[1]);
                                        if(magiaAtiva[2] && !ganhou)
                                            SDL_BlitSurface(magiaGanon,&magiaRect[keyMagia],tela,&spriteMagiaRect[2]);
                                        if(magiaAtiva[3] && !ganhou)
                                            SDL_BlitSurface(magiaGanon,&magiaRect[keyMagia],tela,&spriteMagiaRect[3]);
                                        if(magiaAtiva[4] && !ganhou)
                                            SDL_BlitSurface(magiaGanon,&magiaRect[keyMagia],tela,&spriteMagiaRect[4]);
                                        if(magiaAtiva[5] && !ganhou)
                                            SDL_BlitSurface(magiaGanon,&magiaRect[keyMagia],tela,&spriteMagiaRect[5]);
                                        if(magiaAtiva[6] && !ganhou)
                                            SDL_BlitSurface(magiaGanon,&magiaRect[keyMagia],tela,&spriteMagiaRect[6]);
                                        if(magiaAtiva[7] && !ganhou)
                                            SDL_BlitSurface(magiaGanon,&magiaRect[keyMagia],tela,&spriteMagiaRect[7]);

                                        //Desenha Link
                                        if(!pegouEspada){

                                            if(!a[1] && !a[2]){
                                                SDL_BlitSurface(link.surface,NULL,tela,&link.rectSRC);

                                            }
                                            else
                                                SDL_BlitSurface(link.spriteSurface,&link.rectSprite[key],tela,&link.rectSRC);

                                        }
                                        else{

                                            giroEspadaRect.x = link.rectSRC.x;
                                            giroEspadaRect.y = link.rectSRC.y + 10;

                                            tempoAnimaGiro++;

                                            if(tempoAnimaGiro > 5){

                                                keyGiroEspada++;
                                                tempoAnimaGiro = 0;

                                            }

                                            if(keyGiroEspada > 7){

                                                keyGiroEspada = 0;

                                            }

                                            if(!ganhou)
                                                SDL_BlitSurface(spriteGiroEspada,&spriteGiroEspadaRect[keyGiroEspada],tela,&giroEspadaRect);
                                            else{

                                                SDL_BlitSurface(link.surface,NULL,tela,&linkFinalRect);

                                            }


                                        }

                                        if(colisao(link.rectSRC,espadaRect)){

                                            pegouEspada = 1;

                                        }

                                        //Ganondorf

                                        if((spriteMagiaRect[0].x == pisoRect2[2][4].x + 49 && spriteMagiaRect[0].y == pisoRect2[2][4].y - magiaGanon->h)
                                        || (spriteMagiaRect[1].x == pisoRect2[2][4].x + 49 && spriteMagiaRect[1].y == pisoRect2[2][4].y - magiaGanon->h)
                                        || (spriteMagiaRect[2].x == pisoRect2[2][4].x + 49 && spriteMagiaRect[2].y == pisoRect2[2][4].y - magiaGanon->h)
                                        || (spriteMagiaRect[3].x == pisoRect2[2][4].x + 49 && spriteMagiaRect[3].y == pisoRect2[2][4].y - magiaGanon->h)
                                        || (spriteMagiaRect[4].x == pisoRect2[2][4].x + 49 && spriteMagiaRect[4].y == pisoRect2[2][4].y - magiaGanon->h)
                                        || (spriteMagiaRect[5].x == pisoRect2[2][4].x + 49 && spriteMagiaRect[5].y == pisoRect2[2][4].y - magiaGanon->h)
                                        || (spriteMagiaRect[6].x == pisoRect2[2][4].x + 49 && spriteMagiaRect[6].y == pisoRect2[2][4].y - magiaGanon->h)
                                        || (spriteMagiaRect[7].x == pisoRect2[2][4].x + 49 && spriteMagiaRect[7].y == pisoRect2[2][4].y - magiaGanon->h))
                                            ataqueGanon = 1;
                                        else
                                            ataqueGanon = 0;

                                        if(!ganhou){

                                            if(ataqueGanon){

                                                SDL_BlitSurface(ganondorf.spriteSurface,&ganondorf.rectSprite[keyGanon],tela,&ganondorf.rectSRC);

                                                keyGanon++;
                                                if(keyGanon > 3)
                                                    keyGanon = 0;


                                            }
                                            else

                                                SDL_BlitSurface(ganondorf.surface,NULL,tela,&ganondorf.rectSRC);
                                        }

                                        //Chave de Animação da Magia.
                                        contMagia++;
                                        if(contMagia > 5){
                                            keyMagia++;
                                        }
                                        if(keyMagia > 1){
                                            keyMagia = 0;
                                            contMagia = 0;
                                        }
                                        //SDL_BlitSurface(ganondorf.surface,NULL,tela,&ganondorf.rectSRC);
                                        //Magia 0
                                        if(tempoMagia > 50){
                                            if(pisoMagia[0] == 6){

                                                if(spriteMagiaRect[0].x <= pisoRect2[2][13].x + piso->w)
                                                    spriteMagiaRect[0].x += magiaVel;
                                                //Ajustando piso 6
                                                if(spriteMagiaRect[0].x >= piso->w*10 && spriteMagiaRect[0].x < piso->w*11)
                                                    spriteMagiaRect[0].y = (pisoRect2[2][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*11 && spriteMagiaRect[0].x < piso->w*12)
                                                    spriteMagiaRect[0].y = (pisoRect2[2][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*12 && spriteMagiaRect[0].x < piso->w*13)
                                                    spriteMagiaRect[0].y = (pisoRect2[2][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[0].x == 589 && spriteMagiaRect[0].y <= pisoRect1[2][13].y - magiaGanon->h)
                                                    spriteMagiaRect[0].y += magiaVel;

                                                if(spriteMagiaRect[0].y == 145)
                                                    pisoMagia[0] = 5;


                                            }

                                            if(pisoMagia[0] == 5){

                                                if(spriteMagiaRect[0].x >= pisoRect1[2][0].x - (magiaGanon->w / 2))
                                                    spriteMagiaRect[0].x -= magiaVel;
                                                //Ajustando piso 5
                                                if(spriteMagiaRect[0].x >= piso->w && spriteMagiaRect[0].x < piso->w*2)
                                                    spriteMagiaRect[0].y = (pisoRect1[2][0].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*2 && spriteMagiaRect[0].x < piso->w*3)
                                                    spriteMagiaRect[0].y = (pisoRect1[2][1].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*3 && spriteMagiaRect[0].x < piso->w*4)
                                                    spriteMagiaRect[0].y = (pisoRect1[2][3].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*4 && spriteMagiaRect[0].x < piso->w*5)
                                                    spriteMagiaRect[0].y = (pisoRect1[2][4].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*5 && spriteMagiaRect[0].x < piso->w*6)
                                                    spriteMagiaRect[0].y = (pisoRect1[2][5].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*6 && spriteMagiaRect[0].x < piso->w*7)
                                                    spriteMagiaRect[0].y = (pisoRect1[2][6].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*7 && spriteMagiaRect[0].x < piso->w*8)
                                                    spriteMagiaRect[0].y = (pisoRect1[2][7].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*8 && spriteMagiaRect[0].x < piso->w*9)
                                                    spriteMagiaRect[0].y = (pisoRect1[2][8].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*9 && spriteMagiaRect[0].x < piso->w*10)
                                                    spriteMagiaRect[0].y = (pisoRect1[2][9].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*10 && spriteMagiaRect[0].x < piso->w*11)
                                                    spriteMagiaRect[0].y = (pisoRect1[2][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*11 && spriteMagiaRect[0].x < piso->w*12)
                                                    spriteMagiaRect[0].y = (pisoRect1[2][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*12 && spriteMagiaRect[0].x < piso->w*13)
                                                    spriteMagiaRect[0].y = (pisoRect1[2][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[0].x == 21 && spriteMagiaRect[0].y <= pisoRect2[1][0].y - magiaGanon->h)
                                                    spriteMagiaRect[0].y += magiaVel;

                                                if(spriteMagiaRect[0].y == 223)
                                                    pisoMagia[0] = 4;

                                            }

                                            if(pisoMagia[0] == 4){

                                                if(spriteMagiaRect[0].x <= pisoRect2[1][13].x + piso->w)
                                                    spriteMagiaRect[0].x += magiaVel;
                                                //Ajustando piso 4
                                                if(spriteMagiaRect[0].x >= 0 && spriteMagiaRect[0].x < piso->w)
                                                    spriteMagiaRect[0].y = (pisoRect2[1][0].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w && spriteMagiaRect[0].x < piso->w*2)
                                                    spriteMagiaRect[0].y = (pisoRect2[1][1].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*2 && spriteMagiaRect[0].x < piso->w*3)
                                                    spriteMagiaRect[0].y = (pisoRect2[1][2].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*3 && spriteMagiaRect[0].x < piso->w*4)
                                                    spriteMagiaRect[0].y = (pisoRect2[1][3].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*4 && spriteMagiaRect[0].x < piso->w*5)
                                                    spriteMagiaRect[0].y = (pisoRect2[1][4].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*5 && spriteMagiaRect[0].x < piso->w*6)
                                                    spriteMagiaRect[0].y = (pisoRect2[1][5].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*6 && spriteMagiaRect[0].x < piso->w*7)
                                                    spriteMagiaRect[0].y = (pisoRect2[1][6].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*7 && spriteMagiaRect[0].x < piso->w*8)
                                                    spriteMagiaRect[0].y = (pisoRect2[1][7].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*8 && spriteMagiaRect[0].x < piso->w*9)
                                                    spriteMagiaRect[0].y = (pisoRect2[1][8].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*9 && spriteMagiaRect[0].x < piso->w*10)
                                                    spriteMagiaRect[0].y = (pisoRect2[1][9].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*10 && spriteMagiaRect[0].x < piso->w*11)
                                                    spriteMagiaRect[0].y = (pisoRect2[1][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*11 && spriteMagiaRect[0].x < piso->w*12)
                                                    spriteMagiaRect[0].y = (pisoRect2[1][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*12 && spriteMagiaRect[0].x < piso->w*13)
                                                    spriteMagiaRect[0].y = (pisoRect2[1][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[0].x == 589 && spriteMagiaRect[0].y <= pisoRect1[1][13].y - magiaGanon->h)
                                                    spriteMagiaRect[0].y += magiaVel;

                                                if(spriteMagiaRect[0].y == 300)
                                                    pisoMagia[0] = 3;

                                            }

                                            if(pisoMagia[0] == 3){

                                                if(spriteMagiaRect[0].x >= pisoRect1[1][0].x - (magiaGanon->w / 2))
                                                    spriteMagiaRect[0].x -= magiaVel;
                                                //Ajustando piso 3
                                                if(spriteMagiaRect[0].x >= piso->w && spriteMagiaRect[0].x < piso->w*2)
                                                    spriteMagiaRect[0].y = (pisoRect1[1][0].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*2 && spriteMagiaRect[0].x < piso->w*3)
                                                    spriteMagiaRect[0].y = (pisoRect1[1][1].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*3 && spriteMagiaRect[0].x < piso->w*4)
                                                    spriteMagiaRect[0].y = (pisoRect1[1][3].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*4 && spriteMagiaRect[0].x < piso->w*5)
                                                    spriteMagiaRect[0].y = (pisoRect1[1][4].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*5 && spriteMagiaRect[0].x < piso->w*6)
                                                    spriteMagiaRect[0].y = (pisoRect1[1][5].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*6 && spriteMagiaRect[0].x < piso->w*7)
                                                    spriteMagiaRect[0].y = (pisoRect1[1][6].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*7 && spriteMagiaRect[0].x < piso->w*8)
                                                    spriteMagiaRect[0].y = (pisoRect1[1][7].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*8 && spriteMagiaRect[0].x < piso->w*9)
                                                    spriteMagiaRect[0].y = (pisoRect1[1][8].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*9 && spriteMagiaRect[0].x < piso->w*10)
                                                    spriteMagiaRect[0].y = (pisoRect1[1][9].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*10 && spriteMagiaRect[0].x < piso->w*11)
                                                    spriteMagiaRect[0].y = (pisoRect1[1][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*11 && spriteMagiaRect[0].x < piso->w*12)
                                                    spriteMagiaRect[0].y = (pisoRect1[1][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*12 && spriteMagiaRect[0].x < piso->w*13)
                                                    spriteMagiaRect[0].y = (pisoRect1[1][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[0].x == 21 && spriteMagiaRect[0].y <= pisoRect2[0][0].y - magiaGanon->h)
                                                    spriteMagiaRect[0].y += magiaVel;

                                                if(spriteMagiaRect[0].y == 376)
                                                    pisoMagia[0] = 2;

                                            }

                                            if(pisoMagia[0] == 2){

                                                if(spriteMagiaRect[0].x <= pisoRect2[0][13].x + piso->w)
                                                    spriteMagiaRect[0].x += magiaVel;
                                                //Ajustando piso 2
                                                if(spriteMagiaRect[0].x >= 0 && spriteMagiaRect[0].x < piso->w)
                                                    spriteMagiaRect[0].y = (pisoRect2[0][0].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w && spriteMagiaRect[0].x < piso->w*2)
                                                    spriteMagiaRect[0].y = (pisoRect2[0][1].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*2 && spriteMagiaRect[0].x < piso->w*3)
                                                    spriteMagiaRect[0].y = (pisoRect2[0][2].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*3 && spriteMagiaRect[0].x < piso->w*4)
                                                    spriteMagiaRect[0].y = (pisoRect2[0][3].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*4 && spriteMagiaRect[0].x < piso->w*5)
                                                    spriteMagiaRect[0].y = (pisoRect2[0][4].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*5 && spriteMagiaRect[0].x < piso->w*6)
                                                    spriteMagiaRect[0].y = (pisoRect2[0][5].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*6 && spriteMagiaRect[0].x < piso->w*7)
                                                    spriteMagiaRect[0].y = (pisoRect2[0][6].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*7 && spriteMagiaRect[0].x < piso->w*8)
                                                    spriteMagiaRect[0].y = (pisoRect2[0][7].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*8 && spriteMagiaRect[0].x < piso->w*9)
                                                    spriteMagiaRect[0].y = (pisoRect2[0][8].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*9 && spriteMagiaRect[0].x < piso->w*10)
                                                    spriteMagiaRect[0].y = (pisoRect2[0][9].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*10 && spriteMagiaRect[0].x < piso->w*11)
                                                    spriteMagiaRect[0].y = (pisoRect2[0][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*11 && spriteMagiaRect[0].x < piso->w*12)
                                                    spriteMagiaRect[0].y = (pisoRect2[0][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[0].x >= piso->w*12 && spriteMagiaRect[0].x < piso->w*13)
                                                    spriteMagiaRect[0].y = (pisoRect2[0][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[0].x == 589 && spriteMagiaRect[0].y <= pisoRect1[0][13].y - magiaGanon->h)
                                                    spriteMagiaRect[0].y += magiaVel;
                                                if(spriteMagiaRect[0].y == 450)
                                                    pisoMagia[0] = 1;

                                            }

                                            if(pisoMagia[0] == 1){

                                                    if(spriteMagiaRect[0].x > pisoRect1[0][0].x)
                                                    spriteMagiaRect[0].x -= magiaVel;
                                                    //Ajustando piso 1
                                                    if(spriteMagiaRect[0].x + magiaGanon->w < piso->w*7)
                                                        spriteMagiaRect[0].y = ((tela->h - piso->h)-magiaGanon->h)+2;
                                                    if(spriteMagiaRect[0].x + magiaGanon->w >= piso->w*7 && spriteMagiaRect[0].x + magiaGanon->w < piso->w*8)
                                                        spriteMagiaRect[0].y = (pisoRect1[0][7].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[0].x + magiaGanon->w >= piso->w*8 && spriteMagiaRect[0].x + magiaGanon->w < piso->w*9)
                                                        spriteMagiaRect[0].y = (pisoRect1[0][8].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[0].x + magiaGanon->w >= piso->w*9 && spriteMagiaRect[0].x + magiaGanon->w < piso->w*10)
                                                        spriteMagiaRect[0].y = (pisoRect1[0][9].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[0].x + magiaGanon->w >= piso->w*10 && spriteMagiaRect[0].x + magiaGanon->w < piso->w*11)
                                                        spriteMagiaRect[0].y = (pisoRect1[0][10].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[0].x + magiaGanon->w >= piso->w*11 && spriteMagiaRect[0].x + magiaGanon->w < piso->w*12)
                                                        spriteMagiaRect[0].y = (pisoRect1[0][11].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[0].x + magiaGanon->w >= piso->w*12 && spriteMagiaRect[0].x + magiaGanon->w < piso->w*13)
                                                        spriteMagiaRect[0].y = (pisoRect1[0][12].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[0].x + magiaGanon->w >= piso->w*13 && spriteMagiaRect[0].x + magiaGanon->w < piso->w*14)
                                                        spriteMagiaRect[0].y = (pisoRect1[0][13].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[0].x + magiaGanon->w >= piso->w*14 && spriteMagiaRect[0].x + magiaGanon->w < piso->w*15)
                                                        spriteMagiaRect[0].y = (pisoRect1[0][14].y + 2) - magiaGanon->h;

                                                    //Voltando a Magia
                                                    if(spriteMagiaRect[0].x == 0){

                                                        pisoMagia[0] = 6;
                                                        spriteMagiaRect[0].x = pisoRect2[2][4].x + 45;
                                                        spriteMagiaRect[0].y = pisoRect2[2][4].y - magiaGanon->h;
                                                        magiaAtiva[0] = 1;

                                                    }

                                                }
                                            }
                                        //Magia 1
                                        if(tempoMagia > 300){
                                            if(pisoMagia[1] == 6){

                                                if(spriteMagiaRect[1].x <= pisoRect2[2][13].x + piso->w)
                                                    spriteMagiaRect[1].x += magiaVel;
                                                //Ajustando piso 6
                                                if(spriteMagiaRect[1].x >= piso->w*10 && spriteMagiaRect[1].x < piso->w*11)
                                                    spriteMagiaRect[1].y = (pisoRect2[2][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*11 && spriteMagiaRect[1].x < piso->w*12)
                                                    spriteMagiaRect[1].y = (pisoRect2[2][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*12 && spriteMagiaRect[1].x < piso->w*13)
                                                    spriteMagiaRect[1].y = (pisoRect2[2][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[1].x == 589 && spriteMagiaRect[1].y <= pisoRect1[2][13].y - magiaGanon->h)
                                                    spriteMagiaRect[1].y += magiaVel;

                                                if(spriteMagiaRect[1].y == 145)
                                                    pisoMagia[1] = 5;


                                            }

                                            if(pisoMagia[1] == 5){

                                                if(spriteMagiaRect[1].x >= pisoRect1[2][0].x - (magiaGanon->w / 2))
                                                    spriteMagiaRect[1].x -= magiaVel;
                                                //Ajustando piso 5
                                                if(spriteMagiaRect[1].x >= piso->w && spriteMagiaRect[1].x < piso->w*2)
                                                    spriteMagiaRect[1].y = (pisoRect1[2][0].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*2 && spriteMagiaRect[1].x < piso->w*3)
                                                    spriteMagiaRect[1].y = (pisoRect1[2][1].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*3 && spriteMagiaRect[1].x < piso->w*4)
                                                    spriteMagiaRect[1].y = (pisoRect1[2][3].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*4 && spriteMagiaRect[1].x < piso->w*5)
                                                    spriteMagiaRect[1].y = (pisoRect1[2][4].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*5 && spriteMagiaRect[1].x < piso->w*6)
                                                    spriteMagiaRect[1].y = (pisoRect1[2][5].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*6 && spriteMagiaRect[1].x < piso->w*7)
                                                    spriteMagiaRect[1].y = (pisoRect1[2][6].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*7 && spriteMagiaRect[1].x < piso->w*8)
                                                    spriteMagiaRect[1].y = (pisoRect1[2][7].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*8 && spriteMagiaRect[1].x < piso->w*9)
                                                    spriteMagiaRect[1].y = (pisoRect1[2][8].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*9 && spriteMagiaRect[1].x < piso->w*10)
                                                    spriteMagiaRect[1].y = (pisoRect1[2][9].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*10 && spriteMagiaRect[1].x < piso->w*11)
                                                    spriteMagiaRect[1].y = (pisoRect1[2][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*11 && spriteMagiaRect[1].x < piso->w*12)
                                                    spriteMagiaRect[1].y = (pisoRect1[2][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*12 && spriteMagiaRect[1].x < piso->w*13)
                                                    spriteMagiaRect[1].y = (pisoRect1[2][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[1].x == 21 && spriteMagiaRect[1].y <= pisoRect2[1][0].y - magiaGanon->h)
                                                    spriteMagiaRect[1].y += magiaVel;

                                                if(spriteMagiaRect[1].y == 223)
                                                    pisoMagia[1] = 4;

                                            }

                                            if(pisoMagia[1] == 4){

                                                if(spriteMagiaRect[1].x <= pisoRect2[1][13].x + piso->w)
                                                    spriteMagiaRect[1].x += magiaVel;
                                                //Ajustando piso 4
                                                if(spriteMagiaRect[1].x >= 0 && spriteMagiaRect[1].x < piso->w)
                                                    spriteMagiaRect[1].y = (pisoRect2[1][0].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w && spriteMagiaRect[1].x < piso->w*2)
                                                    spriteMagiaRect[1].y = (pisoRect2[1][1].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*2 && spriteMagiaRect[1].x < piso->w*3)
                                                    spriteMagiaRect[1].y = (pisoRect2[1][2].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*3 && spriteMagiaRect[1].x < piso->w*4)
                                                    spriteMagiaRect[1].y = (pisoRect2[1][3].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*4 && spriteMagiaRect[1].x < piso->w*5)
                                                    spriteMagiaRect[1].y = (pisoRect2[1][4].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*5 && spriteMagiaRect[1].x < piso->w*6)
                                                    spriteMagiaRect[1].y = (pisoRect2[1][5].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*6 && spriteMagiaRect[1].x < piso->w*7)
                                                    spriteMagiaRect[1].y = (pisoRect2[1][6].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*7 && spriteMagiaRect[1].x < piso->w*8)
                                                    spriteMagiaRect[1].y = (pisoRect2[1][7].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*8 && spriteMagiaRect[1].x < piso->w*9)
                                                    spriteMagiaRect[1].y = (pisoRect2[1][8].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*9 && spriteMagiaRect[1].x < piso->w*10)
                                                    spriteMagiaRect[1].y = (pisoRect2[1][9].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*10 && spriteMagiaRect[1].x < piso->w*11)
                                                    spriteMagiaRect[1].y = (pisoRect2[1][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*11 && spriteMagiaRect[1].x < piso->w*12)
                                                    spriteMagiaRect[1].y = (pisoRect2[1][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*12 && spriteMagiaRect[1].x < piso->w*13)
                                                    spriteMagiaRect[1].y = (pisoRect2[1][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[1].x == 589 && spriteMagiaRect[1].y <= pisoRect1[1][13].y - magiaGanon->h)
                                                    spriteMagiaRect[1].y += magiaVel;

                                                if(spriteMagiaRect[1].y == 300)
                                                    pisoMagia[1] = 3;

                                            }

                                            if(pisoMagia[1] == 3){

                                                if(spriteMagiaRect[1].x >= pisoRect1[1][0].x - (magiaGanon->w / 2))
                                                    spriteMagiaRect[1].x -= magiaVel;
                                                //Ajustando piso 3
                                                if(spriteMagiaRect[1].x >= piso->w && spriteMagiaRect[1].x < piso->w*2)
                                                    spriteMagiaRect[1].y = (pisoRect1[1][0].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*2 && spriteMagiaRect[1].x < piso->w*3)
                                                    spriteMagiaRect[1].y = (pisoRect1[1][1].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*3 && spriteMagiaRect[1].x < piso->w*4)
                                                    spriteMagiaRect[1].y = (pisoRect1[1][3].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*4 && spriteMagiaRect[1].x < piso->w*5)
                                                    spriteMagiaRect[1].y = (pisoRect1[1][4].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*5 && spriteMagiaRect[1].x < piso->w*6)
                                                    spriteMagiaRect[1].y = (pisoRect1[1][5].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*6 && spriteMagiaRect[1].x < piso->w*7)
                                                    spriteMagiaRect[1].y = (pisoRect1[1][6].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*7 && spriteMagiaRect[1].x < piso->w*8)
                                                    spriteMagiaRect[1].y = (pisoRect1[1][7].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*8 && spriteMagiaRect[1].x < piso->w*9)
                                                    spriteMagiaRect[1].y = (pisoRect1[1][8].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*9 && spriteMagiaRect[1].x < piso->w*10)
                                                    spriteMagiaRect[1].y = (pisoRect1[1][9].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*10 && spriteMagiaRect[1].x < piso->w*11)
                                                    spriteMagiaRect[1].y = (pisoRect1[1][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*11 && spriteMagiaRect[1].x < piso->w*12)
                                                    spriteMagiaRect[1].y = (pisoRect1[1][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*12 && spriteMagiaRect[1].x < piso->w*13)
                                                    spriteMagiaRect[1].y = (pisoRect1[1][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[1].x == 21 && spriteMagiaRect[1].y <= pisoRect2[0][0].y - magiaGanon->h)
                                                    spriteMagiaRect[1].y += magiaVel;

                                                if(spriteMagiaRect[1].y == 376)
                                                    pisoMagia[1] = 2;

                                            }

                                            if(pisoMagia[1] == 2){

                                                if(spriteMagiaRect[1].x <= pisoRect2[0][13].x + piso->w)
                                                    spriteMagiaRect[1].x += magiaVel;
                                                //Ajustando piso 2
                                                if(spriteMagiaRect[1].x >= 0 && spriteMagiaRect[1].x < piso->w)
                                                    spriteMagiaRect[1].y = (pisoRect2[0][0].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w && spriteMagiaRect[1].x < piso->w*2)
                                                    spriteMagiaRect[1].y = (pisoRect2[0][1].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*2 && spriteMagiaRect[1].x < piso->w*3)
                                                    spriteMagiaRect[1].y = (pisoRect2[0][2].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*3 && spriteMagiaRect[1].x < piso->w*4)
                                                    spriteMagiaRect[1].y = (pisoRect2[0][3].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*4 && spriteMagiaRect[1].x < piso->w*5)
                                                    spriteMagiaRect[1].y = (pisoRect2[0][4].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*5 && spriteMagiaRect[1].x < piso->w*6)
                                                    spriteMagiaRect[1].y = (pisoRect2[0][5].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*6 && spriteMagiaRect[1].x < piso->w*7)
                                                    spriteMagiaRect[1].y = (pisoRect2[0][6].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*7 && spriteMagiaRect[1].x < piso->w*8)
                                                    spriteMagiaRect[1].y = (pisoRect2[0][7].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*8 && spriteMagiaRect[1].x < piso->w*9)
                                                    spriteMagiaRect[1].y = (pisoRect2[0][8].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*9 && spriteMagiaRect[1].x < piso->w*10)
                                                    spriteMagiaRect[1].y = (pisoRect2[0][9].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*10 && spriteMagiaRect[1].x < piso->w*11)
                                                    spriteMagiaRect[1].y = (pisoRect2[0][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*11 && spriteMagiaRect[1].x < piso->w*12)
                                                    spriteMagiaRect[1].y = (pisoRect2[0][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[1].x >= piso->w*12 && spriteMagiaRect[1].x < piso->w*13)
                                                    spriteMagiaRect[1].y = (pisoRect2[0][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[1].x == 589 && spriteMagiaRect[1].y <= pisoRect1[0][13].y - magiaGanon->h)
                                                    spriteMagiaRect[1].y += magiaVel;
                                                if(spriteMagiaRect[1].y == 450)
                                                    pisoMagia[1] = 1;

                                            }

                                            if(pisoMagia[1] == 1){

                                                if(spriteMagiaRect[1].x > pisoRect1[0][0].x)
                                                    spriteMagiaRect[1].x -= magiaVel;
                                                    //Ajustando piso 1
                                                if(spriteMagiaRect[1].x + magiaGanon->w < piso->w*7)
                                                        spriteMagiaRect[1].y = ((tela->h - piso->h)-magiaGanon->h)+2;
                                                if(spriteMagiaRect[1].x + magiaGanon->w >= piso->w*7 && spriteMagiaRect[1].x + magiaGanon->w < piso->w*8)
                                                        spriteMagiaRect[1].y = (pisoRect1[0][7].y + 2) - magiaGanon->h;
                                                if(spriteMagiaRect[1].x + magiaGanon->w >= piso->w*8 && spriteMagiaRect[1].x + magiaGanon->w < piso->w*9)
                                                        spriteMagiaRect[1].y = (pisoRect1[0][8].y + 2) - magiaGanon->h;
                                                if(spriteMagiaRect[1].x + magiaGanon->w >= piso->w*9 && spriteMagiaRect[1].x + magiaGanon->w < piso->w*10)
                                                        spriteMagiaRect[1].y = (pisoRect1[0][9].y + 2) - magiaGanon->h;
                                                if(spriteMagiaRect[1].x + magiaGanon->w >= piso->w*10 && spriteMagiaRect[1].x + magiaGanon->w < piso->w*11)
                                                        spriteMagiaRect[1].y = (pisoRect1[0][10].y + 2) - magiaGanon->h;
                                                if(spriteMagiaRect[1].x + magiaGanon->w >= piso->w*11 && spriteMagiaRect[1].x + magiaGanon->w < piso->w*12)
                                                        spriteMagiaRect[1].y = (pisoRect1[0][11].y + 2) - magiaGanon->h;
                                                if(spriteMagiaRect[1].x + magiaGanon->w >= piso->w*12 && spriteMagiaRect[1].x + magiaGanon->w < piso->w*13)
                                                        spriteMagiaRect[1].y = (pisoRect1[0][12].y + 2) - magiaGanon->h;
                                                if(spriteMagiaRect[1].x + magiaGanon->w >= piso->w*13 && spriteMagiaRect[1].x + magiaGanon->w < piso->w*14)
                                                        spriteMagiaRect[1].y = (pisoRect1[0][13].y + 2) - magiaGanon->h;
                                                if(spriteMagiaRect[1].x + magiaGanon->w >= piso->w*14 && spriteMagiaRect[1].x + magiaGanon->w < piso->w*15)
                                                        spriteMagiaRect[1].y = (pisoRect1[0][14].y + 2) - magiaGanon->h;

                                                //Voltando a Magia
                                                if(spriteMagiaRect[1].x == 0){

                                                        pisoMagia[1] = 6;
                                                        spriteMagiaRect[1].x = pisoRect2[2][4].x + 45;
                                                        spriteMagiaRect[1].y = pisoRect2[2][4].y - magiaGanon->h;
                                                        magiaAtiva[1] = 1;

                                                }

                                            }
                                        }
                                        //Magia 2
                                        if(tempoMagia > 500){
                                            if(pisoMagia[2] == 6){

                                                if(spriteMagiaRect[2].x <= pisoRect2[2][13].x + piso->w)
                                                    spriteMagiaRect[2].x += magiaVel;
                                                //Ajustando piso 6
                                                if(spriteMagiaRect[2].x >= piso->w*10 && spriteMagiaRect[2].x < piso->w*11)
                                                    spriteMagiaRect[2].y = (pisoRect2[2][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*11 && spriteMagiaRect[2].x < piso->w*12)
                                                    spriteMagiaRect[2].y = (pisoRect2[2][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*12 && spriteMagiaRect[2].x < piso->w*13)
                                                    spriteMagiaRect[2].y = (pisoRect2[2][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[2].x == 589 && spriteMagiaRect[2].y <= pisoRect1[2][13].y - magiaGanon->h)
                                                    spriteMagiaRect[2].y += magiaVel;

                                                if(spriteMagiaRect[2].y == 145)
                                                    pisoMagia[2] = 5;


                                            }

                                            if(pisoMagia[2] == 5){

                                                if(spriteMagiaRect[2].x >= pisoRect1[2][0].x - (magiaGanon->w / 2))
                                                    spriteMagiaRect[2].x -= magiaVel;
                                                //Ajustando piso 5
                                                if(spriteMagiaRect[2].x >= piso->w && spriteMagiaRect[2].x < piso->w*2)
                                                    spriteMagiaRect[2].y = (pisoRect1[2][0].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*2 && spriteMagiaRect[2].x < piso->w*3)
                                                    spriteMagiaRect[2].y = (pisoRect1[2][1].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*3 && spriteMagiaRect[2].x < piso->w*4)
                                                    spriteMagiaRect[2].y = (pisoRect1[2][3].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*4 && spriteMagiaRect[2].x < piso->w*5)
                                                    spriteMagiaRect[2].y = (pisoRect1[2][4].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*5 && spriteMagiaRect[2].x < piso->w*6)
                                                    spriteMagiaRect[2].y = (pisoRect1[2][5].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*6 && spriteMagiaRect[2].x < piso->w*7)
                                                    spriteMagiaRect[2].y = (pisoRect1[2][6].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*7 && spriteMagiaRect[2].x < piso->w*8)
                                                    spriteMagiaRect[2].y = (pisoRect1[2][7].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*8 && spriteMagiaRect[2].x < piso->w*9)
                                                    spriteMagiaRect[2].y = (pisoRect1[2][8].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*9 && spriteMagiaRect[2].x < piso->w*10)
                                                    spriteMagiaRect[2].y = (pisoRect1[2][9].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*10 && spriteMagiaRect[2].x < piso->w*11)
                                                    spriteMagiaRect[2].y = (pisoRect1[2][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*11 && spriteMagiaRect[2].x < piso->w*12)
                                                    spriteMagiaRect[2].y = (pisoRect1[2][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*12 && spriteMagiaRect[2].x < piso->w*13)
                                                    spriteMagiaRect[2].y = (pisoRect1[2][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[2].x == 21 && spriteMagiaRect[2].y <= pisoRect2[1][0].y - magiaGanon->h)
                                                    spriteMagiaRect[2].y += magiaVel;

                                                if(spriteMagiaRect[2].y == 223)
                                                    pisoMagia[2] = 4;

                                            }

                                            if(pisoMagia[2] == 4){

                                                if(spriteMagiaRect[2].x <= pisoRect2[1][13].x + piso->w)
                                                    spriteMagiaRect[2].x += magiaVel;
                                                //Ajustando piso 4
                                                if(spriteMagiaRect[2].x >= 0 && spriteMagiaRect[2].x < piso->w)
                                                    spriteMagiaRect[2].y = (pisoRect2[1][0].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w && spriteMagiaRect[2].x < piso->w*2)
                                                    spriteMagiaRect[2].y = (pisoRect2[1][1].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*2 && spriteMagiaRect[2].x < piso->w*3)
                                                    spriteMagiaRect[2].y = (pisoRect2[1][2].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*3 && spriteMagiaRect[2].x < piso->w*4)
                                                    spriteMagiaRect[2].y = (pisoRect2[1][3].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*4 && spriteMagiaRect[2].x < piso->w*5)
                                                    spriteMagiaRect[2].y = (pisoRect2[1][4].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*5 && spriteMagiaRect[2].x < piso->w*6)
                                                    spriteMagiaRect[2].y = (pisoRect2[1][5].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*6 && spriteMagiaRect[2].x < piso->w*7)
                                                    spriteMagiaRect[2].y = (pisoRect2[1][6].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*7 && spriteMagiaRect[2].x < piso->w*8)
                                                    spriteMagiaRect[2].y = (pisoRect2[1][7].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*8 && spriteMagiaRect[2].x < piso->w*9)
                                                    spriteMagiaRect[2].y = (pisoRect2[1][8].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*9 && spriteMagiaRect[2].x < piso->w*10)
                                                    spriteMagiaRect[2].y = (pisoRect2[1][9].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*10 && spriteMagiaRect[2].x < piso->w*11)
                                                    spriteMagiaRect[2].y = (pisoRect2[1][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*11 && spriteMagiaRect[2].x < piso->w*12)
                                                    spriteMagiaRect[2].y = (pisoRect2[1][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*12 && spriteMagiaRect[2].x < piso->w*13)
                                                    spriteMagiaRect[2].y = (pisoRect2[1][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[2].x == 589 && spriteMagiaRect[2].y <= pisoRect1[1][13].y - magiaGanon->h)
                                                    spriteMagiaRect[2].y += magiaVel;

                                                if(spriteMagiaRect[2].y == 300)
                                                    pisoMagia[2] = 3;
                                            }

                                            if(pisoMagia[2] == 3){

                                                if(spriteMagiaRect[2].x >= pisoRect1[1][0].x - (magiaGanon->w / 2))
                                                    spriteMagiaRect[2].x -= magiaVel;
                                                //Ajustando piso 3
                                                if(spriteMagiaRect[2].x >= piso->w && spriteMagiaRect[2].x < piso->w*2)
                                                    spriteMagiaRect[2].y = (pisoRect1[1][0].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*2 && spriteMagiaRect[2].x < piso->w*3)
                                                    spriteMagiaRect[2].y = (pisoRect1[1][1].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*3 && spriteMagiaRect[2].x < piso->w*4)
                                                    spriteMagiaRect[2].y = (pisoRect1[1][3].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*4 && spriteMagiaRect[2].x < piso->w*5)
                                                    spriteMagiaRect[2].y = (pisoRect1[1][4].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*5 && spriteMagiaRect[2].x < piso->w*6)
                                                    spriteMagiaRect[2].y = (pisoRect1[1][5].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*6 && spriteMagiaRect[2].x < piso->w*7)
                                                    spriteMagiaRect[2].y = (pisoRect1[1][6].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*7 && spriteMagiaRect[2].x < piso->w*8)
                                                    spriteMagiaRect[2].y = (pisoRect1[1][7].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*8 && spriteMagiaRect[2].x < piso->w*9)
                                                    spriteMagiaRect[2].y = (pisoRect1[1][8].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*9 && spriteMagiaRect[2].x < piso->w*10)
                                                    spriteMagiaRect[2].y = (pisoRect1[1][9].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*10 && spriteMagiaRect[2].x < piso->w*11)
                                                    spriteMagiaRect[2].y = (pisoRect1[1][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*11 && spriteMagiaRect[2].x < piso->w*12)
                                                    spriteMagiaRect[2].y = (pisoRect1[1][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*12 && spriteMagiaRect[2].x < piso->w*13)
                                                    spriteMagiaRect[2].y = (pisoRect1[1][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[2].x == 21 && spriteMagiaRect[2].y <= pisoRect2[0][0].y - magiaGanon->h)
                                                    spriteMagiaRect[2].y += magiaVel;

                                                if(spriteMagiaRect[2].y == 376)
                                                    pisoMagia[2] = 2;

                                            }

                                            if(pisoMagia[2] == 2){

                                                if(spriteMagiaRect[2].x <= pisoRect2[0][13].x + piso->w)
                                                    spriteMagiaRect[2].x += magiaVel;
                                                //Ajustando piso 2
                                                if(spriteMagiaRect[2].x >= 0 && spriteMagiaRect[2].x < piso->w)
                                                    spriteMagiaRect[2].y = (pisoRect2[0][0].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w && spriteMagiaRect[2].x < piso->w*2)
                                                    spriteMagiaRect[2].y = (pisoRect2[0][1].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*2 && spriteMagiaRect[2].x < piso->w*3)
                                                    spriteMagiaRect[2].y = (pisoRect2[0][2].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*3 && spriteMagiaRect[2].x < piso->w*4)
                                                    spriteMagiaRect[2].y = (pisoRect2[0][3].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*4 && spriteMagiaRect[2].x < piso->w*5)
                                                    spriteMagiaRect[2].y = (pisoRect2[0][4].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*5 && spriteMagiaRect[2].x < piso->w*6)
                                                    spriteMagiaRect[2].y = (pisoRect2[0][5].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*6 && spriteMagiaRect[2].x < piso->w*7)
                                                    spriteMagiaRect[2].y = (pisoRect2[0][6].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*7 && spriteMagiaRect[2].x < piso->w*8)
                                                    spriteMagiaRect[2].y = (pisoRect2[0][7].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*8 && spriteMagiaRect[2].x < piso->w*9)
                                                    spriteMagiaRect[2].y = (pisoRect2[0][8].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*9 && spriteMagiaRect[2].x < piso->w*10)
                                                    spriteMagiaRect[2].y = (pisoRect2[0][9].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*10 && spriteMagiaRect[2].x < piso->w*11)
                                                    spriteMagiaRect[2].y = (pisoRect2[0][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*11 && spriteMagiaRect[2].x < piso->w*12)
                                                    spriteMagiaRect[2].y = (pisoRect2[0][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[2].x >= piso->w*12 && spriteMagiaRect[2].x < piso->w*13)
                                                    spriteMagiaRect[2].y = (pisoRect2[0][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[2].x == 589 && spriteMagiaRect[2].y <= pisoRect1[0][13].y - magiaGanon->h)
                                                    spriteMagiaRect[2].y += magiaVel;
                                                if(spriteMagiaRect[2].y == 450)
                                                    pisoMagia[2] = 1;

                                            }

                                            if(pisoMagia[2] == 1){

                                                    if(spriteMagiaRect[2].x > pisoRect1[0][0].x)
                                                    spriteMagiaRect[2].x -= magiaVel;
                                                    //Ajustando piso 1
                                                    if(spriteMagiaRect[2].x + magiaGanon->w < piso->w*7)
                                                        spriteMagiaRect[2].y = ((tela->h - piso->h)-magiaGanon->h)+2;
                                                    if(spriteMagiaRect[2].x + magiaGanon->w >= piso->w*7 && spriteMagiaRect[2].x + magiaGanon->w < piso->w*8)
                                                        spriteMagiaRect[2].y = (pisoRect1[0][7].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[2].x + magiaGanon->w >= piso->w*8 && spriteMagiaRect[2].x + magiaGanon->w < piso->w*9)
                                                        spriteMagiaRect[2].y = (pisoRect1[0][8].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[2].x + magiaGanon->w >= piso->w*9 && spriteMagiaRect[2].x + magiaGanon->w < piso->w*10)
                                                        spriteMagiaRect[2].y = (pisoRect1[0][9].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[2].x + magiaGanon->w >= piso->w*10 && spriteMagiaRect[2].x + magiaGanon->w < piso->w*11)
                                                        spriteMagiaRect[2].y = (pisoRect1[0][10].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[2].x + magiaGanon->w >= piso->w*11 && spriteMagiaRect[2].x + magiaGanon->w < piso->w*12)
                                                        spriteMagiaRect[2].y = (pisoRect1[0][11].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[2].x + magiaGanon->w >= piso->w*12 && spriteMagiaRect[2].x + magiaGanon->w < piso->w*13)
                                                        spriteMagiaRect[2].y = (pisoRect1[0][12].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[2].x + magiaGanon->w >= piso->w*13 && spriteMagiaRect[2].x + magiaGanon->w < piso->w*14)
                                                        spriteMagiaRect[2].y = (pisoRect1[0][13].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[2].x + magiaGanon->w >= piso->w*14 && spriteMagiaRect[2].x + magiaGanon->w < piso->w*15)
                                                        spriteMagiaRect[2].y = (pisoRect1[0][14].y + 2) - magiaGanon->h;

                                                    //Voltando a Magia
                                                    if(spriteMagiaRect[2].x == 0){

                                                        pisoMagia[2] = 6;
                                                        spriteMagiaRect[2].x = pisoRect2[2][4].x + 45;
                                                        spriteMagiaRect[2].y = pisoRect2[2][4].y - magiaGanon->h;
                                                        magiaAtiva[2] = 1;

                                                    }

                                                }
                                            }
                                        //Magia 3
                                        if(tempoMagia > 700){
                                            if(pisoMagia[3] == 6){

                                                if(spriteMagiaRect[3].x <= pisoRect2[2][13].x + piso->w)
                                                    spriteMagiaRect[3].x += magiaVel;
                                                //Ajustando piso 6
                                                if(spriteMagiaRect[3].x >= piso->w*10 && spriteMagiaRect[3].x < piso->w*11)
                                                    spriteMagiaRect[3].y = (pisoRect2[2][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*11 && spriteMagiaRect[3].x < piso->w*12)
                                                    spriteMagiaRect[3].y = (pisoRect2[2][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*12 && spriteMagiaRect[3].x < piso->w*13)
                                                    spriteMagiaRect[3].y = (pisoRect2[2][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[3].x == 589 && spriteMagiaRect[3].y <= pisoRect1[2][13].y - magiaGanon->h)
                                                    spriteMagiaRect[3].y += magiaVel;

                                                if(spriteMagiaRect[3].y == 145)
                                                    pisoMagia[3] = 5;


                                            }

                                            if(pisoMagia[3] == 5){

                                                if(spriteMagiaRect[3].x >= pisoRect1[2][0].x - (magiaGanon->w / 2))
                                                    spriteMagiaRect[3].x -= magiaVel;
                                                //Ajustando piso 5
                                                if(spriteMagiaRect[3].x >= piso->w && spriteMagiaRect[3].x < piso->w*2)
                                                    spriteMagiaRect[3].y = (pisoRect1[2][0].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*2 && spriteMagiaRect[3].x < piso->w*3)
                                                    spriteMagiaRect[3].y = (pisoRect1[2][1].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*3 && spriteMagiaRect[3].x < piso->w*4)
                                                    spriteMagiaRect[3].y = (pisoRect1[2][3].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*4 && spriteMagiaRect[3].x < piso->w*5)
                                                    spriteMagiaRect[3].y = (pisoRect1[2][4].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*5 && spriteMagiaRect[3].x < piso->w*6)
                                                    spriteMagiaRect[3].y = (pisoRect1[2][5].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*6 && spriteMagiaRect[3].x < piso->w*7)
                                                    spriteMagiaRect[3].y = (pisoRect1[2][6].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*7 && spriteMagiaRect[3].x < piso->w*8)
                                                    spriteMagiaRect[3].y = (pisoRect1[2][7].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*8 && spriteMagiaRect[3].x < piso->w*9)
                                                    spriteMagiaRect[3].y = (pisoRect1[2][8].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*9 && spriteMagiaRect[3].x < piso->w*10)
                                                    spriteMagiaRect[3].y = (pisoRect1[2][9].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*10 && spriteMagiaRect[3].x < piso->w*11)
                                                    spriteMagiaRect[3].y = (pisoRect1[2][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*11 && spriteMagiaRect[3].x < piso->w*12)
                                                    spriteMagiaRect[3].y = (pisoRect1[2][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*12 && spriteMagiaRect[3].x < piso->w*13)
                                                    spriteMagiaRect[3].y = (pisoRect1[2][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[3].x == 21 && spriteMagiaRect[3].y <= pisoRect2[1][0].y - magiaGanon->h)
                                                    spriteMagiaRect[3].y += magiaVel;

                                                if(spriteMagiaRect[3].y == 223)
                                                    pisoMagia[3] = 4;

                                            }

                                            if(pisoMagia[3] == 4){

                                                if(spriteMagiaRect[3].x <= pisoRect2[1][13].x + piso->w)
                                                    spriteMagiaRect[3].x += magiaVel;
                                                //Ajustando piso 4
                                                if(spriteMagiaRect[3].x >= 0 && spriteMagiaRect[3].x < piso->w)
                                                    spriteMagiaRect[3].y = (pisoRect2[1][0].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w && spriteMagiaRect[3].x < piso->w*2)
                                                    spriteMagiaRect[3].y = (pisoRect2[1][1].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*2 && spriteMagiaRect[3].x < piso->w*3)
                                                    spriteMagiaRect[3].y = (pisoRect2[1][2].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*3 && spriteMagiaRect[3].x < piso->w*4)
                                                    spriteMagiaRect[3].y = (pisoRect2[1][3].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*4 && spriteMagiaRect[3].x < piso->w*5)
                                                    spriteMagiaRect[3].y = (pisoRect2[1][4].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*5 && spriteMagiaRect[3].x < piso->w*6)
                                                    spriteMagiaRect[3].y = (pisoRect2[1][5].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*6 && spriteMagiaRect[3].x < piso->w*7)
                                                    spriteMagiaRect[3].y = (pisoRect2[1][6].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*7 && spriteMagiaRect[3].x < piso->w*8)
                                                    spriteMagiaRect[3].y = (pisoRect2[1][7].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*8 && spriteMagiaRect[3].x < piso->w*9)
                                                    spriteMagiaRect[3].y = (pisoRect2[1][8].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*9 && spriteMagiaRect[3].x < piso->w*10)
                                                    spriteMagiaRect[3].y = (pisoRect2[1][9].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*10 && spriteMagiaRect[3].x < piso->w*11)
                                                    spriteMagiaRect[3].y = (pisoRect2[1][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*11 && spriteMagiaRect[3].x < piso->w*12)
                                                    spriteMagiaRect[3].y = (pisoRect2[1][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*12 && spriteMagiaRect[3].x < piso->w*13)
                                                    spriteMagiaRect[3].y = (pisoRect2[1][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[3].x == 589 && spriteMagiaRect[3].y <= pisoRect1[1][13].y - magiaGanon->h)
                                                    spriteMagiaRect[3].y += magiaVel;

                                                if(spriteMagiaRect[3].y == 300)
                                                    pisoMagia[3] = 3;
                                            }

                                            if(pisoMagia[3] == 3){

                                                if(spriteMagiaRect[3].x >= pisoRect1[1][0].x - (magiaGanon->w / 2))
                                                    spriteMagiaRect[3].x -= magiaVel;
                                                //Ajustando piso 3
                                                if(spriteMagiaRect[3].x >= piso->w && spriteMagiaRect[3].x < piso->w*2)
                                                    spriteMagiaRect[3].y = (pisoRect1[1][0].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*2 && spriteMagiaRect[3].x < piso->w*3)
                                                    spriteMagiaRect[3].y = (pisoRect1[1][1].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*3 && spriteMagiaRect[3].x < piso->w*4)
                                                    spriteMagiaRect[3].y = (pisoRect1[1][3].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*4 && spriteMagiaRect[3].x < piso->w*5)
                                                    spriteMagiaRect[3].y = (pisoRect1[1][4].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*5 && spriteMagiaRect[3].x < piso->w*6)
                                                    spriteMagiaRect[3].y = (pisoRect1[1][5].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*6 && spriteMagiaRect[3].x < piso->w*7)
                                                    spriteMagiaRect[3].y = (pisoRect1[1][6].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*7 && spriteMagiaRect[3].x < piso->w*8)
                                                    spriteMagiaRect[3].y = (pisoRect1[1][7].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*8 && spriteMagiaRect[3].x < piso->w*9)
                                                    spriteMagiaRect[3].y = (pisoRect1[1][8].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*9 && spriteMagiaRect[3].x < piso->w*10)
                                                    spriteMagiaRect[3].y = (pisoRect1[1][9].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*10 && spriteMagiaRect[3].x < piso->w*11)
                                                    spriteMagiaRect[3].y = (pisoRect1[1][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*11 && spriteMagiaRect[3].x < piso->w*12)
                                                    spriteMagiaRect[3].y = (pisoRect1[1][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*12 && spriteMagiaRect[3].x < piso->w*13)
                                                    spriteMagiaRect[3].y = (pisoRect1[1][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[3].x == 21 && spriteMagiaRect[3].y <= pisoRect2[0][0].y - magiaGanon->h)
                                                    spriteMagiaRect[3].y += magiaVel;

                                                if(spriteMagiaRect[3].y == 376)
                                                    pisoMagia[3] = 2;

                                            }

                                            if(pisoMagia[3] == 2){

                                                if(spriteMagiaRect[3].x <= pisoRect2[0][13].x + piso->w)
                                                    spriteMagiaRect[3].x += magiaVel;
                                                //Ajustando piso 2
                                                if(spriteMagiaRect[3].x >= 0 && spriteMagiaRect[3].x < piso->w)
                                                    spriteMagiaRect[3].y = (pisoRect2[0][0].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w && spriteMagiaRect[3].x < piso->w*2)
                                                    spriteMagiaRect[3].y = (pisoRect2[0][1].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*2 && spriteMagiaRect[3].x < piso->w*3)
                                                    spriteMagiaRect[3].y = (pisoRect2[0][2].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*3 && spriteMagiaRect[3].x < piso->w*4)
                                                    spriteMagiaRect[3].y = (pisoRect2[0][3].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*4 && spriteMagiaRect[3].x < piso->w*5)
                                                    spriteMagiaRect[3].y = (pisoRect2[0][4].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*5 && spriteMagiaRect[3].x < piso->w*6)
                                                    spriteMagiaRect[3].y = (pisoRect2[0][5].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*6 && spriteMagiaRect[3].x < piso->w*7)
                                                    spriteMagiaRect[3].y = (pisoRect2[0][6].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*7 && spriteMagiaRect[3].x < piso->w*8)
                                                    spriteMagiaRect[3].y = (pisoRect2[0][7].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*8 && spriteMagiaRect[3].x < piso->w*9)
                                                    spriteMagiaRect[3].y = (pisoRect2[0][8].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*9 && spriteMagiaRect[3].x < piso->w*10)
                                                    spriteMagiaRect[3].y = (pisoRect2[0][9].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*10 && spriteMagiaRect[3].x < piso->w*11)
                                                    spriteMagiaRect[3].y = (pisoRect2[0][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*11 && spriteMagiaRect[3].x < piso->w*12)
                                                    spriteMagiaRect[3].y = (pisoRect2[0][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[3].x >= piso->w*12 && spriteMagiaRect[3].x < piso->w*13)
                                                    spriteMagiaRect[3].y = (pisoRect2[0][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[3].x == 589 && spriteMagiaRect[3].y <= pisoRect1[0][13].y - magiaGanon->h)
                                                    spriteMagiaRect[3].y += magiaVel;
                                                if(spriteMagiaRect[3].y == 450)
                                                    pisoMagia[3] = 1;

                                            }

                                            if(pisoMagia[3] == 1){

                                                    if(spriteMagiaRect[3].x > pisoRect1[0][0].x)
                                                    spriteMagiaRect[3].x -= magiaVel;
                                                    //Ajustando piso 1
                                                    if(spriteMagiaRect[3].x + magiaGanon->w < piso->w*7)
                                                        spriteMagiaRect[3].y = ((tela->h - piso->h)-magiaGanon->h)+2;
                                                    if(spriteMagiaRect[3].x + magiaGanon->w >= piso->w*7 && spriteMagiaRect[3].x + magiaGanon->w < piso->w*8)
                                                        spriteMagiaRect[3].y = (pisoRect1[0][7].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[3].x + magiaGanon->w >= piso->w*8 && spriteMagiaRect[3].x + magiaGanon->w < piso->w*9)
                                                        spriteMagiaRect[3].y = (pisoRect1[0][8].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[3].x + magiaGanon->w >= piso->w*9 && spriteMagiaRect[3].x + magiaGanon->w < piso->w*10)
                                                        spriteMagiaRect[3].y = (pisoRect1[0][9].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[3].x + magiaGanon->w >= piso->w*10 && spriteMagiaRect[3].x + magiaGanon->w < piso->w*11)
                                                        spriteMagiaRect[3].y = (pisoRect1[0][10].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[3].x + magiaGanon->w >= piso->w*11 && spriteMagiaRect[3].x + magiaGanon->w < piso->w*12)
                                                        spriteMagiaRect[3].y = (pisoRect1[0][11].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[3].x + magiaGanon->w >= piso->w*12 && spriteMagiaRect[3].x + magiaGanon->w < piso->w*13)
                                                        spriteMagiaRect[3].y = (pisoRect1[0][12].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[3].x + magiaGanon->w >= piso->w*13 && spriteMagiaRect[3].x + magiaGanon->w < piso->w*14)
                                                        spriteMagiaRect[3].y = (pisoRect1[0][13].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[3].x + magiaGanon->w >= piso->w*14 && spriteMagiaRect[3].x + magiaGanon->w < piso->w*15)
                                                        spriteMagiaRect[3].y = (pisoRect1[0][14].y + 2) - magiaGanon->h;

                                                    //Voltando a Magia
                                                    if(spriteMagiaRect[3].x == 0){

                                                        pisoMagia[3] = 6;
                                                        spriteMagiaRect[3].x = pisoRect2[2][4].x + 45;
                                                        spriteMagiaRect[3].y = pisoRect2[2][4].y - magiaGanon->h;
                                                        magiaAtiva[3] = 1;

                                                    }

                                                }
                                            }
                                        //Magia 4
                                        if(tempoMagia > 900){
                                            if(pisoMagia[4] == 6){

                                                if(spriteMagiaRect[4].x <= pisoRect2[2][13].x + piso->w)
                                                    spriteMagiaRect[4].x += magiaVel;
                                                //Ajustando piso 6
                                                if(spriteMagiaRect[4].x >= piso->w*10 && spriteMagiaRect[4].x < piso->w*11)
                                                    spriteMagiaRect[4].y = (pisoRect2[2][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*11 && spriteMagiaRect[4].x < piso->w*12)
                                                    spriteMagiaRect[4].y = (pisoRect2[2][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*12 && spriteMagiaRect[4].x < piso->w*13)
                                                    spriteMagiaRect[4].y = (pisoRect2[2][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[4].x == 589 && spriteMagiaRect[4].y <= pisoRect1[2][13].y - magiaGanon->h)
                                                    spriteMagiaRect[4].y += magiaVel;

                                                if(spriteMagiaRect[4].y == 145)
                                                    pisoMagia[4] = 5;


                                            }

                                            if(pisoMagia[4] == 5){

                                                if(spriteMagiaRect[4].x >= pisoRect1[2][0].x - (magiaGanon->w / 2))
                                                    spriteMagiaRect[4].x -= magiaVel;
                                                //Ajustando piso 5
                                                if(spriteMagiaRect[4].x >= piso->w && spriteMagiaRect[4].x < piso->w*2)
                                                    spriteMagiaRect[4].y = (pisoRect1[2][0].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*2 && spriteMagiaRect[4].x < piso->w*3)
                                                    spriteMagiaRect[4].y = (pisoRect1[2][1].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*3 && spriteMagiaRect[4].x < piso->w*4)
                                                    spriteMagiaRect[4].y = (pisoRect1[2][3].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*4 && spriteMagiaRect[4].x < piso->w*5)
                                                    spriteMagiaRect[4].y = (pisoRect1[2][4].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*5 && spriteMagiaRect[4].x < piso->w*6)
                                                    spriteMagiaRect[4].y = (pisoRect1[2][5].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*6 && spriteMagiaRect[4].x < piso->w*7)
                                                    spriteMagiaRect[4].y = (pisoRect1[2][6].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*7 && spriteMagiaRect[4].x < piso->w*8)
                                                    spriteMagiaRect[4].y = (pisoRect1[2][7].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*8 && spriteMagiaRect[4].x < piso->w*9)
                                                    spriteMagiaRect[4].y = (pisoRect1[2][8].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*9 && spriteMagiaRect[4].x < piso->w*10)
                                                    spriteMagiaRect[4].y = (pisoRect1[2][9].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*10 && spriteMagiaRect[4].x < piso->w*11)
                                                    spriteMagiaRect[4].y = (pisoRect1[2][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*11 && spriteMagiaRect[4].x < piso->w*12)
                                                    spriteMagiaRect[4].y = (pisoRect1[2][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*12 && spriteMagiaRect[4].x < piso->w*13)
                                                    spriteMagiaRect[4].y = (pisoRect1[2][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[4].x == 21 && spriteMagiaRect[4].y <= pisoRect2[1][0].y - magiaGanon->h)
                                                    spriteMagiaRect[4].y += magiaVel;

                                                if(spriteMagiaRect[4].y == 223)
                                                    pisoMagia[4] = 4;

                                            }

                                            if(pisoMagia[4] == 4){

                                                if(spriteMagiaRect[4].x <= pisoRect2[1][13].x + piso->w)
                                                    spriteMagiaRect[4].x += magiaVel;
                                                //Ajustando piso 4
                                                if(spriteMagiaRect[4].x >= 0 && spriteMagiaRect[4].x < piso->w)
                                                    spriteMagiaRect[4].y = (pisoRect2[1][0].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w && spriteMagiaRect[4].x < piso->w*2)
                                                    spriteMagiaRect[4].y = (pisoRect2[1][1].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*2 && spriteMagiaRect[4].x < piso->w*3)
                                                    spriteMagiaRect[4].y = (pisoRect2[1][2].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*3 && spriteMagiaRect[4].x < piso->w*4)
                                                    spriteMagiaRect[4].y = (pisoRect2[1][3].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*4 && spriteMagiaRect[4].x < piso->w*5)
                                                    spriteMagiaRect[4].y = (pisoRect2[1][4].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*5 && spriteMagiaRect[4].x < piso->w*6)
                                                    spriteMagiaRect[4].y = (pisoRect2[1][5].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*6 && spriteMagiaRect[4].x < piso->w*7)
                                                    spriteMagiaRect[4].y = (pisoRect2[1][6].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*7 && spriteMagiaRect[4].x < piso->w*8)
                                                    spriteMagiaRect[4].y = (pisoRect2[1][7].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*8 && spriteMagiaRect[4].x < piso->w*9)
                                                    spriteMagiaRect[4].y = (pisoRect2[1][8].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*9 && spriteMagiaRect[4].x < piso->w*10)
                                                    spriteMagiaRect[4].y = (pisoRect2[1][9].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*10 && spriteMagiaRect[4].x < piso->w*11)
                                                    spriteMagiaRect[4].y = (pisoRect2[1][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*11 && spriteMagiaRect[4].x < piso->w*12)
                                                    spriteMagiaRect[4].y = (pisoRect2[1][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*12 && spriteMagiaRect[4].x < piso->w*13)
                                                    spriteMagiaRect[4].y = (pisoRect2[1][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[4].x == 589 && spriteMagiaRect[4].y <= pisoRect1[1][13].y - magiaGanon->h)
                                                    spriteMagiaRect[4].y += magiaVel;

                                                if(spriteMagiaRect[4].y == 300)
                                                    pisoMagia[4] = 3;
                                            }

                                            if(pisoMagia[4] == 3){

                                                if(spriteMagiaRect[4].x >= pisoRect1[1][0].x - (magiaGanon->w / 2))
                                                    spriteMagiaRect[4].x -= magiaVel;
                                                //Ajustando piso 3
                                                if(spriteMagiaRect[4].x >= piso->w && spriteMagiaRect[4].x < piso->w*2)
                                                    spriteMagiaRect[4].y = (pisoRect1[1][0].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*2 && spriteMagiaRect[4].x < piso->w*3)
                                                    spriteMagiaRect[4].y = (pisoRect1[1][1].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*3 && spriteMagiaRect[4].x < piso->w*4)
                                                    spriteMagiaRect[4].y = (pisoRect1[1][3].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*4 && spriteMagiaRect[4].x < piso->w*5)
                                                    spriteMagiaRect[4].y = (pisoRect1[1][4].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*5 && spriteMagiaRect[4].x < piso->w*6)
                                                    spriteMagiaRect[4].y = (pisoRect1[1][5].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*6 && spriteMagiaRect[4].x < piso->w*7)
                                                    spriteMagiaRect[4].y = (pisoRect1[1][6].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*7 && spriteMagiaRect[4].x < piso->w*8)
                                                    spriteMagiaRect[4].y = (pisoRect1[1][7].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*8 && spriteMagiaRect[4].x < piso->w*9)
                                                    spriteMagiaRect[4].y = (pisoRect1[1][8].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*9 && spriteMagiaRect[4].x < piso->w*10)
                                                    spriteMagiaRect[4].y = (pisoRect1[1][9].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*10 && spriteMagiaRect[4].x < piso->w*11)
                                                    spriteMagiaRect[4].y = (pisoRect1[1][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*11 && spriteMagiaRect[4].x < piso->w*12)
                                                    spriteMagiaRect[4].y = (pisoRect1[1][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*12 && spriteMagiaRect[4].x < piso->w*13)
                                                    spriteMagiaRect[4].y = (pisoRect1[1][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[4].x == 21 && spriteMagiaRect[4].y <= pisoRect2[0][0].y - magiaGanon->h)
                                                    spriteMagiaRect[4].y += magiaVel;

                                                if(spriteMagiaRect[4].y == 376)
                                                    pisoMagia[4] = 2;

                                            }

                                            if(pisoMagia[4] == 2){

                                                if(spriteMagiaRect[4].x <= pisoRect2[0][13].x + piso->w)
                                                    spriteMagiaRect[4].x += magiaVel;
                                                //Ajustando piso 2
                                                if(spriteMagiaRect[4].x >= 0 && spriteMagiaRect[4].x < piso->w)
                                                    spriteMagiaRect[4].y = (pisoRect2[0][0].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w && spriteMagiaRect[4].x < piso->w*2)
                                                    spriteMagiaRect[4].y = (pisoRect2[0][1].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*2 && spriteMagiaRect[4].x < piso->w*3)
                                                    spriteMagiaRect[4].y = (pisoRect2[0][2].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*3 && spriteMagiaRect[4].x < piso->w*4)
                                                    spriteMagiaRect[4].y = (pisoRect2[0][3].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*4 && spriteMagiaRect[4].x < piso->w*5)
                                                    spriteMagiaRect[4].y = (pisoRect2[0][4].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*5 && spriteMagiaRect[4].x < piso->w*6)
                                                    spriteMagiaRect[4].y = (pisoRect2[0][5].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*6 && spriteMagiaRect[4].x < piso->w*7)
                                                    spriteMagiaRect[4].y = (pisoRect2[0][6].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*7 && spriteMagiaRect[4].x < piso->w*8)
                                                    spriteMagiaRect[4].y = (pisoRect2[0][7].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*8 && spriteMagiaRect[4].x < piso->w*9)
                                                    spriteMagiaRect[4].y = (pisoRect2[0][8].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*9 && spriteMagiaRect[4].x < piso->w*10)
                                                    spriteMagiaRect[4].y = (pisoRect2[0][9].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*10 && spriteMagiaRect[4].x < piso->w*11)
                                                    spriteMagiaRect[4].y = (pisoRect2[0][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*11 && spriteMagiaRect[4].x < piso->w*12)
                                                    spriteMagiaRect[4].y = (pisoRect2[0][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[4].x >= piso->w*12 && spriteMagiaRect[4].x < piso->w*13)
                                                    spriteMagiaRect[4].y = (pisoRect2[0][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[4].x == 589 && spriteMagiaRect[4].y <= pisoRect1[0][13].y - magiaGanon->h)
                                                    spriteMagiaRect[4].y += magiaVel;
                                                if(spriteMagiaRect[4].y == 450)
                                                    pisoMagia[4] = 1;

                                            }

                                            if(pisoMagia[4] == 1){

                                                    if(spriteMagiaRect[4].x > pisoRect1[0][0].x)
                                                    spriteMagiaRect[4].x -= magiaVel;
                                                    //Ajustando piso 1
                                                    if(spriteMagiaRect[4].x + magiaGanon->w < piso->w*7)
                                                        spriteMagiaRect[4].y = ((tela->h - piso->h)-magiaGanon->h)+2;
                                                    if(spriteMagiaRect[4].x + magiaGanon->w >= piso->w*7 && spriteMagiaRect[4].x + magiaGanon->w < piso->w*8)
                                                        spriteMagiaRect[4].y = (pisoRect1[0][7].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[4].x + magiaGanon->w >= piso->w*8 && spriteMagiaRect[4].x + magiaGanon->w < piso->w*9)
                                                        spriteMagiaRect[4].y = (pisoRect1[0][8].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[4].x + magiaGanon->w >= piso->w*9 && spriteMagiaRect[4].x + magiaGanon->w < piso->w*10)
                                                        spriteMagiaRect[4].y = (pisoRect1[0][9].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[4].x + magiaGanon->w >= piso->w*10 && spriteMagiaRect[4].x + magiaGanon->w < piso->w*11)
                                                        spriteMagiaRect[4].y = (pisoRect1[0][10].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[4].x + magiaGanon->w >= piso->w*11 && spriteMagiaRect[4].x + magiaGanon->w < piso->w*12)
                                                        spriteMagiaRect[4].y = (pisoRect1[0][11].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[4].x + magiaGanon->w >= piso->w*12 && spriteMagiaRect[4].x + magiaGanon->w < piso->w*13)
                                                        spriteMagiaRect[4].y = (pisoRect1[0][12].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[4].x + magiaGanon->w >= piso->w*13 && spriteMagiaRect[4].x + magiaGanon->w < piso->w*14)
                                                        spriteMagiaRect[4].y = (pisoRect1[0][13].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[4].x + magiaGanon->w >= piso->w*14 && spriteMagiaRect[4].x + magiaGanon->w < piso->w*15)
                                                        spriteMagiaRect[4].y = (pisoRect1[0][14].y + 2) - magiaGanon->h;

                                                    //Voltando a Magia
                                                    if(spriteMagiaRect[4].x == 0){

                                                        pisoMagia[4] = 6;
                                                        spriteMagiaRect[4].x = pisoRect2[2][4].x + 45;
                                                        spriteMagiaRect[4].y = pisoRect2[2][4].y - magiaGanon->h;
                                                        magiaAtiva[4] = 1;

                                                    }

                                                }
                                            }
                                        //Magia 5
                                        if(tempoMagia > 1100){
                                            if(pisoMagia[5] == 6){

                                                if(spriteMagiaRect[5].x <= pisoRect2[2][13].x + piso->w)
                                                    spriteMagiaRect[5].x += magiaVel;
                                                //Ajustando piso 6
                                                if(spriteMagiaRect[5].x >= piso->w*10 && spriteMagiaRect[5].x < piso->w*11)
                                                    spriteMagiaRect[5].y = (pisoRect2[2][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*11 && spriteMagiaRect[5].x < piso->w*12)
                                                    spriteMagiaRect[5].y = (pisoRect2[2][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*12 && spriteMagiaRect[5].x < piso->w*13)
                                                    spriteMagiaRect[5].y = (pisoRect2[2][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[5].x == 589 && spriteMagiaRect[5].y <= pisoRect1[2][13].y - magiaGanon->h)
                                                    spriteMagiaRect[5].y += magiaVel;

                                                if(spriteMagiaRect[5].y == 145)
                                                    pisoMagia[5] = 5;


                                            }

                                            if(pisoMagia[5] == 5){

                                                if(spriteMagiaRect[5].x >= pisoRect1[2][0].x - (magiaGanon->w / 2))
                                                    spriteMagiaRect[5].x -= magiaVel;
                                                //Ajustando piso 5
                                                if(spriteMagiaRect[5].x >= piso->w && spriteMagiaRect[5].x < piso->w*2)
                                                    spriteMagiaRect[5].y = (pisoRect1[2][0].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*2 && spriteMagiaRect[5].x < piso->w*3)
                                                    spriteMagiaRect[5].y = (pisoRect1[2][1].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*3 && spriteMagiaRect[5].x < piso->w*4)
                                                    spriteMagiaRect[5].y = (pisoRect1[2][3].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*4 && spriteMagiaRect[5].x < piso->w*5)
                                                    spriteMagiaRect[5].y = (pisoRect1[2][4].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*5 && spriteMagiaRect[5].x < piso->w*6)
                                                    spriteMagiaRect[5].y = (pisoRect1[2][5].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*6 && spriteMagiaRect[5].x < piso->w*7)
                                                    spriteMagiaRect[5].y = (pisoRect1[2][6].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*7 && spriteMagiaRect[5].x < piso->w*8)
                                                    spriteMagiaRect[5].y = (pisoRect1[2][7].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*8 && spriteMagiaRect[5].x < piso->w*9)
                                                    spriteMagiaRect[5].y = (pisoRect1[2][8].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*9 && spriteMagiaRect[5].x < piso->w*10)
                                                    spriteMagiaRect[5].y = (pisoRect1[2][9].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*10 && spriteMagiaRect[5].x < piso->w*11)
                                                    spriteMagiaRect[5].y = (pisoRect1[2][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*11 && spriteMagiaRect[5].x < piso->w*12)
                                                    spriteMagiaRect[5].y = (pisoRect1[2][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*12 && spriteMagiaRect[5].x < piso->w*13)
                                                    spriteMagiaRect[5].y = (pisoRect1[2][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[5].x == 21 && spriteMagiaRect[5].y <= pisoRect2[1][0].y - magiaGanon->h)
                                                    spriteMagiaRect[5].y += magiaVel;

                                                if(spriteMagiaRect[5].y == 223)
                                                    pisoMagia[5] = 4;

                                            }

                                            if(pisoMagia[5] == 4){

                                                if(spriteMagiaRect[5].x <= pisoRect2[1][13].x + piso->w)
                                                    spriteMagiaRect[5].x += magiaVel;
                                                //Ajustando piso 4
                                                if(spriteMagiaRect[5].x >= 0 && spriteMagiaRect[5].x < piso->w)
                                                    spriteMagiaRect[5].y = (pisoRect2[1][0].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w && spriteMagiaRect[5].x < piso->w*2)
                                                    spriteMagiaRect[5].y = (pisoRect2[1][1].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*2 && spriteMagiaRect[5].x < piso->w*3)
                                                    spriteMagiaRect[5].y = (pisoRect2[1][2].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*3 && spriteMagiaRect[5].x < piso->w*4)
                                                    spriteMagiaRect[5].y = (pisoRect2[1][3].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*4 && spriteMagiaRect[5].x < piso->w*5)
                                                    spriteMagiaRect[5].y = (pisoRect2[1][4].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*5 && spriteMagiaRect[5].x < piso->w*6)
                                                    spriteMagiaRect[5].y = (pisoRect2[1][5].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*6 && spriteMagiaRect[5].x < piso->w*7)
                                                    spriteMagiaRect[5].y = (pisoRect2[1][6].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*7 && spriteMagiaRect[5].x < piso->w*8)
                                                    spriteMagiaRect[5].y = (pisoRect2[1][7].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*8 && spriteMagiaRect[5].x < piso->w*9)
                                                    spriteMagiaRect[5].y = (pisoRect2[1][8].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*9 && spriteMagiaRect[5].x < piso->w*10)
                                                    spriteMagiaRect[5].y = (pisoRect2[1][9].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*10 && spriteMagiaRect[5].x < piso->w*11)
                                                    spriteMagiaRect[5].y = (pisoRect2[1][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*11 && spriteMagiaRect[5].x < piso->w*12)
                                                    spriteMagiaRect[5].y = (pisoRect2[1][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*12 && spriteMagiaRect[5].x < piso->w*13)
                                                    spriteMagiaRect[5].y = (pisoRect2[1][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[5].x == 589 && spriteMagiaRect[5].y <= pisoRect1[1][13].y - magiaGanon->h)
                                                    spriteMagiaRect[5].y += magiaVel;

                                                if(spriteMagiaRect[5].y == 300)
                                                    pisoMagia[5] = 3;
                                            }

                                            if(pisoMagia[5] == 3){

                                                if(spriteMagiaRect[5].x >= pisoRect1[1][0].x - (magiaGanon->w / 2))
                                                    spriteMagiaRect[5].x -= magiaVel;
                                                //Ajustando piso 3
                                                if(spriteMagiaRect[5].x >= piso->w && spriteMagiaRect[5].x < piso->w*2)
                                                    spriteMagiaRect[5].y = (pisoRect1[1][0].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*2 && spriteMagiaRect[5].x < piso->w*3)
                                                    spriteMagiaRect[5].y = (pisoRect1[1][1].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*3 && spriteMagiaRect[5].x < piso->w*4)
                                                    spriteMagiaRect[5].y = (pisoRect1[1][3].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*4 && spriteMagiaRect[5].x < piso->w*5)
                                                    spriteMagiaRect[5].y = (pisoRect1[1][4].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*5 && spriteMagiaRect[5].x < piso->w*6)
                                                    spriteMagiaRect[5].y = (pisoRect1[1][5].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*6 && spriteMagiaRect[5].x < piso->w*7)
                                                    spriteMagiaRect[5].y = (pisoRect1[1][6].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*7 && spriteMagiaRect[5].x < piso->w*8)
                                                    spriteMagiaRect[5].y = (pisoRect1[1][7].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*8 && spriteMagiaRect[5].x < piso->w*9)
                                                    spriteMagiaRect[5].y = (pisoRect1[1][8].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*9 && spriteMagiaRect[5].x < piso->w*10)
                                                    spriteMagiaRect[5].y = (pisoRect1[1][9].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*10 && spriteMagiaRect[5].x < piso->w*11)
                                                    spriteMagiaRect[5].y = (pisoRect1[1][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*11 && spriteMagiaRect[5].x < piso->w*12)
                                                    spriteMagiaRect[5].y = (pisoRect1[1][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*12 && spriteMagiaRect[5].x < piso->w*13)
                                                    spriteMagiaRect[5].y = (pisoRect1[1][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[5].x == 21 && spriteMagiaRect[5].y <= pisoRect2[0][0].y - magiaGanon->h)
                                                    spriteMagiaRect[5].y += magiaVel;

                                                if(spriteMagiaRect[5].y == 376)
                                                    pisoMagia[5] = 2;

                                            }

                                            if(pisoMagia[5] == 2){

                                                if(spriteMagiaRect[5].x <= pisoRect2[0][13].x + piso->w)
                                                    spriteMagiaRect[5].x += magiaVel;
                                                //Ajustando piso 2
                                                if(spriteMagiaRect[5].x >= 0 && spriteMagiaRect[5].x < piso->w)
                                                    spriteMagiaRect[5].y = (pisoRect2[0][0].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w && spriteMagiaRect[5].x < piso->w*2)
                                                    spriteMagiaRect[5].y = (pisoRect2[0][1].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*2 && spriteMagiaRect[5].x < piso->w*3)
                                                    spriteMagiaRect[5].y = (pisoRect2[0][2].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*3 && spriteMagiaRect[5].x < piso->w*4)
                                                    spriteMagiaRect[5].y = (pisoRect2[0][3].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*4 && spriteMagiaRect[5].x < piso->w*5)
                                                    spriteMagiaRect[5].y = (pisoRect2[0][4].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*5 && spriteMagiaRect[5].x < piso->w*6)
                                                    spriteMagiaRect[5].y = (pisoRect2[0][5].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*6 && spriteMagiaRect[5].x < piso->w*7)
                                                    spriteMagiaRect[5].y = (pisoRect2[0][6].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*7 && spriteMagiaRect[5].x < piso->w*8)
                                                    spriteMagiaRect[5].y = (pisoRect2[0][7].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*8 && spriteMagiaRect[5].x < piso->w*9)
                                                    spriteMagiaRect[5].y = (pisoRect2[0][8].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*9 && spriteMagiaRect[5].x < piso->w*10)
                                                    spriteMagiaRect[5].y = (pisoRect2[0][9].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*10 && spriteMagiaRect[5].x < piso->w*11)
                                                    spriteMagiaRect[5].y = (pisoRect2[0][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*11 && spriteMagiaRect[5].x < piso->w*12)
                                                    spriteMagiaRect[5].y = (pisoRect2[0][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[5].x >= piso->w*12 && spriteMagiaRect[5].x < piso->w*13)
                                                    spriteMagiaRect[5].y = (pisoRect2[0][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[5].x == 589 && spriteMagiaRect[5].y <= pisoRect1[0][13].y - magiaGanon->h)
                                                    spriteMagiaRect[5].y += magiaVel;
                                                if(spriteMagiaRect[5].y == 450)
                                                    pisoMagia[5] = 1;

                                            }

                                            if(pisoMagia[5] == 1){

                                                    if(spriteMagiaRect[5].x > pisoRect1[0][0].x)
                                                    spriteMagiaRect[5].x -= magiaVel;
                                                    //Ajustando piso 1
                                                    if(spriteMagiaRect[5].x + magiaGanon->w < piso->w*7)
                                                        spriteMagiaRect[5].y = ((tela->h - piso->h)-magiaGanon->h)+2;
                                                    if(spriteMagiaRect[5].x + magiaGanon->w >= piso->w*7 && spriteMagiaRect[5].x + magiaGanon->w < piso->w*8)
                                                        spriteMagiaRect[5].y = (pisoRect1[0][7].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[5].x + magiaGanon->w >= piso->w*8 && spriteMagiaRect[5].x + magiaGanon->w < piso->w*9)
                                                        spriteMagiaRect[5].y = (pisoRect1[0][8].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[5].x + magiaGanon->w >= piso->w*9 && spriteMagiaRect[5].x + magiaGanon->w < piso->w*10)
                                                        spriteMagiaRect[5].y = (pisoRect1[0][9].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[5].x + magiaGanon->w >= piso->w*10 && spriteMagiaRect[5].x + magiaGanon->w < piso->w*11)
                                                        spriteMagiaRect[5].y = (pisoRect1[0][10].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[5].x + magiaGanon->w >= piso->w*11 && spriteMagiaRect[5].x + magiaGanon->w < piso->w*12)
                                                        spriteMagiaRect[5].y = (pisoRect1[0][11].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[5].x + magiaGanon->w >= piso->w*12 && spriteMagiaRect[5].x + magiaGanon->w < piso->w*13)
                                                        spriteMagiaRect[5].y = (pisoRect1[0][12].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[5].x + magiaGanon->w >= piso->w*13 && spriteMagiaRect[5].x + magiaGanon->w < piso->w*14)
                                                        spriteMagiaRect[5].y = (pisoRect1[0][13].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[5].x + magiaGanon->w >= piso->w*14 && spriteMagiaRect[5].x + magiaGanon->w < piso->w*15)
                                                        spriteMagiaRect[5].y = (pisoRect1[0][14].y + 2) - magiaGanon->h;

                                                    //Voltando a Magia
                                                    if(spriteMagiaRect[5].x == 0){

                                                        pisoMagia[5] = 6;
                                                        spriteMagiaRect[5].x = pisoRect2[2][4].x + 45;
                                                        spriteMagiaRect[5].y = pisoRect2[2][4].y - magiaGanon->h;
                                                        magiaAtiva[5] = 1;

                                                    }

                                                }
                                            }
                                        //Magia 6
                                        if(tempoMagia > 1300){
                                            if(pisoMagia[6] == 6){

                                                if(spriteMagiaRect[6].x <= pisoRect2[2][13].x + piso->w)
                                                    spriteMagiaRect[6].x += magiaVel;
                                                //Ajustando piso 6
                                                if(spriteMagiaRect[6].x >= piso->w*10 && spriteMagiaRect[6].x < piso->w*11)
                                                    spriteMagiaRect[6].y = (pisoRect2[2][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*11 && spriteMagiaRect[6].x < piso->w*12)
                                                    spriteMagiaRect[6].y = (pisoRect2[2][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*12 && spriteMagiaRect[6].x < piso->w*13)
                                                    spriteMagiaRect[6].y = (pisoRect2[2][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[6].x == 589 && spriteMagiaRect[6].y <= pisoRect1[2][13].y - magiaGanon->h)
                                                    spriteMagiaRect[6].y += magiaVel;

                                                if(spriteMagiaRect[6].y == 145)
                                                    pisoMagia[6] = 5;


                                            }

                                            if(pisoMagia[6] == 5){

                                                if(spriteMagiaRect[6].x >= pisoRect1[2][0].x - (magiaGanon->w / 2))
                                                    spriteMagiaRect[6].x -= magiaVel;
                                                //Ajustando piso 5
                                                if(spriteMagiaRect[6].x >= piso->w && spriteMagiaRect[6].x < piso->w*2)
                                                    spriteMagiaRect[6].y = (pisoRect1[2][0].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*2 && spriteMagiaRect[6].x < piso->w*3)
                                                    spriteMagiaRect[6].y = (pisoRect1[2][1].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*3 && spriteMagiaRect[6].x < piso->w*4)
                                                    spriteMagiaRect[6].y = (pisoRect1[2][3].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*4 && spriteMagiaRect[6].x < piso->w*5)
                                                    spriteMagiaRect[6].y = (pisoRect1[2][4].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*5 && spriteMagiaRect[6].x < piso->w*6)
                                                    spriteMagiaRect[6].y = (pisoRect1[2][5].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*6 && spriteMagiaRect[6].x < piso->w*7)
                                                    spriteMagiaRect[6].y = (pisoRect1[2][6].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*7 && spriteMagiaRect[6].x < piso->w*8)
                                                    spriteMagiaRect[6].y = (pisoRect1[2][7].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*8 && spriteMagiaRect[6].x < piso->w*9)
                                                    spriteMagiaRect[6].y = (pisoRect1[2][8].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*9 && spriteMagiaRect[6].x < piso->w*10)
                                                    spriteMagiaRect[6].y = (pisoRect1[2][9].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*10 && spriteMagiaRect[6].x < piso->w*11)
                                                    spriteMagiaRect[6].y = (pisoRect1[2][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*11 && spriteMagiaRect[6].x < piso->w*12)
                                                    spriteMagiaRect[6].y = (pisoRect1[2][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*12 && spriteMagiaRect[6].x < piso->w*13)
                                                    spriteMagiaRect[6].y = (pisoRect1[2][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[6].x == 21 && spriteMagiaRect[6].y <= pisoRect2[1][0].y - magiaGanon->h)
                                                    spriteMagiaRect[6].y += magiaVel;

                                                if(spriteMagiaRect[6].y == 223)
                                                    pisoMagia[6] = 4;

                                            }

                                            if(pisoMagia[6] == 4){

                                                if(spriteMagiaRect[6].x <= pisoRect2[1][13].x + piso->w)
                                                    spriteMagiaRect[6].x += magiaVel;
                                                //Ajustando piso 4
                                                if(spriteMagiaRect[6].x >= 0 && spriteMagiaRect[6].x < piso->w)
                                                    spriteMagiaRect[6].y = (pisoRect2[1][0].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w && spriteMagiaRect[6].x < piso->w*2)
                                                    spriteMagiaRect[6].y = (pisoRect2[1][1].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*2 && spriteMagiaRect[6].x < piso->w*3)
                                                    spriteMagiaRect[6].y = (pisoRect2[1][2].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*3 && spriteMagiaRect[6].x < piso->w*4)
                                                    spriteMagiaRect[6].y = (pisoRect2[1][3].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*4 && spriteMagiaRect[6].x < piso->w*5)
                                                    spriteMagiaRect[6].y = (pisoRect2[1][4].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*5 && spriteMagiaRect[6].x < piso->w*6)
                                                    spriteMagiaRect[6].y = (pisoRect2[1][5].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*6 && spriteMagiaRect[6].x < piso->w*7)
                                                    spriteMagiaRect[6].y = (pisoRect2[1][6].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*7 && spriteMagiaRect[6].x < piso->w*8)
                                                    spriteMagiaRect[6].y = (pisoRect2[1][7].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*8 && spriteMagiaRect[6].x < piso->w*9)
                                                    spriteMagiaRect[6].y = (pisoRect2[1][8].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*9 && spriteMagiaRect[6].x < piso->w*10)
                                                    spriteMagiaRect[6].y = (pisoRect2[1][9].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*10 && spriteMagiaRect[6].x < piso->w*11)
                                                    spriteMagiaRect[6].y = (pisoRect2[1][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*11 && spriteMagiaRect[6].x < piso->w*12)
                                                    spriteMagiaRect[6].y = (pisoRect2[1][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*12 && spriteMagiaRect[6].x < piso->w*13)
                                                    spriteMagiaRect[6].y = (pisoRect2[1][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[6].x == 589 && spriteMagiaRect[6].y <= pisoRect1[1][13].y - magiaGanon->h)
                                                    spriteMagiaRect[6].y += magiaVel;

                                                if(spriteMagiaRect[6].y == 300)
                                                    pisoMagia[6] = 3;
                                            }

                                            if(pisoMagia[6] == 3){

                                                if(spriteMagiaRect[6].x >= pisoRect1[1][0].x - (magiaGanon->w / 2))
                                                    spriteMagiaRect[6].x -= magiaVel;
                                                //Ajustando piso 3
                                                if(spriteMagiaRect[6].x >= piso->w && spriteMagiaRect[6].x < piso->w*2)
                                                    spriteMagiaRect[6].y = (pisoRect1[1][0].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*2 && spriteMagiaRect[6].x < piso->w*3)
                                                    spriteMagiaRect[6].y = (pisoRect1[1][1].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*3 && spriteMagiaRect[6].x < piso->w*4)
                                                    spriteMagiaRect[6].y = (pisoRect1[1][3].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*4 && spriteMagiaRect[6].x < piso->w*5)
                                                    spriteMagiaRect[6].y = (pisoRect1[1][4].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*5 && spriteMagiaRect[6].x < piso->w*6)
                                                    spriteMagiaRect[6].y = (pisoRect1[1][5].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*6 && spriteMagiaRect[6].x < piso->w*7)
                                                    spriteMagiaRect[6].y = (pisoRect1[1][6].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*7 && spriteMagiaRect[6].x < piso->w*8)
                                                    spriteMagiaRect[6].y = (pisoRect1[1][7].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*8 && spriteMagiaRect[6].x < piso->w*9)
                                                    spriteMagiaRect[6].y = (pisoRect1[1][8].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*9 && spriteMagiaRect[6].x < piso->w*10)
                                                    spriteMagiaRect[6].y = (pisoRect1[1][9].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*10 && spriteMagiaRect[6].x < piso->w*11)
                                                    spriteMagiaRect[6].y = (pisoRect1[1][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*11 && spriteMagiaRect[6].x < piso->w*12)
                                                    spriteMagiaRect[6].y = (pisoRect1[1][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*12 && spriteMagiaRect[6].x < piso->w*13)
                                                    spriteMagiaRect[6].y = (pisoRect1[1][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[6].x == 21 && spriteMagiaRect[6].y <= pisoRect2[0][0].y - magiaGanon->h)
                                                    spriteMagiaRect[6].y += magiaVel;

                                                if(spriteMagiaRect[6].y == 376)
                                                    pisoMagia[6] = 2;

                                            }

                                            if(pisoMagia[6] == 2){

                                                if(spriteMagiaRect[6].x <= pisoRect2[0][13].x + piso->w)
                                                    spriteMagiaRect[6].x += magiaVel;
                                                //Ajustando piso 2
                                                if(spriteMagiaRect[6].x >= 0 && spriteMagiaRect[6].x < piso->w)
                                                    spriteMagiaRect[6].y = (pisoRect2[0][0].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w && spriteMagiaRect[6].x < piso->w*2)
                                                    spriteMagiaRect[6].y = (pisoRect2[0][1].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*2 && spriteMagiaRect[6].x < piso->w*3)
                                                    spriteMagiaRect[6].y = (pisoRect2[0][2].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*3 && spriteMagiaRect[6].x < piso->w*4)
                                                    spriteMagiaRect[6].y = (pisoRect2[0][3].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*4 && spriteMagiaRect[6].x < piso->w*5)
                                                    spriteMagiaRect[6].y = (pisoRect2[0][4].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*5 && spriteMagiaRect[6].x < piso->w*6)
                                                    spriteMagiaRect[6].y = (pisoRect2[0][5].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*6 && spriteMagiaRect[6].x < piso->w*7)
                                                    spriteMagiaRect[6].y = (pisoRect2[0][6].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*7 && spriteMagiaRect[6].x < piso->w*8)
                                                    spriteMagiaRect[6].y = (pisoRect2[0][7].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*8 && spriteMagiaRect[6].x < piso->w*9)
                                                    spriteMagiaRect[6].y = (pisoRect2[0][8].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*9 && spriteMagiaRect[6].x < piso->w*10)
                                                    spriteMagiaRect[6].y = (pisoRect2[0][9].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*10 && spriteMagiaRect[6].x < piso->w*11)
                                                    spriteMagiaRect[6].y = (pisoRect2[0][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*11 && spriteMagiaRect[6].x < piso->w*12)
                                                    spriteMagiaRect[6].y = (pisoRect2[0][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[6].x >= piso->w*12 && spriteMagiaRect[6].x < piso->w*13)
                                                    spriteMagiaRect[6].y = (pisoRect2[0][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[6].x == 589 && spriteMagiaRect[6].y <= pisoRect1[0][13].y - magiaGanon->h)
                                                    spriteMagiaRect[6].y += magiaVel;
                                                if(spriteMagiaRect[6].y == 450)
                                                    pisoMagia[6] = 1;

                                            }

                                            if(pisoMagia[6] == 1){

                                                    if(spriteMagiaRect[6].x > pisoRect1[0][0].x)
                                                    spriteMagiaRect[6].x -= magiaVel;
                                                    //Ajustando piso 1
                                                    if(spriteMagiaRect[6].x + magiaGanon->w < piso->w*7)
                                                        spriteMagiaRect[6].y = ((tela->h - piso->h)-magiaGanon->h)+2;
                                                    if(spriteMagiaRect[6].x + magiaGanon->w >= piso->w*7 && spriteMagiaRect[6].x + magiaGanon->w < piso->w*8)
                                                        spriteMagiaRect[6].y = (pisoRect1[0][7].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[6].x + magiaGanon->w >= piso->w*8 && spriteMagiaRect[6].x + magiaGanon->w < piso->w*9)
                                                        spriteMagiaRect[6].y = (pisoRect1[0][8].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[6].x + magiaGanon->w >= piso->w*9 && spriteMagiaRect[6].x + magiaGanon->w < piso->w*10)
                                                        spriteMagiaRect[6].y = (pisoRect1[0][9].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[6].x + magiaGanon->w >= piso->w*10 && spriteMagiaRect[6].x + magiaGanon->w < piso->w*11)
                                                        spriteMagiaRect[6].y = (pisoRect1[0][10].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[6].x + magiaGanon->w >= piso->w*11 && spriteMagiaRect[6].x + magiaGanon->w < piso->w*12)
                                                        spriteMagiaRect[6].y = (pisoRect1[0][11].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[6].x + magiaGanon->w >= piso->w*12 && spriteMagiaRect[6].x + magiaGanon->w < piso->w*13)
                                                        spriteMagiaRect[6].y = (pisoRect1[0][12].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[6].x + magiaGanon->w >= piso->w*13 && spriteMagiaRect[6].x + magiaGanon->w < piso->w*14)
                                                        spriteMagiaRect[6].y = (pisoRect1[0][13].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[6].x + magiaGanon->w >= piso->w*14 && spriteMagiaRect[6].x + magiaGanon->w < piso->w*15)
                                                        spriteMagiaRect[6].y = (pisoRect1[0][14].y + 2) - magiaGanon->h;

                                                    //Voltando a Magia
                                                    if(spriteMagiaRect[6].x == 0){

                                                        pisoMagia[6] = 6;
                                                        spriteMagiaRect[6].x = pisoRect2[2][4].x + 45;
                                                        spriteMagiaRect[6].y = pisoRect2[2][4].y - magiaGanon->h;
                                                        magiaAtiva[6] = 1;

                                                    }

                                                }
                                            }
                                        //Magia 7
                                        if(tempoMagia > 1500){
                                            if(pisoMagia[7] == 6){

                                                if(spriteMagiaRect[7].x <= pisoRect2[2][13].x + piso->w)
                                                    spriteMagiaRect[7].x += magiaVel;
                                                //Ajustando piso 6
                                                if(spriteMagiaRect[7].x >= piso->w*10 && spriteMagiaRect[7].x < piso->w*11)
                                                    spriteMagiaRect[7].y = (pisoRect2[2][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*11 && spriteMagiaRect[7].x < piso->w*12)
                                                    spriteMagiaRect[7].y = (pisoRect2[2][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*12 && spriteMagiaRect[7].x < piso->w*13)
                                                    spriteMagiaRect[7].y = (pisoRect2[2][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[7].x == 589 && spriteMagiaRect[7].y <= pisoRect1[2][13].y - magiaGanon->h)
                                                    spriteMagiaRect[7].y += magiaVel;

                                                if(spriteMagiaRect[7].y == 145)
                                                    pisoMagia[7] = 5;


                                            }

                                            if(pisoMagia[7] == 5){

                                                if(spriteMagiaRect[7].x >= pisoRect1[2][0].x - (magiaGanon->w / 2))
                                                    spriteMagiaRect[7].x -= magiaVel;
                                                //Ajustando piso 5
                                                if(spriteMagiaRect[7].x >= piso->w && spriteMagiaRect[7].x < piso->w*2)
                                                    spriteMagiaRect[7].y = (pisoRect1[2][0].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*2 && spriteMagiaRect[7].x < piso->w*3)
                                                    spriteMagiaRect[7].y = (pisoRect1[2][1].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*3 && spriteMagiaRect[7].x < piso->w*4)
                                                    spriteMagiaRect[7].y = (pisoRect1[2][3].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*4 && spriteMagiaRect[7].x < piso->w*5)
                                                    spriteMagiaRect[7].y = (pisoRect1[2][4].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*5 && spriteMagiaRect[7].x < piso->w*6)
                                                    spriteMagiaRect[7].y = (pisoRect1[2][5].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*6 && spriteMagiaRect[7].x < piso->w*7)
                                                    spriteMagiaRect[7].y = (pisoRect1[2][6].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*7 && spriteMagiaRect[7].x < piso->w*8)
                                                    spriteMagiaRect[7].y = (pisoRect1[2][7].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*8 && spriteMagiaRect[7].x < piso->w*9)
                                                    spriteMagiaRect[7].y = (pisoRect1[2][8].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*9 && spriteMagiaRect[7].x < piso->w*10)
                                                    spriteMagiaRect[7].y = (pisoRect1[2][9].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*10 && spriteMagiaRect[7].x < piso->w*11)
                                                    spriteMagiaRect[7].y = (pisoRect1[2][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*11 && spriteMagiaRect[7].x < piso->w*12)
                                                    spriteMagiaRect[7].y = (pisoRect1[2][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*12 && spriteMagiaRect[7].x < piso->w*13)
                                                    spriteMagiaRect[7].y = (pisoRect1[2][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[7].x == 21 && spriteMagiaRect[7].y <= pisoRect2[1][0].y - magiaGanon->h)
                                                    spriteMagiaRect[7].y += magiaVel;

                                                if(spriteMagiaRect[7].y == 223)
                                                    pisoMagia[7] = 4;

                                            }

                                            if(pisoMagia[7] == 4){

                                                if(spriteMagiaRect[7].x <= pisoRect2[1][13].x + piso->w)
                                                    spriteMagiaRect[7].x += magiaVel;
                                                //Ajustando piso 4
                                                if(spriteMagiaRect[7].x >= 0 && spriteMagiaRect[7].x < piso->w)
                                                    spriteMagiaRect[7].y = (pisoRect2[1][0].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w && spriteMagiaRect[7].x < piso->w*2)
                                                    spriteMagiaRect[7].y = (pisoRect2[1][1].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*2 && spriteMagiaRect[7].x < piso->w*3)
                                                    spriteMagiaRect[7].y = (pisoRect2[1][2].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*3 && spriteMagiaRect[7].x < piso->w*4)
                                                    spriteMagiaRect[7].y = (pisoRect2[1][3].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*4 && spriteMagiaRect[7].x < piso->w*5)
                                                    spriteMagiaRect[7].y = (pisoRect2[1][4].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*5 && spriteMagiaRect[7].x < piso->w*6)
                                                    spriteMagiaRect[7].y = (pisoRect2[1][5].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*6 && spriteMagiaRect[7].x < piso->w*7)
                                                    spriteMagiaRect[7].y = (pisoRect2[1][6].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*7 && spriteMagiaRect[7].x < piso->w*8)
                                                    spriteMagiaRect[7].y = (pisoRect2[1][7].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*8 && spriteMagiaRect[7].x < piso->w*9)
                                                    spriteMagiaRect[7].y = (pisoRect2[1][8].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*9 && spriteMagiaRect[7].x < piso->w*10)
                                                    spriteMagiaRect[7].y = (pisoRect2[1][9].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*10 && spriteMagiaRect[7].x < piso->w*11)
                                                    spriteMagiaRect[7].y = (pisoRect2[1][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*11 && spriteMagiaRect[7].x < piso->w*12)
                                                    spriteMagiaRect[7].y = (pisoRect2[1][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*12 && spriteMagiaRect[7].x < piso->w*13)
                                                    spriteMagiaRect[7].y = (pisoRect2[1][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[7].x == 589 && spriteMagiaRect[7].y <= pisoRect1[1][13].y - magiaGanon->h)
                                                    spriteMagiaRect[7].y += magiaVel;

                                                if(spriteMagiaRect[7].y == 300)
                                                    pisoMagia[7] = 3;
                                            }

                                            if(pisoMagia[7] == 3){

                                                if(spriteMagiaRect[7].x >= pisoRect1[1][0].x - (magiaGanon->w / 2))
                                                    spriteMagiaRect[7].x -= magiaVel;
                                                //Ajustando piso 3
                                                if(spriteMagiaRect[7].x >= piso->w && spriteMagiaRect[7].x < piso->w*2)
                                                    spriteMagiaRect[7].y = (pisoRect1[1][0].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*2 && spriteMagiaRect[7].x < piso->w*3)
                                                    spriteMagiaRect[7].y = (pisoRect1[1][1].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*3 && spriteMagiaRect[7].x < piso->w*4)
                                                    spriteMagiaRect[7].y = (pisoRect1[1][3].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*4 && spriteMagiaRect[7].x < piso->w*5)
                                                    spriteMagiaRect[7].y = (pisoRect1[1][4].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*5 && spriteMagiaRect[7].x < piso->w*6)
                                                    spriteMagiaRect[7].y = (pisoRect1[1][5].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*6 && spriteMagiaRect[7].x < piso->w*7)
                                                    spriteMagiaRect[7].y = (pisoRect1[1][6].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*7 && spriteMagiaRect[7].x < piso->w*8)
                                                    spriteMagiaRect[7].y = (pisoRect1[1][7].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*8 && spriteMagiaRect[7].x < piso->w*9)
                                                    spriteMagiaRect[7].y = (pisoRect1[1][8].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*9 && spriteMagiaRect[7].x < piso->w*10)
                                                    spriteMagiaRect[7].y = (pisoRect1[1][9].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*10 && spriteMagiaRect[7].x < piso->w*11)
                                                    spriteMagiaRect[7].y = (pisoRect1[1][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*11 && spriteMagiaRect[7].x < piso->w*12)
                                                    spriteMagiaRect[7].y = (pisoRect1[1][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*12 && spriteMagiaRect[7].x < piso->w*13)
                                                    spriteMagiaRect[7].y = (pisoRect1[1][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[7].x == 21 && spriteMagiaRect[7].y <= pisoRect2[0][0].y - magiaGanon->h)
                                                    spriteMagiaRect[7].y += magiaVel;

                                                if(spriteMagiaRect[7].y == 376)
                                                    pisoMagia[7] = 2;

                                            }

                                            if(pisoMagia[7] == 2){

                                                if(spriteMagiaRect[7].x <= pisoRect2[0][13].x + piso->w)
                                                    spriteMagiaRect[7].x += magiaVel;
                                                //Ajustando piso 2
                                                if(spriteMagiaRect[7].x >= 0 && spriteMagiaRect[7].x < piso->w)
                                                    spriteMagiaRect[7].y = (pisoRect2[0][0].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w && spriteMagiaRect[7].x < piso->w*2)
                                                    spriteMagiaRect[7].y = (pisoRect2[0][1].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*2 && spriteMagiaRect[7].x < piso->w*3)
                                                    spriteMagiaRect[7].y = (pisoRect2[0][2].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*3 && spriteMagiaRect[7].x < piso->w*4)
                                                    spriteMagiaRect[7].y = (pisoRect2[0][3].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*4 && spriteMagiaRect[7].x < piso->w*5)
                                                    spriteMagiaRect[7].y = (pisoRect2[0][4].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*5 && spriteMagiaRect[7].x < piso->w*6)
                                                    spriteMagiaRect[7].y = (pisoRect2[0][5].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*6 && spriteMagiaRect[7].x < piso->w*7)
                                                    spriteMagiaRect[7].y = (pisoRect2[0][6].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*7 && spriteMagiaRect[7].x < piso->w*8)
                                                    spriteMagiaRect[7].y = (pisoRect2[0][7].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*8 && spriteMagiaRect[7].x < piso->w*9)
                                                    spriteMagiaRect[7].y = (pisoRect2[0][8].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*9 && spriteMagiaRect[7].x < piso->w*10)
                                                    spriteMagiaRect[7].y = (pisoRect2[0][9].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*10 && spriteMagiaRect[7].x < piso->w*11)
                                                    spriteMagiaRect[7].y = (pisoRect2[0][10].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*11 && spriteMagiaRect[7].x < piso->w*12)
                                                    spriteMagiaRect[7].y = (pisoRect2[0][11].y - magiaGanon->h) + 2;
                                                if(spriteMagiaRect[7].x >= piso->w*12 && spriteMagiaRect[7].x < piso->w*13)
                                                    spriteMagiaRect[7].y = (pisoRect2[0][12].y - magiaGanon->h) + 2;

                                                if(spriteMagiaRect[7].x == 589 && spriteMagiaRect[7].y <= pisoRect1[0][13].y - magiaGanon->h)
                                                    spriteMagiaRect[7].y += magiaVel;
                                                if(spriteMagiaRect[7].y == 450)
                                                    pisoMagia[7] = 1;

                                            }

                                            if(pisoMagia[7] == 1){

                                                    if(spriteMagiaRect[7].x > pisoRect1[0][0].x)
                                                    spriteMagiaRect[7].x -= magiaVel;
                                                    //Ajustando piso 1
                                                    if(spriteMagiaRect[7].x + magiaGanon->w < piso->w*7)
                                                        spriteMagiaRect[7].y = ((tela->h - piso->h)-magiaGanon->h)+2;
                                                    if(spriteMagiaRect[7].x + magiaGanon->w >= piso->w*7 && spriteMagiaRect[7].x + magiaGanon->w < piso->w*8)
                                                        spriteMagiaRect[7].y = (pisoRect1[0][7].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[7].x + magiaGanon->w >= piso->w*8 && spriteMagiaRect[7].x + magiaGanon->w < piso->w*9)
                                                        spriteMagiaRect[7].y = (pisoRect1[0][8].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[7].x + magiaGanon->w >= piso->w*9 && spriteMagiaRect[7].x + magiaGanon->w < piso->w*10)
                                                        spriteMagiaRect[7].y = (pisoRect1[0][9].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[7].x + magiaGanon->w >= piso->w*10 && spriteMagiaRect[7].x + magiaGanon->w < piso->w*11)
                                                        spriteMagiaRect[7].y = (pisoRect1[0][10].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[7].x + magiaGanon->w >= piso->w*11 && spriteMagiaRect[7].x + magiaGanon->w < piso->w*12)
                                                        spriteMagiaRect[7].y = (pisoRect1[0][11].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[7].x + magiaGanon->w >= piso->w*12 && spriteMagiaRect[7].x + magiaGanon->w < piso->w*13)
                                                        spriteMagiaRect[7].y = (pisoRect1[0][12].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[7].x + magiaGanon->w >= piso->w*13 && spriteMagiaRect[7].x + magiaGanon->w < piso->w*14)
                                                        spriteMagiaRect[7].y = (pisoRect1[0][13].y + 2) - magiaGanon->h;
                                                    if(spriteMagiaRect[7].x + magiaGanon->w >= piso->w*14 && spriteMagiaRect[7].x + magiaGanon->w < piso->w*15)
                                                        spriteMagiaRect[7].y = (pisoRect1[0][14].y + 2) - magiaGanon->h;

                                                    //Voltando a Magia
                                                    if(spriteMagiaRect[7].x == 0){

                                                        pisoMagia[7] = 6;
                                                        spriteMagiaRect[7].x = pisoRect2[2][4].x + 45;
                                                        spriteMagiaRect[7].y = pisoRect2[2][4].y - magiaGanon->h;
                                                        magiaAtiva[7] = 1;

                                                    }

                                                }
                                            }

                                        //Verifica Se Ganhou e entra no loop
                                        if(ganhou){

                                            quitTelaVenceu = 0;
                                            Mix_HaltMusic();

                                            if(Mix_PlayingMusic() == 0){
                                            //Play the music
                                                if( Mix_PlayMusic(VenceuMusic, -1) == -1 ){
                                                    return 1;
                                                }
                                            }

                                            tempoEntrada = 0;
                                            while(tempoEntrada<100)
                                                tempoEntrada++;
                                            tempoEntrada = 0;


                                            char nome[4] = {' ',' ',' ','\0'};
                                            char p[7];

                                            sprintf(p,"%d",score);

                                            i = -1;
                                            surfaceAtual = venceu;
                                            link.rectSRC.x = piso->w - link.surface->w;
                                            link.rectSRC.y = ((tela->h - piso->h)-link.surface->h)+4;
                                            vidas = 3;

                                            while(!quitTelaVenceu){

                                                    while(SDL_PollEvent(&event)){

                                                        switch(event.type){
                                                                //caso escolha sair (x) termina a execuçao
                                                                case SDL_QUIT:
                                                                    SDL_Quit();
                                                                    TTF_Quit();
                                                                    Mix_Quit();

                                                                    return 0;
                                                                    break;

                                                                case SDL_KEYDOWN:
                                                                    switch(event.key.keysym.sym){

                                                                        case SDLK_a:
                                                                            if(i == 2){
                                                                                nome[i] = 'A';

                                                                            }
                                                                            else{

                                                                                i++;
                                                                                nome[i] = 'A';

                                                                            }

                                                                            break;

                                                                        case SDLK_b:
                                                                            if(i == 2){
                                                                                nome[i] = 'B';

                                                                            }
                                                                            else{

                                                                                i++;
                                                                                nome[i] = 'B';

                                                                            }

                                                                            break;

                                                                        case SDLK_c:
                                                                            if(i == 2){
                                                                                nome[i] = 'C';

                                                                            }
                                                                            else{

                                                                                i++;
                                                                                nome[i] = 'C';

                                                                            }

                                                                            break;

                                                                        case SDLK_d:
                                                                            if(i == 2){
                                                                                nome[i] = 'D';

                                                                            }
                                                                            else{

                                                                                i++;
                                                                                nome[i] = 'D';

                                                                            }

                                                                            break;

                                                                        case SDLK_e:
                                                                            if(i == 2){
                                                                                nome[i] = 'E';

                                                                            }
                                                                            else{

                                                                                i++;
                                                                                nome[i] = 'E';

                                                                            }

                                                                            break;

                                                                        case SDLK_f:
                                                                            if(i == 2){
                                                                                nome[i] = 'F';

                                                                            }
                                                                            else{

                                                                                i++;
                                                                                nome[i] = 'F';

                                                                            }

                                                                            break;

                                                                        case SDLK_g:
                                                                            if(i == 2){
                                                                                nome[i] = 'G';

                                                                            }
                                                                            else{

                                                                                i++;
                                                                                nome[i] = 'G';

                                                                            }

                                                                            break;

                                                                        case SDLK_h:

                                                                            if(i == 2){
                                                                                nome[i] = 'H';
                                                                            }
                                                                            else{

                                                                                i++;
                                                                                nome[i] = 'H';

                                                                            }

                                                                            break;

                                                                        case SDLK_i:
                                                                            if(i == 2){
                                                                                nome[i] = 'I';

                                                                            }
                                                                            else{

                                                                                i++;
                                                                                nome[i] = 'I';

                                                                            }

                                                                            break;

                                                                        case SDLK_j:
                                                                            if(i == 2){
                                                                                nome[i] = 'J';

                                                                            }
                                                                            else{

                                                                                i++;
                                                                                nome[i] = 'J';

                                                                            }

                                                                            break;

                                                                        case SDLK_k:
                                                                            if(i == 2){
                                                                                nome[i] = 'K';

                                                                            }
                                                                            else{

                                                                                i++;
                                                                                nome[i] = 'K';

                                                                            }

                                                                            break;

                                                                        case SDLK_l:
                                                                            if(i == 2){
                                                                                nome[i] = 'L';

                                                                            }
                                                                            else{

                                                                                i++;
                                                                                nome[i] = 'L';

                                                                            }

                                                                            break;

                                                                        case SDLK_m:
                                                                            if(i == 2){
                                                                                nome[i] = 'M';

                                                                            }
                                                                            else{

                                                                                i++;
                                                                                nome[i] = 'M';

                                                                            }

                                                                            break;

                                                                        case SDLK_n:
                                                                            if(i == 2){
                                                                                nome[i] = 'N';

                                                                            }
                                                                            else{

                                                                                i++;
                                                                                nome[i] = 'N';

                                                                            }

                                                                            break;

                                                                        case SDLK_o:
                                                                            if(i == 2){
                                                                                nome[i] = 'O';

                                                                            }
                                                                            else{

                                                                                i++;
                                                                                nome[i] = 'O';

                                                                            }

                                                                            break;

                                                                        case SDLK_p:
                                                                            if(i == 2){
                                                                                nome[i] = 'P';

                                                                            }
                                                                            else{

                                                                                i++;
                                                                                nome[i] = 'P';

                                                                            }

                                                                            break;

                                                                        case SDLK_q:
                                                                            if(i == 2){
                                                                                nome[i] = 'Q';

                                                                            }
                                                                            else{

                                                                                i++;
                                                                                nome[i] = 'Q';

                                                                            }

                                                                            break;

                                                                        case SDLK_r:
                                                                            if(i == 2){
                                                                                nome[i] = 'R';

                                                                            }
                                                                            else{

                                                                                i++;
                                                                                nome[i] = 'R';

                                                                            }

                                                                            break;

                                                                        case SDLK_s:
                                                                            if(i == 2){
                                                                                nome[i] = 'S';

                                                                            }
                                                                            else{

                                                                                i++;
                                                                                nome[i] = 'S';

                                                                            }

                                                                            break;

                                                                        case SDLK_t:
                                                                            if(i == 2){
                                                                                nome[i] = 'T';

                                                                            }
                                                                            else{

                                                                                i++;
                                                                                nome[i] = 'T';

                                                                            }

                                                                            break;

                                                                        case SDLK_u:
                                                                            if(i == 2){
                                                                                nome[i] = 'U';

                                                                            }
                                                                            else{

                                                                                i++;
                                                                                nome[i] = 'U';

                                                                            }

                                                                            break;

                                                                        case SDLK_v:
                                                                            if(i == 2){
                                                                                nome[i] = 'V';

                                                                            }
                                                                            else{

                                                                                i++;
                                                                                nome[i] = 'V';

                                                                            }

                                                                            break;

                                                                        case SDLK_w:
                                                                            if(i == 2){
                                                                                nome[i] = 'W';

                                                                            }
                                                                            else{

                                                                                i++;
                                                                                nome[i] = 'W';

                                                                            }

                                                                            break;

                                                                        case SDLK_x:
                                                                            if(i == 2){
                                                                                nome[i] = 'X';

                                                                            }
                                                                            else{

                                                                                i++;
                                                                                nome[i] = 'X';

                                                                            }

                                                                            break;

                                                                        case SDLK_y:
                                                                            if(i == 2){
                                                                                nome[i] = 'Y';

                                                                            }
                                                                            else{

                                                                                i++;
                                                                                nome[i] = 'Y';

                                                                            }

                                                                            break;

                                                                        case SDLK_z:
                                                                            if(i == 2){
                                                                                nome[i] = 'Z';

                                                                            }
                                                                            else{

                                                                                i++;
                                                                                nome[i] = 'Z';

                                                                            }

                                                                            break;




                                                                        case SDLK_BACKSPACE:

                                                                            if(i == -1){
                                                                                i = -1;
                                                                            }
                                                                            else{
                                                                                nome[i] = ' ';
                                                                                i--;
                                                                            }

                                                                            break;

                                                                        default:
                                                                            break;

                                                                    }
                                                                    break;

                                                                case SDL_MOUSEMOTION:

                                                                    if((event.motion.x > btMenu.x && event.motion.x < btMenu.x + btMenu.w) && (event.motion.y > btJogarNov.y && event.motion.y < btMenu.y + btMenu.h)){

                                                                        surfaceAtual = venceu2;

                                                                    }

                                                                    else
                                                                        surfaceAtual = venceu;
                                                                    break;

                                                                case SDL_MOUSEBUTTONDOWN:

                                                                    if(event.button.button == SDL_BUTTON_LEFT){ //Botão Jogar Novamente

                                                                        if((event.motion.x > btMenu.x && event.motion.x < btMenu.x + btMenu.w) && (event.motion.y > btMenu.y && event.motion.y < btMenu.y + btMenu.h) && i == 2){
                                                                        //Botao Menu
                                                                            tempoEntrada = 0;

                                                                            Mix_PlayChannel( -1, SelecaoMusic, 0 );

                                                                            sco = fopen("score.txt","w+");

                                                                            fscanf(sco,"%d %s",&primeiroLugar.pontos,primeiroLugar.nome);
                                                                            fscanf(sco,"%d %s",&segundoLugar.pontos,segundoLugar.nome);
                                                                            fscanf(sco,"%d %s",&terceiroLugar.pontos,terceiroLugar.nome);

                                                                            if(score > primeiroLugar.pontos){

                                                                                fprintf(sco,"%d %s\n",score,nome);
                                                                                fprintf(sco,"%d %s\n",primeiroLugar.pontos,primeiroLugar.nome);
                                                                                fprintf(sco,"%d %s",segundoLugar.pontos,segundoLugar.nome);

                                                                            }
                                                                            else if(score > segundoLugar.pontos){

                                                                                fprintf(sco,"%d %s\n",primeiroLugar.pontos,primeiroLugar.nome);
                                                                                fprintf(sco,"%d %s\n",score,nome);
                                                                                fprintf(sco,"%d %s",segundoLugar.pontos,segundoLugar.nome);

                                                                            }
                                                                            else if(score > terceiroLugar.pontos){

                                                                                fprintf(sco,"%d %s\n",primeiroLugar.pontos,primeiroLugar.nome);
                                                                                fprintf(sco,"%d %s\n",segundoLugar.pontos,segundoLugar.nome);
                                                                                fprintf(sco,"%d %s\n",score,nome);

                                                                            }

                                                                            fclose(sco);
                                                                            score = 0;
                                                                            while(tempoEntrada < 6){

                                                                                SDL_BlitSurface(venceu,NULL,tela,&entradaRect);
                                                                                SDL_BlitSurface(message,NULL,tela,&nomeRect);
                                                                                SDL_BlitSurface(message2,NULL,tela,&pontoRect);
                                                                                SDL_Flip(tela);
                                                                                SDL_Delay(10);
                                                                                SDL_BlitSurface(venceu1,NULL,tela,&entradaRect);
                                                                                SDL_BlitSurface(message,NULL,tela,&nomeRect);
                                                                                SDL_BlitSurface(message2,NULL,tela,&pontoRect);
                                                                                SDL_Flip(tela);

                                                                                SDL_FillRect(tela, 0, SDL_MapRGB(tela->format,0,0,0)); //Limpar a tela.
                                                                                tempoEntrada++;

                                                                            }

                                                                            surfaceAtual = menu;
                                                                            Mix_HaltMusic();
                                                                            quitTelaVenceu = 1;
                                                                            quit = 1;
                                                                            ganhou = 0;
                                                                            pegouEspada = 0;
                                                                            vidas = 3;
                                                                            for(int l = 0;l < 8;l++){

                                                                                pisoMagia[l] = 6;
                                                                                magiaAtiva[l] = 0;

                                                                            }
                                                                            pisoAtual = 1;

                                                                        }

                                                                    }
                                                                    break;

                                                        }

                                                    }

                                                    message = TTF_RenderText_Solid(font, nome, corTexto);
                                                    message2 = TTF_RenderText_Solid(font, p, corTexto);

                                                    SDL_FillRect(tela, 0, SDL_MapRGB(tela->format,0,0,0)); //Limpar a tela.

                                                    SDL_BlitSurface(surfaceAtual,NULL,tela,&entradaRect);
                                                    SDL_BlitSurface(message,NULL,tela,&nomeRect);
                                                    SDL_BlitSurface(message2,NULL,tela,&pontoRect);

                                                    SDL_Flip(tela);


                                            }



                                        }

                                        if(!pegouEspada){

                                            if(colisao(link.rectSRC,spriteMagiaRect[0]) || colisao(link.rectSRC,spriteMagiaRect[1])
                                            || colisao(link.rectSRC,spriteMagiaRect[2]) || colisao(link.rectSRC,spriteMagiaRect[3])
                                            || colisao(link.rectSRC,spriteMagiaRect[4]) || colisao(link.rectSRC,spriteMagiaRect[5])
                                            || colisao(link.rectSRC,spriteMagiaRect[6]) || colisao(link.rectSRC,spriteMagiaRect[7])
                                            || colisao(link.rectSRC,ganondorf.rectSRC)){

                                                        vidas--;

                                                        pisoMagia[0] = 6;
                                                        pisoMagia[1] = 6;
                                                        pisoMagia[2] = 6;
                                                        pisoMagia[3] = 6;
                                                        pisoMagia[4] = 6;
                                                        pisoMagia[5] = 6;
                                                        pisoMagia[6] = 6;
                                                        pisoMagia[7] = 6;

                                                        spriteMagiaRect[0].x = pisoRect2[2][4].x + 45;
                                                        spriteMagiaRect[0].y = pisoRect2[2][4].y - magiaGanon->h;
                                                        spriteMagiaRect[1].x = pisoRect2[2][4].x + 45;
                                                        spriteMagiaRect[1].y = pisoRect2[2][4].y - magiaGanon->h;
                                                        spriteMagiaRect[2].x = pisoRect2[2][4].x + 45;
                                                        spriteMagiaRect[2].y = pisoRect2[2][4].y - magiaGanon->h;
                                                        spriteMagiaRect[3].x = pisoRect2[2][4].x + 45;
                                                        spriteMagiaRect[3].y = pisoRect2[2][4].y - magiaGanon->h;
                                                        spriteMagiaRect[4].x = pisoRect2[2][4].x + 45;
                                                        spriteMagiaRect[4].y = pisoRect2[2][4].y - magiaGanon->h;
                                                        spriteMagiaRect[5].x = pisoRect2[2][4].x + 45;
                                                        spriteMagiaRect[5].y = pisoRect2[2][4].y - magiaGanon->h;
                                                        spriteMagiaRect[6].x = pisoRect2[2][4].x + 45;
                                                        spriteMagiaRect[6].y = pisoRect2[2][4].y - magiaGanon->h;
                                                        spriteMagiaRect[7].x = pisoRect2[2][4].x + 45;
                                                        spriteMagiaRect[7].y = pisoRect2[2][4].y - magiaGanon->h;

                                                        link.rectSRC.x = piso->w - link.surface->w;
                                                        link.rectSRC.y = ((tela->h - piso->h)-link.surface->h)+4;

                                                        pisoAtual = 1;
                                                        naEscada = 0;
                                                        tempoMagia = 51;

                                            }

                                        }
                                        else{

                                            if(colisao(giroEspadaRect,spriteMagiaRect[0]) && magiaAtiva[0] == 1){
                                                magiaAtiva[0] = 0;
                                                score += 200;

                                            }
                                            if(colisao(giroEspadaRect,spriteMagiaRect[1]) && magiaAtiva[1] == 1){
                                                magiaAtiva[1] = 0;
                                                score += 200;

                                            }
                                            if(colisao(giroEspadaRect,spriteMagiaRect[2]) && magiaAtiva[2] == 1){
                                                magiaAtiva[2] = 0;
                                                score += 200;

                                            }
                                            if(colisao(giroEspadaRect,spriteMagiaRect[3]) && magiaAtiva[3] == 1){
                                                magiaAtiva[3] = 0;
                                                score += 200;

                                            }
                                            if(colisao(giroEspadaRect,spriteMagiaRect[4]) && magiaAtiva[4] == 1){
                                                magiaAtiva[4] = 0;
                                                score += 200;

                                            }
                                            if(colisao(giroEspadaRect,spriteMagiaRect[5]) && magiaAtiva[5] == 1){
                                                magiaAtiva[5] = 0;
                                                score += 200;

                                            }
                                            if(colisao(giroEspadaRect,spriteMagiaRect[6]) && magiaAtiva[6] == 1){
                                                magiaAtiva[6] = 0;
                                                score += 200;

                                            }
                                            if(colisao(giroEspadaRect,spriteMagiaRect[7]) && magiaAtiva[7] == 1){
                                                magiaAtiva[7] = 0;
                                                score += 200;

                                            }


                                            if(colisao(giroEspadaRect,ganondorf.rectSRC)){

                                                ganhou = 1;



                                            }




                                        }




                                        if(vidas == 0){

                                            quitTelaGameOver = 0;
                                            Mix_HaltMusic();

                                            if(Mix_PlayingMusic() == 0){
                                            //Play the music
                                                if( Mix_PlayMusic(GameOverMusic, -1) == -1 ){
                                                    return 1;
                                                }
                                            }

                                            char nome[4] = {' ',' ',' ','\0'};

                                            char p[7];

                                            sprintf(p,"%d",score);

                                            i = -1;

                                            surfaceAtual = gameOver;

                                            while(!quitTelaGameOver){

                                                while(SDL_PollEvent(&event)){

                                                    switch(event.type){
                                                            //caso escolha sair (x) termina a execuçao
                                                            case SDL_QUIT:
                                                                SDL_Quit();
                                                                TTF_Quit();
                                                                Mix_Quit();
                                                                return 0;
                                                                break;

                                                            case SDL_KEYDOWN:
                                                                switch(event.key.keysym.sym){

                                                                    case SDLK_a:
                                                                        if(i == 2){
                                                                            nome[i] = 'A';

                                                                        }
                                                                        else{

                                                                            i++;
                                                                            nome[i] = 'A';

                                                                        }

                                                                        break;

                                                                    case SDLK_b:
                                                                        if(i == 2){
                                                                            nome[i] = 'B';

                                                                        }
                                                                        else{

                                                                            i++;
                                                                            nome[i] = 'B';

                                                                        }

                                                                        break;

                                                                    case SDLK_c:
                                                                        if(i == 2){
                                                                            nome[i] = 'C';

                                                                        }
                                                                        else{

                                                                            i++;
                                                                            nome[i] = 'C';

                                                                        }

                                                                        break;

                                                                    case SDLK_d:
                                                                        if(i == 2){
                                                                            nome[i] = 'D';

                                                                        }
                                                                        else{

                                                                            i++;
                                                                            nome[i] = 'D';

                                                                        }

                                                                        break;

                                                                    case SDLK_e:
                                                                        if(i == 2){
                                                                            nome[i] = 'E';

                                                                        }
                                                                        else{

                                                                            i++;
                                                                            nome[i] = 'E';

                                                                        }

                                                                        break;

                                                                    case SDLK_f:
                                                                        if(i == 2){
                                                                            nome[i] = 'F';

                                                                        }
                                                                        else{

                                                                            i++;
                                                                            nome[i] = 'F';

                                                                        }

                                                                        break;

                                                                    case SDLK_g:
                                                                        if(i == 2){
                                                                            nome[i] = 'G';

                                                                        }
                                                                        else{

                                                                            i++;
                                                                            nome[i] = 'G';

                                                                        }

                                                                        break;

                                                                    case SDLK_h:

                                                                        if(i == 2){
                                                                            nome[i] = 'H';
                                                                        }
                                                                        else{

                                                                            i++;
                                                                            nome[i] = 'H';

                                                                        }

                                                                        break;

                                                                    case SDLK_i:
                                                                        if(i == 2){
                                                                            nome[i] = 'I';

                                                                        }
                                                                        else{

                                                                            i++;
                                                                            nome[i] = 'I';

                                                                        }

                                                                        break;

                                                                    case SDLK_j:
                                                                        if(i == 2){
                                                                            nome[i] = 'J';

                                                                        }
                                                                        else{

                                                                            i++;
                                                                            nome[i] = 'J';

                                                                        }

                                                                        break;

                                                                    case SDLK_k:
                                                                        if(i == 2){
                                                                            nome[i] = 'K';

                                                                        }
                                                                        else{

                                                                            i++;
                                                                            nome[i] = 'K';

                                                                        }

                                                                        break;

                                                                    case SDLK_l:
                                                                        if(i == 2){
                                                                            nome[i] = 'L';

                                                                        }
                                                                        else{

                                                                            i++;
                                                                            nome[i] = 'L';

                                                                        }

                                                                        break;

                                                                    case SDLK_m:
                                                                        if(i == 2){
                                                                            nome[i] = 'M';

                                                                        }
                                                                        else{

                                                                            i++;
                                                                            nome[i] = 'M';

                                                                        }

                                                                        break;

                                                                    case SDLK_n:
                                                                        if(i == 2){
                                                                            nome[i] = 'N';

                                                                        }
                                                                        else{

                                                                            i++;
                                                                            nome[i] = 'N';

                                                                        }

                                                                        break;

                                                                    case SDLK_o:
                                                                        if(i == 2){
                                                                            nome[i] = 'O';

                                                                        }
                                                                        else{

                                                                            i++;
                                                                            nome[i] = 'O';

                                                                        }

                                                                        break;

                                                                    case SDLK_p:
                                                                        if(i == 2){
                                                                            nome[i] = 'P';

                                                                        }
                                                                        else{

                                                                            i++;
                                                                            nome[i] = 'P';

                                                                        }

                                                                        break;

                                                                    case SDLK_q:
                                                                        if(i == 2){
                                                                            nome[i] = 'Q';

                                                                        }
                                                                        else{

                                                                            i++;
                                                                            nome[i] = 'Q';

                                                                        }

                                                                        break;

                                                                    case SDLK_r:
                                                                        if(i == 2){
                                                                            nome[i] = 'R';

                                                                        }
                                                                        else{

                                                                            i++;
                                                                            nome[i] = 'R';

                                                                        }

                                                                        break;

                                                                    case SDLK_s:
                                                                        if(i == 2){
                                                                            nome[i] = 'S';

                                                                        }
                                                                        else{

                                                                            i++;
                                                                            nome[i] = 'S';

                                                                        }

                                                                        break;

                                                                    case SDLK_t:
                                                                        if(i == 2){
                                                                            nome[i] = 'T';

                                                                        }
                                                                        else{

                                                                            i++;
                                                                            nome[i] = 'T';

                                                                        }

                                                                        break;

                                                                    case SDLK_u:
                                                                        if(i == 2){
                                                                            nome[i] = 'U';

                                                                        }
                                                                        else{

                                                                            i++;
                                                                            nome[i] = 'U';

                                                                        }

                                                                        break;

                                                                    case SDLK_v:
                                                                        if(i == 2){
                                                                            nome[i] = 'V';

                                                                        }
                                                                        else{

                                                                            i++;
                                                                            nome[i] = 'V';

                                                                        }

                                                                        break;

                                                                    case SDLK_w:
                                                                        if(i == 2){
                                                                            nome[i] = 'W';

                                                                        }
                                                                        else{

                                                                            i++;
                                                                            nome[i] = 'W';

                                                                        }

                                                                        break;

                                                                    case SDLK_x:
                                                                        if(i == 2){
                                                                            nome[i] = 'X';

                                                                        }
                                                                        else{

                                                                            i++;
                                                                            nome[i] = 'X';

                                                                        }

                                                                        break;

                                                                    case SDLK_y:
                                                                        if(i == 2){
                                                                            nome[i] = 'Y';

                                                                        }
                                                                        else{

                                                                            i++;
                                                                            nome[i] = 'Y';

                                                                        }

                                                                        break;

                                                                    case SDLK_z:
                                                                        if(i == 2){
                                                                            nome[i] = 'Z';

                                                                        }
                                                                        else{

                                                                            i++;
                                                                            nome[i] = 'Z';

                                                                        }

                                                                        break;




                                                                    case SDLK_BACKSPACE:

                                                                        if(i == -1){
                                                                            i = -1;
                                                                        }
                                                                        else{
                                                                            nome[i] = ' ';
                                                                            i--;
                                                                        }

                                                                        break;

                                                                    default:
                                                                        break;

                                                                }
                                                                break;

                                                            case SDL_MOUSEMOTION:

                                                                if((event.motion.x > btJogarNov.x && event.motion.x < btJogarNov.x + btJogarNov.w) && (event.motion.y > btJogarNov.y && event.motion.y < btJogarNov.y + btJogarNov.h)){

                                                                    surfaceAtual = gameOver2;

                                                                }
                                                                else if((event.motion.x > btMenu.x && event.motion.x < btMenu.x + btMenu.w) && (event.motion.y > btMenu.y && event.motion.y < btMenu.y + btMenu.h)){

                                                                    surfaceAtual = gameOver1;

                                                                }
                                                                else
                                                                    surfaceAtual = gameOver;
                                                                break;

                                                            case SDL_MOUSEBUTTONDOWN:

                                                                if(event.button.button == SDL_BUTTON_LEFT){ //Botão Jogar Novamente

                                                                    if((event.motion.x > btJogarNov.x && event.motion.x < btJogarNov.x + btJogarNov.w) && (event.motion.y > btJogarNov.y && event.motion.y < btJogarNov.y + btJogarNov.h) && i == 2){
                                                                        Mix_PlayChannel( -1, SelecaoMusic, 0 );
                                                                        vidas = 3;

                                                                        sco = fopen("score.txt","w+");

                                                                        fscanf(sco,"%d %s",&primeiroLugar.pontos,primeiroLugar.nome);
                                                                        fscanf(sco,"%d %s",&segundoLugar.pontos,segundoLugar.nome);
                                                                        fscanf(sco,"%d %s",&terceiroLugar.pontos,terceiroLugar.nome);

                                                                        if(score > primeiroLugar.pontos){

                                                                            fprintf(sco,"%d %s\n",score,nome);
                                                                            fprintf(sco,"%d %s\n",segundoLugar.pontos,segundoLugar.nome);
                                                                            fprintf(sco,"%d %s",terceiroLugar.pontos,terceiroLugar.nome);

                                                                        }
                                                                        else if(score > segundoLugar.pontos){

                                                                            fprintf(sco,"%d %s\n",primeiroLugar.pontos,primeiroLugar.nome);
                                                                            fprintf(sco,"%d %s\n",score,nome);
                                                                            fprintf(sco,"%d %s",terceiroLugar.pontos,terceiroLugar.nome);

                                                                        }
                                                                        else if(score > terceiroLugar.pontos){

                                                                            fprintf(sco,"%d %s\n",primeiroLugar.pontos,primeiroLugar.nome);
                                                                            fprintf(sco,"%d %s\n",segundoLugar.pontos,segundoLugar.nome);
                                                                            fprintf(sco,"%d %s\n",score,nome);

                                                                        }

                                                                        fclose(sco);

                                                                        score = 0;
                                                                        tempoEntrada = 0;
                                                                        while(tempoEntrada < 6){

                                                                            SDL_BlitSurface(gameOver,NULL,tela,&entradaRect);
                                                                            SDL_BlitSurface(message,NULL,tela,&nomeRect);
                                                                            SDL_BlitSurface(message2,NULL,tela,&pontoRect);
                                                                            SDL_Flip(tela);
                                                                            SDL_Delay(10);
                                                                            SDL_BlitSurface(gameOver2,NULL,tela,&entradaRect);
                                                                            SDL_BlitSurface(message,NULL,tela,&nomeRect);
                                                                            SDL_BlitSurface(message2,NULL,tela,&pontoRect);
                                                                            SDL_Flip(tela);

                                                                            SDL_FillRect(tela, 0, SDL_MapRGB(tela->format,0,0,0)); //Limpar a tela.
                                                                            tempoEntrada++;

                                                                        }

                                                                        a[1] = 0;
                                                                        a[2] = 0;
                                                                        ganhou = 0;
                                                                        pegouEspada = 0;
                                                                        Mix_HaltMusic();
                                                                        for(int l = 0;l < 8;l++){


                                                                                pisoMagia[l] = 6;

                                                                        }
                                                                        pisoAtual = 1;
                                                                        quitTelaGameOver = 1;


                                                                    }

                                                                    else if((event.motion.x > btMenu.x && event.motion.x < btMenu.x + btMenu.w) && (event.motion.y > btMenu.y && event.motion.y < btMenu.y + btMenu.h) && i == 2){
                                                                    //Botao Menu
                                                                        Mix_PlayChannel( -1, SelecaoMusic, 0 );
                                                                        tempoEntrada = 0;

                                                                        sco = fopen("score.txt","w+");

                                                                        fscanf(sco,"%d %s",&primeiroLugar.pontos,primeiroLugar.nome);
                                                                        fscanf(sco,"%d %s",&segundoLugar.pontos,segundoLugar.nome);
                                                                        fscanf(sco,"%d %s",&terceiroLugar.pontos,terceiroLugar.nome);

                                                                        if(score > primeiroLugar.pontos){

                                                                            fprintf(sco,"%d %s\n",score,nome);
                                                                            fprintf(sco,"%d %s\n",primeiroLugar.pontos,primeiroLugar.nome);
                                                                            fprintf(sco,"%d %s",segundoLugar.pontos,segundoLugar.nome);

                                                                        }
                                                                        else if(score > segundoLugar.pontos){

                                                                            fprintf(sco,"%d %s\n",primeiroLugar.pontos,primeiroLugar.nome);
                                                                            fprintf(sco,"%d %s\n",score,nome);
                                                                            fprintf(sco,"%d %s",segundoLugar.pontos,segundoLugar.nome);

                                                                        }
                                                                        else if(score > terceiroLugar.pontos){

                                                                            fprintf(sco,"%d %s\n",primeiroLugar.pontos,primeiroLugar.nome);
                                                                            fprintf(sco,"%d %s\n",segundoLugar.pontos,segundoLugar.nome);
                                                                            fprintf(sco,"%d %s\n",score,nome);

                                                                        }

                                                                        fclose(sco);
                                                                        score = 0;
                                                                        while(tempoEntrada < 6){

                                                                            SDL_BlitSurface(gameOver,NULL,tela,&entradaRect);
                                                                            SDL_BlitSurface(message,NULL,tela,&nomeRect);
                                                                            SDL_BlitSurface(message2,NULL,tela,&pontoRect);
                                                                            SDL_Flip(tela);
                                                                            SDL_Delay(10);
                                                                            SDL_BlitSurface(gameOver1,NULL,tela,&entradaRect);
                                                                            SDL_BlitSurface(message,NULL,tela,&nomeRect);
                                                                            SDL_BlitSurface(message2,NULL,tela,&pontoRect);
                                                                            SDL_Flip(tela);

                                                                            SDL_FillRect(tela, 0, SDL_MapRGB(tela->format,0,0,0)); //Limpar a tela.
                                                                            tempoEntrada++;

                                                                        }

                                                                        surfaceAtual = menu;
                                                                        Mix_HaltMusic();
                                                                        pisoAtual = 1;
                                                                        quitTelaGameOver = 1;
                                                                        quit = 1;

                                                                    }

                                                                }
                                                                break;

                                                    }

                                                }

                                                message = TTF_RenderText_Solid(font, nome, corTexto);
                                                message2 = TTF_RenderText_Solid(font, p, corTexto);

                                                SDL_FillRect(tela, 0, SDL_MapRGB(tela->format,0,0,0)); //Limpar a tela.

                                                SDL_BlitSurface(surfaceAtual,NULL,tela,&entradaRect);
                                                SDL_BlitSurface(message,NULL,tela,&nomeRect);
                                                SDL_BlitSurface(message2,NULL,tela,&pontoRect);

                                                SDL_Flip(tela);


                                            }

                                        }

                                        SDL_Flip(tela); //Atualiza a tela.

                                        //Velocidade de Transição de Frames
                                        frame += 0.5;
                                        if(frame > 7)
                                            frame = 0;


                                        if(1000/FPS > SDL_GetTicks() - start)
                                            SDL_Delay(1000/FPS - (SDL_GetTicks() - start));




                                    }while(!quit);


                                }

                                else if((event.motion.x > btComoJogar.x && event.motion.x < btComoJogar.x + btComoJogar.w) && (event.motion.y > btComoJogar.y && event.motion.y < btComoJogar.y + btComoJogar.h)){
                                    //Entrando na tela de Como Jogar
                                    Mix_PlayChannel( -1, SelecaoMusic, 0 );
                                    quitLoopComoJogar = 0;
                                    tempoEntrada = 0;
                                    while(tempoEntrada < 6){

                                        SDL_BlitSurface(menu,NULL,tela,&entradaRect);
                                        SDL_Flip(tela);
                                        SDL_Delay(10);
                                        SDL_BlitSurface(menu2,NULL,tela,&entradaRect);
                                        SDL_Flip(tela);

                                        SDL_FillRect(tela, 0, SDL_MapRGB(tela->format,0,0,0)); //Limpar a tela.
                                        tempoEntrada++;

                                    }

                                    surfaceAtual = comoJogar1;
                                    while(!quitLoopComoJogar){

                                        while(SDL_PollEvent(&event)){

                                            switch(event.type){

                                                case SDL_QUIT:
                                                    SDL_Quit();
                                                    TTF_Quit();
                                                    Mix_Quit();
                                                    return 0;
                                                    break;

                                                case SDL_MOUSEMOTION:

                                                    if((event.motion.x > btVoltar.x && event.motion.x < btVoltar.x + btVoltar.w) && (event.motion.y > btVoltar.y && event.motion.y < btVoltar.y + btVoltar.h)){

                                                        surfaceAtual = comoJogar2;

                                                    }
                                                    else
                                                        surfaceAtual = comoJogar1;
                                                    break;

                                                case SDL_MOUSEBUTTONDOWN:

                                                    if(event.button.button == SDL_BUTTON_LEFT){

                                                        if((event.motion.x > btVoltar.x && event.motion.x < btVoltar.x + btVoltar.w) && (event.motion.y > btVoltar.y && event.motion.y < btVoltar.y + btVoltar.h)){
                                                            Mix_PlayChannel( -1, SelecaoMusic, 0 );
                                                            tempoEntrada = 0;
                                                            while(tempoEntrada < 6){

                                                                SDL_BlitSurface(comoJogar1,NULL,tela,&entradaRect);
                                                                SDL_Flip(tela);
                                                                SDL_Delay(10);
                                                                SDL_BlitSurface(comoJogar2,NULL,tela,&entradaRect);
                                                                SDL_Flip(tela);

                                                                SDL_FillRect(tela, 0, SDL_MapRGB(tela->format,0,0,0)); //Limpar a tela.
                                                                tempoEntrada++;
                                                            }

                                                            surfaceAtual = menu;
                                                            quitLoopComoJogar = 1;

                                                        }

                                                    }
                                                    break;

                                            }
                                        }


                                        SDL_FillRect(tela, 0, SDL_MapRGB(tela->format,0,0,0)); //Limpar a tela.

                                        SDL_BlitSurface(surfaceAtual,NULL,tela,&entradaRect);

                                        SDL_Flip(tela);

                                    }

                                }
                                else if((event.motion.x > btRecordes.x && event.motion.x < btRecordes.x + btRecordes.w) && (event.motion.y > btRecordes.y && event.motion.y < btRecordes.y + btRecordes.h)){

                                    quitLoopRecordes = 0;
                                    Mix_PlayChannel( -1, SelecaoMusic, 0 );
                                    tempoEntrada = 0;
                                    while(tempoEntrada < 6){

                                        SDL_BlitSurface(menu,NULL,tela,&entradaRect);
                                        SDL_Flip(tela);
                                        SDL_Delay(10);
                                        SDL_BlitSurface(menu3,NULL,tela,&entradaRect);
                                        SDL_Flip(tela);

                                        SDL_FillRect(tela, 0, SDL_MapRGB(tela->format,0,0,0)); //Limpar a tela.
                                        tempoEntrada++;

                                    }

                                    surfaceAtual = recordes1;

                                    FILE* sco2;
                                    sco2 = fopen("score.txt","r");

                                    fscanf(sco2,"%d %s",&primeiroLugar.pontos,primeiroLugar.nome);
                                    fscanf(sco2,"%d %s",&segundoLugar.pontos,segundoLugar.nome);
                                    fscanf(sco2,"%d %s",&terceiroLugar.pontos,terceiroLugar.nome);

                                    fclose(sco2);


                                    char ponto1[7], ponto2[7], ponto3[7];

                                    sprintf(ponto1,"%d",primeiroLugar.pontos);
                                    sprintf(ponto2,"%d",segundoLugar.pontos);
                                    sprintf(ponto3,"%d",terceiroLugar.pontos);

                                    while(!quitLoopRecordes){

                                        while(SDL_PollEvent(&event)){

                                            switch(event.type){

                                                case SDL_QUIT:
                                                    SDL_Quit();
                                                    TTF_Quit();
                                                    return 0;
                                                    break;

                                                case SDL_MOUSEMOTION:

                                                    if((event.motion.x > btVoltar.x && event.motion.x < btVoltar.x + btVoltar.w) && (event.motion.y > btVoltar.y && event.motion.y < btVoltar.y + btVoltar.h)){

                                                        surfaceAtual = recordes2;

                                                    }
                                                    else
                                                        surfaceAtual = recordes1;
                                                    break;

                                                case SDL_MOUSEBUTTONDOWN:

                                                    if(event.button.button == SDL_BUTTON_LEFT){

                                                        if((event.motion.x > btVoltar.x && event.motion.x < btVoltar.x + btVoltar.w) && (event.motion.y > btVoltar.y && event.motion.y < btVoltar.y + btVoltar.h)){

                                                            tempoEntrada = 0;
                                                            Mix_PlayChannel( -1, SelecaoMusic, 0 );
                                                            while(tempoEntrada < 6){

                                                                SDL_BlitSurface(recordes1,NULL,tela,&entradaRect);

                                                                SDL_BlitSurface(message3,NULL,tela,&primeiroRect);
                                                                SDL_BlitSurface(message4,NULL,tela,&nomePrimeiroRect);
                                                                SDL_BlitSurface(message5,NULL,tela,&segundoRect);
                                                                SDL_BlitSurface(message6,NULL,tela,&nomeSegundoRect);
                                                                SDL_BlitSurface(message7,NULL,tela,&terceiroRect);
                                                                SDL_BlitSurface(message8,NULL,tela,&nomeTerceiroRect);

                                                                SDL_Flip(tela);
                                                                SDL_Delay(10);
                                                                SDL_BlitSurface(recordes2,NULL,tela,&entradaRect);

                                                                SDL_BlitSurface(message3,NULL,tela,&primeiroRect);
                                                                SDL_BlitSurface(message4,NULL,tela,&nomePrimeiroRect);
                                                                SDL_BlitSurface(message5,NULL,tela,&segundoRect);
                                                                SDL_BlitSurface(message6,NULL,tela,&nomeSegundoRect);
                                                                SDL_BlitSurface(message7,NULL,tela,&terceiroRect);
                                                                SDL_BlitSurface(message8,NULL,tela,&nomeTerceiroRect);

                                                                SDL_Flip(tela);

                                                                SDL_FillRect(tela, 0, SDL_MapRGB(tela->format,0,0,0)); //Limpar a tela.
                                                                tempoEntrada++;
                                                            }

                                                            surfaceAtual = menu;
                                                            quitLoopRecordes = 1;

                                                        }

                                                    }
                                                    break;

                                            }
                                        }

                                        SDL_FillRect(tela, 0, SDL_MapRGB(tela->format,0,0,0)); //Limpar a tela.

                                        SDL_BlitSurface(surfaceAtual,NULL,tela,&entradaRect);

                                        message3 = TTF_RenderText_Solid(font2, ponto1, corTexto);
                                        message4 = TTF_RenderText_Solid(font2, primeiroLugar.nome, corTexto);
                                        message5 = TTF_RenderText_Solid(font2, ponto2, corTexto);
                                        message6 = TTF_RenderText_Solid(font2, segundoLugar.nome, corTexto);
                                        message7 = TTF_RenderText_Solid(font2, ponto3, corTexto);
                                        message8 = TTF_RenderText_Solid(font2, terceiroLugar.nome, corTexto);

                                        SDL_BlitSurface(message3,NULL,tela,&primeiroRect);
                                        SDL_BlitSurface(message4,NULL,tela,&nomePrimeiroRect);
                                        SDL_BlitSurface(message5,NULL,tela,&segundoRect);
                                        SDL_BlitSurface(message6,NULL,tela,&nomeSegundoRect);
                                        SDL_BlitSurface(message7,NULL,tela,&terceiroRect);
                                        SDL_BlitSurface(message8,NULL,tela,&nomeTerceiroRect);

                                        SDL_Flip(tela);

                                    }

                                }
                                else if((event.motion.x > btCreditos.x && event.motion.x < btCreditos.x + btCreditos.w) && (event.motion.y > btCreditos.y && event.motion.y < btCreditos.y + btCreditos.h)){

                                    quitLoopCreditos = 0;
                                    Mix_PlayChannel( -1, SelecaoMusic, 0 );
                                    tempoEntrada = 0;
                                    while(tempoEntrada < 6){

                                        SDL_BlitSurface(menu,NULL,tela,&entradaRect);
                                        SDL_Flip(tela);
                                        SDL_Delay(10);
                                        SDL_BlitSurface(menu4,NULL,tela,&entradaRect);
                                        SDL_Flip(tela);

                                        SDL_FillRect(tela, 0, SDL_MapRGB(tela->format,0,0,0)); //Limpar a tela.
                                        tempoEntrada++;

                                    }

                                    surfaceAtual = creditos1;
                                    while(!quitLoopCreditos){

                                        while(SDL_PollEvent(&event)){

                                            switch(event.type){

                                                case SDL_QUIT:
                                                    SDL_Quit();
                                                    return 0;
                                                    break;

                                                case SDL_MOUSEMOTION:

                                                    if((event.motion.x > btVoltar.x && event.motion.x < btVoltar.x + btVoltar.w) && (event.motion.y > btVoltar.y && event.motion.y < btVoltar.y + btVoltar.h)){

                                                        surfaceAtual = creditos2;

                                                    }
                                                    else
                                                        surfaceAtual = creditos1;
                                                    break;

                                                case SDL_MOUSEBUTTONDOWN:

                                                    if(event.button.button == SDL_BUTTON_LEFT){

                                                        if((event.motion.x > btVoltar.x && event.motion.x < btVoltar.x + btVoltar.w) && (event.motion.y > btVoltar.y && event.motion.y < btVoltar.y + btVoltar.h)){

                                                            tempoEntrada = 0;
                                                            Mix_PlayChannel( -1, SelecaoMusic, 0 );
                                                            while(tempoEntrada < 6){

                                                                SDL_BlitSurface(creditos1,NULL,tela,&entradaRect);
                                                                SDL_Flip(tela);
                                                                SDL_Delay(10);
                                                                SDL_BlitSurface(creditos2,NULL,tela,&entradaRect);
                                                                SDL_Flip(tela);

                                                                SDL_FillRect(tela, 0, SDL_MapRGB(tela->format,0,0,0)); //Limpar a tela.
                                                                tempoEntrada++;
                                                            }

                                                            surfaceAtual = menu;
                                                            quitLoopCreditos = 1;

                                                        }

                                                    }
                                                    break;

                                            }
                                        }


                                        SDL_FillRect(tela, 0, SDL_MapRGB(tela->format,0,0,0)); //Limpar a tela.

                                        SDL_BlitSurface(surfaceAtual,NULL,tela,&entradaRect);

                                        SDL_Flip(tela);

                                    }

                                }
                                else if((event.motion.x > btSair.x && event.motion.x < btSair.x + btSair.w) && (event.motion.y > btSair.y && event.motion.y < btSair.y + btSair.h)){

                                    quitLoopSair = 0;
                                    Mix_PlayChannel( -1, SelecaoMusic, 0 );
                                    tempoEntrada = 0;
                                    while(tempoEntrada < 6){

                                        SDL_BlitSurface(menu,NULL,tela,&entradaRect);
                                        SDL_Flip(tela);
                                        SDL_Delay(10);
                                        SDL_BlitSurface(menu5,NULL,tela,&entradaRect);
                                        SDL_Flip(tela);

                                        SDL_FillRect(tela, 0, SDL_MapRGB(tela->format,0,0,0)); //Limpar a tela.
                                        tempoEntrada++;

                                    }

                                    surfaceAtual = sair;
                                    while(!quitLoopSair){

                                        while(SDL_PollEvent(&event)){

                                            switch(event.type){

                                                case SDL_QUIT:
                                                    SDL_Quit();
                                                    TTF_Quit();
                                                    Mix_Quit();
                                                    return 0;
                                                    break;

                                                case SDL_KEYDOWN:
                                                    switch(event.key.keysym.sym){

                                                        case SDLK_s:
                                                            SDL_Quit();
                                                            TTF_Quit();
                                                            Mix_Quit();
                                                            return 0;
                                                            break;

                                                        case SDLK_n:
                                                            surfaceAtual = menu;
                                                            quitLoopSair = 1;
                                                            break;

                                                        default:
                                                            break;

                                                    }
                                            }

                                        }

                                        SDL_FillRect(tela, 0, SDL_MapRGB(tela->format,0,0,0)); //Limpar a tela.

                                        SDL_BlitSurface(surfaceAtual,NULL,tela,&entradaRect);

                                        SDL_Flip(tela);

                                    }

                                }


                            }
                            break;



                    }


                }

                SDL_FillRect(tela, 0, SDL_MapRGB(tela->format,0,0,0)); //Limpar a tela.

                SDL_BlitSurface(surfaceAtual,NULL,tela,&entradaRect);

                SDL_Flip(tela);

            }








        }
        else{


            SDL_FillRect(tela, 0, SDL_MapRGB(tela->format,0,0,0)); //Limpar a tela.

            //Desenhar imagem de entrada
            SDL_BlitSurface(entrada1,NULL,tela,&entradaRect);




        }

        SDL_Flip(tela);

    }while(!quitMenu);

    SDL_FreeSurface(tela);
    SDL_Quit(); //Encerrar a SDL

    return 0;
}
