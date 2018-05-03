#include <iostream>
#include <fstream>

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>

using namespace std;

static bool light0Ligada = 1;   // Luz branca ligada?
static bool light1Ligada = 1;   // Luz verde ligada?
static float d = 1;           // Intensidade da cor difusa da luz branca
static float e = 1;           // Intensidade da cor especular da luz branca
static float m = 0.3;           // Intensidade da luz ambiente global
static float p = 1.0;           // A luz branca é posicional?
static float s = 50.0;          // Expoente especular do material (shininess)
float matShine[] = { s };                       // expoente especular (shininess)
static float xAngle = 0.0, yAngle = 0.0;        // Rotação da luz branca
static long font = (long)GLUT_BITMAP_8_BY_13;   // Fonte usada para imprimir na tela
static char theStringBuffer[10];                // String buffer
static float xMouse = 250, yMouse = 250;        // (x,y) do ponteiro do mouse
static float larguraJanela, alturaJanela;       // (w,h) da janela
static bool isLightingOn = true;               // O sistema de iluminação está ligado?
static float anguloEsferaY = 0;                 // Rotação da esfera em torno do eixo y
static float anguloPlaneta = 0;
static int esferaLados = 200;                   // Quantas subdivisões latitudinais/longitudinais da esfera
static bool localViewer = false;              // Quantas subdivisões latitudinais/longitudinais da esfera
static bool OrbsOn = false;
static int camera=1;
float posicaoCameraX=1,posicaoCameraY=1,posicaoCameraZ=10;
static int marsTexture,sunTexture,earthTexture,pdoisTexture;
int listOrbitas=0;
int contador=0,qtdPlanetas=3;
float zoom=1.0;
float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
float lightDif0[] = { d, d, d, 1.0 };
float lightSpec0[] = { e, e, e, 1.0 };
float lightPos0[] = { 0.5, 0.5, 0.5, p };
float globAmb[] = { m, m, m, 1.0 };

