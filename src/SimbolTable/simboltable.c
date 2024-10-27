#include "simboltable.h"

void Inserir(No **lista, char *str) {
    No *aux; 
    No *novo = malloc(sizeof(No));
    if (novo == NULL) {
        printf("Falha na alocacao de memoria\n");
        exit(EXIT_FAILURE);
    }

    novo->str = malloc(strlen(str) + 1);
    if (novo->str == NULL) {
        printf("Falha na alocacao de memoria para a string\n");
        exit(EXIT_FAILURE);
    }

    strcpy(novo->str, str);
    novo->proximo = NULL;
    if (*lista == NULL) {
        *lista = novo;
    } else {
        aux = *lista;
        while (aux->proximo != NULL) {
            aux = aux->proximo;
        }
        aux->proximo = novo;
    }

}

void Imprimir(No *no) {
    No *aux = no;
    printf("\nTabela de simbolos\n\n");
    while (no) {
        printf("[%i] - %s\n", BuscarIndice(&aux, no->str), no->str);
        no = no->proximo;
    }
    printf("\n\n");
}

int BuscarIndice(No **lista, char str[]) {
    if (*lista == NULL) {
        Inserir(lista, str);
        return 1;
    }

    No *aux = *lista;
    int indice = 1;

    while (aux != NULL) {
    
        if (strcmp(aux->str, str) == 0) {
            return indice;
        }

        aux = aux->proximo;
        indice++; // Incrementa o índice a cada iteração
    }

    if (aux == NULL) {
        Inserir(lista, str);
    }

    return indice;
}