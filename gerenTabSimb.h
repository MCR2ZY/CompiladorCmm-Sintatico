#ifndef GERENTABSIMB_H_INCLUDED
#define GERENTABSIMB_H_INCLUDED

#include "sintatico.h"

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
    int zumbi; // bool. Verdadeira se funcao do parametro ja foi terminada
} Simbolo;

void addTabSimbolo();
bool checaTabSimbolo();
void removeTabSimbolo();

extern Simbolo TabelaSimbolos[QntSimbolos];
extern CategoriaSimbolo catSimbolo;
extern EscopoSimbolo escSimbolo;
extern TipoSimbolo tipSimbolo;


#endif // GERENTABSIMB_H_INCLUDED
