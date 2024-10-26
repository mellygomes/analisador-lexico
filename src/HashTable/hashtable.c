#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

#define TAM 23

void InicializarTabelaHash(char *ts[]) {
    for (int i = 0; i < TAM; i++) {
        ts[i] = NULL;
    }
}

int FuncHash(int chave) {
    return chave % TAM;
}

int FuncHashStr(char str[]) {
    int tamStr = strlen(str);
    unsigned int hash = 0;

    for (int i = 0; i < tamStr; i++) {
        hash += str[i] * (i+1);
    }

    return hash % TAM;
}

void InserirHash(char *ts[], char *str) {
    int id = FuncHashStr(str);

    while (ts[id] != NULL) {
        id = FuncHash(id + 1);
    }

    // Aloca memória para a string e a copia para a tabela
    ts[id] = malloc(strlen(str) + 1); 
    if (ts[id] != NULL) {
        strcpy(ts[id], str);  // Copia a string para a posição correta na tabela
    } else {
        printf("Erro ao alocar memória para str na tabela\n");
    }

}

char *BuscarHash(char *ts[], char chave[]) {
    int id = FuncHashStr(chave);
    int idInicial = id;  // Armazena o índice inicial (para fazer uma verificacao e evitar um loop infinito no while)

    while (ts[id] != NULL) {
        if (strcmp(ts[id], chave) == 0) {
            return ts[id];
        } else {
            id = FuncHash(id + 1);
            if (id == idInicial) {  // Se voltarmos ao índice original, a tabela foi completamente percorrida
                break;
            }
        }
    }
    return NULL;
}

void MostrarTabela(char *ts[]) {
    for (int i = 0; i < TAM; i++) {
        if (ts[i] != NULL) {
            printf("[%d:\t%s\t\t]\n", i, ts[i]);
        }
    }
}

//A tabela sera iniciada com todas as palavras reservadas
void InserirPalavrasReservadas(char *ts[]) {
    InicializarTabelaHash(ts);
    InserirHash(ts, "program");
    InserirHash(ts, "var");
    InserirHash(ts, "integer");
    InserirHash(ts, "real");
    InserirHash(ts, "begin");
    InserirHash(ts, "end");
    InserirHash(ts, "if");
    InserirHash(ts, "then");
    InserirHash(ts, "else");
    InserirHash(ts, "while");
    InserirHash(ts, "do");
}