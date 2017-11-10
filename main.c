/**
******************************************************************************
* @file	analex.h
* @author Maurício Menezes
* @version  x.x
* @date 10.10.17
* @brief
******************************************************************************
*/
#include "sintatico.c"

Token token;
FILE *fp;


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

    //analex(fp);
    sintatico();
    printf("\n\nFECHANDO ARQUIVO...\n");
    fclose(fp);
    return 0;
}
