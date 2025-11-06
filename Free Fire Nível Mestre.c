#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX 20

// Enumeração para critérios de ordenação
typedef enum {
    NOME = 1,
    TIPO,
    PRIORIDADE
} Ordenacao;

// Estrutura do componente
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade; // valor de 1 a 10
} Componente;

// Variáveis globais
Componente mochila[MAX];
int numItens = 0;
bool ordenadoPorNome = false;

// -------------------- Funções Auxiliares --------------------

// Mostrar todos os componentes
void mostrarComponentes() {
    printf("\n================= MOCHILA =================\n");
    printf("%-30s | %-20s | %-10s\n", "NOME", "TIPO", "PRIORIDADE");
    printf("---------------------------------------------------------------\n");
    for(int i=0;i<numItens;i++)
        printf("%-30s | %-20s | %-10d\n", mochila[i].nome, mochila[i].tipo, mochila[i].prioridade);
    printf("---------------------------------------------------------------\n");
}

// Medir tempo de execução de uma ordenação
void medirTempo(void (*algoritmo)(Componente[], int, int*), Componente itens[], int n, int *comparacoes) {
    clock_t start = clock();
    algoritmo(itens, n, comparacoes);
    clock_t end = clock();
    double tempo = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Tempo de execucao: %.6f s\n", tempo);
    printf("Comparacoes realizadas: %d\n", *comparacoes);
}

// -------------------- Ordenações --------------------

// Bubble Sort por nome
void bubbleSortNome(Componente itens[], int n, int *comparacoes) {
    *comparacoes = 0;
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            (*comparacoes)++;
            if(strcmp(itens[j].nome,itens[j+1].nome)>0){
                Componente tmp=itens[j]; itens[j]=itens[j+1]; itens[j+1]=tmp;
            }
        }
    }
    ordenadoPorNome = true;
}

// Insertion Sort por tipo
void insertionSortTipo(Componente itens[], int n, int *comparacoes) {
    *comparacoes = 0;
    for(int i=1;i<n;i++){
        Componente key=itens[i];
        int j=i-1;
        while(j>=0 && (++(*comparacoes) && strcmp(itens[j].tipo,key.tipo)>0)){
            itens[j+1]=itens[j];
            j--;
        }
        itens[j+1]=key;
    }
    ordenadoPorNome = false;
}

// Selection Sort por prioridade
void selectionSortPrioridade(Componente itens[], int n, int *comparacoes) {
    *comparacoes=0;
    for(int i=0;i<n-1;i++){
        int min=i;
        for(int j=i+1;j<n;j++){
            (*comparacoes)++;
            if(itens[j].prioridade<itens[min].prioridade){
                min=j;
            }
        }
        Componente tmp=itens[i]; itens[i]=itens[min]; itens[min]=tmp;
    }
    ordenadoPorNome=false;
}

// -------------------- Busca --------------------

// Busca binária por nome (apenas se estiver ordenada por nome)
int buscaBinariaPorNome(Componente itens[], int n, char chave[]) {
    if(!ordenadoPorNome){
        printf("ERRO: Lista precisa estar ordenada por NOME para busca binaria!\n");
        return -1;
    }
    int ini=0, fim=n-1;
    int comparacoes=0;
    while(ini<=fim){
        int meio=(ini+fim)/2;
        comparacoes++;
        int c=strcmp(itens[meio].nome,chave);
        if(c==0){
            printf("Item encontrado!\nNome: %s | Tipo: %s | Prioridade: %d\n",itens[meio].nome,itens[meio].tipo,itens[meio].prioridade);
            printf("Comparacoes realizadas: %d\n",comparacoes);
            return meio;
        } else if(c<0) ini=meio+1; else fim=meio-1;
    }
    printf("Item NAO encontrado\n");
    printf("Comparacoes realizadas: %d\n",comparacoes);
    return -1;
}

// -------------------- Cadastro --------------------

// Inserir novo componente
void inserirItem(){
    if(numItens>=MAX){printf("Mochila cheia!\n"); return;}
    Componente novo;

    // Limpa buffer corretamente antes de cada fgets
    int c;
    while((c=getchar()) != '\n' && c != EOF);

    printf("Nome do componente: ");
    fgets(novo.nome,30,stdin);
    novo.nome[strcspn(novo.nome,"\n")]=0;

    printf("Tipo do componente: ");
    fgets(novo.tipo,20,stdin);
    novo.tipo[strcspn(novo.tipo,"\n")]=0;

    printf("Prioridade (1-10): "); 
    scanf("%d",&novo.prioridade);

    if(novo.prioridade<1 || novo.prioridade>10){
        printf("Prioridade invalida!\n"); 
        return;
    }
    mochila[numItens++] = novo;
    printf("Componente adicionado!\n");
}

// -------------------- Menu --------------------

void menu(){
    int op;
    do{
        printf("\n====== MOCHILA DA TORRE DE FUGA ======\n");
        printf("Itens cadastrados: %d/%d\n",numItens,MAX);
        printf("1 - Inserir componente\n");
        printf("2 - Mostrar componentes\n");
        printf("3 - Ordenar por NOME (Bubble Sort)\n");
        printf("4 - Ordenar por TIPO (Insertion Sort)\n");
        printf("5 - Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("6 - Buscar componente por NOME (binaria)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: "); scanf("%d",&op); getchar();
        int comparacoes;
        char chave[30];
        switch(op){
            case 1: inserirItem(); break;
            case 2: mostrarComponentes(); break;
            case 3: 
                printf("Ordenando por NOME...\n");
                medirTempo(bubbleSortNome,mochila,numItens,&comparacoes);
                mostrarComponentes();
                break;
            case 4:
                printf("Ordenando por TIPO...\n");
                medirTempo(insertionSortTipo,mochila,numItens,&comparacoes);
                mostrarComponentes();
                break;
            case 5:
                printf("Ordenando por PRIORIDADE...\n");
                medirTempo(selectionSortPrioridade,mochila,numItens,&comparacoes);
                mostrarComponentes();
                break;
            case 6:
                printf("Digite o NOME do componente chave: ");
                fgets(chave,30,stdin); chave[strcspn(chave,"\n")]=0;
                buscaBinariaPorNome(mochila,numItens,chave);
                break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    }while(op!=0);
}

// -------------------- Main --------------------

int main(){
    printf("=== DESAFIO NÍVEL MESTRE: TORRE DE FUGA ===\n");
    menu();
    return 0;
}
