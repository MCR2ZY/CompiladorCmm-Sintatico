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

#include "lexico.h"

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

void prog();
bool tipo();
void tipos_param();
void tipos_p_opc();
void cmd();
void atrib();
void expr();
void expr_simp();
void termo();
void fator();
bool op_rel();
void func(); // Adicionada para facilitar tratamento de funções. Não consta na gramatica

extern Simbolo TabelaSimbolos[QntSimbolos];


#endif // SINTATICO_H_INCLUDED
