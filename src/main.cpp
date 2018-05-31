#include <iostream>
#include <fstream>

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SDL/SDL.h>
#include <SDL/SDL_audio.h>
#include <SDL/SDL_mixer.h>
#include <cmath>
#include <cstdlib>
#include "../lib/texto.h"
#include "../lib/config.h"
#include "../lib/texturas.h"

using namespace std;

int volume_musica=100;
Mix_Music *musicMenu=NULL;

static bool light0Ligada = 1; 
static bool localViewer = false;   
float mundo = 5000;
float sky=1000;     
static float d = 1;           // Intensidade da cor difusa da luz branca
static float e = 1;           // Intensidade da cor especular da luz branca
static float m = 0.3;           // Intensidade da luz ambiente global
static float p = 1.0;           // A luz branca é posicional?
static float s = 50.0;          // Expoente especular do material (shininess)
static float anguloEsferaY = 0,anguloPlaneta = 0;   
static int esferaLados = 200;  
int listOrbitas=0,contador=0,momentoAnterior;
const int qtdPlanetas=5;
coords olhoCamera,centroCamera,upCamera,mouse,mousef;
material gasoso,rochoso, congelado,silver;
float distancia_cameraX=1,distancia_cameraZ=1;
float velocidadeTrans=0,tamanhoSolReal=1390000,tamanhoSol,fps;
int texturas[qtdPlanetas];
material mats[qtdPlanetas];
char musicas[5][50]={"../musicas/1.mp3","../musicas/2.mp3",
"../musicas/3.mp3"};
/*ILUMINACAO*/
float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
float lightDif0[] = { d, d, d, 1.0 };
float lightSpec0[] = { e, e, e, 1.0 };
float lightPos0[] = { 0.5, 0.5, 0.5, p };
float globAmb[] = { m, m, m, 1.0 };
float matShine[] = { s };


void iniciar_musica(char  *music){
	if(!Mix_PlayingMusic()){
		Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,1024);
		musicMenu=Mix_LoadMUS(music);
		Mix_VolumeMusic(volume_musica);
		Mix_PlayMusic(musicMenu,-1);
	}
}
void parar_musica(){
	if(Mix_PlayingMusic()){
		Mix_FadeOutMusic(0);
	}
}
void realidade(){
       int i=0;
    if(real==true){
     
        for(i= 0;i<=qtdPlanetas;i++){
            tamanhoSol=tamanhoSolReal*escalaS;
            distanciaX[i]=(distanciaReal[i])*escalaD+(2*tamanhoSol);
            distanciaZ[i]=distanciaX[i]+1;
            tamanho[i]=tamanhoReal[i]*escalaT;
            sky=1000;
            mundo=5000;
        }

    velocidadeTrans=velocidadeTranslacao[c_planeta];
    distancia_cameraX=distanciaX[c_planeta]+(tamanho[c_planeta]*3.7);
    distancia_cameraZ=distanciaZ[c_planeta]+(tamanho[c_planeta]*3.7);
    if (c_planeta==0){
       distancia_cameraX=distanciaX[c_planeta]+(tamanho[c_planeta]*5);
       distancia_cameraZ=distanciaZ[c_planeta]+(tamanho[c_planeta]*5);
    }

    }else{
         tamanhoSol=3.2;
         
        for(i= 0;i<=qtdPlanetas;i++){
          
            distanciaX[i]=tamanhoSol+5+(i*1.5);
            distanciaZ[i]=distanciaX[i]+1.5;
            tamanho[i]=(1+i)/10.0;
            //printf("%2.2f ",tamanho[i]);
            sky=50;
            mundo=200;
        }
        velocidadeTrans=velocidadeTranslacao[c_planeta];
        distancia_cameraX=distanciaX[c_planeta]+(tamanho[c_planeta]*4.7);
        distancia_cameraZ=distanciaZ[c_planeta]+(tamanho[c_planeta]*4.7);
        if (c_planeta==0){
        distancia_cameraX=distanciaX[c_planeta]+(2*tamanho[c_planeta]*7.0);
        distancia_cameraZ=distanciaZ[c_planeta]+(2*tamanho[c_planeta]*7.0);
        }

    }
}
void aneis(){
    int i=0;
    float angulo,raio=3;
    float variante=-0.5;
      glPushMatrix();
        glLineWidth(3);
        glBegin(GL_LINE_LOOP);
            //glTranslatef(2, 2, 0);
                for (i = 0; i <= 100; i++) {
                    angulo = 2 * 3.14 * i / 100;
                    glVertex3f(0,cos(angulo),sin(angulo) );
                    
                    if(variante>=0.5) variante-=0.001;
                    if(variante<=-0.5) variante+=0.001;
                }
        glEnd();
    glPopMatrix();
}
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
    float aumento =1;
    if(real==true){
        aumento=10;
    }
   glPushMatrix(); 
        glColor3f(1,1,1);
        glTranslatef(0,0,0);
        glLineWidth(1);
        for(float c=-mundo;c<mundo;c+=aumento){
            glPushMatrix(); 
                glTranslatef(0, 0, c); 
                glBegin(GL_LINES);
                    glVertex3f(-mundo,0,0);
                    glVertex3f( mundo,0,0);
                glEnd();
            glPopMatrix();   
            glPushMatrix(); 
                glTranslatef(c, 0, 0); 
                    glBegin(GL_LINES);
                    glVertex3f(0,0,-mundo);
                    glVertex3f(0,0, mundo);
                glEnd();
            glPopMatrix();  
        }
    glPopMatrix();
}

