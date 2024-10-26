#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 23

void InicializarTabelaHash(char *t[]);
void InserirPalavrasReservadas(char *ts[]);
int FuncHash(int chave);
int FuncHashStr(char str[]);
void InserirHash(char *t[], char *str);
char *BuscarHash(char *t[], char chave[]);
void MostrarTabela(char *t[]);

#endif