#ifndef CONFIGURACOES_H
#define CONFIGURACOES_H
#include <iostream>
#include <fstream>
#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>
#include <cstdlib>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

using namespace std;

typedef struct coords {
 union {
     float v[4];
     struct {
         float x, y, z, w;
     };
     struct {
         float r, g, b, a;
     };
 };
} cor;

typedef struct material {
   cor ambiente;
   cor emissiva;
   cor difusa;
   cor especular;
   float brilhosidade[1];
} material;
extern float escala;
extern bool OrbsOn;
extern bool PlanOn;
extern bool infoOn;
extern bool full; 
extern bool isLightingOn;
extern float zoom,tempo,sateliteX,sateliteZ,larguraJanela, alturaJanela;
extern int p1,sunTexture,p2,p3,p4,p5,spaceTexture,deathTexture; // TEXTURAS
extern int camera,c_planeta;
extern char theStringBuffer[10]; 
extern float gravidade[];
extern float massa[];
extern float temperatura[];
extern char nomes[5][10];
extern char materia[5][10];
/*PLANETAS */
extern float tamanho[] ;
extern float distanciaX[];
extern float distanciaZ[] ;
extern float velocidadeTranslacao[];

#endif // CONFIGURACOES_H