// Escreve uma cadeia de caracteres
void escreveTextoNaTela(void *font, char *string){
    char *c;
    for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

// Converte um número decimal em string
void floatParaString(char * destStr, int precision, float val){
    sprintf(destStr,"%f",val);
    destStr[precision] = '\0';
}
void orbitas(){
    float angulo,raio=3;
    int i;
    
    glPushMatrix();
	glColor3f(1,0,0);
    glTranslatef(0,-1,0);
    glLineWidth(3);
    for(int c=0;c<qtdPlanetas;c++){
	glBegin(GL_LINE_LOOP);
	  glTranslatef(2, 2, 0);
	    for (i = 0; i <= 100; ++i) {
			angulo = 2 * 3.14 * i / 100;
	        glVertex3f(cos(angulo) * raio,1,sin(angulo) * raio);
        }
    glEnd();
    raio+=1.5;
    i=0;
	}
	glPopMatrix();
}
void informacoes(){
	glDisable(GL_LIGHTING); // Desabilita iluminação
    glColor3f(.85f, .85f, .85f);

    glRasterPos3f(-1.0, 1.10, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Posicao X: ");
    floatParaString(theStringBuffer, 4, posicaoCameraX);
    escreveTextoNaTela((void*)font, theStringBuffer);

   	glRasterPos3f(-1.0, 1.05, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Posicao Y: ");
    floatParaString(theStringBuffer, 4, posicaoCameraY);
    escreveTextoNaTela((void*)font, theStringBuffer);

    glRasterPos3f(-1.0, 1.0, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Posicao Z: ");
    floatParaString(theStringBuffer, 4, posicaoCameraZ);
    escreveTextoNaTela((void*)font, theStringBuffer);

    glRasterPos3f(-1.0, 0.95, -2.0);
     escreveTextoNaTela((void*)font, (char*)"Orbitas (o): ");
    escreveTextoNaTela((void*)font, (char*)(OrbsOn ? "ligada" : "desligada"));



}
void aneis(){
	float angulo,raio=0.5;
    int i;
    glColor3f(1,1,0);
    glPushMatrix();
	
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


void eixos(){

	glColor3f(1,0,0);//eixo x
	glBegin(GL_LINES);
		glVertex3f(0,0,0);
		glVertex3f(100,0,0);
	glEnd();
	glColor3f(0,1,0); //eixo y
	glBegin(GL_LINES);
		glVertex3f(0,0,0);
		glVertex3f(0,100,0);
	glEnd();

	glColor3f(0,0,1);
	glBegin(GL_LINES);
		glVertex3f(0,0,0);
		glVertex3f(0,0,100);
	glEnd();
	glColor3f(1,1,1);
}

// Configuração inicial do OpenGL e GLUT
void setup(void){
   //glClearColor(.4,.4,.4, 0.0);                    // fundo cinza
    glClearColor(0,0,0, 0.0);
    glEnable(GL_DEPTH_TEST);                        // Ativa teste Z

    
    // Propriedades do material da esfera
    float matAmbAndDif[] = {1.0, 1.0, 1.0, 1.0};    // cor ambiente e difusa: branca
    float matSpec[] = { 1.0, 1.0, 1,0, 1.0 };       // cor especular: branca

    // Definindo as propriedades do material
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Carrega a textura
    marsTexture = SOIL_load_OGL_texture
	(
		"mars-small.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(marsTexture == 0)
    {
        cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }
    sunTexture = SOIL_load_OGL_texture
    (
        "sun.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    if(sunTexture == 0)
    {
        cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }
    earthTexture = SOIL_load_OGL_texture
    (
        "p4.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    if(earthTexture == 0)
    {
        cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }
    pdoisTexture = SOIL_load_OGL_texture
    (
        "p2.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    if(pdoisTexture == 0)
    {
        cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }
    // Não mostrar faces do lado de dentro
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Esconder o ponteiro do mouse quando dentro da janela
    glutSetCursor(GLUT_CURSOR_NONE);
}
void solidSphere(float radius, int stacks, int columns){
    // cria uma quádrica
    GLUquadric* quadObj = gluNewQuadric();
    // estilo preenchido... poderia ser GLU_LINE, GLU_SILHOUETTE
    // ou GLU_POINT
    gluQuadricDrawStyle(quadObj, GLU_FILL);
    // chama 01 glNormal para cada vértice.. poderia ser
    // GLU_FLAT (01 por face) ou GLU_NONE
    gluQuadricNormals(quadObj, GLU_SMOOTH);
    // chama 01 glTexCoord por vértice
    gluQuadricTexture(quadObj, GL_TRUE);
    // cria os vértices de uma esfera
    gluSphere(quadObj, radius, stacks, columns);
    // limpa as variáveis que a GLU usou para criar
    // a esfera
    gluDeleteQuadric(quadObj);
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
       
    // Limpa a tela e o z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    informacoes();


	   gluLookAt(posicaoCameraX,posicaoCameraY,posicaoCameraZ,
            0, 0, 0,
            0, 1, 0);
    glPushMatrix();
        glRotatef(xAngle, 1.0, 0.0, 0.0); // Rotação no eixo x
        glRotatef(yAngle, 0.0, 1.0, 0.0); // Rotação no eixo y
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
        glTranslatef(lightPos0[0], lightPos0[1], lightPos0[2]);
        glColor3f(d, d, d);
        if (light0Ligada){
         glutWireSphere(0.05, 8, 8); // Esfera indicativa
           
        }
    glPopMatrix();

    // Define (atualiza) o valor do expoente de especularidade
    matShine[0] = s;
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
    glColor3f(1, 1, 1);
// Desenha o sol
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, sunTexture);
        glColor3f(1,1,1);
    glPushMatrix();
   //   glTranslatef(lightPos0[0], lightPos0[1], lightPos0[2]);
        glRotatef(anguloEsferaY, 0, 1, 0);
        glRotatef(90, 1, 0, 0);
        solidSphere(1.5, esferaLados, esferaLados);
      if (isLightingOn) {
        glEnable(GL_LIGHTING);
         glEnable(GL_LIGHT0);
    	}else{
    		 glDisable(GL_LIGHT0);
    	}

      

    glPopMatrix();   

   
   	//planeta

	
   		if(OrbsOn)orbitas();
    glBindTexture(GL_TEXTURE_2D, marsTexture);
        glPushMatrix();
        	glTranslatef(-cos(anguloEsferaY*0.1)*3,0,-sin(anguloEsferaY*0.1)*3);//movimento de translação
            glRotatef(anguloPlaneta, 0, 1, 0); //movimento de rotação
            solidSphere(0.5, esferaLados, esferaLados);
        glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, earthTexture);
        glPushMatrix();
			glTranslatef(-cos(anguloEsferaY*0.2)*4.5,0,-sin(anguloEsferaY*0.2)*4.5);//movimento de translação
            glRotatef(anguloPlaneta, 0, 1, 0); //movimento de rotação
            solidSphere(0.5, esferaLados, esferaLados);
            //esfera camera 
            glTranslatef(0,1,0);
            solidSphere(0.1,esferaLados,esferaLados);
		glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, pdoisTexture);
        glPushMatrix();
          	glTranslatef(-cos(anguloEsferaY*0.1)*6,0,-sin(anguloEsferaY*0.1)*6);//movimento de translação
            glRotatef(anguloPlaneta, 0, 1, 0); //movimento de rotação
            solidSphere(0.5, esferaLados, esferaLados);
            aneis();
        glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    
    if (camera==2){
    	posicaoCameraX=-cos(anguloEsferaY*0.1)*6;
    	posicaoCameraZ=-sin(anguloEsferaY*0.1)*6;
    }
   
    glutSwapBuffers();
}
void changeCamera(){
	if (camera>3){
		camera=1;
	}
	if (camera==1){
		posicaoCameraX = 1;
		posicaoCameraY = 1;
		posicaoCameraZ = 10;
	}else if(camera==2){
		posicaoCameraX = lightPos0[0]+5;
		posicaoCameraY = lightPos0[1]+1;
		posicaoCameraZ = lightPos0[2]+1;

	}else if (camera==3){
		posicaoCameraX = 0.3;
		posicaoCameraY = 10;
		posicaoCameraZ = 0.3;	
	}
}

// Callback do evento de teclado
void keyInput(unsigned char key, int x, int y){
    switch (key){
    case 27:
        exit(0);
        break;
    case 'c':
    case 'C':
    	camera++;
    	changeCamera();
    	break;
    case'o':
    OrbsOn = !OrbsOn;
    break;	
    case '+':
    	posicaoCameraZ+=0.5;
    	break;
    case '-':
    	posicaoCameraZ-=0.5;
    	break;
    default:
        break;
    }
    glutPostRedisplay();
}

// Callback para setas do teclado
void specialKeyInput(int key, int x, int y){
    if(key == GLUT_KEY_DOWN){
    	posicaoCameraY--;
    }
    if(key == GLUT_KEY_UP){
        posicaoCameraY++;
    }
    if(key == GLUT_KEY_RIGHT){
        posicaoCameraX++;
    }
    if(key == GLUT_KEY_LEFT){
    	posicaoCameraX--;
    }
    glutPostRedisplay();
}

// Callback de redimensionamento
void resize(int w, int h){
    larguraJanela = w;
    alturaJanela = h;

    glViewport (0, 0, w, h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w/(float)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}



void rotacionaEsfera() {
    anguloEsferaY += .2f;
    anguloPlaneta += .5f;
    glutPostRedisplay();
}
int main(int argc, char *argv[]){
    
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition (100, 100);
   
    glutCreateWindow("SISTEMA SOLAR");
    
    glutDisplayFunc(desenhaCena);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialKeyInput);
    glutIdleFunc(rotacionaEsfera);
    setup();

    glutMainLoop();
}
