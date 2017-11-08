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

Token token;
FILE *fp;

void imprimeToken(Token ); //Função temporaria de teste para imprimir tokens

int main(int argc, char const *argv[])
{
    char nomeFile[tamNomeFile];

    printf("Insira o nome do arquivo(nomeArquivo.extensao):\n");
    scanf(" %s", nomeFile);
    fp = fopen(nomeFile, "r+");

    if(fp==NULL){
        printf("\n\tERRO AO ABRIR ARQUIVO");
        printf("\n\tPressione <ENTER> para finalizar...\n\t");
        exit(1);
    }

    while(!feof (fp)){
        analex(fp);
        imprimeToken(token);
    }

    fclose(fp);
    return 0;
}

void imprimeToken(Token tkn){

    switch (tkn.tipo){
        case CT_C:
            printf("\n\t< CT_C, \" %s \" >", tkn.lexema);;
            break;
        case CT_I:
            printf("\n\t< CT_I, \" %d \" >", tkn.valor.valorInt);
            break;
        case CT_L:
            printf("\n\t< CT_L, \" %s \" >", tkn.lexema);
            break;
        case CT_R:
            printf("\n\t< CT_R, \" %f \" >", tkn.valor.valorReal);
            break;
        case ID:
            printf("\n\t< ID, \" %s \" >", tkn.lexema);
            break;
        case PR:
            printf("\n\t< PR, \" %s \" >", TabPalReservadas[tkn.valor.codPR]);
            break;
        case SN:
            printf("\n\t< SN, \" %s \" >", tkn.lexema);
            break;
        case END:
            if(tkn.valor.valorInt == 1){
            printf("\n\t< END, \"ERRO\" >");
            printf ("\n\n\tAnalise lexica executada com sucesso.\n");
            printf("\n\n\tEncerando...\n");
            exit (1);
            }
            else{
                printf("\n\t< END, \"FIM\" >");
                printf ("\n\n\tAnalise lexica executada com sucesso.\n");
                printf("\n\n\tEncerando...\n");
            }
            break;
        default:
            printf("\n\t< END, \"DEFAULT\" >");
            printf ("\n\n\tAnalise lexica executada com sucesso.\n");
            printf("\n\n\tEncerando...\n");
            break;
    }

    return;
}
