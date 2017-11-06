/**
******************************************************************************
* @file	analex.h
* @author Maurício Menezes
* @version  x.x
* @date 10.10.17
* @brief
******************************************************************************
*/
#include "analex.h"

int contlin = 1;
int ultimoLiteral = 0;
char TabelaLiterais[QntLiteral][TamLexema];
char TabPalReservadas[QntPalReservadas][TamPalReservadas] = {
        "booleano",        "caracter",        "enquanto",
        "inteiro",         "para",            "real",
        "retorne",         "se",              "semparam",
        "semretorno",     "senao"
    };

Token exceptionToken(); // Função implementada no fim do analex.c

Token analex(FILE *fp){
    Token token;                       // Recebe o token do analisador lexico
    int i;                             // Variavel auxiliar para laços de repeticao
    int estado = 0;                    // Controla o estado no automato
    int p = 0;                         // Controla a posição tanto da vetor para literal quanto do vetor para o numero
    char c;                             // Recebe o caracter do arquivo
    char literal[TamLexema];           // Vetor temporario que guarda o literal
    char numero[TamNum];               // Vetor temporario que guarda o numero

    while(1){

        switch (estado){

            case 0:
                c = fgetc(fp);

                if(c == ' ' || c == '\t'){  // Filtra espacos e tabs exceto \n
                    estado = 0;
                }
                else if(c == '\n')            //Filtra os enter's + incrementa o contador de linhas
                {
                    estado = 0;
                    contlin++;
                }

                else if(isalpha(c)){   // Trata ID's e pal. reservadas
                    estado = 1;
                }
                else if(isdigit(c)){   // Trata constantes inteiras e constantes reais
                    estado = 3;
                }
                else if(c == '\''){         // Trata as constantes caracter, constante '\n' e constante '\0'
                    estado = 8;
                }
                else if(c == '\"'){         // Trata as constantes cadeia de caracteres
                    estado = 16;
                }
                else if(c == ';'){          // Trata o Ponto e Virgula
                    estado = 18;
                }
                else if(c == '('){          // Trata o abri parentese
                    estado = 19;
                }
                else if(c == ')'){          // Trata o fecha parentese
                    estado = 20;
                }
                else if(c == '-'){          // Trata o menos
                    estado = 21;
                }
                else if(c == '+'){          // Trata o mais
                    estado = 22;
                }
                else if(c == '*'){          // Trata o vezes
                    estado = 23;
                }
                else if(c == ','){          // Trata a virgula
                    estado = 24;
                }
                else if(c == '&'){          // Trata o AND
                    estado = 25;
                }
                else if(c == '|'){          // Trata o OR
                    estado = 27;
                }
                else if(c == '<'){          // Trata o menor ou menor igual
                    estado = 29;
                }
                else if(c == '>'){          // Trata o maior ou maior igual
                    estado = 32;
                }
                else if(c == '='){          // Trata a atribuicao ou a comparacao
                    estado = 35;
                }
                else if(c == '!'){          // Trata a negacao ou o diferente
                    estado = 38;
                }
                else if(c == '/'){          // Trata o comentario ou divisao
                    estado = 41;
                }
                else if(c == '{'){          // Trata o abri chave
                    estado = 45;
                }
                else if(c == '}'){          // Trata o fecha chave
                    estado = 46;
                }
                else if(c == EOF){
                    estado = 47;
                }
                else{
                    token = exceptionToken();
                    return token;
                }
                break;
            case 1:
                literal[p] = c;
                p++;
                c = fgetc(fp);
                if(isalnum(c) || c == '_'){
                    estado = 1;
                }else{
                    estado = 2;
                }
                break;
            case 2:
                literal[p] = EOS;
                ungetc(c, fp);
                for(i = 0; i < QntPalReservadas; i++){
                    if(!strcmp(literal, TabPalReservadas[i])){
                        token.tipo = PR;
                        strcpy(token.lexema, literal);
                        token.valor.codPR = i;
                        return token;
                    }
                }
                for(i=0; i<QntLiteral; i++){
                    if(!strcmp(literal, TabelaLiterais[i])){
                        token.tipo = ID;
                        strcpy(token.lexema, literal);
                        token.valor.posLiteral = i;
                        return token;
                    }
                }
                // Novo ID
                token.tipo = ID;
                token.valor.posLiteral = ultimoLiteral;
                strcpy(token.lexema, literal);
                strcpy(TabelaLiterais[ultimoLiteral], literal);
                ultimoLiteral++;
                return token;
                break;
            case 3:
                numero[p] = c;
                p++;
                c = fgetc(fp);
                if(isdigit(c)){
                    estado = 3;
                }else if(c == '.'){
                    estado = 5;
                }else{
                    estado = 4;
                }
                break;
            case 4:
                ungetc(c, fp);
                numero[p] = EOS;
                token.tipo = CT_I;
                token.valor.valorInt = atoi(numero);    // converter string para inteiro
                return token;
                break;
            case 5:
                numero[p] = c;
                p++;
                c = fgetc(fp);
                if(isdigit(c)){
                    estado = 6;
                }else{
                    token = exceptionToken();
                    return token;
                }
                break;
            case 6:
                numero[p] = c;
                p++;
                c = fgetc(fp);
                if(isdigit(c)){
                    estado = 6;
                }else{
                    estado = 7;
                }
                break;
            case 7:
                ungetc(c, fp);
                numero[p] = EOS;
                token.tipo = CT_R;
                token.valor.valorReal = atof(numero);   // Converter string para num real
                return token;
                break;
            case 8:
                literal[p] = c;
                p++;
                c = fgetc(fp);
                if(c == '\\'){
                    estado = 11;
                }else if(isprint(c)){
                    estado = 9;
                }
                break;
            case 9:
                literal[p] = c;
                p++;
                c = fgetc(fp);
                if(c == '\''){
                    estado = 10;
                }else{
                    token = exceptionToken();
                    return token;
                }
                break;
            case 10:
                literal[p] = c;
                p++;
                literal[p] = EOS;
                token.tipo = CT_C;
                strcpy(token.lexema, literal);
                return token;
                break;
            case 11:
                literal[p] = c;
                p++;
                c = fgetc(fp);
                if(c == '0'){
                    estado = 12;
                }else if(c == 'n'){
                    estado = 14;
                }else {
                    token = exceptionToken();
                    return token;
                }
                break;
            case 12:
                literal[p] = c;
                p++;
                c = fgetc(fp);
                if(c == '\''){
                    estado = 13;
                }else{
                    token = exceptionToken();
                    return token;
                }
                break;
            case 13:
                literal[p] = c;
                p++;
                literal[p] = EOS;
                token.tipo = CT_C;
                strcpy(token.lexema, literal);
                return token;
                break;
            case 14:
                literal[p] = c;
                p++;
                c = fgetc(fp);
                if(c == '\''){
                    estado = 15;
                }else{
                    token = exceptionToken();
                    return token;
                }
                break;
            case 15:
                literal[p] = c;
                p++;
                literal[p] = EOS;
                token.tipo = CT_C;
                strcpy(token.lexema, literal);
                return token;
                break;
            case 16:
                literal[p] = c;
                p++;
                c = fgetc(fp);
                if(isprint(c) && c != '\"' && c != '\n'){
                    estado = 16;
                }else if(c == '\"'){
                    estado = 17;
                }else{
                    token = exceptionToken();
                    return token;
                }
                break;
            case 17:
                literal[p] = c;
                p++;
                literal[p] = EOS;
                token.tipo = CT_L;
                strcpy(token.lexema, literal);
                return token;
                break;
            case 18:
                token.tipo = SN;
                token.valor.codSN = SN_PTO_VIRGULA;
                strcpy(token.lexema, ";");
                return token;
                break;
            case 19:
                token.tipo = SN;
                token.valor.codSN = SN_ABRI_PARENTESE;
                strcpy(token.lexema, "(");
                return token;
                break;
            case 20:
                token.tipo = SN;
                token.valor.codSN = SN_FECHA_PARENTESE;
                strcpy(token.lexema, ")");
                return token;
                break;
            case 21:
                token.tipo = SN;
                token.valor.codSN = SN_SUBTRACAO;
                strcpy(token.lexema,"-");
                return token;
                break;
            case 22:
                token.tipo = SN;
                token.valor.codSN = SN_SOMA;
                strcpy(token.lexema, "+");
                return token;
                break;
            case 23:
                token.tipo = SN;
                token.valor.codSN = SN_MULTIPLICACAO;
                strcpy(token.lexema, "*");
                return token;
                break;
            case 24:
                token.tipo = SN;
                token.valor.codSN = SN_VIRGULA;
                strcpy(token.lexema, ",");
                return token;
                break;
            case 25:
                c = fgetc(fp);
                if(c == '&'){
                    estado = 26;
                }else{
                    token = exceptionToken();
                    return token;
                }
                break;
            case 26:
                token.tipo = SN;
                token.valor.codSN = SN_AND;
                strcpy(token.lexema, "&&");
                return token;
                break;
            case 27:
                c = fgetc(fp);
                if(c == '|'){
                    estado = 28;
                }else{
                    token = exceptionToken();
                    return token;
                }
                break;
            case 28:
                token.tipo = SN;
                token.valor.codSN = SN_OR;
                strcpy(token.lexema, "||");
                return token;
                break;
            case 29:
                c = fgetc(fp);
                if(c == '='){
                    estado = 31;
                }else{
                    estado = 30;
                }
                break;
            case 30:
                ungetc(c, fp);
                token.tipo = SN;
                token.valor.codSN = SN_MENOR;
                strcpy (token.lexema, "<");
                return token;
                break;
            case 31:
                token.tipo = SN;
                token.valor.codSN = SN_MENOR_IGUAL;
                strcpy (token.lexema, "<=");
                return token;
                break;
            case 32:
                c = fgetc(fp);
                if(c == '='){
                    estado = 33;
                }else{
                    estado = 34;
                }
                break;
            case 33:
                ungetc(c, fp);
                token.tipo = SN;
                token.valor.codSN = SN_MAIOR;
                strcpy (token.lexema, ">");
                return token;
                break;
            case 34:
                token.tipo = SN;
                token.valor.codSN = SN_MAIOR_IGUAL;
                strcpy (token.lexema, ">=");
                return token;
                break;
            case 35:
                c = fgetc(fp);
                if(c == '='){
                    estado = 37;
                }else{
                    estado = 36;
                }
                break;
            case 36:
                ungetc(c, fp);
                token.tipo = SN;
                token.valor.codSN = SN_ATRIBUICAO;
                strcpy (token.lexema, "=");
                return token;
                break;
            case 37:
                token.tipo = SN;
                token.valor.codSN = SN_COMPARACAO;
                strcpy(token.lexema, "==");
                return token;
                break;
            case 38:
                c = fgetc(fp);
                if(c == '='){
                    estado = 40;
                }else{
                    estado = 39;
                }
                break;
            case 39:
                ungetc(c, fp);
                token.tipo = SN;
                token.valor.codSN = SN_NEGACAO;
                strcpy(token.lexema, "!");
                return token;
                break;
            case 40:
                token.tipo = SN;
                token.valor.codSN = SN_DIFERENTE;
                strcpy(token.lexema, "!=");
                return token;
                break;
            case 41:
                c = fgetc(fp);
                if(c == '*'){
                    estado = 43;
                }else{
                    estado = 42;
                }
                break;
            case 42:
                ungetc(c, fp);
                token.tipo = SN;
                token.valor.codSN = SN_DIVISAO;
                strcpy (token.lexema, "/");
                return token;
                break;
            case 43:
                c = fgetc(fp);
                if(c == '*'){
                    estado = 44;
                }else if(isprint(c) && c != '*' && c != '\n'){
                    estado = 43;
                }else if(c == '\n'){
                    contlin ++;
                }else if(c == EOF){
                    printf("\n\n\tERRO!!! Comentario aberto nao foi fechado!\n\n");
                    exit (1);
                }
                break;
            case 44:
                c = fgetc(fp);
                if(c == '*'){
                    estado = 44;
                }else if(isprint(c) && c != '*' && c != '/'){
                    estado = 43;
                }else if(c == '/'){
                    estado = 0;
                }
                break;
            case 45:
                token.tipo = SN;
                token.valor.codSN = SN_ABRI_CHAVE;
                strcpy(token.lexema, "{");
                return token;
                break;
            case 46:
                token.tipo = SN;
                token.valor.codSN = SN_FECHA_CHAVE;
                strcpy(token.lexema, "}");
                return token;
                break;
            case 47:
                token.tipo = END;
                token.valor.valorInt=0;
                return token;
            default:
                printf("\n\tErro Léxico!!!\n");
                exit (1);
            break;
        }

    }

}

Token exceptionToken(){
    Token tknAux;
    printf("\n\n\tErro, Token Invalido na Linha %d", contlin);
    tknAux.tipo = END;
    tknAux.valor.valorInt = 1;
    return tknAux;
}
