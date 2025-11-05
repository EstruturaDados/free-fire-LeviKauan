#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

typedef struct {
    char nome[30];
    char tipo[20];
    int qtd;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// Vetor
Item mochilaVetor[MAX];
int numItensVetor=0, compSeqV=0, compBinV=0;

// Lista encadeada
No* mochilaLista=NULL;
int compSeqL=0;

// -------------------- Vetor --------------------

void listarVetor(){
    printf("\n====================================\n");
    printf("          ITENS NA MOCHILA           \n");
    printf("       (%d/%d itens)\n", numItensVetor, MAX);
    printf("====================================\n");
    printf("%-30s | %-20s | %-10s\n","NOME","TIPO","QTD");
    printf("------------------------------------------------------------\n");
    for(int i=0;i<numItensVetor;i++)
        printf("%-30s | %-20s | %-10d\n",mochilaVetor[i].nome,mochilaVetor[i].tipo,mochilaVetor[i].qtd);
    printf("------------------------------------------------------------\n");
}

void inserirItemVetor(){
    if(numItensVetor>=MAX){printf("\nMochila cheia!\n"); return;}
    Item novo; getchar();
    printf("\nInserir item\nNome: "); fgets(novo.nome,30,stdin); novo.nome[strcspn(novo.nome,"\n")]=0;
    printf("Tipo: "); fgets(novo.tipo,20,stdin); novo.tipo[strcspn(novo.tipo,"\n")]=0;
    printf("Qtd: "); scanf("%d",&novo.qtd);
    if(novo.qtd<=0){printf("Qtd invalida\n"); return;}
    mochilaVetor[numItensVetor++]=novo;
    printf("Item adicionado!\n");
    listarVetor();
}

void removerItemVetor(){
    char nome[30]; getchar();
    printf("\nRemover item\nNome: "); fgets(nome,30,stdin); nome[strcspn(nome,"\n")]=0;
    int achou=0;
    for(int i=0;i<numItensVetor;i++){
        if(strcmp(mochilaVetor[i].nome,nome)==0){
            achou=1; for(int j=i;j<numItensVetor-1;j++) mochilaVetor[j]=mochilaVetor[j+1];
            numItensVetor--; printf("Item removido!\n"); listarVetor(); break;
        }
    }
    if(!achou) printf("Item nao encontrado\n");
}

void ordenarVetor(){
    for(int i=0;i<numItensVetor-1;i++)
        for(int j=0;j<numItensVetor-i-1;j++)
            if(strcmp(mochilaVetor[j].nome,mochilaVetor[j+1].nome)>0){
                Item tmp=mochilaVetor[j]; mochilaVetor[j]=mochilaVetor[j+1]; mochilaVetor[j+1]=tmp;
            }
    printf("Vetor ordenado\n");
    listarVetor();
}

void buscarSeqVetor(){
    char nome[30]; getchar();
    printf("\nBuscar item (sequencial)\nNome: "); fgets(nome,30,stdin); nome[strcspn(nome,"\n")]=0;
    compSeqV=0; int achou=0;
    for(int i=0;i<numItensVetor;i++){
        compSeqV++;
        if(strcmp(mochilaVetor[i].nome,nome)==0){
            achou=1; printf("Achei: %s | %s | %d\n",mochilaVetor[i].nome,mochilaVetor[i].tipo,mochilaVetor[i].qtd); break;
        }
    }
    if(!achou) printf("Nao achei\n"); 
    printf("Comparacoes: %d\n",compSeqV);
}

void buscarBinVetor(){
    char nome[30]; getchar();
    printf("\nBuscar item (binaria)\nNome: "); fgets(nome,30,stdin); nome[strcspn(nome,"\n")]=0;
    int ini=0,fim=numItensVetor-1,achou=0; compBinV=0;
    while(ini<=fim){
        int m=(ini+fim)/2; compBinV++;
        int c=strcmp(mochilaVetor[m].nome,nome);
        if(c==0){achou=1; printf("Achei: %s | %s | %d\n",mochilaVetor[m].nome,mochilaVetor[m].tipo,mochilaVetor[m].qtd); break;}
        else if(c<0) ini=m+1; else fim=m-1;
    }
    if(!achou) printf("Nao achei\n"); 
    printf("Comparacoes: %d\n",compBinV);
}

// -------------------- Lista --------------------

void listarLista(){
    int count=0; No* aux=mochilaLista;
    while(aux){count++; aux=aux->proximo;}
    printf("\n====================================\n");
    printf("          ITENS NA MOCHILA           \n");
    printf("       (%d/%d itens)\n", count, MAX);
    printf("====================================\n");
    printf("%-30s | %-20s | %-10s\n","NOME","TIPO","QTD");
    printf("------------------------------------------------------------\n");
    aux=mochilaLista;
    while(aux){printf("%-30s | %-20s | %-10d\n",aux->dados.nome,aux->dados.tipo,aux->dados.qtd); aux=aux->proximo;}
    printf("------------------------------------------------------------\n");
}

void inserirItemLista(){
    No* novo=(No*)malloc(sizeof(No)); getchar();
    printf("\nInserir item\nNome: "); fgets(novo->dados.nome,30,stdin); novo->dados.nome[strcspn(novo->dados.nome,"\n")]=0;
    printf("Tipo: "); fgets(novo->dados.tipo,20,stdin); novo->dados.tipo[strcspn(novo->dados.tipo,"\n")]=0;
    printf("Qtd: "); scanf("%d",&novo->dados.qtd);
    if(novo->dados.qtd<=0){printf("Qtd invalida\n"); free(novo); return;}
    novo->proximo=mochilaLista; mochilaLista=novo; printf("Item adicionado!\n");
    listarLista();
}

void removerItemLista(){
    char nome[30]; getchar();
    printf("\nRemover item\nNome: "); fgets(nome,30,stdin); nome[strcspn(nome,"\n")]=0;
    No *at=mochilaLista,*ant=NULL; int achou=0;
    while(at){
        if(strcmp(at->dados.nome,nome)==0){
            achou=1; if(!ant) mochilaLista=at->proximo; else ant->proximo=at->proximo; free(at); printf("Item removido!\n"); listarLista(); break;
        }
        ant=at; at=at->proximo;
    }
    if(!achou) printf("Nao achei\n");
}

void buscarSeqLista(){
    char nome[30]; getchar();
    printf("\nBuscar item (seq lista)\nNome: "); fgets(nome,30,stdin); nome[strcspn(nome,"\n")]=0;
    compSeqL=0; int achou=0; No* aux=mochilaLista;
    while(aux){compSeqL++; if(strcmp(aux->dados.nome,nome)==0){achou=1; printf("Achei: %s | %s | %d\n",aux->dados.nome,aux->dados.tipo,aux->dados.qtd); break;} aux=aux->proximo;}
    if(!achou) printf("Nao achei\n"); printf("Comparacoes: %d\n",compSeqL);
}

// -------------------- Menus --------------------

void menuVetor(){int op; do{
    printf("\n======= MOCHILA (VETOR) =======\nItens: %d/%d\n",numItensVetor,MAX);
    printf("1. Inserir item\n");
    printf("2. Remover item\n");
    printf("3. Listar itens\n");
    printf("4. Ordenar itens por nome\n");
    printf("5. Buscar item (sequencial)\n");
    printf("6. Buscar item (binaria)\n");
    printf("0. Voltar\n");
    printf("Escolha: "); scanf("%d",&op);
    switch(op){case 1:inserirItemVetor();break; case 2:removerItemVetor();break; case 3:listarVetor();break; case 4:ordenarVetor();break; case 5:buscarSeqVetor();break; case 6:buscarBinVetor();break;}
}while(op!=0);}

void menuLista(){int op; do{
    int count=0; No* aux=mochilaLista; while(aux){count++; aux=aux->proximo;}
    printf("\n==== MOCHILA (LISTA) ====\nItens: %d/%d\n", count, MAX);
    printf("1. Inserir item\n");
    printf("2. Remover item\n");
    printf("3. Listar itens\n");
    printf("4. Buscar item (sequencial)\n");
    printf("0. Voltar\n");
    printf("Escolha: "); scanf("%d",&op);
    switch(op){case 1:inserirItemLista();break; case 2:removerItemLista();break; case 3:listarLista();break; case 4:buscarSeqLista();break;}
}while(op!=0);}

// -------------------- Main --------------------

int main(){
    int op; do{
        int countV=0; No* aux=mochilaLista; while(aux){countV++; aux=aux->proximo;}
        printf("\n====== MOCHILA SOBREVIVENCIA ======\n");
        printf("1. Vetor (lista sequencial)\n");
        printf("2. Lista encadeada\n");
        printf("0. Sair\n");
        printf("Escolha: "); scanf("%d",&op);
        switch(op){case 1:menuVetor();break; case 2:menuLista();break;}
    }while(op!=0);
    printf("\nSaindo...\n"); return 0;
}
