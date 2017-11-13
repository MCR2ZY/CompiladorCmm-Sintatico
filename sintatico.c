/**
******************************************************************************
* @file	sintatico.c
* @author Marcelo Henrique, Mauricio Souza
* @version
* @date
* @brief
******************************************************************************
*/
/*
prog() (x)




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

void tipos_param()
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
                        else
                        {
                            printf("ERRO, token inesperado na linha %d", contlin);
                            exit(1);
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
                    else
                    {
                        printf("ERRO, token inesperado na linha %d", contlin);
                        exit(1);
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
}

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
}



int termo()
{
    if(fator())
    {
        analex(fp);
        if(token.tipo == SN && (token.valor.codSN == SN_DIVISAO || token.valor.codSN == SN_AND || token.valor.codSN == SN_MULTIPLICACAO))
        {
            analex(fp);
            if(fator()) {}
            else
            {
                error();
                return 1;
            }
        }
    }
    else
    {
        error();
        return 1;
    }
    return 0;
}
void atrib()
{
    if(token.tipo == ID)
    {

    }
}

int expr()
{
    analex(fp);
    if(expr_simp())
    {
        analex(fp);
        if(op_rel())
        {
            analex(fp);
            if(expr_simp())
            {

            }
            else
            {
                error();
                return 1;
            }
        }
    }


    return 0;
}
int expr_simp()
{
    analex(fp);
    if((token.tipo == SN && (token.valor.codSN == SN_SOMA || token.valor.codSN == SN_SUBTRACAO)) || termo())
    {

        if(token.tipo == SN) // se for SN TEM QUE SER  + ou -
        {
            if(token.valor.codSN == SN_SOMA || token.valor.codSN == SN_SUBTRACAO)
            {

            }
            else
            {
                error();
                return 1;
            }

        }

        if(termo())
        {
            analex(fp);
            if(token.valor.codSN == SN_SOMA || token.valor.codSN == SN_SUBTRACAO || token.valor.codSN == SN_OR || termo())
            {
                while(token.valor.codSN == SN_SOMA || token.valor.codSN == SN_SUBTRACAO || token.valor.codSN == SN_OR)
                {
                    analex(fp);
                    if(termo())
                    {

                    }
                    else
                    {
                        error();
                    }
                }

            }
        }

    }
    return 0;
}

int fator()
{
    if(token.tipo == ID || token.tipo == CT_I || token.tipo == CT_R || token.tipo == CT_C || (token.tipo == SN && token.valor.codSN == SN_NEGACAO))
    {
        analex(fp);
        while(token.tipo == ID || token.tipo == CT_I || token.tipo == CT_R || token.tipo == CT_C || (token.tipo == SN && token.valor.codSN == SN_NEGACAO))
        {
            analex(fp);
            if(token.tipo == ID)
            {
                analex(fp);
                if(token.tipo == SN && token.valor.codSN == SN_ABRI_PARENTESE)
                {
                    analex(fp);
                    if(expr())
                    {
                        analex(fp);
                    }
                    else if(token.tipo == SN && token.valor.codSN == SN_FECHA_PARENTESE)
                    {
                        analex(fp);
                    }
                    else if(token.tipo == SN && token.valor.codSN == SN_VIRGULA)
                    {

                        while(token.tipo == SN && token.valor.codSN == SN_VIRGULA)
                        {
                            if(token.tipo == SN && token.valor.codSN == SN_VIRGULA)
                            {

                            }
                            else
                            {
                                error();
                                return 1;
                            }
                            analex(fp);
                            if(expr())
                            {
                                analex(fp);
                            }
                            else if(token.tipo == SN && token.valor.codSN == SN_FECHA_PARENTESE)
                            {
                                analex(fp);
                            }
                        }
                    }
                }


            }

        }


        if(token.tipo == SN && token.valor.codSN == SN_NEGACAO)
        {
            analex(fp);
            if(fator())
            {
                analex(fp);
            }
            else
            {
                error();
                return 1;
            }
        }

    }
    return 0;
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
