#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 20

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// ---------------- Funções uteis ----------------
void mostrarComponentes(Componente c[], int n){
    printf("\n====================================\n");
    printf("        COMPONENTES CADASTRADOS     \n");
    printf("          (%d/%d)\n", n, MAX);
    printf("====================================\n");
    printf("%-30s | %-20s | %-10s\n","NOME","TIPO","PRIORIDADE");
    printf("------------------------------------------------------------\n");
    for(int i=0;i<n;i++)
        printf("%-30s | %-20s | %-10d\n", c[i].nome, c[i].tipo, c[i].prioridade);
    printf("------------------------------------------------------------\n");
}

// ---------------- Ordenacoes ----------------

// Bubble sort por nome
void bubbleSortNome(Componente c[], int n, int* comp){
    *comp=0;
    clock_t start=clock();
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            (*comp)++;
            if(strcmp(c[j].nome, c[j+1].nome) > 0){
                Componente tmp=c[j]; c[j]=c[j+1]; c[j+1]=tmp;
            }
        }
    }
    clock_t end=clock();
    printf("Ordenado por NOME (Bubble Sort) em %.3f seg com %d comparacoes\n", (double)(end-start)/CLOCKS_PER_SEC,*comp);
}

// Insertion sort por tipo
void insertionSortTipo(Componente c[], int n, int* comp){
    *comp=0;
    clock_t start=clock();
    for(int i=1;i<n;i++){
        Componente key=c[i];
        int j=i-1;
        while(j>=0){ 
            (*comp)++;
            if(strcmp(c[j].tipo,key.tipo)>0){ c[j+1]=c[j]; j--; } else break;
        }
        c[j+1]=key;
    }
    clock_t end=clock();
    printf("Ordenado por TIPO (Insertion Sort) em %.3f seg com %d comparacoes\n", (double)(end-start)/CLOCKS_PER_SEC,*comp);
}

// Selection sort por prioridade
void selectionSortPrioridade(Componente c[], int n, int* comp){
    *comp=0;
    clock_t start=clock();
    for(int i=0;i<n-1;i++){
        int min=i;
        for(int j=i+1;j<n;j++){
            (*comp)++;
            if(c[j].prioridade < c[min].prioridade) min=j;
        }
        if(min!=i){Componente tmp=c[i]; c[i]=c[min]; c[min]=tmp;}
    }
    clock_t end=clock();
    printf("Ordenado por PRIORIDADE (Selection Sort) em %.3f seg com %d comparacoes\n", (double)(end-start)/CLOCKS_PER_SEC,*comp);
}

// ---------------- Busca Binaria ----------------
void buscaBinariaNome(Componente c[], int n){
    char nome[30]; getchar();
    printf("\nBuscar componente por NOME (binaria): "); fgets(nome,30,stdin); nome[strcspn(nome,"\n")]=0;
    int ini=0,fim=n-1,achou=0, comp=0;
    clock_t start=clock();
    while(ini<=fim){
        int m=(ini+fim)/2; comp++;
        int res=strcmp(c[m].nome,nome);
        if(res==0){ achou=1; printf("Achou: %s | %s | %d\n",c[m].nome,c[m].tipo,c[m].prioridade); break;}
        else if(res<0) ini=m+1;
        else fim=m-1;
    }
    clock_t end=clock();
    if(!achou) printf("Nao achei o componente\n");
    printf("Comparacoes: %d, Tempo: %.3f seg\n", comp, (double)(end-start)/CLOCKS_PER_SEC);
}

// ---------------- Menu Principal ----------------
int main(){
    Componente comp[MAX];
    int n=0;
    int op;

    do{
        printf("\n====== TORRE DE RESGATE ======\n");
        printf("1. Adicionar componente\n");
        printf("2. Mostrar componentes\n");
        printf("3. Ordenar por NOME (Bubble Sort)\n");
        printf("4. Ordenar por TIPO (Insertion Sort)\n");
        printf("5. Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("6. Buscar componente por NOME (Binaria)\n");
        printf("0. Sair\n");
        printf("Escolha: "); scanf("%d",&op);

        switch(op){
            case 1:
                if(n>=MAX){printf("Lista cheia!\n"); break;}
                getchar();
                printf("\nNome: "); fgets(comp[n].nome,30,stdin); comp[n].nome[strcspn(comp[n].nome,"\n")]=0;
                printf("Tipo: "); fgets(comp[n].tipo,20,stdin); comp[n].tipo[strcspn(comp[n].tipo,"\n")]=0;
                printf("Prioridade (1-10): "); scanf("%d",&comp[n].prioridade);
                if(comp[n].prioridade<1) comp[n].prioridade=1;
                if(comp[n].prioridade>10) comp[n].prioridade=10;
                n++;
                printf("Componente adicionado!\n");
                mostrarComponentes(comp,n);
                break;
            case 2:
                mostrarComponentes(comp,n);
                break;
            case 3: { int c; bubbleSortNome(comp,n,&c); mostrarComponentes(comp,n); break; }
            case 4: { int c; insertionSortTipo(comp,n,&c); mostrarComponentes(comp,n); break; }
            case 5: { int c; selectionSortPrioridade(comp,n,&c); mostrarComponentes(comp,n); break; }
            case 6:
                buscaBinariaNome(comp,n);
                break;
        }

    }while(op!=0);

    printf("\nSaindo...\n");
    return 0;
}