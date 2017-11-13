/**
******************************************************************************
* @file	sintatico.h
* @author Marcelo Henrique, Mauricio Souza
* @version  x.x
* @date 08.11.17
* @brief Cabeçalho do Analisador Sintático
******************************************************************************
*/
#ifndef SINTATICO_H_INCLUDED
#define SINTATICO_H_INCLUDED

#include "analex.h"

#define QntSimbolos 100

typedef enum tipoSimbolo{
    BOOLEANO, CARACTER, INTEIRO, REAL, SEMRETORNO
} TipoSimbolo;

typedef enum categoriaSimbolo{
    FUNCAO, PARAMETRO, VARIAVEL
} CategoriaSimbolo;

typedef enum escopoSimbolo{
    GLOBAL, LOCAL
} EscopoSimbolo;


typedef struct simbolo{
    char lexema[TamLexema];
    TipoSimbolo tipo;
    CategoriaSimbolo categoria;
    EscopoSimbolo escopo;
    int excluido; // bool. Verdadeira se função do parametro já foi terminada
} Simbolo;

void sintatico();
void prog(); //ok
bool tipo(); //ok
void tipos_param();//ok
void tipos_p_opc();//ok
void cmd();
void atrib();
int expr(); //ok
int termo(); //ok
int expr_simp(); //ok
int fator(); //ok
bool op_rel(); //ok
void func(); // Adicionada para facilitar tratamento de funções. Não consta na gramatica
void error(); // deixar codigo arrumado parte de erro

extern Simbolo TabelaSimbolos[QntSimbolos];


#endif // SINTATICO_H_INCLUDED
