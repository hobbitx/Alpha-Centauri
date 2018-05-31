#include "texturas.h"


void carregaTextura(){
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glEnable(GL_BLEND );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Carrega a textura
    sunTexture = SOIL_load_OGL_texture(
       "../imagens/sun.jpg",
       SOIL_LOAD_AUTO,
       SOIL_CREATE_NEW_ID,
       SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    if(sunTexture == 0){
       cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }
    p1 = SOIL_load_OGL_texture(
        "../imagens/p1.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    if(p1 == 0){
       cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }
   
    p2 = SOIL_load_OGL_texture(
       "../imagens/p2.jpg",
       SOIL_LOAD_AUTO,
       SOIL_CREATE_NEW_ID,
       SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    if(p2 == 0){
       cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }
    p3 = SOIL_load_OGL_texture(
       "../imagens/p3.jpg",
       SOIL_LOAD_AUTO,
       SOIL_CREATE_NEW_ID,
       SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    if(p3 == 0){
       cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    } 
    p4 = SOIL_load_OGL_texture(
       "../imagens/p4.jpg",
       SOIL_LOAD_AUTO,
       SOIL_CREATE_NEW_ID,
       SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    if(p4 == 0){
       cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }
    p5 = SOIL_load_OGL_texture(
       "../imagens/p5.jpg",
       SOIL_LOAD_AUTO,
       SOIL_CREATE_NEW_ID,
       SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    if(p5 == 0){
       cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }
    spaceTexture = SOIL_load_OGL_texture(
       "../imagens/sky.png",
       SOIL_LOAD_AUTO,
       SOIL_CREATE_NEW_ID,
       SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    if(spaceTexture == 0){
       cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }
    deathTexture = SOIL_load_OGL_texture(
       "../imagens/death.jpg",
       SOIL_LOAD_AUTO,
       SOIL_CREATE_NEW_ID,
       SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    if(deathTexture == 0){
       cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }


    atmosferaTextura = SOIL_load_OGL_texture(
       "../imagens/atmosfera.jpg",
       SOIL_LOAD_AUTO,
       SOIL_CREATE_NEW_ID,
       SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    if(atmosferaTextura == 0){
       cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }
}

