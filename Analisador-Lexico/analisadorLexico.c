/*
    O seguinte codigo opera de forma comumente utilizada para a implementacao de automatos finitos e/ou maquinas de turing, onde
    o conteudo do arquivo a ser analisado e lido e inserido numa variavel (fita), que por sua vez e percorrida por outra variavel (head),
    sempre que a funcao obtercaractere() for chamada.
*/

#include "analisadorLexico.h"
#include "tabelasimbolo.h"

void InicializarAnalizadorLexico(AnalisadorLexico *lex) {
    lex->head = 0;    
    lex->numLinha = 1;
    lex->lexema[300] = '\0';
    lex->coluna = 1;

    // abrindo arquivo de entrada e testando caso ocorra erro
    FILE *arquivoEntrada;
    arquivoEntrada = fopen("entrada.txt", "r");
    if (arquivoEntrada == NULL) {
        printf("\nErro ao abrir o arquivo aaa\n");
        exit(EXIT_FAILURE);
    }

    // Aloca memória para armazenar o conteúdo do arquivo
    // Inicialmente, alocamos um tamanho fixo e depois redimensionamos se necessário
    size_t bufferSize = 1024;
    size_t contenize = 0;
    char *buffer = malloc(bufferSize);
    if (buffer == NULL) {
        printf("Erro ao alocar memória\n");
        fclose(arquivoEntrada);
        exit(EXIT_FAILURE);
    }

    // Lê o arquivo em blocos e armazena no buffer
    size_t bytesRead;
    while ((bytesRead = fread(buffer + contenize, 1, bufferSize - contenize - 1, arquivoEntrada)) > 0) {
        contenize += bytesRead;
        if (contenize + 1 >= bufferSize) {
            bufferSize *= 2;
            buffer = realloc(buffer, bufferSize);
            if (buffer == NULL) {
                printf("Erro ao realocar memória\n");
                fclose(arquivoEntrada);
                exit(EXIT_FAILURE);
            }
        }
    }
    
    //terminador nulo ao final da string
    buffer[contenize] = '\0';

    //copia o conteudo do buffer para lex->fita
    strncpy(lex->fita, buffer, sizeof(lex->fita) - 1);
    lex->fita[sizeof(lex->fita) - 1] = '\0'; //arante que a string está terminada

    // Libera a memória do buffer
    free(buffer);
    fclose(arquivoEntrada);
}

void IniciarToken(Token token) {
    strcpy(token.Nome, "\0");
    strcpy(token.ValorLexema, "\0");
    token.linha = 1;
    token.coluna = 1;
}

void AtualizarLinhaColuna(AnalisadorLexico *lex, char c) {
    if (c == '\n') {
        lex->numLinha++;
        lex->coluna = 1;
    } else {
        lex->coluna++;
    }
}

//concatena utilizando como base a ultima posição (ou seja, o tamanho da palavra)
char *concatenarChar(char texto[], char c){
    size_t tam = strlen(texto);
    texto[tam] = c;
    texto[tam + 1] = '\0'; //recolocar terminador nulo
    return texto;
}

//retorna fita no indice indicado por head que será iterada. Concatena caracteres válidos para formar o lexema
char ObterCharactere(AnalisadorLexico *lex) {
    char caractere;
    size_t tamanhoFita = strlen(lex->fita);

    if ((size_t)lex->head < tamanhoFita + 1) {
        caractere = lex->fita[lex->head];
        
        //concatena o character aceito para formar o lexema
        if ((caractere != ' ') && (caractere != '\t')  && (caractere != '\0') && (caractere != '\n')) {
            concatenarChar(lex->lexema, caractere);
        }

        //se o caractere for '/n' o numero de linha sera iterado e coluna reiniciado
        AtualizarLinhaColuna(lex, caractere);
        lex->head++;

    } else {
        printf("ERRO: Algo deu errado. A fita acabou!");
        return '\n';
    }
    return caractere;
}

