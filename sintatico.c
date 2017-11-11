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
#include "analex.h"

Simbolo TabelaSimbolos[QntSimbolos];

FILE *fp;
Token token;
Token tokenNext;
int contlin;

void sintatico()
{
    prog();
}

void prog()
{
    while(!feof (fp))
    {
        analex(fp);
        // Trata declaração de ID's e Funções
        if(tipo())
        {
            analex(fp);
            if(token.tipo == ID)
            {
                analex(fp);
                if(token.tipo == SN && token.valor.codSN == SN_ABRI_PARENTESE)
                {
                    func();                 // Tratamendo do restante da função //
                }
                else if(token.tipo == SN && token.valor.codSN == SN_VIRGULA)
                {
                    while(token.tipo == SN && token.valor.codSN == SN_VIRGULA)
                    {
                        analex(fp);
                        if(token.tipo == ID)
                        {
                            analex(fp);
                        }
                        else
                        {
                            printf("ERRO, Token inesperado na linha %d", contlin);
                            exit(1);
                        }
                    }
                    if(token.tipo == SN && token.valor.codSN == SN_PTO_VIRGULA) {}
                    else
                    {
                        printf("ERRO, Token inesperado na linha %d", contlin);
                        exit(1);
                    }
                }
                else if(token.tipo == SN && token.valor.codSN == SN_PTO_VIRGULA) {}
                else
                {
                    printf("ERRO, Token inesperado na linha %d", contlin);
                    exit(1);
                }
            }
        }
        else if(token.tipo == PR && token.valor.codPR == PR_PROTOTIPO)
        {
            analex(fp);
            if(tipo())
            {
                analex(fp);
                if(token.tipo == ID)
                {
                    analex(fp);
                    if(token.tipo == SN && token.valor.codSN == SN_ABRI_PARENTESE)
                    {
                        tipos_p_opc();
                        if(token.tipo == SN && token.valor.codSN == SN_FECHA_PARENTESE)
                        {
                            analex(fp);
                            if(token.tipo == SN && token.valor.codSN == SN_PTO_VIRGULA) {}
                            else if(token.tipo == SN && token.valor.codSN == SN_VIRGULA)
                            {
                                while(token.tipo == SN && token.valor.codSN == SN_VIRGULA)
                                {
                                    analex(fp);
                                    if(token.tipo == ID)
                                    {
                                        analex(fp);
                                        if(token.tipo == SN && token.valor.codSN == SN_ABRI_PARENTESE)
                                        {
                                            tipos_p_opc();
                                            if(token.tipo == SN && token.valor.codSN == SN_FECHA_PARENTESE)
                                            {
                                                analex(fp);
                                            }
                                            else
                                            {
                                                printf("ERRO, Token inesperado na linha %d", contlin);
                                                exit(1);
                                            }
                                        }
                                        else
                                        {
                                            printf("ERRO, Token inesperado na linha %d", contlin);
                                            exit(1);
                                        }
                                    }
                                    else
                                    {
                                        printf("ERRO, Token inesperado na linha %d", contlin);
                                        exit(1);
                                    }
                                }
                                if(token.tipo == SN && token.valor.codSN == SN_PTO_VIRGULA) {}
                                else
                                {
                                    printf("ERRO, Token inesperado na linha %d", contlin);
                                    exit(1);
                                }
                            }
                            else
                            {
                                printf("ERRO, Token inesperado na linha %d", contlin);
                                exit(1);
                            }
                        }
                        else
                        {
                            printf("ERRO, Token inesperado na linha %d", contlin);
                            exit(1);
                        }
                    }
                    else
                    {
                        printf("ERRO, Token inesperado na linha %d", contlin);
                        exit(1);
                    }
                }
                else
                {
                    printf("ERRO, Token inesperado na linha %d", contlin);
                    exit(1);
                }
            }
            else if(token.tipo == PR && token.valor.codPR == PR_SEM_RETORNO)
            {
                analex(fp);
                if(token.tipo == ID)
                {
                    analex(fp);
                    if(token.tipo == SN && token.valor.codSN == SN_ABRI_PARENTESE)
                    {
                        tipos_p_opc();
                        if(token.tipo == SN && token.valor.codSN == SN_FECHA_PARENTESE)
                        {
                            analex(fp);
                            if(token.tipo == SN && token.valor.codSN == SN_PTO_VIRGULA) {}
                            else if(token.tipo == SN && token.valor.codSN == SN_VIRGULA)
                            {
                                while(token.tipo == SN && token.valor.codSN == SN_VIRGULA)
                                {
                                    analex(fp);
                                    if(token.tipo == ID)
                                    {
                                        analex(fp);
                                        if(token.tipo == SN && token.valor.codSN == SN_ABRI_PARENTESE)
                                        {
                                            tipos_p_opc();
                                            if(token.tipo == SN && token.valor.codSN == SN_FECHA_PARENTESE)
                                            {
                                                analex(fp);
                                            }
                                            else
                                            {
                                                printf("ERRO, Token inesperado na linha %d", contlin);
                                                exit(1);
                                            }
                                        }
                                        else
                                        {
                                            printf("ERRO, Token inesperado na linha %d", contlin);
                                            exit(1);
                                        }
                                    }
                                    else
                                    {
                                        printf("ERRO, Token inesperado na linha %d", contlin);
                                        exit(1);
                                    }
                                }
                                if(token.tipo == SN && token.valor.codSN == SN_PTO_VIRGULA) {}
                                else
                                {
                                    printf("ERRO, Token inesperado na linha %d", contlin);
                                    exit(1);
                                }
                            }
                            else
                            {
                                printf("ERRO, Token inesperado na linha %d", contlin);
                                exit(1);
                            }
                        }
                        else
                        {
                            printf("ERRO, Token inesperado na linha %d", contlin);
                            exit(1);
                        }
                    }
                    else
                    {
                        printf("ERRO, Token inesperado na linha %d", contlin);
                        exit(1);
                    }
                }
                else
                {
                    printf("ERRO, Token inesperado na linha %d", contlin);
                    exit(1);
                }
            }
        }
        else if(token.tipo == PR && token.valor.codPR == PR_SEM_RETORNO)
        {
            analex(fp);
            if(token.tipo == SN && token.valor.codSN == SN_ABRI_PARENTESE)
            {
                func();
            }
            else
            {
                printf("ERRO, Token inesperado na linha %d", contlin);
                exit(1);
            }
        }
        else if(token.tipo == END)
        {
            printf("ANALISE SINTATICA REALIZADA COM SUCESSO");
        }
        else
        {
            printf("ERRO, Token inesperado na linha %d", contlin);
            exit(1);
        }
    }
}

