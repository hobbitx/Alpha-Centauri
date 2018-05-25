#include "texto.h"


void escreveTextoNaTela(void *font, char *string){
    char *c;
    for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}


void floatParaString(char * destStr, int precision, float val){
    sprintf(destStr,"%f",val);
    destStr[precision] = '\0';
}