//inicio da analise
void EstadoInicial(AnalisadorLexico *lex, No *prlist) {
    No *TS = NULL;
    Inserir(&TS, "\0");
    size_t tamanhoFita = strlen(lex->fita);
    while ((size_t)lex->head < tamanhoFita) {

        char c = ObterCharactere(lex);
    
        if (c ==' ') {
            continue;
        } else if (c =='\n') {
            continue;
        } else if (c =='\t') {
            continue;
    
        } else if (isalpha(c)) {
            q1(lex,TS, prlist);

        } else if (isdigit(c)) {
            q2(lex, TS);

        } else if (c == '{') {
            EstadoFinal(lex, TS, "SMB-OBC", lex->lexema, lex->numLinha, lex->coluna);

        } else if (c == '}') {
            EstadoFinal(lex, TS, "SMB-CBC", lex->lexema, lex->numLinha, lex->coluna);

        } else if (c == ',') {
            EstadoFinal(lex, TS, "SMB-COM", lex->lexema, lex->numLinha, lex->coluna);

        } else if (c == '(') {
            EstadoFinal(lex, TS, "SMB-OPA", lex->lexema, lex->numLinha, lex->coluna);

        } else if (c == ')') {
            EstadoFinal(lex, TS, "SMB-CPA", lex->lexema, lex->numLinha, lex->coluna);

        } else if (c == '.') {
            EstadoFinal(lex, TS, "SMB-PFS", lex->lexema, lex->numLinha, lex->coluna);

        } else if (c == ';') {
            EstadoFinal(lex, TS, "SBL-SEM", lex->lexema, lex->numLinha, lex->coluna);

        } else if (c == '=') {
            EstadoFinal(lex, TS, "OP-EQ", lex->lexema, lex->numLinha, lex->coluna);

        } else if (c == '/') {
            EstadoFinal(lex, TS, "OP-DIV", lex->lexema, lex->numLinha, lex->coluna);

        } else if (c == '+') {
            EstadoFinal(lex, TS, "OP-AD", lex->lexema, lex->numLinha, lex->coluna);

        } else if (c == '-') {
            EstadoFinal(lex, TS, "OP-MIN", lex->lexema, lex->numLinha, lex->coluna);

        } else if (c == '*') {
            EstadoFinal(lex, TS, "OP-MUL", lex->lexema, lex->numLinha, lex->coluna);

        } else if (c == ':') {
            char c = ObterCharactere(lex);

            if (c == '=') {
                EstadoFinal(lex, TS, "SMB-ASS", lex->lexema, lex->numLinha, lex->coluna);
                continue;
            }
            
            //garantindo que a ultima posicao seja o caractere nulo finalizador
            lex->lexema[strlen(lex->lexema)] = '\0';
            lex->head--; //voltando o caractere que tinha sido avançado para a verificação
            lex->coluna--;
            EstadoFinal(lex, TS, "SMB-CL", lex->lexema, lex->numLinha, lex->coluna);

        } else if (c == '>') {
            char c = ObterCharactere(lex);

            if (c == '=') {
                EstadoFinal(lex, TS, "OP-GE", lex->lexema, lex->numLinha, lex->coluna);
                continue;
            }

            lex->lexema[strlen(lex->lexema)] = '\0';
            lex->head--;
            lex->coluna--;
            EstadoFinal(lex, TS, "OP-GT", lex->lexema, lex->numLinha, lex->coluna);

        } else if (c == '<') {
            char c = ObterCharactere(lex);

            if (c == '=') {
                EstadoFinal(lex, TS, "OP-LE", lex->lexema, lex->numLinha, lex->coluna);
                continue;
            } else if (c == '>') {
                EstadoFinal(lex, TS, "OP-NE", lex->lexema, lex->numLinha, lex->coluna);
                continue;
            }

            lex->lexema[strlen(lex->lexema)] = '\0';
            lex->head--; //voltando o q charactere que tinha sido avançado para a verificação
            lex->coluna--;
            EstadoFinal(lex, TS, "OP-LT", lex->lexema, lex->numLinha, lex->coluna);

        } else {
            printf("\nERRO: caractere nao reconhecido (linha: %i, coluna: %i)\n\n", lex->numLinha, lex->coluna - 2);
            exit(1);
        }
    }

    //ao fim do loop
    printf("\n\nAnalise lexica finalizada. Um arquivo '.lex' foi gerado com os tokens.\n");
    printf("Consulte a tabela de simbolos com o indice de cada um: \n\n");
    Imprimir(TS);
    printf("(^-^)");
    free(TS);
    exit(EXIT_FAILURE);
}

