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
int contlin;

void prog(){
    while(!feof (fp)){
        analex(fp);
        // Trata declaração de ID's e Funções
        if(tipo();){
            analex(fp);
            if(token.tipo == ID){
                analex(fp);
                if(token.tipo == SN && token.codSN == SN_ABRI_PARENTESE){
                    func();
                }
                else if(token.tipo == SN && token.codSN == SN_VIRGULA){
                    while(token.tipo == SN && token.codSN == SN_VIRGULA){
                        analex(fp);
                        if(token.tipo == SN){
                            analex(fp);
                        }
                        else{
                            printf("ERRO, Token inesperado na linha %d", contlin);
                            exit(1);
                        }
                    }
                    analex(fp);
                    if(token.tipo == SN && token.codSN == SN_PTO_VIRGULA)
                    else{
                        printf("ERRO, Token inesperado na linha %d", contlin);
                        exit(1);
                    }
                }
                else if(token.tipo == SN && token.codSN == SN_PTO_VIRGULA)
                else{
                    printf("ERRO, Token inesperado na linha %d", contlin);
                    exit(1);
                }
            }
        }
        else if(token.tipo == PR && token.codPR == PR_PROTOTIPO){
            analex(fp);
            if(tipo();){
                analex(fp);
                if(token.tipo == ID){
                    analex(fp);
                    if(token.tipo == SN && token.codSN == SN_ABRI_PARENTESE){
                        tipos_p_opc();
                        analex(fp);
                        if(token.tipo == SN && token.codSN == SN_FECHA_PARENTESE){
                            analex(fp);
                            if(token.tipo == SN && token.codSN == SN_PTO_VIRGULA)
                            else if(token.tipo == SN && token.codSN == SN_VIRGULA){
                                while(token.tipo == SN && token.codSN == SN_VIRGULA){
                                    analex(fp);
                                    if(token.tipo == ID){
                                        analex(fp);
                                        if(token.tipo == SN && token.codSN == SN_ABRI_PARENTESE){
                                            tipos_p_opc();
                                            analex(fp);
                                            if(token.tipo == SN && token.codSN == SN_FECHA_PARENTESE)
                                            else{
                                                printf("ERRO, Token inesperado na linha %d", contlin);
                                                exit(1);
                                            }
                                            analex(fp);
                                            if(token.tipo == SN && token.codSN == SN_PTO_VIRGULA)
                                            else{
                                                printf("ERRO, Token inesperado na linha %d", contlin);
                                                exit(1);
                                            }
                                        }
                                        else{
                                            printf("ERRO, Token inesperado na linha %d", contlin);
                                            exit(1);
                                        }
                                    }
                                    else{
                                        printf("ERRO, Token inesperado na linha %d", contlin);
                                        exit(1);
                                    }
                                }
                            }
                            else{
                                printf("ERRO, Token inesperado na linha %d", contlin);
                                exit(1);
                            }
                        }
                        else{
                            printf("ERRO, Token inesperado na linha %d", contlin);
                            exit(1);
                        }
                    }
                    else{
                        printf("ERRO, Token inesperado na linha %d", contlin);
                        exit(1);
                    }
                }
                else{
                    printf("ERRO, Token inesperado na linha %d", contlin);
                    exit(1);
                }
            }
            else if(token.tipo == PR && token.codPR == SEMRETORNO){
                analex(fp);
                if(token.tipo == ID){
                    analex(fp);
                    if(token.tipo == SN && token.codSN == SN_ABRI_PARENTESE){
                        tipos_p_opc();
                        analex(fp);
                        if(token.tipo == SN && token.codSN == SN_FECHA_PARENTESE){
                            analex(fp);
                            if(token.tipo == SN && token.codSN == SN_PTO_VIRGULA)
                            else if(token.tipo == SN && token.codSN == SN_VIRGULA){
                                while(token.tipo == SN && token.codSN == SN_VIRGULA){
                                    analex(fp);
                                    if(token.tipo == ID){
                                        analex(fp);
                                        if(token.tipo == SN && token.codSN == SN_ABRI_PARENTESE){
                                            tipos_p_opc();
                                            analex(fp);
                                            if(token.tipo == SN && token.codSN == SN_FECHA_PARENTESE)
                                            else{
                                                printf("ERRO, Token inesperado na linha %d", contlin);
                                                exit(1);
                                            }
                                            analex(fp);
                                            if(token.tipo == SN && token.codSN == SN_PTO_VIRGULA)
                                            else{
                                                printf("ERRO, Token inesperado na linha %d", contlin);
                                                exit(1);
                                            }
                                        }
                                        else{
                                            printf("ERRO, Token inesperado na linha %d", contlin);
                                            exit(1);
                                        }
                                    }
                                    else{
                                        printf("ERRO, Token inesperado na linha %d", contlin);
                                        exit(1);
                                    }
                                }
                            }
                            else{
                                printf("ERRO, Token inesperado na linha %d", contlin);
                                exit(1);
                            }
                        }
                        else{
                            printf("ERRO, Token inesperado na linha %d", contlin);
                            exit(1);
                        }
                    }
                    else{
                        printf("ERRO, Token inesperado na linha %d", contlin);
                        exit(1);
                    }
                }
                else{
                    printf("ERRO, Token inesperado na linha %d", contlin);
                    exit(1);
                }
            }
        }
        else if(token.tipo == PR && token.codPR == SEMRETORNO){
            analex(fp);
            if(token.tipo == SN && token.codSN == SN_ABRI_PARENTESE){
                func();
            }
            else{
                printf("ERRO, Token inesperado na linha %d", contlin);
                exit(1);
            }
        }
        else{
            printf("ERRO, Token inesperado na linha %d", contlin);
            exit(1);
        }
    }
}

bool tipo(){
    if(token.tipo == PR && (token.codPR == CARACTER || token.codPR == INTEIRO || token.codPR == REAL || token.codPR == BOOLEANO)){
        return 1;
    }
    else{
        return 0;
    }
}