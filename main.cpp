#include <iostream>
#include <fstream>

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>
#include "texto.h"
using namespace std;


#define MAX(x, y) (((x) > (y)) ? (x) : (y))
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

coords olhoCamera,centroCamera,upCamera;
material gasoso,rochoso, congelado,silver;

static bool light0Ligada = 1;   // Luz branca ligada?
static float d = 1;           // Intensidade da cor difusa da luz branca
static float e = 1;           // Intensidade da cor especular da luz branca
static float m = 0.3;           // Intensidade da luz ambiente global
static float p = 1.0;           // A luz branca é posicional?
static float s = 50.0;          // Expoente especular do material (shininess)
float matShine[] = { s };                       // expoente especular (shininess)
static char theStringBuffer[10];                // String buffer
static float anguloEsferaY = 0,anguloPlaneta = 0;
static float larguraJanela, alturaJanela;       // (w,h) da janela
static int esferaLados = 200;                   // Quantas subdivisões latitudinais/longitudinais da esfera
static bool localViewer = false;              // Quantas subdivisões latitudinais/longitudinais da esfera
static bool OrbsOn = false;
static bool PlanOn = false;
static bool infoOn = false;
static bool isLightingOn = true;
static int camera=1,c_planeta=6;
static int p1,sunTexture,p2,p3,p4,p5,spaceTexture,deathTexture;
float distancia_cameraX=1,distancia_cameraZ=1;
float velocidadeTrans=0,tamanhoSol=3.2;
int listOrbitas=0,contador=0;
const int qtdPlanetas=5;
float zoom=1,sateliteX,sateliteZ;
float tamanho[] = {0.3,0.4,0.5,0.6,0.9};
float distanciaX[] = {5.0,6.5,9.0,11.5,13.0};
float distanciaZ[] = {6.0,7.5,10.0,12.5,15.0};
float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
float lightDif0[] = { d, d, d, 1.0 };
float lightSpec0[] = { e, e, e, 1.0 };
float lightPos0[] = { 0.5, 0.5, 0.5, p };
float globAmb[] = { m, m, m, 1.0 };
float velocidadeTranslacao[] = {0.5,0.3,0.1,0.09,0.025 };
char nomes[5][10] = {"Planeta 1", "Planeta 2", "Planeta 3", "Planeta 4", "Planeta 5"};
char materia[5][10] = {"Rocha", "Gas", "Planeta 3", "Planeta 4", "Planeta 5"};
int momentoAnterior;
float fps = 0;
material mats[qtdPlanetas];
float gravidade[] = {0.5,0.3,0.1,0.09,0.025 };
float massa[] = {0.2,0.3,0.7,0.09,0.025 };


void orbitas(){
   float angulo,raio=3;
   int i;

   glPushMatrix();
    glColor3f(0,0.45,0.78);
   glTranslatef(0,-1,0);
   glLineWidth(3);
   for(int c=0;c<qtdPlanetas;c++){
    glBegin(GL_LINE_LOOP);
 	 glTranslatef(2, 2, 0);
 	   for (i = 0; i <= 100; ++i) {
            angulo = 2 * 3.14 * i / 100;
 	       glVertex3f(cos(angulo) * distanciaX[c],1,sin(angulo) * distanciaZ[c]);
       }
   glEnd();
   i=0;
    }
    glPopMatrix();
}
void plano(){
   int i;
 
   //plano em =0
   glPushMatrix(); 
        glColor3f(1,1,1);
 	   glTranslatef(0,0,0);
 	   glLineWidth(1);
    for(float c=-100;c<100;c+=0.5){
        glPushMatrix(); 
        glTranslatef(0, 0, c); 
            glBegin(GL_LINES);
         	   glVertex3f(-200,0,0);
         	   glVertex3f(200,0,0);
     	   glEnd();
     	  
        glPopMatrix();   
    }
    for(float c=-100;c<100;c+=0.5){
        glPushMatrix(); 
        glTranslatef(c, 0, 0); 
            glBegin(GL_LINES);
         	   glVertex3f(0,0,-200);
         	   glVertex3f(0,0,200);
     	   glEnd();
     	  
        glPopMatrix();   
    }
    glPopMatrix();
}


