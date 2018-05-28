#include "config.h"

bool OrbsOn = false;
bool PlanOn = false;
bool infoOn = false;
bool isLightingOn = true;
bool full=false; 
int controlaTardis=0;
float inicioT=0,fimTardis=10;
float zoom=1,tempo,sateliteX,sateliteZ,larguraJanela, alturaJanela;
char theStringBuffer[10]; 
int p1=0,p2=0,p3=0,p4=0,p5=0,sunTexture=0,spaceTexture=0,deathTexture=0; // TEXTURAS
int camera=1,c_planeta=6;
float gravidade[] = {0.5,0.3,0.1,0.09,0.025 };
float massa[] = {0.55,0.81,1.2,14.0,37.0 };
char nomes[5][10] = {"Slik 9a", "Slik 9b", "Slik 9c", "Slik 10a", "Slik 10b"};
char materia[5][10] = {"Rocha", "Rocha", "Rocha", "Gas", "Gas"};
/*PLANETAS */
float tamanho[] = {0.3,0.4,0.5,0.6,0.9};
float temperatura[] = {433,134,15,-190,-600};
float distanciaX[] = {5.0,6.5,9.0,11.5,13.0};
float distanciaZ[] = {6.0,7.5,10.0,12.5,15.0};
float velocidadeTranslacao[] = {0.5,0.3,0.1,0.09,0.025 };
