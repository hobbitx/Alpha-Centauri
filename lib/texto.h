#ifndef _TEXTO_H_
#define _TEXTO_H_

#include <iostream>
#include <fstream>
#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>
#include "config.h"



static long font = (long)GLUT_BITMAP_TIMES_ROMAN_10;   // Fonte usada para imprimir na tela
static long fonte_planeta= (long)GLUT_BITMAP_HELVETICA_12;

void escreveTextoNaTela(void *font, char *string);
void floatParaString(char * destStr, int precision, float val);
void informacoes(coords olhoCamera,coords centroCamera,coords upCamera);
void info_planeta();
#endif // _TEXTO_H_
