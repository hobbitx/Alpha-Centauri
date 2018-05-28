#include "texto.h"


void escreveTextoNaTela(void *font, char *string){
    char *c;
    for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}


void floatParaString(char * destStr, int precision, float val){
    sprintf(destStr,"%f",val);
    destStr[precision] = '\0';
}
void informacoes(coords olhoCamera,coords centroCamera,coords upCamera ){
    glDisable(GL_LIGHTING); // Desabilita iluminação
    glColor3f(.85f, .85f, .85f);

    glRasterPos3f(-2.0, 2.2, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Posicao X: ");
    floatParaString(theStringBuffer, 4, olhoCamera.x);
    escreveTextoNaTela((void*)font, theStringBuffer);

    glRasterPos3f(-2.0, 2.1, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Posicao Y: ");
    floatParaString(theStringBuffer, 4, olhoCamera.y);
    escreveTextoNaTela((void*)font, theStringBuffer);

    glRasterPos3f(-2.0, 2.0, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Posicao Z: ");
    floatParaString(theStringBuffer, 4, olhoCamera.z);
    escreveTextoNaTela((void*)font, theStringBuffer);

    glRasterPos3f(-1.0, 2.2, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Centro X: ");
    floatParaString(theStringBuffer, 4, centroCamera.x);
    escreveTextoNaTela((void*)font, theStringBuffer);

    glRasterPos3f(-1.0, 2.1, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Centro Y: ");
    floatParaString(theStringBuffer, 4, centroCamera.y);
    escreveTextoNaTela((void*)font, theStringBuffer);

    glRasterPos3f(-1.0, 2.0, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Centro Z: ");
    floatParaString(theStringBuffer, 4, centroCamera.z);
    escreveTextoNaTela((void*)font, theStringBuffer);

    glRasterPos3f(0.0, 2.2, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Camera: ");
    floatParaString(theStringBuffer, 4, camera);
    escreveTextoNaTela((void*)font, theStringBuffer);

    glRasterPos3f(0.0, 2.1, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Planeta: ");
    floatParaString(theStringBuffer, 4, c_planeta);
    escreveTextoNaTela((void*)font, theStringBuffer);
    
    glRasterPos3f(0.0, 2.0, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Zoom: ");
    floatParaString(theStringBuffer, 4, zoom);
    escreveTextoNaTela((void*)font, theStringBuffer);

    glRasterPos3f(1.0, 2.20, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Orbitas (o): ");
    escreveTextoNaTela((void*)font, (char*)(OrbsOn ? "ligada" : "desligada"));

    glRasterPos3f(1.0, 2.10, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Iluminacao (l): ");
    escreveTextoNaTela((void*)font, (char*)(isLightingOn ? "ligada" : "desligada"));

    glRasterPos3f(1.0, 2.0, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Plano (p): ");
    escreveTextoNaTela((void*)font, (char*)(PlanOn ? "ligado" : "desligado"));

    glRasterPos3f(1.0, 1.9, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Fullscream (f): ");
    escreveTextoNaTela((void*)font, (char*)(full ? "ligado" : "desligado"));
    
    glRasterPos3f(2.0, 2.0, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Tempo : ");
    floatParaString(theStringBuffer, 4, tempo);
    escreveTextoNaTela((void*)font, theStringBuffer);
    glRasterPos3f(2.7, 2.0, -2.0);
    escreveTextoNaTela((void*)font, (char*)"s");
    
    glRasterPos3f(2.0, 1.9, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Inicio : ");
    floatParaString(theStringBuffer, 4, inicioT);
    escreveTextoNaTela((void*)font, theStringBuffer);
    glRasterPos3f(2.0, 1.7, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Fim : ");
    floatParaString(theStringBuffer, 4, fimTardis);
    escreveTextoNaTela((void*)font, theStringBuffer);

}
void info_planeta(){
    float perimetro = 2*3.14* sqrt((pow(distanciaX[c_planeta],2)+
    pow(distanciaZ[c_planeta],2)/2));
    glDisable(GL_LIGHTING); // Desabilita iluminação
    glColor3f(.85f, .85f, .85f);

    glRasterPos3f(2.0, 1.60, -2.6);
    escreveTextoNaTela((void*)font, (char*)"Nome:");
    glRasterPos3f(2.7, 1.60, -2.6);
    escreveTextoNaTela((void*)font,nomes[c_planeta]);

    glRasterPos3f(2.0, 1.50, -2.6);
    escreveTextoNaTela((void*)font, (char*)"Distancia:");
    glRasterPos3f(2.7, 1.50, -2.6);   
    floatParaString(theStringBuffer, 4, distanciaX[c_planeta]*1000);
    escreveTextoNaTela((void*)font, theStringBuffer);
    glRasterPos3f(2.9, 1.50, -2.6);
    escreveTextoNaTela((void*)font, (char*)"KM");

    glRasterPos3f(2.0, 1.40, -2.6);
    escreveTextoNaTela((void*)font, (char*)"Raio do planeta:");
    glRasterPos3f(2.7, 1.40, -2.6);   
    floatParaString(theStringBuffer, 4, tamanho[c_planeta]*1000);
    escreveTextoNaTela((void*)font, theStringBuffer);
    glRasterPos3f(2.9, 1.40, -2.6);
    escreveTextoNaTela((void*)font, (char*)"KM");

    glRasterPos3f(2.0, 1.30, -2.6);
    escreveTextoNaTela((void*)font, (char*)"Material:");
    glRasterPos3f(2.7, 1.30, -2.6);   
    escreveTextoNaTela((void*)font,materia[c_planeta]);


    glRasterPos3f(2.0, 1.20, -2.6);
    escreveTextoNaTela((void*)font, (char*)"Gravidade:");
    glRasterPos3f(2.7, 1.20, -2.6);   
    floatParaString(theStringBuffer, 4, gravidade[c_planeta]);
    escreveTextoNaTela((void*)font, theStringBuffer);
    glRasterPos3f(2.9, 1.20, -2.6);
    escreveTextoNaTela((void*)font, (char*)"m/s^2");

    glRasterPos3f(2.0, 1.10, -2.6);
    escreveTextoNaTela((void*)font, (char*)"Massa:");
    glRasterPos3f(2.7, 1.10, -2.6);   
    floatParaString(theStringBuffer, 4, massa[c_planeta]*1000);
    escreveTextoNaTela((void*)font, theStringBuffer);
    glRasterPos3f(2.9, 1.10, -2.6);
    escreveTextoNaTela((void*)font, (char*)"Kg");

    glRasterPos3f(2.0, 1.00, -2.6);
    escreveTextoNaTela((void*)font, (char*)"Temperatura:");
    glRasterPos3f(2.7, 1.00, -2.6);   
    floatParaString(theStringBuffer, 4, temperatura[c_planeta]);
    escreveTextoNaTela((void*)font, theStringBuffer);
    glRasterPos3f(3.0, 1.00, -2.6);
    escreveTextoNaTela((void*)font, (char*)"C");
    
    glRasterPos3f(2.0, 0.90, -2.6);
    escreveTextoNaTela((void*)font, (char*)"Periodo orbital:");
    glRasterPos3f(2.7, 0.90, -2.6);   
    floatParaString(theStringBuffer, 4, perimetro);
    escreveTextoNaTela((void*)font, theStringBuffer);
    glRasterPos3f(2.9, 0.90, -2.6);
    escreveTextoNaTela((void*)font, (char*)"Anos");

}