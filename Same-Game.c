#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Localizacoes{
    int linha;
    int coluna;
};

struct fila{
    int elem[25];
    int inicio;
    int fim;
    int tamMAX;
};

void inicializaFila (struct fila *q){
    q->inicio=-1;
    q->fim=-1;
}

int filaVazia (struct fila *q){
  return q->inicio==q->fim;
}

int filaCheia (struct fila *q){
    return q->fim==q->tamMAX;
}

void descolaFila (struct fila *q){
    int desloc=q->inicio+1;
    for(int i=desloc;i<q->fim;i++){
        q->elem[i-desloc]=q->elem[i];
    }
    q->inicio=-1;
    q->fim=q->fim-desloc;
}

void insereFila (struct fila *q, int x){
    if(filaCheia(q)){
    descolaFila(q);
    } else {
        q->fim=q->fim+1;
        q->elem[q->fim]=x;
    }
}

void removeFila (struct fila *q){
    int x;
    if(!filaVazia(q)){
        q->inicio=q->inicio+1;
        x=q->elem[q->inicio];
        if (filaVazia(q)){
            inicializaFila(q);
        }
    }
};

int primeirodaFila (struct fila *q){
    if (!filaVazia(q)){
        return q->elem[q->inicio+1];
    }
};

struct fila1{
    struct Localizacoes elem[25];
    int inicio;
    int fim;
    int tamMAX;
};

void comecaFila1 (struct fila1 *q){
  q->inicio=-1;
  q->fim=-1;
}

int filaVazia1 (struct fila1 *q){
  return q->inicio==q->fim;
}

int filaCheia1 (struct fila1 *q){
    return q->fim==q->tamMAX;
}

void arrumaFila1 (struct fila1 *q){
    int desloc=q->inicio+1;
    for(int i=desloc;i<q->fim;i++){
        q->elem[i-desloc]=q->elem[i];
    }
    q->inicio=-1;
    q->fim=q->fim-desloc;
}

void insereFila1 (struct fila1 *q, struct Localizacoes *x){
    if(filaCheia1(q)){
        arrumaFila1(q);
    } else {
        q->fim=q->fim+1;
        q->elem[q->fim]=*x;
    }
}

struct Localizacoes removeFila1 (struct fila1 *q){
    struct Localizacoes x;
    if(!filaVazia1(q)){
        q->inicio=q->inicio+1;
        x=q->elem[q->inicio];
        if (filaVazia1(q)){
            comecaFila1(q);
        }
    }
    return x;
};

struct Localizacoes primeirodaFila1 (struct fila1 *q){
    if (!filaVazia1(q)){
        return q->elem[q->inicio+1];
    }
};


void busca(int mSAME[12][16], int par, int linha, int coluna){
    struct fila1 ke;
    struct fila1 *q=&ke;
    q->tamMAX=12*16;
    comecaFila1(q);
    struct Localizacoes p;
    struct Localizacoes c;
    struct Localizacoes b;
    struct Localizacoes e;
    struct Localizacoes d;
    struct Localizacoes *pri=&p;
    struct Localizacoes *cima=&c;
    struct Localizacoes *baixo=&b;
    struct Localizacoes *esq=&e;
    struct Localizacoes *dir=&d;
    pri->linha=linha;
    pri->coluna=coluna;
    insereFila1(q,pri);
    while (!filaVazia1(q)){
        *pri=primeirodaFila1(q);
        if (mSAME[pri->linha][pri->coluna]==par||mSAME[pri->linha][pri->coluna]==0){
            mSAME[pri->linha][pri->coluna]=0;
            if (pri->linha+1<12){
                baixo->linha=pri->linha+1;
                baixo->coluna=pri->coluna;
                if (mSAME[baixo->linha][baixo->coluna]==par){
                    mSAME[baixo->linha][baixo->coluna]=0;
                    insereFila1(q,baixo);
                }
            }
            if (pri->linha-1>-1){
                cima->linha=pri->linha-1;
                cima->coluna=pri->coluna;
                if (mSAME[cima->linha][cima->coluna]==par){
                    mSAME[cima->linha][cima->coluna]=0;
                    insereFila1(q,cima);
                }
            }
            if (pri->coluna-1>-1){
                esq->linha=pri->linha;
                esq->coluna=pri->coluna-1;
                if (mSAME[esq->linha][esq->coluna]==par){
                    mSAME[esq->linha][esq->coluna]=0;
                    insereFila1(q,esq);
                }
            }
            if (pri->coluna+1<16){
                dir->linha=pri->linha;
                dir->coluna=pri->coluna+1;
                if (mSAME[dir->linha][dir->coluna]==par){
                    mSAME[dir->linha][dir->coluna]=0;
                    insereFila1(q,dir);
                }
            }
        }
        removeFila1(q);
    }
}

