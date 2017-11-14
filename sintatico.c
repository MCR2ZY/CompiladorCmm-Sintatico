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

void sintatico() {
    prog();
}

void prog() {
    while(!feof (fp)) {
        analex(fp);
        // Trata declaração de ID's e Funções
        if(tipo()) {
            analex(fp);
            if(token.tipo == ID) {
                analex(fp);
                if(token.tipo == SN && token.valor.codSN == SN_ABRI_PARENTESE) {
                    func();                 // Tratamendo do restante da função //
                } else if(token.tipo == SN && token.valor.codSN == SN_VIRGULA) {
                    while(token.tipo == SN && token.valor.codSN == SN_VIRGULA) {
                        analex(fp);
                        if(token.tipo == ID) {
                            analex(fp);
                        } else {
                            error();
                        }
                    }
                    if(token.tipo == SN && token.valor.codSN == SN_PTO_VIRGULA) {}
                    else {
                        error();
                    }
                } else if(token.tipo == SN && token.valor.codSN == SN_PTO_VIRGULA) {}
                else {
                    error();
                }
            }
        } else if(token.tipo == PR && token.valor.codPR == PR_PROTOTIPO) {
            analex(fp);
            if(tipo()) {
                analex(fp);
                if(token.tipo == ID) {
                    analex(fp);
                    if(token.tipo == SN && token.valor.codSN == SN_ABRI_PARENTESE) {
                        tipos_p_opc();
                        if(token.tipo == SN && token.valor.codSN == SN_FECHA_PARENTESE) {
                            analex(fp);
                            if(token.tipo == SN && token.valor.codSN == SN_PTO_VIRGULA) {}
                            else if(token.tipo == SN && token.valor.codSN == SN_VIRGULA) {
                                while(token.tipo == SN && token.valor.codSN == SN_VIRGULA) {
                                    analex(fp);
                                    if(token.tipo == ID) {
                                        analex(fp);
                                        if(token.tipo == SN && token.valor.codSN == SN_ABRI_PARENTESE) {
                                            tipos_p_opc();
                                            if(token.tipo == SN && token.valor.codSN == SN_FECHA_PARENTESE) {
                                                analex(fp);
                                            } else {
                                                error();
                                            }
                                        } else {
                                            error();
                                        }
                                    } else {
                                        error();
                                    }
                                }
                                if(token.tipo == SN && token.valor.codSN == SN_PTO_VIRGULA) {}
                                else {
                                    error();
                                }
                            } else {
                                error();
                            }
                        } else {
                            error();
                        }
                    } else {
                        error();
                    }
                } else {
                    error();
                }
            } else if(token.tipo == PR && token.valor.codPR == PR_SEM_RETORNO) {
                analex(fp);
                if(token.tipo == ID) {
                    analex(fp);
                    if(token.tipo == SN && token.valor.codSN == SN_ABRI_PARENTESE) {
                        tipos_p_opc();
                        if(token.tipo == SN && token.valor.codSN == SN_FECHA_PARENTESE) {
                            analex(fp);
                            if(token.tipo == SN && token.valor.codSN == SN_PTO_VIRGULA) {}
                            else if(token.tipo == SN && token.valor.codSN == SN_VIRGULA) {
                                while(token.tipo == SN && token.valor.codSN == SN_VIRGULA) {
                                    analex(fp);
                                    if(token.tipo == ID) {
                                        analex(fp);
                                        if(token.tipo == SN && token.valor.codSN == SN_ABRI_PARENTESE) {
                                            tipos_p_opc();
                                            if(token.tipo == SN && token.valor.codSN == SN_FECHA_PARENTESE) {
                                                analex(fp);
                                            } else {
                                                error();
                                            }
                                        } else {
                                            error();
                                        }
                                    } else {
                                        error();
                                    }
                                }
                                if(token.tipo == SN && token.valor.codSN == SN_PTO_VIRGULA) {}
                                else {
                                    error();
                                }
                            } else {
                                error();
                            }
                        } else {
                            error();
                        }
                    } else {
                        error();
                    }
                } else {
                    error();
                }
            }
        } else if(token.tipo == PR && token.valor.codPR == PR_SEM_RETORNO) {
            analex(fp);
            if(token.tipo == SN && token.valor.codSN == SN_ABRI_PARENTESE) {
                func();
            } else {
                error();
            }
        } else if(token.tipo == END) {
            printf("ANALISE SINTATICA REALIZADA COM SUCESSO");
        } else {
            error();
        }
    }
}

bool tipo() {
    if(token.tipo == PR && (token.valor.codPR == PR_CARACTER || token.valor.codPR == PR_INTEIRO || token.valor.codPR == PR_REAL || token.valor.codPR == PR_BOOLEANO)) {
        return true;
    } else {
        return false;
    }
}