void q1(AnalisadorLexico *lex, No *TS, No *prlist) {
    char c = ObterCharactere(lex);
    int colum = lex->coluna; //quarda o numero da coluna, pois se um '\n' for lido ela sera reiniciada

    while (isalnum(c)) {//enquanto o caractere for alfanumerico, o lexema (token) continuara sendo formado
        c = ObterCharactere(lex);
    }

    if (c == '\n') { //preciso passar (numLinha - 1) como argumento quando o ultimo caracter lido for \n pq ai ele ja teria reiterado a linha e o lexema aparecia na linha seguinte
        if(Buscar(&prlist, lex->lexema) != NULL) {
            EstadoFinal(lex, TS, "PAL-RES", lex->lexema, lex->numLinha - 1, colum + strlen(lex->lexema)-1);
            return;

        } else {
            EstadoFinal(lex, TS, "ID", lex->lexema, lex->numLinha - 1,  colum + strlen(lex->lexema)-1);
            return;
        }

    } else if ((c == ' ') || (c == '\0')) {
        if(Buscar(&prlist, lex->lexema) != NULL) {
            EstadoFinal(lex, TS, "PAL-RES", lex->lexema, lex->numLinha, lex->coluna);
            return;

        } else {
            EstadoFinal(lex, TS, "ID", lex->lexema, lex->numLinha, lex->coluna);
            return;
        }

    } else if ((isalnum(c) == 0)) {
        lex->lexema[strlen(lex->lexema) - 1] = '\0';
        lex->head--;
        lex->coluna--;
       
        if(Buscar(&prlist, lex->lexema) != NULL) {
            EstadoFinal(lex, TS, "PAL-RES", lex->lexema, lex->numLinha, lex->coluna);
            return;

        } else {
            EstadoFinal(lex, TS, "ID", lex->lexema, lex->numLinha, lex->coluna);
            return;
        }
    }
}

//reconhece numeros inteiros
void q2(AnalisadorLexico *lex, No *TS) {
    lex->lexema[strlen(lex->lexema) - 1] = '\0';
    lex->head--;
    lex->coluna--;
    char c = ObterCharactere(lex);

    while (isdigit(c) != 0) {
        c = ObterCharactere(lex);
        if(c == '.') {
            q3(lex, TS);
            return;      
        } else if (isalpha(c)) {
            printf("\nERRO: Caractere alfabetico invalido nesta posicao (linha: %i, coluna: %i)\n\n", lex->numLinha, lex->coluna - 2);
            exit(EXIT_FAILURE);
        }
    }

    if (c == '\n') {
        EstadoFinal(lex, TS, "NUM_INT", lex->lexema, lex->numLinha - 1, lex->coluna);
        return;

    } else if ((c == ' ') || (c == '\0')) {
        EstadoFinal(lex, TS, "NUM_INT", lex->lexema, lex->numLinha, lex->coluna);
        return;

    } else if ((isdigit(c) == 0)) {
        lex->lexema[strlen(lex->lexema) - 1] = '\0';
        lex->head--;
        lex->coluna--;
        EstadoFinal(lex, TS, "NUM_INT", lex->lexema, lex->numLinha, lex->coluna);
        return;
    }
}

//reconhece numeros float
void q3(AnalisadorLexico *lex, No *TS) {
    char c = ObterCharactere(lex);

    if (isdigit(c) == 0) {
        printf("\n\nERRO: numero real mal formado (linha: %i, coluna: %i)\n\n", lex->numLinha, lex->coluna);
        exit(1);
    }

    while (isdigit(c)) {
        c = ObterCharactere(lex);

        if((c == 'e') || (c == 'E')) {
            q4(lex, TS);
            return;
        } else if (isalpha(c)) {
            printf("\nERRO: Caractere alfabetico invalido nesta posicao (linha: %i, coluna: %i)\n\n", lex->numLinha, lex->coluna - 2);
            exit(1);
        } 
    }

    if (c == '\n') {
        EstadoFinal(lex, TS, "NUM_FLT", lex->lexema, lex->numLinha - 1, lex->coluna);
        return;

    } else if ((c == ' ') || (c == '\0')) {
        EstadoFinal(lex, TS, "NUM_FLT", lex->lexema, lex->numLinha, lex->coluna);
        return;

    } else if ((isdigit(c) == 0)) {
        lex->lexema[strlen(lex->lexema) - 1] = '\0';
        lex->head--;
        lex->coluna--;
        EstadoFinal(lex, TS, "NUM_FLT", lex->lexema, lex->numLinha, lex->coluna);
        return;
    }
}

