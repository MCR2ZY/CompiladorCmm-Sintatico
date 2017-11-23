/**
******************************************************************************
* @file	sintatico.c
* @author Marcelo Henrique, Mauricio Souza
* @version x.x
* @date 22.11.17
* @brief Analisador Sintatico
******************************************************************************
*/

#include "sintatico.h"
#include "analex.h"
#include "gerenTabSimb.h"

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
        // Trata declaracao de ID's e Funcoes
        if(tipo()) {
            analex(fp);
            if(token.tipo == ID) {
                analex(fp);
                if(token.tipo == SN && token.valor.codSN == SN_ABRI_PARENTESE) {
                    func();                 // Tratamendo do restante da funcao //
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
            if(token.tipo == ID) {
                analex(fp);
                if(token.tipo == SN && token.valor.codSN == SN_ABRI_PARENTESE) {
                    func();
                } else {
                    error();
                }
            }
        } else if(token.tipo == END) {
            printf("ANALISE SINTATICA REALIZADA COM SUCESSO");
        } else {
            error();
        }
    }
}

void func() {
    tipos_param();
    if(token.tipo == SN && token.valor.codSN == SN_FECHA_PARENTESE) {
        analex(fp);
        if(token.tipo == SN && token.valor.codSN == SN_ABRI_CHAVE) {
            analex(fp);
            if(tipo()) {
                while(tipo()) {
                    analex(fp);
                    if(token.tipo == ID) {
                        analex(fp);
                        if(token.tipo == SN && token.valor.codSN == SN_VIRGULA) {
                            while(token.tipo == SN && token.valor.codSN == SN_VIRGULA) {
                                analex(fp);
                                if(token.tipo == ID) {
                                    analex(fp);
                                } else {
                                    error();
                                }
                            }
                            if (token.tipo == SN && token.valor.codSN == SN_PTO_VIRGULA) {
                                analex(fp);
                            } else {
                                error();
                            }
                        } else if(token.tipo == SN && token.valor.codSN == SN_PTO_VIRGULA) {
                            analex(fp);
                            if(token.tipo != SN || token.valor.codSN != SN_FECHA_CHAVE) {
                                while(token.tipo != SN || token.valor.codSN != SN_FECHA_CHAVE) {
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
            }
            if(token.tipo != SN || token.valor.codSN != SN_FECHA_CHAVE) {
                while(token.tipo != SN || token.valor.codSN != SN_FECHA_CHAVE) {
                    cmd();
                    analex(fp);
                }
            }
        } else {
            error();
        }
    } else {
        error();
    }
}

bool tipo() {
    if(token.tipo == PR && (token.valor.codPR == PR_CARACTER || token.valor.codPR == PR_INTEIRO || token.valor.codPR == PR_REAL || token.valor.codPR == PR_BOOLEANO)) {
        return true;
    } else {
        return false;
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

void cmd() {
    if(token.tipo == PR && token.valor.codPR == PR_SE) {
        analex(fp);
        if(token.tipo == SN && token.valor.codSN == SN_ABRI_PARENTESE) {
            analex(fp);
            expr();
            if(token.tipo == SN && token.valor.codSN == SN_FECHA_PARENTESE) {
                cmd();
                analex(fp);
                if(token.tipo == PR && token.valor.codPR == PR_SENAO) {
                    cmd();
                }
            } else {
                error();
            }
        } else {
            error();
        }
    } else if(token.tipo == PR && token.valor.codPR == PR_ENQUANTO) {
        analex(fp);
        if(token.tipo == SN && token.valor.codSN == SN_ABRI_PARENTESE) {
            expr();
            analex(fp);
            if(token.tipo == SN && token.valor.codSN == SN_FECHA_PARENTESE) {
                cmd();
            } else {
                error();
            }
        } else {
            error();
        }
    } else if(token.tipo == PR && token.valor.codPR == PR_PARA) {
        analex(fp);
        if(token.tipo == SN && token.valor.codSN == SN_ABRI_PARENTESE) {
            analex(fp);
            if(token.tipo == SN && token.valor.codSN == SN_PTO_VIRGULA) {
                analex(fp);
                if(token.tipo == SN && token.valor.codSN == SN_PTO_VIRGULA) {
                    analex(fp);
                    if(token.tipo == SN && token.valor.codSN == SN_FECHA_PARENTESE) {
                        analex(fp);
                        cmd();
                    } else {
                        atrib();
                        analex(fp);
                        if(token.tipo == SN && token.valor.codSN == SN_FECHA_PARENTESE) {
                            analex(fp);
                            cmd();
                        } else {
                            error();
                        }
                    }
                } else {
                    expr();
                    analex(fp);
                    if(token.tipo == SN && token.valor.codSN == SN_FECHA_PARENTESE) {
                        analex(fp);
                        cmd();
                    } else {
                        atrib();
                        analex(fp);
                        if(token.tipo == SN && token.valor.codSN == SN_FECHA_PARENTESE) {
                            analex(fp);
                            cmd();
                        } else {
                            error();
                        }
                    }
                }
            } else {
                atrib();
                if(token.tipo == SN && token.valor.codSN == SN_PTO_VIRGULA) {
                    analex(fp);
                    if(token.tipo == SN && token.valor.codSN == SN_PTO_VIRGULA) {
                        analex(fp);
                        if(token.tipo == SN && token.valor.codSN == SN_FECHA_PARENTESE) {
                        analex(fp);
                        cmd();
                        } else {
                            expr();
                            analex(fp);
                            if(token.tipo == SN && token.valor.codSN == SN_FECHA_PARENTESE) {
                                analex(fp);
                                cmd();
                            } else {
                                atrib();
                                analex(fp);
                                if(token.tipo == SN && token.valor.codSN == SN_FECHA_PARENTESE) {
                                    analex(fp);
                                    cmd();
                                } else {
                                    error();
                                }
                            }
                        }
                    } else {
                        expr();
                        if(token.tipo == SN && token.valor.codSN == SN_PTO_VIRGULA) {
                            analex(fp);
                            if(token.tipo == SN && token.valor.codSN == SN_FECHA_PARENTESE) {
                                analex(fp);
                                cmd();
                            } else {
                                atrib(fp);
                                if(token.tipo == SN && token.valor.codSN == SN_FECHA_PARENTESE) {
                                    analex(fp);
                                    cmd();
                                } else {
                                    error();
                                }
                            }
                        } else {
                            error();
                        }
                    }
                } else {
                    error();
                }
            }
        } else {
            error();
        }
    } else if(token.tipo == PR && token.valor.codPR == PR_RETORNE) {
        analex(fp);
        if(token.tipo != SN || token.valor.codSN != SN_PTO_VIRGULA) {
            expr();
            analex(fp);
            if(token.tipo == SN && token.valor.codSN == SN_PTO_VIRGULA) {
                analex(fp);
            } else {
                error();
            }
        }
    } else if(token.tipo == ID) {
        if(tokenNext.tipo == SN && tokenNext.valor.codSN == SN_ATRIBUICAO) {
            atrib();
        } else if(tokenNext.tipo == SN && tokenNext.valor.codSN == SN_ABRI_PARENTESE) {
            analex(fp);
            analex(fp);
            if(token.tipo == SN && token.valor.codSN == SN_FECHA_PARENTESE) {
                analex(fp);
                if(token.tipo == SN && token.valor.codSN == SN_PTO_VIRGULA) {
                    analex(fp);
                } else {
                    error();
                }
            } else {
                expr();
                if(token.tipo == SN && token.valor.codSN == SN_VIRGULA) {
                    while(token.tipo == SN && token.valor.codSN == SN_VIRGULA) {
                        expr();
                    }
                    analex(fp);
                    if(token.tipo == SN && token.valor.codSN == SN_FECHA_PARENTESE) {
                        analex(fp);
                        if(token.tipo == SN && token.valor.codSN == SN_PTO_VIRGULA) {
                            analex(fp);
                        } else {
                            error();
                        }
                    } else {
                        error();
                    }
                } else if(token.tipo == SN && token.valor.codSN == SN_FECHA_PARENTESE) {
                    analex(fp);
                    if(token.tipo == SN && token.valor.codSN == SN_PTO_VIRGULA) {
                    } else {
                        error();
                    }
                } else {
                    error();
                }
            }
        } else {
            error();
        }
    } else if(token.tipo == SN && token.valor.codSN == SN_ABRI_CHAVE) {
        analex(fp);
        if(token.tipo != SN || token.valor.codSN != SN_FECHA_CHAVE) {
            while(token.tipo != SN || token.valor.codSN != SN_FECHA_CHAVE) {
                cmd();
            }
        } else {
            error();
        }
    } else if(token.tipo == SN && token.valor.codSN == SN_PTO_VIRGULA) {
        return;
    } else {
        error();
    }
}

void atrib() {
    analex(fp);
    if(token.tipo == ID) {
        analex(fp);
        if(token.tipo == SN && token.valor.codSN == SN_ATRIBUICAO) {
            expr();
        } else {
            error();
        }
    } else {
        error();
    }
    return;
}

void expr() {
    expr_simp();
    if(op_rel) {
        expr_simp();
    }
    return;
}

void expr_simp() {
    if(token.tipo == SN && (token.valor.codSN == SN_SOMA || token.valor.codSN == SN_SUBTRACAO)) {
        analex(fp);
        termo();
        while(token.tipo == SN && (token.valor.codSN == SN_SOMA || token.valor.codSN == SN_SUBTRACAO || token.valor.codSN == SN_OR)) {
            analex(fp);
            termo();
        }
    } else {
        analex(fp);
        termo();
        while(token.tipo == SN && (token.valor.codSN == SN_SOMA || token.valor.codSN == SN_SUBTRACAO || token.valor.codSN == SN_OR)) {
            analex(fp);
            termo();
        }
    }
    return;
}

void termo() {
    fator();
    while(tokenNext.tipo == SN && (tokenNext.valor.codSN == SN_MULTIPLICACAO || tokenNext.valor.codSN == SN_DIVISAO || tokenNext.valor.codSN == SN_AND)) {
        analex(fp);
        fator();;
    }
    return;
}

void fator() {
    if(token.tipo == CT_I || token.tipo == CT_R || token.tipo == CT_C || token.tipo == CT_L) {
        return;
    } else if(token.tipo == ID) {
        if(tokenNext.tipo == SN && tokenNext.valor.codSN == SN_ABRI_PARENTESE) {
            analex(fp);
            if(tokenNext.tipo == SN && tokenNext.valor.codSN == SN_FECHA_PARENTESE) {
                analex(fp);
                return;
            } else {
                expr();
                while(token.tipo == SN && token.valor.codSN == SN_VIRGULA) {
                    expr();
                }
                if(token.tipo == SN && token.valor.codSN == SN_FECHA_PARENTESE) {
                    return;
                } else {
                    error();
                }
            }
        } else {
            return;
        }
    } else if(token.tipo == SN && token.valor.codSN == SN_ABRI_PARENTESE) {
        expr();
        if(token.tipo == SN && token.valor.codSN == SN_FECHA_PARENTESE) {
            return;
        } else {
            error();
        }
    } else if(token.tipo == SN && token.valor.codSN == SN_NEGACAO) {
        fator();
    } else {
        error();
    }
}

bool op_rel() {
    if((token.tipo = SN) && (token.valor.codSN == SN_COMPARACAO || token.valor.codSN == SN_DIFERENTE || token.valor.codSN == SN_MENOR_IGUAL || token.valor.codSN == SN_MENOR || token.valor.codSN == SN_MAIOR_IGUAL || token.valor.codSN == SN_MAIOR)) {
        return true;
    } else {
        return false;
    }
}