void func() {
    tipos_param();
    analex(fp);
    if(token.tipo == SN && token.valor.codSN == SN_FECHA_PARENTESE) {
        analex(fp);
        if(token.tipo == SN && token.valor.codSN == SN_ABRI_CHAVE) {
            while(token.tipo != SN && token.valor.codSN != SN_FECHA_CHAVE) {
                analex(fp);
                if(tipo()) {
                    analex(fp);
                    if(token.tipo == ID) {
                        analex(fp);
                        while(token.tipo == SN && token.valor.codSN == SN_VIRGULA) {
                            analex(fp);
                            if(token.tipo == ID) {
                                analex(fp);
                            } else {
                                error();
                            }
                        }
                        if(token.tipo == SN && token.valor.codSN == SN_PTO_VIRGULA) {
                            analex(fp);
                        }
                    } else {
                        error();
                    }
                } else if (token.tipo == SN && token.valor.codSN == SN_PTO_VIRGULA) {
                    analex(fp);
                } else {
                    cmd();
                }
            }
        } else {
            error();
        }
    } else {
        error();
    }
}

void tipos_param() {
    analex(fp);
    if(token.tipo == PR && token.valor.codPR == PR_SEM_PARAM) {
        analex(fp);
    } else if(tipo()) {
        analex(fp);
        if(token.tipo == ID) {
            analex(fp);
            if(token.tipo == SN && token.valor.codSN == SN_VIRGULA) {
                while(token.tipo == SN && token.valor.codSN == SN_VIRGULA) {
                    analex(fp);
                    if(tipo()) {
                        analex(fp);
                        if(token.tipo == ID) {
                            analex(fp);
                        } else {
                            error();
                        }
                    } else {
                        error();
                    }
                }
            }
        }
    } else {
        error();
    }
}

void tipos_p_opc() {
    analex(fp);
    if(token.tipo == PR && token.valor.codPR == PR_SEM_PARAM) {
        analex(fp);
    } else if(tipo()) {
        analex(fp);
        if(token.tipo == ID) {
            analex(fp);
            if(token.tipo == SN && token.valor.codSN == SN_VIRGULA) {
                while(token.tipo == SN && token.valor.codSN == SN_VIRGULA) {
                    analex(fp);
                    if(tipo()) {
                        analex(fp);
                        if(token.tipo == ID) {
                            analex(fp);
                        }
                    } else {
                        error();
                    }
                }
            }
        } else if(token.tipo == SN && token.valor.codSN == SN_VIRGULA) {
            while(token.tipo == SN && token.valor.codSN == SN_VIRGULA) {
                analex(fp);
                if(tipo()) {
                    analex(fp);
                    if(token.tipo == ID) {
                        analex(fp);
                    }
                } else {
                    error();
                }
            }
        }
    } else {
        error();
    }
}


void atrib() {
    if(token.tipo == ID) {
        //tratar atribuicao
    }else{
    error();
    }
}

void expr() {
    expr_simp();
    analex(fp);
    if(op_rel()) {
        analex(fp);
        expr_simp();
    }else{
    error();
    }
}
void expr_simp() {
    analex(fp);
    if((token.tipo == SN && (token.valor.codSN == SN_SOMA || token.valor.codSN == SN_SUBTRACAO))) {
        termo();
        if(token.tipo == SN) { // se for SN TEM QUE SER  + ou -
            if(token.valor.codSN == SN_SOMA || token.valor.codSN == SN_SUBTRACAO || token.valor.codSN == SN_OR) {
                analex(fp);
                termo();
            } else {
                error();
            }

        }

    }
    termo(); //tratamento de termo puro (pode ocorrer)
}

void termo() {
    fator();
    analex(fp);
    if(token.tipo == SN && (token.valor.codSN == SN_DIVISAO || token.valor.codSN == SN_AND || token.valor.codSN == SN_MULTIPLICACAO)) {
       while(token.tipo == SN && (token.valor.codSN == SN_DIVISAO || token.valor.codSN == SN_AND || token.valor.codSN == SN_MULTIPLICACAO)) {
        analex(fp);
        fator();
       }
    }
}

void fator() {
    analex(fp);
    if(token.tipo == ID) {
        analex(fp);
        if(token.tipo == SN && token.valor.codSN == SN_ABRI_PARENTESE) {
            analex(fp);
            if(token.tipo == SN && token.valor.codSN == SN_FECHA_PARENTESE) {
                analex(fp);
            } else {
                expr();
                while(token.tipo == SN &&  token.valor.codSN ==  SN_VIRGULA) {
                    expr();
                }
                analex(fp);

            }
        } else {
            analex(fp);
        }

    } else if(token.tipo == CT_I || token.tipo == CT_R || token.tipo == CT_C) {
        analex(fp);
    } else if(token.tipo == SN && token.valor.codSN == SN_ABRI_PARENTESE) {
        expr();
        analex(fp);
        if(token.tipo == SN && token.valor.codSN == SN_FECHA_PARENTESE) {
            }else{
                error();
            }
}
    else if(token.tipo == SN && token.valor.codSN == SN_NEGACAO) {
        fator();
    }else{
    error();
    }
}

bool op_rel() {
    analex(fp);
    if((token.tipo = SN) && (token.valor.codSN == SN_COMPARACAO || token.valor.codSN == SN_DIFERENTE || token.valor.codSN == SN_MENOR_IGUAL || token.valor.codSN == SN_MENOR || token.valor.codSN == SN_MAIOR_IGUAL || token.valor.codSN == SN_MAIOR)) {
        return true;
    } else {
        return false;
    }
}
