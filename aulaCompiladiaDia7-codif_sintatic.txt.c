// declaracao para uso


//modelo cmm

inteiro i,j,k;
real f; 
real  integra(semparam){
    f =  i+j+k
        retorne f;
}
semretorno principal(semparam){
    real x;
    i = 2;
    j = 3;
    k = 4;
    x = integfra();
    retorne;
}

/* Implementação de Prog() */
prog(){
    while{
    se (t.cat = pr && (t.codigo ==  caracter || t.codigo ==  inteiro ...t.codigo == semretorno))
        analex();
        se(t.cat == ID){
            analex();
        }else{
            erro("id inesperado")
        }
    se(t.cat == SN && t.cod == ABRE_PARENTESE){
        func();
    }
}
    
/*Imprlementação de CMD() */

/*Checar no abri chave se vem o fecha chave, senão chama comando*/
cmd()
    se (t.cat == PR || t.cat == ID || t.cat == SN)
        se (t.cat == SN)
            caso (t.codigo)
                PONTO_VIRGULA: analex(); fim caso;
                ABRE_CHAVE:
                    analex(); 
                    enquanto(t.cat != SN && t.codigo != FECHA_CHAVE)
                        cmd();
                    analex();
                fim caso;
    
/*Diferencia Atrib de ID '(' */

/*Tabela de Simbolos || Variaveis */
    /*Todos os identificadores devem ser guardados e seus atributos.
    Os identificadores serão usados futuramente.*/
    
inteiro i,j,k;
real f; 
real  integra(semparam){
    f =  i+j+k
        retorne f;
}

    formato da tabela
        lexema - tipo(int, caracter, real, booleano, semretorno) - cat(Variavel, Parametro, Função) - Escopo(Local, Global)
        
        //Gerencia da tabela. Variaveis tem de sair da tabela no fim da função.//
        
        /*Estrutura deve ser uma pilha - Inserção e remorção
        Na checagem não deve desempilhar
        No final da função desempilha até o nome da função, Deixando os parametros
        */