/**
******************************************************************************
* @file	analex.h
* @author Maurício Menezes
* @version  x.x
* @date 10.10.17
* @brief
******************************************************************************
*/
#ifndef ANALEX_H_INCLUDED
#define ANALEX_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define QntPalReservadas 11
#define TamPalReservadas 15
#define QntSinal 21
#define TamSinal 3
#define QntLiteral 100
#define TamLexema 30
#define TamNum 20
#define EOS '\0'
#define tamNomeFile 10

typedef enum palReservada{
    PR_BOOLEANO,        PR_CARACTER,        PR_ENQUANTO,
    PR_INTEIRO,         PR_PARA,            PR_REAL,
    PR_RETORNE,         PR_SE,              PR_SEM_PARAM,
    PR_SEM_RETORNO,     PR_SENAO
}PalReservada;

typedef enum sinal{
    SN_ABRI_CHAVE,          SN_ABRI_PARENTESE,       SN_AND,            SN_ATRIBUICAO,          SN_COMPARACAO,
    SN_DIFERENTE,           SN_DIVISAO,              SN_FECHA_CHAVE,    SN_FECHA_PARENTESE,     SN_MAIOR,
    SN_MAIOR_IGUAL,         SN_MENOR,                SN_MENOR_IGUAL,    SN_MULTIPLICACAO,       SN_NEGACAO,
    SN_OR,                  SN_PTO_VIRGULA,          SN_SOMA,           SN_SUBTRACAO,           SN_VIRGULA
}Sinal;

typedef enum categoria{
    END = -1,   CT_C,       CT_I,
    CT_L,       CT_R,       ID,
    PR,         SN
} Categoria;


typedef struct token{
    Categoria tipo;
    char lexema[TamLexema];
    union campo {
		PalReservada	codPR;
		Sinal			codSN;
		int				valorInt;
		double			valorReal;
		int				posLiteral;
	} valor;
}Token;

extern char TabPalReservadas[QntPalReservadas][TamPalReservadas];
extern char TabSinais[QntSinal][TamSinal];
extern char TabelaLiterais[QntLiteral][TamLexema];
extern int contlin;
extern int ultimoLiteral;

Token analex(FILE *);
Token erroToken();

#endif // ANALEX_H_INCLUDED
