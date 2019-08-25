#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MALLOC(t,n) (t*)malloc(sizeof(t)*n)
#define CALLOC(t,n) (t*)calloc(sizeof(t),n);

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
int MatrizParaAdjacencia(int i,int j,int N,int M){
    return i*M + j;
}
void AdjacenciaParaMatriz(int v,int *i,int *j,int N,int M){
    *i = 0;
    while(v > 0){
        v = v - M;
        *i = *i + 1;
    }
    if(v<0){
        v = v + M;
        *i = *i - 1;
    }
    
    *j = v;
}
void printAdjacencia(Vertice **adjacencia,int N, int M){
    Vertice *v;
    int i;
    int x,y;
    for(i=0;i<N*M;i++){
        v=adjacencia[i];
        while(v!=NULL){
            AdjacenciaParaMatriz(v->label,&x,&y,N,M);
            printf("(%d,%d)->",x,y);
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




void DFS(int verticeAtual,Vertice **adjacencia,int *visitado,int *distancia,int *verticeMaisDistante,int *maiorDistancia){
    if(visitado[verticeAtual])
        return;
    visitado[verticeAtual]=1;
    Vertice *v = adjacencia[verticeAtual]->proximo;
    while(v != NULL){
        if(visitado[v->label] == 0){
            distancia[v->label] = distancia[verticeAtual] + 1;
            if(distancia[v->label] > *maiorDistancia){
                *maiorDistancia = distancia[v->label];
                *verticeMaisDistante = v->label;
            }
            DFS(v->label,adjacencia,visitado,distancia,verticeMaisDistante,maiorDistancia);
        }
        v = v->proximo;
    }
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
            }
           readEOL();
        }
        for(i=0;i<N;i++)
            for(j=0;j<M;j++)
                if(labirinto[i][j]!='#'){
                    if(i-1 >= 0 && labirinto[i-1][j] == '.'){
                            Vertice *v = MALLOC(Vertice,1);
                            v->fim=v->proximo = NULL;
                            v->label = MatrizParaAdjacencia(i-1,j,N,M);
                            insere(MatrizParaAdjacencia(i,j,N,M),v,adjacencia,N*M);
                    }
                    if(i+1 < N && labirinto[i+1][j] == '.'){
                        Vertice *v = MALLOC(Vertice,1);
                        v->fim=v->proximo = NULL;
                        v->label = MatrizParaAdjacencia(i+1,j,N,M);
                        insere(MatrizParaAdjacencia(i,j,N,M),v,adjacencia,N*M);
                    }
                    if(j-1 >= 0 && labirinto[i][j-1] == '.'){
                        Vertice *v = MALLOC(Vertice,1);
                        v->fim=v->proximo = NULL;
                        v->label = MatrizParaAdjacencia(i,j-1,N,M);
                        insere(MatrizParaAdjacencia(i,j,N,M),v,adjacencia,N*M);
                    }
                    if(j+1 < M && labirinto[i][j+1] == '.'){
                        Vertice *v = MALLOC(Vertice,1);
                        v->fim=v->proximo = NULL;
                        v->label = MatrizParaAdjacencia(i,j+1,N,M);
                        insere(MatrizParaAdjacencia(i,j,N,M),v,adjacencia,N*M);
                    }
                }
                
        int *visitado = CALLOC(int,N*M);
        int *distancia = CALLOC(int,N*M);
        int verticeMaisDistante=0,maiorDistancia=0;
        int v,md=0;
        for(i=0;i<N*M;i++){
            if(visitado[i]==0)
                DFS(i,adjacencia,visitado,distancia,&verticeMaisDistante,&maiorDistancia);
            if(maiorDistancia > md){
                md = maiorDistancia;
                v = verticeMaisDistante;
            }
            maiorDistancia = 0;
        }
        visitado = CALLOC(int,N*M);
        distancia = CALLOC(int,N*M);
        DFS(v,adjacencia,visitado,distancia,&verticeMaisDistante,&maiorDistancia);
        printf("%d\n",maiorDistancia);
        //printAdjacencia(adjacencia,N,M);
        scanf("%d%d",&N,&M);
        if(N != 0 && M != 0)    
            readEOL();
    }
    return 0;
}