//reconhece numeros exponenciais
void q4(AnalisadorLexico *lex, No *TS) {
    char c = ObterCharactere(lex);

    if ((isdigit(c)) || (c == '+') || (c == '-')) {
        c = ObterCharactere(lex);
        if (isalpha(c)) {
            printf("\nERRO: Caractere alfabetico invalido nesta posicao (linha: %i, coluna: %i)\n\n", lex->numLinha, lex->coluna - 2);
            exit(1);
        }

        while (isdigit(c)) {
            if (isalpha(c)) {
                printf("\nERRO: Caractere alfabetico invalido nesta posicao (linha: %i, coluna: %i)\n\n", lex->numLinha, lex->coluna - 2);
                exit(1);
            }

            c = ObterCharactere(lex);
        }

    } else if (isdigit(c) == 0) {
        printf("\n\nERRO: numero exponencial mal formado (linha: %i, coluna: %i)\n\n", lex->numLinha, lex->coluna);
        exit(1);
    }

    if (c == '\n') {
        EstadoFinal(lex, TS, "NUM_EXP", lex->lexema, lex->numLinha - 1, lex->coluna);
        return;

    } else if ((c == ' ') || (c == '\0')) {
        EstadoFinal(lex, TS, "NUM_EXP", lex->lexema, lex->numLinha, lex->coluna);
        return;

    } else if ((isdigit(c) == 0)) {
        lex->lexema[strlen(lex->lexema) - 1] = '\0';
        lex->head--;
        lex->coluna--;
        EstadoFinal(lex, TS, "NUM_EXP", lex->lexema, lex->numLinha, lex->coluna);
        return;
    }
}

// Estado Final: insere os tokens no arquivo "listatokens"
Token EstadoFinal(AnalisadorLexico *lex, No *TS, char nome[300], char valor[300], int linha, int coluna) {
    Token token;
    IniciarToken(token);
    strcpy(token.Nome, nome);
    strcpy(token.ValorLexema, valor); 

    token.linha = linha;
    token.coluna = ((coluna - strlen(token.ValorLexema)) - 1);
    if (token.coluna < 1) {
        token.coluna = 1; 
    }

    FILE *arquivoSaida;
    arquivoSaida = fopen("listatoken.lex", "a");
    if (arquivoSaida == NULL) {
        printf("\nERRO: Não foi possível abrir o arquivo de saida\n");
        exit(EXIT_FAILURE);
    }

    if (strcmp(token.Nome, "ID") == 0) {
        int indice = 0;
        indice = BuscarIndice(&TS, token.ValorLexema);
        fprintf(arquivoSaida, "<%s, [%i]> %i, %i\n", token.Nome, indice, token.linha, token.coluna);

    } else if (strcmp(token.Nome, "NUM-INT") == 0) {
        int NumInt = 0;
        NumInt = atoi(lex->lexema);
        fprintf(arquivoSaida, "<%s, \"%i\"> %i, %i\n", token.Nome, NumInt, token.linha, token.coluna);

    } else if (strcmp(token.Nome, "NUM-FLT") == 0 || strcmp(token.Nome, "NUM-EXP") == 0) {
        int NumFlt = 0;
        NumFlt = atof(lex->lexema);
        fprintf(arquivoSaida, "<%s, \"%.f\"> %i, %i\n", token.Nome, NumFlt, token.linha, token.coluna);
    } else {
        fprintf(arquivoSaida, "<%s, \"%s\"> %i, %i\n", token.Nome, lex->lexema, token.linha, token.coluna);
    }

    lex->lexema[0] = '\0';
    fclose(arquivoSaida);

    return token;
}

void IniciarAnaliseLexica(AnalisadorLexico *lex) {
    No *prlist = NULL;
    InicializarAnalizadorLexico(lex);
    InserirPalavrasReservadas(&prlist);
    EstadoInicial(lex, prlist);
    free(prlist);
    free(lex);
}