void relocLinha (int mSAME[12][16]){
    struct fila ke;
    struct fila *q=&ke;
    q->tamMAX=12;
    int aux=11;
    inicializaFila(q);
    for (int j=15;j>=0;j--){
        aux=11;
        for (int i=11;i>=0;i--){
            if(mSAME[i][j]!=0){
                insereFila(q,mSAME[i][j]);
                mSAME[i][j]=0;
            }
        }
        while (!filaVazia(q)){
            mSAME[aux][j]=primeirodaFila(q);
            removeFila(q);
            aux--;
        }
        inicializaFila(q);
    }
}

void relocColuna(int m[12][16]){
    int cont=0;
    int aux=0;
    while(aux < 16){
        if(m[11][cont]==0){
            for (int j=0;j<12;j++){
               for (int k=cont;k<15;k++){
                   m[j][k]=m[j][k+1];
               }

            }
            for (int l = 0; l< 12;l++){
                   m[l][15] = 0;
               }
            aux ++;

        } else {
            cont++;
            aux++;
        }

    }
}

void printarJogo(int mSAME[12][16]){
    int aux=0;
    printf("    0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15\n");
    for(int i=0;i<12;i++){
        for(int j=0;j<16;j++){
            if(j==0){
                if(aux<10){
                    printf("%d ",aux);
                } else {
                    printf("%d",aux);
                }
                aux++;
            }
            if(mSAME[i][j]==1){
                printf("  1");
            } else if (mSAME[i][j]==2){
                printf("  2");
            } else if (mSAME[i][j]==3){
                printf("  3");
            } else if (mSAME[i][j]==0){
                printf("  0");
            }
        }
        printf("\n");
    }
}

void jogarSAME(int mSAME[12][16]){
  int coluna;
  int linha;
  printarJogo(mSAME);
  printf("Digite a linha: \n");
  scanf("%d", &linha);
  printf("Digite a coluna: \n");
  scanf("%d", &coluna);
  if (linha>11||coluna>15){
    printf("Posicao invalida, digite novamente.\n");
  } else {
    busca(mSAME,mSAME[linha][coluna],linha,coluna);
    relocLinha(mSAME);
    relocColuna(mSAME);
  }
}

void preencherSAME(int mSAME[12][16]){
  for (int i=0;i<12;i++){
    for(int j=0;j<16;j++){
      int r = rand() % 9000;
      if (r<3000){
        mSAME[i][j]=1;
      } else if (r<6000){
        mSAME[i][j]=2;
      } else {
        mSAME[i][j]=3;
      }
    }
  }
}

int movimento (int mSAME[12][16]){
    int aux=0;
    for(int i=0;i<12;i++){
        for(int j=0;j<16;j++){
            if(mSAME[i][j]!=0){
                if(mSAME[i][j+1]==mSAME[i][j]||mSAME[i+1][j]==mSAME[i][j]){
                    aux=1;
                }
            }
        }
    }
    return aux;
}

int vencer (int mSAME[12][16]){
    int aux=0;
    for(int j=0;j<16;j++){
        if (mSAME[11][j]!=0){
            aux=1;
        }
    }
    return aux;
}

int main(){
    int mSAME[12][16];
    srand(time(NULL));
    preencherSAME(mSAME);
    while (movimento(mSAME)){
        jogarSAME(mSAME);
    }
    if(vencer(mSAME)==0){
        printf("Voce venceu o jogo.\n");
    } else {
        printf("Voce perdeu o jogo.\n");
    }
}
