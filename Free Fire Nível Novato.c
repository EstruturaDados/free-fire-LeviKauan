#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10 // capacidade máxima total de itens (somando quantidade)

struct Item {
    char nome[30];
    char tipo[20];
    int qtd;
};

struct Item mochila[MAX];
int numTipos = 0;      // número de tipos de itens
int qtdTotalItens = 0; // quantidade total de itens na mochila

void limparTela() {
    for(int i=0;i<20;i++) printf("\n");
}

// função para mostrar os itens no formato solicitado
void listarItens() {
    printf("\n--- ITENS NA MOCHILA (%d/%d) ---\n", qtdTotalItens, MAX);
    printf("------------------------------------------------------------------------------------------\n");
    printf("%-30s | %-30s | %-10s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("------------------------------------------------------------------------------------------\n");
    for(int i=0;i<numTipos;i++)
        printf("%-30s | %-30s | %-10d\n", mochila[i].nome, mochila[i].tipo, mochila[i].qtd);
    printf("------------------------------------------------------------------------------------------\n");
}

void adicionarItem() {
    if(qtdTotalItens >= MAX){
        printf("Mochila cheia!\n");
        return;
    }

    printf("\n=============\nAdicionar novo item\n=============\n");
    printf("Nome do Item: "); scanf("%s", mochila[numTipos].nome);
    printf("Tipo do Item(Arma, Munição, Cura, etc.): "); scanf("%s", mochila[numTipos].tipo);
    int qtd;
    printf("Quantidade: "); scanf("%d", &qtd);

    // verifica se ultrapassa a capacidade máxima
    if(qtdTotalItens + qtd > MAX){
        qtd = MAX - qtdTotalItens; // ajusta para caber na mochila
        printf("Quantidade ajustada para %d para caber na mochila.\n", qtd);
    }

    mochila[numTipos].qtd = qtd;
    qtdTotalItens += qtd;
    numTipos++;

    printf("\nItem adicionado com sucesso!\n");
    listarItens(); // lista automaticamente após adicionar
}

void removerItem() {
    char nome[30];
    int achou = 0;

    printf("\n--- Remover Item ---\n");
    printf("Digite o nome do Item a ser removido: "); scanf("%s", nome);

    for(int i=0;i<numTipos;i++){
        if(strcmp(mochila[i].nome, nome) == 0){
            qtdTotalItens -= mochila[i].qtd; // diminui a quantidade total
            for(int j=i;j<numTipos-1;j++) mochila[j]=mochila[j+1]; // shift
            numTipos--;
            achou = 1;
            printf("Item removido com sucesso!\n");
            break;
        }
    }

    if(!achou) printf("Item nao encontrado!\n");
}

int main() {
    int op;

    do{
        printf("\n====================\n");
        printf("MOCHILA DE SOBREVIVENCIA\n");
        printf("====================\n");
        printf("Itens na Mochila: %d/%d\n\n", qtdTotalItens, MAX);
        printf("1. Adicionar Item (Loot)\n");
        printf("2. Remover Item\n");
        printf("3. Listar itens na mochila\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);

        if(op == 1){
            adicionarItem();
        } else if(op == 2){
            removerItem();
        } else if(op == 3){
            listarItens();
        }

    }while(op != 0);

    printf("Saindo do jogo...\n");
    return 0;
}
