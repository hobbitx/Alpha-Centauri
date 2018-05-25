#ifndef _TEXTO_H_
#define _TEXTO_H_

#include <iostream>
#include <fstream>
#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>

static long font = (long)GLUT_BITMAP_TIMES_ROMAN_10;   // Fonte usada para imprimir na tela


void escreveTextoNaTela(void *font, char *string);
void floatParaString(char * destStr, int precision, float val);

#endif // _TEXTO_H_
