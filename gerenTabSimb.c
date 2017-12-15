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
int topo = -1, i;
Token tokenTabSimb, token;

int qntParamProtot, qntParamFunc;

void addTabSimbolo() {
    if(!checaTabSimbolo()) {
        topo++;
        strcpy(TabelaSimbolos[topo].lexema, tokenTabSimb.lexema);
        TabelaSimbolos[topo].tipo = tipSimbolo;
        TabelaSimbolos[topo].categoria = catSimbolo;
        TabelaSimbolos[topo].escopo = escSimbolo;
        TabelaSimbolos[topo].zumbi = 0;
    } else {
        printf("\nErro, Redeclaracao na linha %d!!!\n", contlin);
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
    if(catSimbolo == PROTOTIPO || (catSimbolo == VARIAVEL && escSimbolo == GLOBAL)) {
        for(i = topo; i >= 0 ; i--) {
            if(!strcmp(TabelaSimbolos[i].lexema, tokenTabSimb.lexema) && (TabelaSimbolos[i].zumbi == 0 && TabelaSimbolos[i].escopo == escSimbolo)) {
                return true;
            }
        }
        return false;
    } else if(catSimbolo == FUNCAO) {
        for(i = topo; i >= 0 ; i--) {
            if(!strcmp(TabelaSimbolos[i].lexema, tokenTabSimb.lexema) && (TabelaSimbolos[i].zumbi == 0 && TabelaSimbolos[i].escopo == escSimbolo) && TabelaSimbolos[i].categoria != PROTOTIPO) {
                return true;
            }
        }
        return false;
    } else {
        for(i = topo; i >= 0 && TabelaSimbolos[i].categoria != FUNCAO ; i--) {
            if(!strcmp(TabelaSimbolos[i].lexema, tokenTabSimb.lexema) && (TabelaSimbolos[i].zumbi == 0 && TabelaSimbolos[i].escopo == escSimbolo) && strcmp(tokenTabSimb.lexema, "lixo") != 0) {
                return true;
            }
        }
        return false;
    }
}

void checaPrototipo() {
    int prototAux, funcAux;

    prototAux = funcAux = topo;

    while(TabelaSimbolos[funcAux].categoria != FUNCAO) {        //VARRE ATE A FUNCAO
        funcAux--;
    }
    while((TabelaSimbolos[prototAux].categoria != PROTOTIPO || strcmp(TabelaSimbolos[funcAux].lexema, TabelaSimbolos[prototAux].lexema) != 0) && prototAux > -1) {     //VARRE ATE O PROTOTIPO DA FUNCAO
        prototAux--;
    }

    if(prototAux == -1 && TabelaSimbolos[prototAux].categoria != PROTOTIPO){     //Funcao sem prototipo
        return;
    }

    for(i = prototAux + 1; TabelaSimbolos[i].categoria == PARAMETRO; i++) {     //Conta parametros do prototipo
        qntParamProtot++;
    }
    for(i = funcAux + 1; i <= topo; i++) {       //Conta parametros da função
        qntParamFunc++;
    }

    if(qntParamFunc != qntParamProtot) {
        printf("Conflict to numbers for parametrs. line: %d\n", contlin);
        exit(EXIT_FAILURE);
    }

    //Funcao com prototipo; CHECA OS TIPOS
    if(TabelaSimbolos[prototAux].tipo == TabelaSimbolos[funcAux].tipo) {
        funcAux++;
        prototAux++;

        if(qntParamFunc + qntParamProtot == 0) {
            return;
        }

        while(TabelaSimbolos[prototAux].categoria == PARAMETRO) {
            if(TabelaSimbolos[prototAux].tipo == TabelaSimbolos[funcAux].tipo) {
                funcAux++;
                prototAux++;
            } else {
                printf("Conflict Tipe to parametrs. line: %d\n", contlin);
                exit(EXIT_FAILURE);
            }
        }
        return;
    } else {
        printf("Conflict Tipe to Func and Prototype. line: %d\n", contlin);
        exit(EXIT_FAILURE);
    }
}

void checaVariavel() {
    int test, i;
    test = 0;

    for(i = topo; i >= 0 && TabelaSimbolos[i].categoria != FUNCAO; i--) {
        if(!strcmp(TabelaSimbolos[i].lexema, token.lexema)){
            test = 1;
        }
    }
    for(i = topo; i >= 0; i--) {
        if(!strcmp(TabelaSimbolos[i].lexema, token.lexema) && TabelaSimbolos[i].escopo == GLOBAL && TabelaSimbolos[i].categoria == VARIAVEL) {
            test = 1;
        }
    }

    if(test == 0) {
       printf("Variavel nao declarada. line: %d\n", contlin);
       exit(EXIT_FAILURE);
    }
}