// Configuração inicial do OpenGL e GLUT
void setup(void){
    realidade();

    glClearColor(0,0,0, 0.0);
    glEnable(GL_DEPTH_TEST);                        // Ativa teste Z
    iniciar_musica("../musicas/space.mp3");
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

    olhoCamera.x=250;olhoCamera.y=100;olhoCamera.z=250;
    centroCamera.x=0;centroCamera.y=0;centroCamera.z=0;
    upCamera.x=0;upCamera.y=1;upCamera.z=0;
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);

    carregaTextura();
    texturas[0] = p1;
    texturas[1] = p2;
    texturas[2] = p3;
    texturas[3] = p4;
    texturas[4] = p5;
   
    glCullFace(GL_FRONT_AND_BACK);
    
}
void solidSphere(float radius, int stacks, int columns){
   GLUquadric* quadObj = gluNewQuadric();
   gluQuadricDrawStyle(quadObj, GLU_FILL);
   gluQuadricNormals(quadObj, GLU_SMOOTH);
   gluQuadricTexture(quadObj, GL_TRUE);
   gluSphere(quadObj, radius, stacks, columns);
   gluDeleteQuadric(quadObj);
}
void luas(int tipo){
    int f;
   // glBindTexture(GL_TEXTURE_2D,texturas[f]);
   if(tipo==1){
    glPushMatrix();
        //glTranslatef(0,1,0);
        glTranslatef(-cos(anguloEsferaY),
            1,-sin(anguloEsferaY));//movimento de translação
        solidSphere(0.2, esferaLados, esferaLados);
    glPopMatrix();
    float angulo,raio=3;
    int i;
    glDisable(GL_LIGHTING);
    glColor3f(0,0.45,0.78);
    if(OrbsOn) {
        glPushMatrix();
        
        glLineWidth(3);
        glBegin(GL_LINE_LOOP);
            glTranslatef(2, 2, 0);
                for (i = 0; i <= 100; i++) {
                    angulo = 2 * 3.14 * i / 100;
                glVertex3f(cos(angulo),1 ,sin(angulo) );
                }
        glEnd();
    }
    glPopMatrix();
   }else{
    glPushMatrix();
        //glTranslatef(0,1,0);
        glTranslatef(0,-cos(anguloEsferaY),
            -sin(anguloEsferaY));//movimento de translação
        solidSphere(0.2, esferaLados, esferaLados);
    glPopMatrix();
    float angulo,raio=3;
    int i;
    glDisable(GL_LIGHTING);
    glColor3f(0,0.45,0.78);
    if(OrbsOn) {
        glPushMatrix();
        
        glLineWidth(3);
        glBegin(GL_LINE_LOOP);
            //glTranslatef(2, 2, 0);
                for (i = 0; i <= 100; i++) {
                    angulo = 2 * 3.14 * i / 100;
                glVertex3f(0,cos(angulo),sin(angulo) );
                }
        glEnd();
    }
    glPopMatrix();
   }
    glEnable(GL_LIGHTING);
    //glDisable(GL_TEXTURE_2D);
}
void planetas(){
    sateliteZ=distanciaZ[1]+1.4;
    sateliteX=distanciaX[1]+1.4;
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
            if(i==4) luas(1);
            if(i==0) luas(0);
            if(i==3) luas(1);
            if(i==2) aneis();

        glPopMatrix();
        
        
    }
    glDisable(GL_TEXTURE_2D);    
}