void informacoes(){
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

}
void aneis(){
    float angulo,raio=0.5;
   int i;

   glPushMatrix();
    glColor3f(1,1,0);
   glTranslatef(0,-1,0);
   for(int c=0;c<qtdPlanetas;c++){
    glBegin(GL_LINE_LOOP);
 	 glTranslatef(2, 2, 0);
 	   for (i = 0; i <= 100; ++i) {
            angulo = 2 * 3.14 * i / 100;
 	       glVertex3f(cos(angulo) * raio,1,sin(angulo) * raio);
       }
    glEnd();
    raio+=0.1;
    i=0;
    }
    glPopMatrix();

}
// Configuração inicial do OpenGL e GLUT
void setup(void){
  //glClearColor(.4,.4,.4, 0.0);                    // fundo cinza
   glClearColor(0,0,0, 0.0);
   glEnable(GL_DEPTH_TEST);                        // Ativa teste Z

   // Propriedades do material da esfera
   float matAmbAndDif[] = {1.0, 1.0, 1.0, 1.0};    // cor ambiente e difusa: branca
   float matSpec[] = { 1.0, 1.0, 1,0, 1.0 };       // cor especular: branca

   gasoso.ambiente = (cor){ 0.9, 0.9, 0.9, 1 };
   gasoso.emissiva = (cor){ 0, 0, 0, 1 };
   gasoso.difusa = (cor){ 0.9, 0.9, 0.9, 1 };
   gasoso.especular = (cor){ 1, 1, 1, 1 };
   gasoso.brilhosidade[0] = 100;

   rochoso.ambiente = (cor){ 0.6, 0.6, 0.6, 1 };
   rochoso.emissiva = (cor){ 0, 0, 0, 1 };
   rochoso.difusa = (cor){ .6, .6, .6, 1 };
   rochoso.especular = (cor){ 0, 0, 0, 1 };

   congelado.ambiente = (cor){ 0.24725, 0.1995, 0.0745, 1 };
   congelado.emissiva = (cor){ 0, 0, 0, 1 };
   congelado.difusa = (cor){ 0.75164,0.60648, 0.22648, 1 };
   congelado.especular = (cor){ 0.628281, 0.555802, 0.366065, 1 };
    congelado.brilhosidade[0] = 0.4;
                        

   silver.ambiente = (cor){ 0.8, 0.8, 0.8, 1 };
   silver.emissiva = (cor){ 0, 0, 0, 1 };
   silver.difusa = (cor){ 0.8,0.8, 0.8, 1 };
   silver.especular = (cor){ 0.8, 0.8, 0.8, 1 };
   silver.brilhosidade[0] = 0.4;       

   mats[0]=gasoso;
   mats[1]=rochoso;
   mats[2]=congelado;
   mats[3]=silver;
   mats[4]=gasoso;

   olhoCamera.x=1;olhoCamera.y=5;olhoCamera.z=12;
   centroCamera.x=0;centroCamera.y=0;centroCamera.z=0;
   upCamera.x=0;upCamera.y=1;upCamera.z=0;
   // Definindo as propriedades do material
   glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
   glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
   glMaterialfv(GL_FRONT, GL_SHININESS, matShine);

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Carrega a textura
    sunTexture = SOIL_load_OGL_texture(
       "sun.jpg",
       SOIL_LOAD_AUTO,
       SOIL_CREATE_NEW_ID,
       SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
   );

   if(sunTexture == 0){
       cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
   }
   p1 = SOIL_load_OGL_texture(
        "p1.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

   if(p1 == 0){
       cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
   }
   
   p2 = SOIL_load_OGL_texture(
       "p2.jpg",
       SOIL_LOAD_AUTO,
       SOIL_CREATE_NEW_ID,
       SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
   );

   if(p2 == 0){
       cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
   }
   p3 = SOIL_load_OGL_texture(
       "p3.jpg",
       SOIL_LOAD_AUTO,
       SOIL_CREATE_NEW_ID,
       SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
   );

   if(p3 == 0){
       cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
   } 
   p4 = SOIL_load_OGL_texture(
       "p4.jpg",
       SOIL_LOAD_AUTO,
       SOIL_CREATE_NEW_ID,
       SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
   );

   if(p4 == 0){
       cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
   }
    p5 = SOIL_load_OGL_texture(
       "p5.jpg",
       SOIL_LOAD_AUTO,
       SOIL_CREATE_NEW_ID,
       SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
   );

   if(p5 == 0){
       cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
   }
   spaceTexture = SOIL_load_OGL_texture(
       "sky.png",
       SOIL_LOAD_AUTO,
       SOIL_CREATE_NEW_ID,
       SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
   );

   if(spaceTexture == 0){
       cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
   }
   deathTexture = SOIL_load_OGL_texture(
       "death.jpg",
       SOIL_LOAD_AUTO,
       SOIL_CREATE_NEW_ID,
       SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
   );

   if(deathTexture == 0){
       cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
   }
   // Não mostrar faces do lado de dentro
  // glEnable(GL_CULL_FACE);
   glCullFace(GL_FRONT_AND_BACK);
   // Esconder o ponteiro do mouse quando dentro da janela
  glutSetCursor(GLUT_CURSOR_NONE);
}
void solidSphere(float radius, int stacks, int columns){
   GLUquadric* quadObj = gluNewQuadric();
   gluQuadricDrawStyle(quadObj, GLU_FILL);
   gluQuadricNormals(quadObj, GLU_SMOOTH);
   gluQuadricTexture(quadObj, GL_TRUE);
   gluSphere(quadObj, radius, stacks, columns);
   gluDeleteQuadric(quadObj);
}

void planetas(){
    sateliteZ=distanciaZ[1]+1.4;
    sateliteX=distanciaX[1]+1.4;
    //planeta
    int texturas[] = {p1,p2,p3,p4,p5};
   //glTranslatef(tamanhoSol,0,tamanhoSol);
    for (int i = 0; i < qtdPlanetas; i++){
    glMaterialfv(GL_FRONT, GL_AMBIENT, mats[i].ambiente.v);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mats[i].difusa.v);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mats[i].especular.v);
    glMaterialfv(GL_FRONT, GL_SHININESS, mats[i].brilhosidade);
    glBindTexture(GL_TEXTURE_2D, texturas[i]);
       glPushMatrix();
           glTranslatef(-cos(anguloEsferaY*velocidadeTranslacao[i])*distanciaX[i],0,-sin(anguloEsferaY*velocidadeTranslacao[i])*distanciaZ[i]);//movimento de translação
           glRotatef(anguloPlaneta, 0, 1, 0); //movimento de rotação
           solidSphere(tamanho[i], esferaLados, esferaLados);
       glPopMatrix();
    }
    glDisable(GL_TEXTURE_2D);    
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
    floatParaString(theStringBuffer, 4, massa[c_planeta]);
    escreveTextoNaTela((void*)font, theStringBuffer);
    glRasterPos3f(2.9, 1.10, -2.6);
    escreveTextoNaTela((void*)font, (char*)"Kg");

    glRasterPos3f(2.0, 1.00, -2.6);
    escreveTextoNaTela((void*)font, (char*)"Periodo orbital:");
    glRasterPos3f(2.7, 1.00, -2.6);   
    floatParaString(theStringBuffer, 4, perimetro);
    escreveTextoNaTela((void*)font, theStringBuffer);
    glRasterPos3f(2.9, 1.00, -2.6);
    escreveTextoNaTela((void*)font, (char*)"Anos");

}

