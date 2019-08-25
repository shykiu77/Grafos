#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MALLOC(t,n) (t*)malloc(sizeof(t)*n)

void readEOL(){
    char c;
    c = getchar();
    while(c != '\n')
        c = getchar();
}

int main(int argc, char** argv){
    int N,M;
    scanf("%d%d",&N,&M);    
    readEOL();
    while(N != 0 && M != 0){
        char **labirinto = MALLOC(char*,N);
        for(int i=0;i<N;i++)
            labirinto[i] = MALLOC(char,M);
        for(int i=0;i<N;i++){
            for(int j=0;j<M;j++){
                labirinto[i][j]=getchar();
            }
           readEOL();
        }
        
        scanf("%d%d",&N,&M);
        if(N != 0 && M != 0)    
            readEOL();
    }
    return 0;
}