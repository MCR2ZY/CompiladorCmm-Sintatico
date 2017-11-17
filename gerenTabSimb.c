#include "gerenTabSimb.h"

Simbolo TabelaSimbolos[QntSimbolos];
CategoriaSimbolo catSimbolo;
EscopoSimbolo escSimbolo;
TipoSimbolo tipSimbolo;
int topo, i;
Token token;
Token tokenNext;
topo = 0;

void addTabSimbolo(){
    if(!checaTabSimbolo()){
        TabelaSimbolos[topo].lexema = token.lexema;
        TabelaSimbolos[topo].tipo = tipSimbolo;
        TabelaSimbolos[topo].categoria = catSimbolo;
        TabelaSimbolos[topo].escopo = escSimbolo;
        TabelaSimbolos[topo].escopo = escSimbolo;
        TabelaSimbolos[topo].zumbi = 0;
        topo++;
    } else {
        printf("\nErro, Redeclaracao!!!\n");
        exit(1);
    } 
}

void removeTabSimbolo(){
    for(i = topo; TabelaSimbolos[i].categoria != PARAMETRO; topo--){
    }
    for(i = topo; TabelaSimbolos[i].categoria != FUNCAO; i--){
        TabelaSimbolos[i].zumbi = 1;
    }
}

bool checaTabSimbolo(){
    for(i = 0; i< topo; i++){
        if(TabelaSimbolos[i].lexema == token.lexema && TabelaSimbolos[i].escopo == escSimbolo && TabelaSimbolos[i].zumbi = 0){
            return true;
        }
    }
    return false;
}