void deathStart(){
    glBindTexture(GL_TEXTURE_2D,deathTexture);
    glPushMatrix();
       glTranslatef(-cos(anguloEsferaY*velocidadeTranslacao[1])*sateliteX,
            1,-sin(anguloEsferaY*velocidadeTranslacao[1])*sateliteZ);//movimento de translação
       solidSphere(0.2, esferaLados, esferaLados);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
// Callback de desenho
void desenhaCena(){
    // Propriedades das fontes de luz
    // Propriedades da fonte de luz LIGHT0
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec0);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb);        // Luz ambiente global
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, localViewer);// Enable local viewpoint

    glDisable(GL_LIGHTING);
    int momentoAtual = glutGet(GLUT_ELAPSED_TIME);
    int delta = momentoAtual - momentoAnterior;

    // Limpa a tela e o z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    if (c_planeta<5){
       info_planeta();
    }
    informacoes();
    if (centroCamera.x>2)centroCamera.x=2;
    if (centroCamera.x<-2)centroCamera.x=-2;
    if (centroCamera.y>2)centroCamera.y=2;
    if (centroCamera.y<-2)centroCamera.y=-2;

    //skysphere
    glPushMatrix();
       glEnable(GL_TEXTURE_2D);
       glBindTexture(GL_TEXTURE_2D, spaceTexture);
       glRotatef(anguloPlaneta*0.009,1,0,0);
       solidSphere(25,esferaLados,esferaLados);
       glDisable(GL_TEXTURE_2D);
    glPopMatrix();

 	gluLookAt(olhoCamera.x,olhoCamera.y,olhoCamera.z,
           centroCamera.x, centroCamera.y, centroCamera.z,
           upCamera.x, upCamera.y, upCamera.z);
    glPushMatrix();
    
       glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
       glTranslatef(lightPos0[0], lightPos0[1], lightPos0[2]);
       glColor3f(d, d, d);
       if (light0Ligada){
        glutWireSphere(0.05, 8, 8); // Esfera indicativa

       }
    glPopMatrix();
       if(OrbsOn)orbitas();
       if(PlanOn)plano();
       if(infoOn)info_planeta();
    // Define (atualiza) o valor do expoente de especularidade
    matShine[0] = s;
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
    glColor3f(1, 1, 1);  
    // Desenha o sol
       glEnable(GL_TEXTURE_2D);
       glBindTexture(GL_TEXTURE_2D, sunTexture);
       glColor3f(1,1,1);
    glPushMatrix();
        glRotatef(anguloEsferaY, 0, 1, 0);
        glRotatef(90, 1, 0, 0);
        solidSphere(tamanhoSol, esferaLados, esferaLados);
        if (isLightingOn) {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        }else{
        	glDisable(GL_LIGHT0);
        }
    glPopMatrix();

    planetas();
    deathStart();
    if (camera==2){   
        olhoCamera.x=-cos(anguloEsferaY*velocidadeTranslacao[1])*sateliteX*zoom;
        olhoCamera.z=-sin(anguloEsferaY*velocidadeTranslacao[1])*sateliteZ*zoom;
        olhoCamera.y=1;
        
        centroCamera.x=-cos(anguloEsferaY*velocidadeTranslacao[1])*sateliteX*0.4;
        centroCamera.z=-sin(anguloEsferaY*velocidadeTranslacao[1])*sateliteZ*0.4;
 
       upCamera.x=0;
       upCamera.y=1;
       upCamera.z=0;

       if (zoom>2)zoom=2;
       if (zoom<1)zoom=1;
    }
    if(c_planeta<5){
       upCamera.x=0;
       upCamera.y=1;
       upCamera.z=0;
       olhoCamera.x=-cos(anguloEsferaY*velocidadeTrans)*distancia_cameraX;
       olhoCamera.z=-sin(anguloEsferaY*velocidadeTrans)*distancia_cameraZ;
       olhoCamera.y=0;  
    }
    fps = 1000.0f / MAX(delta, 1.0f);

    momentoAnterior = momentoAtual;

   glutSwapBuffers();
}
void changeCamera(){
    centroCamera.x=0;
    centroCamera.y=0;
    centroCamera.z=0;
    upCamera.x=0;
    upCamera.y=1;
    upCamera.z=0;
    if (camera>4){
        camera=1;
    }
    if (camera==1){
        olhoCamera.x = 1;
        olhoCamera.y = 0;
        olhoCamera.z = 12; 
    }else if(camera==2){
        olhoCamera.y=1;
        sateliteZ=distanciaZ[1]+1;
        sateliteX=distanciaX[1]+1;
    }else if (camera==3){
        olhoCamera.x = 0.3;
        olhoCamera.y = 11.5;
        olhoCamera.z = 0.3;
        PlanOn=false;
    }else if (camera==4){
        
    }
    c_planeta=6;
}
void changePlanet(){
    centroCamera.x = 0;
    centroCamera.y = 0;
    centroCamera.z = 0;
    camera=4;
    if (c_planeta>=5){
        c_planeta=0;
    }

    velocidadeTrans=velocidadeTranslacao[c_planeta];
    distancia_cameraX=distanciaX[c_planeta]+(tamanho[c_planeta]*3.7);
    distancia_cameraZ=distanciaZ[c_planeta]+(tamanho[c_planeta]*3.7);
    if (c_planeta==0){
       distancia_cameraX=distanciaX[c_planeta]+(tamanho[c_planeta]*5);
       distancia_cameraZ=distanciaZ[c_planeta]+(tamanho[c_planeta]*5);
    }
    
    olhoCamera.y=0;
    camera=4;
}
// Callback do evento de teclado
void keyInput(unsigned char key, int x, int y){
   switch (key){
   case 27:
       exit(0);
       break;
   case'l':
   case'L':
       isLightingOn = !isLightingOn;
       break;
   case 'c':
   case 'C':
       camera++;
       changeCamera();
       break;
   case'o':
   case'O':
   OrbsOn = !OrbsOn;
   break;
   case'p':
   case'P':
   PlanOn = !PlanOn;
   break;
   case 32: //espaço
   c_planeta++;
   changePlanet();
   break;
   case '+':
   if (camera==4){
           olhoCamera.y+=0.1;
       }
   if (camera==2){
           zoom+=0.1;
       }
       break;
   case '-':
   if (camera==4){
           olhoCamera.y-=0.1;
       }
   if (camera==2){
           zoom-=0.1;
       }
       break;
   default:
       break;
   }
   glutPostRedisplay();
}

