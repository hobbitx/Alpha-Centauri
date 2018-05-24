#include <iostream>
#include <fstream>

#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>

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


material gasoso,rochoso, congelado,silver;

static bool light0Ligada = 1;   // Luz branca ligada?
static float d = 1;           // Intensidade da cor difusa da luz branca
static float e = 1;           // Intensidade da cor especular da luz branca
static float m = 0.3;           // Intensidade da luz ambiente global
static float p = 1.0;           // A luz branca é posicional?
static float s = 50.0;          // Expoente especular do material (shininess)
float matShine[] = { s };                       // expoente especular (shininess)
static float xAngle = 0.0, yAngle = 0.0;        // Rotação da luz branca
static long font = (long)GLUT_BITMAP_TIMES_ROMAN_10;   // Fonte usada para imprimir na tela
static char theStringBuffer[10];                // String buffer
static float larguraJanela, alturaJanela;       // (w,h) da janela
static bool isLightingOn = true;               // O sistema de iluminação está ligado?
static float anguloEsferaY = 0;                 // Rotação da esfera em torno do eixo y
static float anguloPlaneta = 0;
static int esferaLados = 200;                   // Quantas subdivisões latitudinais/longitudinais da esfera
static bool localViewer = false;              // Quantas subdivisões latitudinais/longitudinais da esfera
static bool OrbsOn = false;
static bool PlanOn = false;
static bool infoOn = false;
static int camera=1,c_planeta=4;
float posicaoCameraX=1,posicaoCameraY=1,posicaoCameraZ=10;
float centerX=0,centerY=0,centerZ=0;
int distancia_cameraX=1,distancia_cameraY=1;
float velocidadeTrans=0;
static int marsTexture,sunTexture,earthTexture,pdoisTexture,spaceTexture;
int listOrbitas=0;
int contador=0,qtdPlanetas=4;
float zoom=1.0,satelite=4.9;
float distanciaX[] = {3.0,4.5,6.0,7,5,9.0};
float distanciaY[] = {4.0,5.5,7.0,8,5,10.0};
float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
float lightDif0[] = { d, d, d, 1.0 };
float lightSpec0[] = { e, e, e, 1.0 };
float lightPos0[] = { 0.5, 0.5, 0.5, p };
float globAmb[] = { m, m, m, 1.0 };
float velocidadeTranslacao[] = {0.5,0.3,0.1,0.09,0.025 };
char nomes[5][10] = {"Planeta 1", "Planeta 2", "Planeta 3", "Planeta 4", "Planeta 5"};

