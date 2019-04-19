/*Thiago Santos Teixeira nUSP 10736987 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"myHeader.h"
#include"tabelaSimbolo_VD.h"
#include"tabelaSimbolo_VO.h"
#include"tabelaSimbolo_LD.h"
#include"tabelaSimbolo_LO.h"
#include"tabelaSimbolo_AB.h"
/**/
void tabela(char *arquivoTxt,char *tipoTabela , char *tipoOrd){
    int caracter;
    apontadorAB stableAB;
    apontadorLG stableLO, stableLD;
    stableV *stableVO, *stableVD;
    FILE *arquivo;
    Buffer *word;
    /* as tabelas são iniciadas como NULL */
    stableAB = NULL;
    stableVO = stableVD = NULL;
    stableLO = stableLD = NULL;
    arquivo = fopen(arquivoTxt, "r");
    word = criaBuffer();
    /* só iremos criar a tabela que iremos usar. */
     
    if(!strcmp(tipoTabela, "AB")) stableAB = criaStableAB();
    else if(!strcmp(tipoTabela, "LO")) stableLO = criaStableLO();
    else if(!strcmp(tipoTabela, "LD")) stableLD = criaStableLD();
    else if(!strcmp(tipoTabela, "VO")) stableVO = criaStableVO();
    else if(!strcmp(tipoTabela, "VD")) stableVD = criaStableVD();
    while(!feof(arquivo)){
        caracter = fgetc(arquivo);
        
        while(!isalpha(caracter) && !feof(arquivo)) caracter = fgetc(arquivo);
        while(isalnum(caracter)){
            caracter = tolower(caracter);
            adicionaNoBuffer(word, caracter);
            caracter = fgetc(arquivo);
        }
       
        if(feof(arquivo)) break;
        /*como por convenção strings terminan com 0 */
        adicionaNoBuffer(word, 0);
        if(!strcmp(tipoTabela, "AB"))
            stableAB = insereStableAB(word->palavra, stableAB);
        else if(!strcmp(tipoTabela, "LO"))
            stableLO = insereStableLO(word->palavra, stableLO);
        else if(!strcmp(tipoTabela, "LD"))
            stableLD = insereStableLD(word->palavra, stableLD);
        else if(!strcmp(tipoTabela, "VO"))
            stableVO = insereStableVO(word->palavra, stableVO);
        else if(!strcmp(tipoTabela, "VD"))
            stableVD = insereStableVD(word->palavra, stableVD);
        clearBuffer(word);
    }
    destroiBuffer(word);
    
    if(!strcmp(tipoTabela, "AB")){
        if(!strcmp(tipoOrd, "A")) imprimeAB_A(stableAB);
        else{
            imprimeAB_O(stableAB);
        }
        destroiStableAB(stableAB);
    }
    else if(!strcmp(tipoTabela, "LO")){
        if(!strcmp(tipoOrd, "A")) imprimeLO_A(stableLO);
        else imprimeLO_O(stableLO);
        destroiStableLO(stableLO);
    }
    else if(!strcmp(tipoTabela, "LD")){
        if(!strcmp(tipoOrd, "A")) imprimeLD_A(stableLD);
        else imprimeLD_O(stableLD);
        destroiStableLD(stableLD);
    }
    else if(!strcmp(tipoTabela, "VO")){
        if(!strcmp(tipoOrd, "A")) imprimeVO_A(stableVO);
        else imprimeVO_O(stableVO);
        destroiStableVO(stableVO);
    }
    else if(!strcmp(tipoTabela, "VD")){
        if(!strcmp(tipoOrd, "A")) imprimeVD_A(stableVD);
        else imprimeVD_O(stableVD);
        destroiStableVD(stableVD);
    }
    return;
}
int main(int argc, char *argv[])
{
    /*Checa os argumentos */
    if(argv[3] == NULL){
        printf("ERRO, falta de argumento\n");
        return 1;
    }
    if(strcmp(argv[2], "VD") == 0){
        if(strcmp(argv[3], "A") == 0 || strcmp(argv[3], "O") == 0){
            tabela(argv[1], argv[2], argv[3]);
        }
        else{
            printf("Argumento tipo de ordenação não é valido\n");
            printf("os argumentos dados: %s %s %s\n",argv[1], argv[2], argv[3]);
            return 1;
        }
    }
    else if(strcmp(argv[2], "VO") == 0){
        if(strcmp(argv[3], "A") == 0 || strcmp(argv[3], "O") == 0)
            tabela(argv[1], argv[2], argv[3]);
        else{
            printf("Argumento tipo de ordenação não é valido\n");
            printf("os argumentos dados: %s %s %s\n",argv[1], argv[2], argv[3]);
            return 1;
        }
    }
    else if(strcmp(argv[2], "LD") == 0){
        if(strcmp(argv[3], "A") == 0 || strcmp(argv[3], "O") == 0)
            tabela(argv[1], argv[2], argv[3]);
        else{
            printf("Argumento tipo de ordenação não é valido\n");
            printf("os argumentos dados: %s %s %s\n",argv[1], argv[2], argv[3]);
            return 1;
        }
    }
    else if(strcmp(argv[2], "LO") == 0){
        if(strcmp(argv[3], "A") == 0 || strcmp(argv[3], "O") == 0)
            tabela(argv[1], argv[2], argv[3]);
        else{
            printf("Argumento tipo de ordenação não é valido\n");
            printf("os argumentos dados: %s %s %s\n",argv[1], argv[2], argv[3]);
            return 1;
        }
    }
    else if(strcmp(argv[2], "AB") == 0){
        if(strcmp(argv[3], "A") == 0 || strcmp(argv[3], "O") == 0)
            tabela(argv[1], argv[2], argv[3]);
        else{
            printf("Argumento tipo de ordenação não é valido\n");
            printf("os argumentos dados: %s %s %s\n",argv[1], argv[2], argv[3]);
            return 1;
        }
    }
    else{
        printf("Argumento tipo de tabela não é valido\n");
        printf("os argumentos dados: %s %s %s\n",argv[1], argv[2], argv[3]);
        return 1;
    }
    return 0;
}