// Callback para setas do teclado
void specialKeyInput(int key, int x, int y){
   if (camera==1){
 	   if(key == GLUT_KEY_DOWN){
 	       centroCamera.y--;
 	   }
 	   if(key == GLUT_KEY_UP){
 	       centroCamera.y++;
 	   }
 	   if(key == GLUT_KEY_RIGHT){
 	       centroCamera.x++;
 	   }
 	   if(key == GLUT_KEY_LEFT){
 	       centroCamera.x--;
 	   }
    }
    if (camera==4 && c_planeta>=4){
 	   if(key == GLUT_KEY_DOWN){
 	       olhoCamera.z--;
 	   }
 	   if(key == GLUT_KEY_UP){
 	       olhoCamera.z++;
 	   }
 	   if(key == GLUT_KEY_RIGHT){
 	       olhoCamera.x++;
 	   }
 	   if(key == GLUT_KEY_LEFT){
 	       olhoCamera.x--;
 	   }
    }
       glutPostRedisplay();
}


// Callback de redimensionamento
void resize(int w, int h){
   larguraJanela = w;
   alturaJanela = h;
    float razaoAspecto = (float) glutGet(GLUT_WINDOW_WIDTH) / (float) glutGet(GLUT_WINDOW_HEIGHT);
   glViewport (0, 0, w, h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(100.0, (float)w/(float)h, 1.0, 200.0); 
       
     //glFrustum(-razaoAspecto, razaoAspecto, -1.0, 1.0, 2.0, 100.0);
   glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void atualiza() {
    int momentoAtual = glutGet(GLUT_ELAPSED_TIME);
    int delta = momentoAtual - momentoAnterior;
    anguloEsferaY += .2f;
    anguloPlaneta += .5f;

    glutPostRedisplay();
}

char tituloDaJanela[200];
void atualizaFPS(int idx) {
    sprintf(tituloDaJanela,
        "SISTEMA ESTELAR (%.2f fps)",
        fps);
    glutSetWindowTitle(tituloDaJanela);
    glutTimerFunc(1000, atualizaFPS, 0);
}
int main(int argc, char *argv[]){

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition (100, 100);
    glutCreateWindow("SISTEMA ESTELAR (0.00 fps)");

    glutDisplayFunc(desenhaCena);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialKeyInput);
    glutIdleFunc(atualiza);
    glutTimerFunc(0, atualizaFPS, 0);
    setup();
     glewInit();
    glutMainLoop();
}
