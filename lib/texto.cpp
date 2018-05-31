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
    
    glRasterPos3f(2.0, 2.20, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Tempo : ");
    floatParaString(theStringBuffer, 4, tempo);
    escreveTextoNaTela((void*)font, theStringBuffer);
    escreveTextoNaTela((void*)font, (char*)" seg");
       
    glRasterPos3f(2.0, 2.10, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Escala Distancias ");
    floatParaString(theStringBuffer, 10, escalaD);
    escreveTextoNaTela((void*)font, theStringBuffer);
    escreveTextoNaTela((void*)font, (char*)":1");
  
    glRasterPos3f(2.0, 2.0, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Escala Tamanho  ");
    floatParaString(theStringBuffer, 10, escalaT);
    escreveTextoNaTela((void*)font, theStringBuffer);
    escreveTextoNaTela((void*)font, (char*)":1");
      
    glRasterPos3f(2.0, 1.90, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Modelo ");
    escreveTextoNaTela((void*)font, (char*)(real ? "Real" : "Fantasia"));



}
void info_planeta(){
    float a = (float) pow(distanciaReal[1],2);
    float b = (float) pow(distanciaReal[1]+10,2);
    float c = sqrt((a+b)/2);
    float padrao = 2*3.1415*c;
    float parcela_a = (float) pow(distanciaReal[c_planeta],2);
    float parcela_b = (float) pow((distanciaReal[c_planeta]+10),2);
    float parcela_c = sqrt((parcela_a+parcela_b)/2);
    float perimetro = ((2*3.1415*parcela_c)/padrao);

    glDisable(GL_LIGHTING);
    glColor3f(.85f, .85f, .85f);

    glRasterPos3f(2.0, 1.60, -2.6);
    escreveTextoNaTela((void*)fonte_planeta, (char*)"Nome:");
    escreveTextoNaTela((void*)fonte_planeta, nomes[c_planeta]);

    glRasterPos3f(2.0, 1.45, -2.6);
    escreveTextoNaTela((void*)fonte_planeta, (char*)"Distancia:");
    floatParaString(theStringBuffer, 10, distanciaReal[c_planeta]);
    escreveTextoNaTela((void*)fonte_planeta, theStringBuffer);
    escreveTextoNaTela((void*)fonte_planeta, (char*)"KM");

    glRasterPos3f(2.0, 1.30, -2.6);
    escreveTextoNaTela((void*)fonte_planeta, (char*)"Diametro do planeta:");  
    floatParaString(theStringBuffer, 8, tamanhoReal[c_planeta]);
    escreveTextoNaTela((void*)fonte_planeta, theStringBuffer);
    escreveTextoNaTela((void*)fonte_planeta, (char*)"KM");

    glRasterPos3f(2.0, 1.15, -2.6);
    escreveTextoNaTela((void*)fonte_planeta, (char*)"Material:"); 
    escreveTextoNaTela((void*)fonte_planeta,materia[c_planeta]);


    glRasterPos3f(2.0, 1.0, -2.6);
    escreveTextoNaTela((void*)fonte_planeta, (char*)"Gravidade:");  
    floatParaString(theStringBuffer, 4, gravidade[c_planeta]);
    escreveTextoNaTela((void*)fonte_planeta, theStringBuffer);
    escreveTextoNaTela((void*)fonte_planeta, (char*)"m/s^2");

    glRasterPos3f(2.0, 0.85, -2.6);
    escreveTextoNaTela((void*)fonte_planeta, (char*)"Massa:");
    floatParaString(theStringBuffer, 4, massa[c_planeta]*1000);
    escreveTextoNaTela((void*)fonte_planeta, theStringBuffer);
    escreveTextoNaTela((void*)fonte_planeta, (char*)"Kg");

    glRasterPos3f(2.0, 0.70, -2.6);
    escreveTextoNaTela((void*)fonte_planeta, (char*)"Temperatura:");
    floatParaString(theStringBuffer, 4, temperatura[c_planeta]);
    escreveTextoNaTela((void*)fonte_planeta, theStringBuffer);
    escreveTextoNaTela((void*)fonte_planeta, (char*)"C");
    
    glRasterPos3f(2.0, 0.55, -2.6);
    escreveTextoNaTela((void*)fonte_planeta, (char*)"Periodo orbital:"); 
    floatParaString(theStringBuffer, 5, perimetro);
    escreveTextoNaTela((void*)fonte_planeta, theStringBuffer);
    escreveTextoNaTela((void*)fonte_planeta, (char*)"Anos");

    

}