void sun(){
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
    realidade();
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
    if(c_planeta<5 && controlaTardis==1){
       upCamera.x=0;
       upCamera.y=1;
       upCamera.z=0;
       olhoCamera.x=-cos(anguloEsferaY*velocidadeTrans)*distancia_cameraX;
       olhoCamera.z=-sin(anguloEsferaY*velocidadeTrans)*distancia_cameraZ;
       olhoCamera.y=0;  
    }
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
    tempo = glutGet(GLUT_ELAPSED_TIME)/1000;
    // Limpa a tela e o z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    if (c_planeta<qtdPlanetas){
       info_planeta();
    }

    informacoes(olhoCamera,centroCamera,upCamera );
    if (centroCamera.x>2)centroCamera.x=2;
    if (centroCamera.x<-2)centroCamera.x=-2;
    if (centroCamera.y>2)centroCamera.y=2;
    if (centroCamera.y<-2)centroCamera.y=-2;

    //skysphere

    glPushMatrix();
       glEnable(GL_TEXTURE_2D);
       glBindTexture(GL_TEXTURE_2D, spaceTexture);
       glRotatef(anguloPlaneta*0.009,1,0,0);
       solidSphere(sky,esferaLados,esferaLados);
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
    
    matShine[0] = s;
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
    glColor3f(1, 1, 1);  

    sun();
    planetas();
    deathStart();

    fps = 1000.0f / MAX(delta, 1.0f);
    momentoAnterior = momentoAtual;
    if(inicioT>=fimTardis && controlaTardis==0){
        parar_musica();
        controlaTardis=1;
        iniciar_musica(musicas[c_planeta]);
    }else{
        inicioT+=0.1;
    }
    //printf("%.2f ",inicioT);
   glutSwapBuffers();
}
void changeCamera(){
    if(c_planeta<6)  parar_musica();
    iniciar_musica("../musicas/space.mp3");
    centroCamera.x=0;
    centroCamera.y=0;
    centroCamera.z=0;
    upCamera.x=0;
    upCamera.y=1;
    upCamera.z=0;
    if(real==true){
        if (camera>4){
            camera=1;
        }
        if (camera==1){
            olhoCamera.x = 250;
            olhoCamera.y = 100;
            olhoCamera.z = 250; 
        }else if(camera==2){
            olhoCamera.y=1;
            sateliteZ=distanciaZ[1]+1;
            sateliteX=distanciaX[1]+1;
        }else if (camera==3){
            olhoCamera.x = 30;
            olhoCamera.y = 300;
            olhoCamera.z = 30;
        }
    }else{
         if (camera>4){
            camera=1;
        }
        if (camera==1){
            olhoCamera.x = 1;
            olhoCamera.y = 5;
            olhoCamera.z = 12; 
        }else if(camera==2){
            olhoCamera.y=1;
            sateliteZ=distanciaZ[1]+1;
            sateliteX=distanciaX[1]+1;
        }else if (camera==3){
            olhoCamera.x = 0.3;
            olhoCamera.y = 21.5;
            olhoCamera.z = 0.3;
        }
    }
    c_planeta=6;
    
}
void changePlanet(){
    parar_musica();
    inicioT=tempo;
    fimTardis=inicioT+20;
    controlaTardis=0;
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
    iniciar_musica("../musicas/tardis.mp3");
    
}
void fullscream(){
     if(full){
        glutFullScreen(); 
    }else{
        glutReshapeWindow(800, 600);
        glutPositionWindow(100, 100);
    }
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
    case'f':
    case'F':
        full = !full;
        fullscream();
        break;
    case'p':
    case'P':
        PlanOn = !PlanOn;
        break;
    case 'R':
    case 'r':
        real=!real;
       
        break;    
    case 32: //espaço
        c_planeta++;
        changePlanet();
        break;
    case '+':
        if (camera==4){
            olhoCamera.y+=10.1;
        }
        if (camera==2){
            zoom+=0.1;
        }
        break;
    case '-':
        if (camera==4){
            olhoCamera.y-=10.1;
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
void resize(int w, int h){
    larguraJanela = w;
    alturaJanela = h;
    float razaoAspecto = (float) glutGet(GLUT_WINDOW_WIDTH) / (float) glutGet(GLUT_WINDOW_HEIGHT);
    glViewport (0, 0, w, h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100.0, (float)w/(float)h, 1.0, mundo); 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void MenuPrincipal(int op){}
void MenuPlaneta(int op){
    c_planeta=op;
     changePlanet();
}
void lights(int op){
    if(op==0) isLightingOn = false;
    if(op==1) isLightingOn = true;
}
void orbit(int op){
    if(op==0) OrbsOn = false;
    if(op==1) OrbsOn = true;
}
void plan(int op){
    if(op==0) PlanOn = false;
    if(op==1) PlanOn = true;
}
void fulls(int op){
    if(op==0) full = false;
    if(op==1) full = true;
    fullscream();
}
void CriaMenu() {
    int menu,submenu1,submenu2,submenu3,submenu4,submenu5;
    int i;
    submenu1 = glutCreateMenu(MenuPlaneta);
    for(i=0;i<qtdPlanetas;i++){
        glutAddMenuEntry(nomes[i],i);
    }
    submenu2 = glutCreateMenu(lights);
     glutAddMenuEntry("Desligado",0);
     glutAddMenuEntry("Ligado",1);

    submenu3 = glutCreateMenu(orbit);
     glutAddMenuEntry("Desligado",0);
     glutAddMenuEntry("Ligado",1);

     submenu4 = glutCreateMenu(plan);
     glutAddMenuEntry("Desligado",0);
     glutAddMenuEntry("Ligado",1);

    submenu5 = glutCreateMenu(fulls);
     glutAddMenuEntry("Desligado",0);
     glutAddMenuEntry("Ligado",1);

    menu = glutCreateMenu(MenuPrincipal);
    glutAddSubMenu("Planetas",submenu1);
    glutAddSubMenu("Iluminacao",submenu2);
    glutAddSubMenu("Orbitas",submenu3);
    glutAddSubMenu("Plano",submenu4);
    glutAddSubMenu("Fullscream",submenu5);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void mouseClicks(int button, int state, int x, int y){
    
    if (button == GLUT_RIGHT_BUTTON)
        if (state == GLUT_DOWN) 
            CriaMenu();

}

void atualiza() {
    int momentoAtual = glutGet(GLUT_ELAPSED_TIME);
    int delta = momentoAtual - momentoAnterior;
    anguloEsferaY += .2f;
    anguloPlaneta += .5f;
    glutPostRedisplay();
}


void atualizaFPS(int idx) {
    char tituloDaJanela[200];
    sprintf(tituloDaJanela,"ALPHA CENTAURI-II  (%.2f fps)",fps);
    glutSetWindowTitle(tituloDaJanela);
    glutTimerFunc(1000, atualizaFPS, 0);
}
int main(int argc, char *argv[]){

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition (100, 100);
    glutCreateWindow("ALPHA CENTAURI-II (0.00 fps)");
         
    glutDisplayFunc(desenhaCena);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialKeyInput);
    glutIdleFunc(atualiza);
    glutMouseFunc(mouseClicks);
    glutTimerFunc(0, atualizaFPS, 0);
    setup();
    glewInit();
    glutMainLoop();
}