material mats[4];
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
	glColor3f(0,0.45,0.78);
    glTranslatef(0,-1,0);
    glLineWidth(3);
    for(int c=0;c<qtdPlanetas;c++){
	glBegin(GL_LINE_LOOP);
	  glTranslatef(2, 2, 0);
	    for (i = 0; i <= 100; ++i) {
			angulo = 2 * 3.14 * i / 100;
	        glVertex3f(cos(angulo) * distanciaX[c],1,sin(angulo) * distanciaY[c]);
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

    glRasterPos3f(-2.0, 2.10, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Posicao X: ");
    floatParaString(theStringBuffer, 4, posicaoCameraX);
    escreveTextoNaTela((void*)font, theStringBuffer);

   	glRasterPos3f(-2.0, 2.05, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Posicao Y: ");
    floatParaString(theStringBuffer, 4, posicaoCameraY);
    escreveTextoNaTela((void*)font, theStringBuffer);

    glRasterPos3f(-2.0, 2.0, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Posicao Z: ");
    floatParaString(theStringBuffer, 4, posicaoCameraZ);
    escreveTextoNaTela((void*)font, theStringBuffer);


    glRasterPos3f(1.0, 2.10, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Centro X: ");
    floatParaString(theStringBuffer, 4, centerX);
    escreveTextoNaTela((void*)font, theStringBuffer);

   	glRasterPos3f(1.0, 2.05, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Centro Y: ");
    floatParaString(theStringBuffer, 4, centerY);
    escreveTextoNaTela((void*)font, theStringBuffer);

    glRasterPos3f(1.0, 2.0, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Centro Z: ");
    floatParaString(theStringBuffer, 4, centerZ);
    escreveTextoNaTela((void*)font, theStringBuffer);

    glRasterPos3f(2.0, 2.0, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Camera: ");
    floatParaString(theStringBuffer, 4, camera);
    escreveTextoNaTela((void*)font, theStringBuffer);

    glRasterPos3f(2.0, 1.95, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Planeta: ");
    floatParaString(theStringBuffer, 4, c_planeta);
    escreveTextoNaTela((void*)font, theStringBuffer);

    glRasterPos3f(-2.0, 1.95, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Orbitas (o): ");
    escreveTextoNaTela((void*)font, (char*)(OrbsOn ? "ligada" : "desligada"));

    glRasterPos3f(1.0, 1.95, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Iluminacao (l): ");
    escreveTextoNaTela((void*)font, (char*)(isLightingOn ? "ligada" : "desligada"));

    glRasterPos3f(1.0, 1.90, -2.0);
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
    spaceTexture = SOIL_load_OGL_texture(
        "sky.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    if(spaceTexture == 0)
    {
        cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }
    // Não mostrar faces do lado de dentro
   // glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT_AND_BACK);
    // Esconder o ponteiro do mouse quando dentro da janela
   // glutSetCursor(GLUT_CURSOR_NONE);
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
	//planeta
	int texturas[] = {marsTexture,earthTexture,pdoisTexture};
  	
	for (int i = 0; i < qtdPlanetas; i++){
		glMaterialfv(GL_FRONT, GL_AMBIENT, mats[i].ambiente.v);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mats[i].difusa.v);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mats[i].especular.v);
    glMaterialfv(GL_FRONT, GL_SHININESS, mats[i].brilhosidade);
		 glBindTexture(GL_TEXTURE_2D, texturas[i]);
        glPushMatrix();
        	glTranslatef(-cos(anguloEsferaY*velocidadeTranslacao[i])*distanciaX[i],0,-sin(anguloEsferaY*velocidadeTranslacao[i])*distanciaY[i]);//movimento de translação
            glRotatef(anguloPlaneta, 0, 1, 0); //movimento de rotação
            solidSphere(0.5, esferaLados, esferaLados);
        glPopMatrix();
	}
	glPushMatrix();
			glTranslatef(-cos(anguloEsferaY*velocidadeTranslacao[1])*distanciaX[1],1,-sin(anguloEsferaY*velocidadeTranslacao[1])*distanciaY[1]);//movimento de translação
            glRotatef(anguloPlaneta, 0, 1, 0); //movimento de rotação
            solidSphere(0.2, esferaLados, esferaLados);
        glPopMatrix();
}
void info_planeta(){
	glDisable(GL_LIGHTING); // Desabilita iluminação
    glColor3f(.85f, .85f, .85f);

    glRasterPos3f(2.0, 1.60, -2.6);
    escreveTextoNaTela((void*)font, (char*)"Nome:");
    glRasterPos3f(2.5, 1.60, -2.6);
    escreveTextoNaTela((void*)font,nomes[c_planeta]);

    glRasterPos3f(2.0, 1.50, -2.6);
    escreveTextoNaTela((void*)font, (char*)"Distancia:");
    glRasterPos3f(2.5, 1.50, -2.6);    
    floatParaString(theStringBuffer, 4, distanciaX[c_planeta]*1000);
    escreveTextoNaTela((void*)font, theStringBuffer);
     glRasterPos3f(2.7, 1.50, -2.6);
    escreveTextoNaTela((void*)font, (char*)"KM");
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
    if (c_planeta<4){
    	info_planeta();
    }
    informacoes();
    if (centerX>2)centerX=2;
    if (centerX<-2)centerX=-2;
    if (centerY>2)centerY=2;
    if (centerY<-2)centerY=-2;


    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, spaceTexture);
    glRotatef(anguloPlaneta*0.001,1,0,0);
    solidSphere(20,esferaLados,esferaLados);
    
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

	   gluLookAt(posicaoCameraX,posicaoCameraY,posicaoCameraZ,
            centerX, centerY, centerZ,
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
        solidSphere(1.5, esferaLados, esferaLados);
      if (isLightingOn) {
        glEnable(GL_LIGHTING);
         glEnable(GL_LIGHT0);
    	}else{
    		 glDisable(GL_LIGHT0);
    	}



    glPopMatrix();


   	planetas();
	

    if (camera==2){
           
    	posicaoCameraX=-cos(anguloEsferaY*velocidadeTranslacao[1])*satelite*zoom;
    	posicaoCameraZ=-sin(anguloEsferaY*velocidadeTranslacao[1])*satelite*zoom;
        
        if (zoom>2)zoom=2;
        if (zoom<1)zoom=1;
    }
    if(c_planeta<4){

    	posicaoCameraX=-cos(anguloEsferaY*velocidadeTrans)*distancia_cameraX;
    	posicaoCameraZ=-sin(anguloEsferaY*velocidadeTrans)*distancia_cameraY;
        
    }

    glutSwapBuffers();
}
void changeCamera(){
	if (camera>4){
		camera=1;
	}
	if (camera==1){
		posicaoCameraX = 1;
		posicaoCameraY = 1;
		posicaoCameraZ = 10;
        centerX=0;
        centerY=0;
        centerZ=0;
	}else if(camera==2){
		posicaoCameraY=2;
	}else if (camera==3){
		posicaoCameraX = 0.3;
		posicaoCameraY = 10;
		posicaoCameraZ = 0.3;
        centerX=0;
        centerY=0;
        centerZ=0;
	}else if (camera==4){
		
	}
	c_planeta=4;
}
void changePlanet(){
	centerX = 0;
	centerY = 0;
	centerZ = 0;
	camera=4;
	if (c_planeta>4){
		c_planeta=0;
	}
		distancia_cameraX=distanciaX[c_planeta]+1;

		distancia_cameraY=distanciaY[c_planeta]+1;
    	posicaoCameraY=0;
    	velocidadeTrans=velocidadeTranslacao[c_planeta];
	
	if (c_planeta==1){
		distancia_cameraY=distanciaY[c_planeta]+2;
		distancia_cameraX=distanciaX[c_planeta]+2;
	}
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
    case 32:
    c_planeta++;
    changePlanet();
    break;
    case '+':
    if (camera==4){
    		posicaoCameraY+=0.1;
    	}
   	if (camera==2){
    		zoom+=0.1;
    	}
    	break;
    case '-':
    if (camera==4){
    		posicaoCameraY-=0.1;
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
	    	centerY--;
	    }
	    if(key == GLUT_KEY_UP){
	        centerY++;
	    }
	    if(key == GLUT_KEY_RIGHT){
	        centerX++;
	    }
	    if(key == GLUT_KEY_LEFT){
	    	centerX--;
	    }
	}
	if (camera==4){
	    if(key == GLUT_KEY_DOWN){
	    	posicaoCameraZ--;
	    }
	    if(key == GLUT_KEY_UP){
	        posicaoCameraZ++;
	    }
	    if(key == GLUT_KEY_RIGHT){
	        posicaoCameraX++;
	    }
	    if(key == GLUT_KEY_LEFT){
	    	posicaoCameraX--;
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
  	gluPerspective(100.0, (float)w/(float)h, 1.0, 20.0);  
    	
      //glFrustum(-razaoAspecto, razaoAspecto, -1.0, 1.0, 2.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
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
