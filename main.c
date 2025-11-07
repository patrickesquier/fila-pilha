#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5

typedef struct {
    char nomes[MAX][50];
    int inicio, fim, total;
} FilaCircular;

void inicializarFila(FilaCircular *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int filaCheia(FilaCircular *f) {
    return f->total == MAX;
}

int filaVazia(FilaCircular *f) {
    return f->total == 0;
}

void entrarFila(FilaCircular *f, char nome[]) {
    if (filaCheia(f)) {
        printf("\nFila cheia! Não é possível adicionar %s.\n", nome);
        return;
    }
    strcpy(f->nomes[f->fim], nome);
    f->fim = (f->fim + 1) % MAX;
    f->total++;
    printf("%s entrou na fila.\n", nome);
}

void atenderFila(FilaCircular *f) {
    if (filaVazia(f)) {
        printf("\nNenhum cliente na fila.\n");
        return;
    }
    printf("Atendendo: %s\n", f->nomes[f->inicio]);
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
}

void listarFila(FilaCircular *f) {
    if (filaVazia(f)) {
        printf("\nFila vazia.\n");
        return;
    }
    printf("\nClientes na fila:\n");
    int i, pos = f->inicio;
    for (i = 0; i < f->total; i++) {
        printf("%d - %s\n", i + 1, f->nomes[pos]);
        pos = (pos + 1) % MAX;
    }
}

typedef struct {
    char caixas[MAX][50];
    int topo;
} Pilha;

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == MAX - 1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

void empilhar(Pilha *p, char nome[]) {
    if (pilhaCheia(p)) {
        printf("\nPilha cheia! Não é possível empilhar %s.\n", nome);
        return;
    }
    strcpy(p->caixas[++p->topo], nome);
    printf("%s empilhada com sucesso.\n", nome);
}

void desempilhar(Pilha *p) {
    if (pilhaVazia(p)) {
        printf("\nNenhuma caixa na pilha.\n");
        return;
    }
    printf("%s foi retirada do topo.\n", p->caixas[p->topo--]);
}

void topoPilha(Pilha *p) {
    if (pilhaVazia(p)) {
        printf("\nNenhuma caixa no topo.\n");
        return;
    }
    printf("Caixa no topo: %s\n", p->caixas[p->topo]);
}

void listarPilha(Pilha *p) {
    if (pilhaVazia(p)) {
        printf("\nPilha vazia.\n");
        return;
    }
    printf("\nCaixas na pilha (do topo para a base):\n");
    for (int i = p->topo; i >= 0; i--) {
        printf("%s\n", p->caixas[i]);
    }
}

int main() {
    FilaCircular fila;
    Pilha pilha;
    inicializarFila(&fila);
    inicializarPilha(&pilha);

    int opcao;
    char nome[50];

    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Atendimento de Suporte (Fila Circular)\n");
        printf("2. Pilha de Caixas no Depósito\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: {
                int opFila;
                do {
                    printf("\n--- FILA CIRCULAR ---\n");
                    printf("1. Entrar na fila\n2. Atender\n3. Listar\n0. Voltar\nEscolha: ");
                    scanf("%d", &opFila);
                    getchar();

                    if (opFila == 1) {
                        printf("Nome do cliente: ");
                        fgets(nome, 50, stdin);
                        nome[strcspn(nome, "\n")] = '\0';
                        entrarFila(&fila, nome);
                    } else if (opFila == 2)
                        atenderFila(&fila);
                    else if (opFila == 3)
                        listarFila(&fila);

                } while (opFila != 0);
                break;
            }
            case 2: {
                int opPilha;
                do {
                    printf("\n--- PILHA DE CAIXAS ---\n");
                    printf("1. Empilhar\n2. Desempilhar\n3. Mostrar topo\n4. Listar\n0. Voltar\nEscolha: ");
                    scanf("%d", &opPilha);
                    getchar();

                    if (opPilha == 1) {
                        printf("Nome da caixa: ");
                        fgets(nome, 50, stdin);
                        nome[strcspn(nome, "\n")] = '\0';
                        empilhar(&pilha, nome);
                    } else if (opPilha == 2)
                        desempilhar(&pilha);
                    else if (opPilha == 3)
                        topoPilha(&pilha);
                    else if (opPilha == 4)
                        listarPilha(&pilha);

                } while (opPilha != 0);
                break;
            }
        }
    } while (opcao != 0);

    printf("\nEncerrando o programa...\n");
    return 0;
}