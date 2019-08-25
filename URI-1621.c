#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MALLOC(t,n) (t*)malloc(sizeof(t)*n)

typedef struct vertice{
    int label;
    struct vertice *proximo;
    struct vertice *fim;
}Vertice;
void insere(int vertice1,Vertice *vertice2,Vertice **adjacencia,int Nvertices){
    if(adjacencia[vertice1]->fim==NULL){
        adjacencia[vertice1]->proximo=vertice2;
        adjacencia[vertice1]->fim=vertice2;
    }
    else{
        adjacencia[vertice1]->fim->proximo=vertice2;
        adjacencia[vertice1]->fim=vertice2;
    }
}
void printAdjacencia(Vertice **adjacencia,int Nvertices){
    Vertice *v;
    int i;
    for(i=0;i<Nvertices;i++){
        v=adjacencia[i];
        while(v!=NULL){
            printf("%d->",v->label);
            v=v->proximo;
        }
        printf("\n");
    }
    
}
void readEOL(){
    char c;
    c = getchar();
    while(c != '\n')
        c = getchar();
}

int MatrizParaAdjacencia(int i,int j,int N,int M){
    return i*M + j;
}
int adjacenciaParaMatriz(int *i,int *j,int N,int M){
    //TODO
    return 0;
}

int main(int argc, char** argv){
    int N,M,i,j;
    scanf("%d%d",&N,&M);    
    readEOL();
    while(N != 0 && M != 0){
        char **labirinto = MALLOC(char*,N);
        Vertice **adjacencia = MALLOC(Vertice*,N*M);
        for(i=0;i<N;i++)
            labirinto[i] = MALLOC(char,M);
        for(i=0;i<N;i++){
            for(j=0;j<M;j++){
                labirinto[i][j]=getchar();
                adjacencia[MatrizParaAdjacencia(i,j,N,M)] = MALLOC(Vertice,1);
                adjacencia[MatrizParaAdjacencia(i,j,N,M)]->fim=adjacencia[MatrizParaAdjacencia(i,j,N,M)]->proximo=NULL;
                adjacencia[MatrizParaAdjacencia(i,j,N,M)]->label = MatrizParaAdjacencia(i,j,N,M);
                 if(i-1 >= 0){
                   Vertice *v = MALLOC(Vertice,1);
                   v->fim=v->proximo = NULL;
                   v->label = MatrizParaAdjacencia(i-1,j,N,M);
                   insere(MatrizParaAdjacencia(i,j,N,M),v,adjacencia,N*M);
                  
               }
               if(i+1 < N){
                   Vertice *v = MALLOC(Vertice,1);
                   v->fim=v->proximo = NULL;
                   v->label = MatrizParaAdjacencia(i+1,j,N,M);
                   insere(MatrizParaAdjacencia(i,j,N,M),v,adjacencia,N*M);
               }
               if(j-1 >= 0){
                   Vertice *v = MALLOC(Vertice,1);
                   v->fim=v->proximo = NULL;
                   v->label = MatrizParaAdjacencia(i,j-1,N,M);
                   insere(MatrizParaAdjacencia(i,j,N,M),v,adjacencia,N*M);
               }
               if(j+1 < M){
                   Vertice *v = MALLOC(Vertice,1);
                   v->fim=v->proximo = NULL;
                   v->label = MatrizParaAdjacencia(i,j+1,N,M);
                   insere(MatrizParaAdjacencia(i,j,N,M),v,adjacencia,N*M);
               }
            }
           readEOL();
        }
       // printAdjacencia(adjacencia,N*M);
        scanf("%d%d",&N,&M);
        if(N != 0 && M != 0)    
            readEOL();
    }
    return 0;
}