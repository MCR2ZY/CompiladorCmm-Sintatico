/**
******************************************************************************
* @file	sintatico.c
* @author Marcelo Henrique, Mauricio Souza
* @version
* @date
* @brief
******************************************************************************
*/

#include "sintatico.h"

Simbolo TabelaSimbolos[QntSimbolos];

FILE *fp;
Token token;
Token tokenNext;

void prog(){
    while(!feof (fp)){
        analex(fp);
        if(token.categoria == PR && (token.codPR == BOOLEANO || token.codPR == CARACTER || token.codPR == INTEIRO || token.codPR == REAL || token.codPR == SEMRETORNO)){
            analex(fp);
            if(token.categoria == ID){
                analex(fp);
            }
            else{
                printf("ID Inesperado");
            }
        }
        if(token.categoria == SN && token.codSN == SN_ABRI_PARENTESE){
            func();
        }
    }
}