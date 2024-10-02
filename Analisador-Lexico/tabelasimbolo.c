#include "tabelasimbolo.h"

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
    while (no) {
        printf("[%i] - %s\n", BuscarIndice(&aux, no->str), no->str);
        no = no->proximo;
    }
    printf("\n\n");
}

char *Buscar(No **lista, char str[]) {
    No *aux = *lista;
    char *strfound = NULL;

    // Percorre a lista enquanto não achar a string
    while (aux != NULL) {
        // Compara as strings usando strcmp
        if (strcmp(aux->str, str) == 0) { // strcmp retorna 0 quando as strings são iguais
            strfound = aux->str;
            break;
        }
        aux = aux->proximo;
    }

    return strfound; // Retorna a string encontrada ou NULL se não encontrou
}

int BuscarIndice(No **lista, char str[]) {
    No *aux = *lista;
    int indice = 0;
    while (aux != NULL) {
    
        if (strcmp(aux->str, str) == 0) {
            // printf("%s e %s\n", aux->str, str);
            break;
        }

        aux = aux->proximo;
        indice++; // Incrementa o índice a cada iteração
    }

    if (aux == NULL) {
        Inserir(lista, str);

    }

    return indice;
}

void InserirPalavrasReservadas(No **lista) {
    Inserir(lista, "program");
    Inserir(lista, "var");
    Inserir(lista, "integer");
    Inserir(lista, "real");
    Inserir(lista, "begin");
    Inserir(lista, "end");
    Inserir(lista, "if");
    Inserir(lista, "then");
    Inserir(lista, "else");
    Inserir(lista, "while");
    Inserir(lista, "do");
}