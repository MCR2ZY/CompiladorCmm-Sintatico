/**
******************************************************************************
* @file	sintatico.h
* @author Marcelo Henrique, Mauricio Souza
* @version  x.x
* @date 08.11.17
* @brief Cabeçalho do Analisador Sintático
******************************************************************************
*/
#ifndef SINTATICO_H_INCLUDED
#define SINTATICO_H_INCLUDED

#include "analex.h"

void sintatico();
void prog(); //ok
bool tipo(); //ok
void tipos_param();//ok
void tipos_p_opc();//ok
void cmd();
void atrib();
void expr(); //ok
void termo(); //ok
void expr_simp(); //ok
void fator(); //ok
bool op_rel(); //ok
void func(); // Adicionada para facilitar tratamento de funções. Não consta na gramatica
void error(); // deixar codigo arrumado parte de erro

#endif // SINTATICO_H_INCLUDED
