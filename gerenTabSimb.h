/**
******************************************************************************
* @file	gerenTabSimb.h
* @author Marcelo Henrique, Mauricio Souza
* @version x.x
* @date 22.11.17
* @brief Gerenciador da Tabela de Simbolos
******************************************************************************
*/

#ifndef GERENTABSIMB_H_INCLUDED
#define GERENTABSIMB_H_INCLUDED

#include "sintatico.h"

#define QntSimbolos 100

typedef enum tipoSimbolo {
    BOOLEANO, CARACTER, INTEIRO, REAL, SEMRETORNO
} TipoSimbolo;

typedef enum categoriaSimbolo {
    FUNCAO, PARAMETRO, VARIAVEL, PROTOTIPO
} CategoriaSimbolo;

typedef enum escopoSimbolo {
    GLOBAL, LOCAL
} EscopoSimbolo;

typedef struct simbolo {
    char lexema[TamLexema];
    TipoSimbolo tipo;
    CategoriaSimbolo categoria;
    EscopoSimbolo escopo;
    int zumbi; // bool. Verdadeira se funcao do parametro ja foi terminada
} Simbolo;

void addTabSimbolo();
bool checaTabSimbolo();
void removeTabSimbolo();

//Funcoes para checagem semantica

void checaPrototipo();
void checaVariavel();

extern Simbolo TabelaSimbolos[QntSimbolos];
extern CategoriaSimbolo catSimbolo;
extern EscopoSimbolo escSimbolo;
extern TipoSimbolo tipSimbolo;

extern Token tokenTabSimb;


#endif // GERENTABSIMB_H_INCLUDED