bool tipo()
{
    if(token.tipo == PR && (token.valor.codPR == PR_CARACTER || token.valor.codPR == PR_INTEIRO || token.valor.codPR == PR_REAL || token.valor.codPR == PR_BOOLEANO))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void func() {}

void tipos_p_opc()
{
    analex(fp);
    if(token.tipo == PR && token.valor.codPR == PR_SEM_PARAM)
    {
        analex(fp);
    }
    else if(tipo())
    {
        analex(fp);
        if(token.tipo == ID)
        {
            analex(fp);
            if(token.tipo == SN && token.valor.codSN == SN_VIRGULA)
            {
                while(token.tipo == SN && token.valor.codSN == SN_VIRGULA)
                {
                    analex(fp);
                    if(tipo())
                    {
                        analex(fp);
                        if(token.tipo == ID)
                        {
                            analex(fp);
                        }
                    }
                    else
                    {
                        printf("ERRO, token inesperado na linha %d", contlin);
                        exit(1);
                    }
                }
            }
        }
        else if(token.tipo == SN && token.valor.codSN == SN_VIRGULA)
        {
            while(token.tipo == SN && token.valor.codSN == SN_VIRGULA)
            {
                analex(fp);
                if(tipo())
                {
                    analex(fp);
                    if(token.tipo == ID)
                    {
                        analex(fp);
                    }
                }
                else
                {
                    printf("ERRO, token inesperado na linha %d", contlin);
                    exit(1);
                }
            }
        }
    }
    else
    {
        printf("ERRO, token inesperado na linha %d", contlin);
        exit(1);
    }
    bool op_rel()
    {
        analex(fp);
        if((token.tipo = SN) && (token.valor.codSN == SN_COMPARACAO || token.valor.codSN == SN_DIFERENTE || token.valor.codSN == SN_MENOR_IGUAL || token.valor.codSN == SN_MENOR || token.valor.codSN == SN_MAIOR_IGUAL || token.valor.codSN == SN_MAIOR))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
