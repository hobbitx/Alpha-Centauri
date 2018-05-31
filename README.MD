# Alpha Centauri II - Um novo começo

Este projeto realiza a implementação de conhecimentos adquiridos na segunda parte da matéria de computação gráfica do curso de engenharia de computação do CEFET-MG. Neste exemplo implementamos um modelo em 3D de um sistema estelar.
As medidades presentes neste modelo são baseadas nas medidas reais do sistema solar, disponiveis em: http://planetario.ufsc.br/o-sistema-solar/.
Data de acesso:30 de maio de 2018 ás 15:29;
## Começando

```
Para execução do jogo:
1. descompacte o arquivo.
2. abra o terminal 
3. navegue até a pasta do mesmo
4. entre na pasta makefile
5. digite o comando make all
6. digite o comando make run
```


### Pré-requisitos

Sistema Operacional: SO baseados em Linux que possuam  possiblidade de instalação da "extensão" make e das bibliotecas glut, freeglut, glew, SOIL e SDL.

### Instalação 
 
 Antes de inicar é preciso fazer download e instalação das bibliotecas

```
Como instalar cada biblioteca está disponivel no site de download da mesma. Links abaixo.
```

Após a instalação devemos extrair nosso projeto para algum lugar. Recomenda-se a area de trabalho ou alguma pasta de fácil acesso pois iremos utiliza-la posteriormente.

Feito a descompactação abra o terminal e entre na pasta makeflile dentro da pasta do jogo  

```
/home/desktop/aplhaCentauri/makefile por exemplo
```

apos entrar na pasta makefile, ainda no terminal, execute o comando make all
```
Este comando irar criar as bibliotecas necessárias para a perfeita execução do jogo
``` 

Feito a criação e compilação, execute o comando **make run** para executar o jogo. Após isto a tela com os sistema estelar aparecerá.

## Execução
Nesta seção será apresentado todo o funcionamento após a compilação.


### Comandos
Aperte c para mudar a camêra

Aperte space para viajar até os planetas

Aperte l para habilitar ou desabilitar iluminação

Aperte o para visualizar as orbitas

Aperte p para visualizar o plano 

Aperte f para alternar entre fullscreen

Aperte r para mudar entre os modos de realidade e fantasia

Botão direito abre um menu com estas mesmas opções

No modo camêra 1 aperte as setas para movimentar a camera

## Compile

* [freeglut](http://freeglut.sourceforge.net/docs/install.php) - Principal biblioteca
* [SOIL](https://www.lonesock.net/soil.html) - Extensão para texturas
* [SDL](https://wiki.libsdl.org/Installation) - Extensão de audio
* [GLEW](http://glew.sourceforge.net/install.html)-Extensão de comandos
* [GLUT](https://www.opengl.org/resources/libraries/glut/) - Extensão de comandos
## Autores

* **Robert Cristiam** 
* **Matheus Marçal** 

## Itens implementados:

*Skybox - Foi usado uma skyshpere conforme a instrução do professor
*Modo de órbitas visivies - Completo incluindo orbitas de astros.
*Plano orbital - plano completo 
*Orbitas não circulares - orbitas totalmente elípticas.
*Orbitas não coplanares - Alguns objetos possuem orbitas diferenciadas dos demais.
*Anéis - Um objeto possuem um pequeno anel a sua volta.
*Tour entre objetos - Implementado
*Animação do deslocamento - Não implementado porem a um efeito sono que simula a viagem que a nave do observador faz ( efeito da tardis - Doctor Who).
*Escrever na tela dados - Feito.
*Reshape - feito
*Musica - feito
*Fidedignidade - Foi usado esquemas reais com uma escala definida , porém o sistema não retrara o sistema solar , as medidas são reais porem os nomes e planetas não.
*Modo fullscreen - Modo de preenchimento da tela toda foi implementado 
*Menu no mouse- um menu foi criado ao pressionar a tecla direita do mouse com diversa opções.
