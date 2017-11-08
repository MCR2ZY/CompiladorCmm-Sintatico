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
                if(token.categoria == SN && token.codSN == SN_ABRI_PARENTESE)
                    func();
                else if(token.categoria == SN && (token.codSN == SN_PTO_VIRGULA || token.codSN == SN_VIRGULA))
                    decl();
                    analex(fp);
                    if(token.categoria == SN && token.codSN == SN_PTO_VIRGULA){
                        return;
                    }
                    else{
                        print("Token Inesperado!");
                        exit(1);
                    }
                else
                    printf("Token Inesperado!");
                    exit(1);
            }
            else
                printf("Token Inesperado!");
                exit(1);
        }
        else
            printf("Token Inesperado!");
            exit(1);
    }
}

void decl(){
    if(token.codSN == SN_PTO_VIRGULA){
        return;
    }
    else{
        while(token.codSN == SN_VIRGULA){       //Enquanto ocorrer virgula chama func decl_var, para checar se vem ID
            decl_var();
            analex(fp);
        }
    }
}