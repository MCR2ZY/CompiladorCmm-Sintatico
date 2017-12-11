/**
******************************************************************************
* @file	gerenTabSimb.c
* @author Marcelo Henrique, Mauricio Souza
* @version x.x
* @date 22.11.17
* @brief Cabeçalho Gerenciador da Tabela de Simbolos
******************************************************************************
*/

#include "gerenTabSimb.h"

Simbolo TabelaSimbolos[QntSimbolos];
CategoriaSimbolo catSimbolo;
EscopoSimbolo escSimbolo;
TipoSimbolo tipSimbolo;
int topo = 0, i;
Token tokenTabSimb;

void addTabSimbolo() {
    if(!checaTabSimbolo()) {
        strcpy(TabelaSimbolos[topo].lexema, tokenTabSimb.lexema);
        TabelaSimbolos[topo].tipo = tipSimbolo;
        TabelaSimbolos[topo].categoria = catSimbolo;
        TabelaSimbolos[topo].escopo = escSimbolo;
        TabelaSimbolos[topo].zumbi = 0;
        topo++;
    } else {
        printf("\nErro, Redeclaracao!!!\n");
        exit(EXIT_FAILURE);
    }
}

void removeTabSimbolo() {
    while(TabelaSimbolos[topo].categoria != PARAMETRO && topo != 0) {
        topo --;
    }
    for(i = topo; TabelaSimbolos[i].categoria != FUNCAO && i != 0; i--) {
        TabelaSimbolos[i].zumbi = 1;
    }
}

bool checaTabSimbolo() {
    if(catSimbolo == FUNCAO || escSimbolo == GLOBAL) {
        for(i = topo -1; i >= 0 ; i--) {
            if(!strcmp(TabelaSimbolos[i].lexema, tokenTabSimb.lexema) && (TabelaSimbolos[i].zumbi == 0 && TabelaSimbolos[i].escopo == escSimbolo)) {
                return true;
            }
        }
        return false;
    } else {
        for(i = topo -1; i >= 0 && TabelaSimbolos[i].categoria != FUNCAO ; i--) {
            if(!strcmp(TabelaSimbolos[i].lexema, tokenTabSimb.lexema) && (TabelaSimbolos[i].zumbi == 0 && TabelaSimbolos[i].escopo == escSimbolo)) {
                return true;
            }
        }
        return false;
    }
}
