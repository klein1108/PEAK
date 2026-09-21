
# Prompt 1
Estou tentando adicionar isso no meu codigo mas nao funciona, fica esquisito. <br>

_[Imagem do erro]_

```c++
glm::mat4 modelground = Matrix_Translate(0.0f, 0.0f, 0.0f) * Matrix_Scale(

                                                                         GROUND_DEFAULT_SX,

                                                                         GROUND_DEFAULT_SY,

                                                                         GROUND_DEFAULT_SZ);

        glUniformMatrix4fv(g_model_uniform, 1, GL_FALSE, glm::value_ptr(modelground));

        glUniform1i(g_object_id_uniform, PLANE);

        DrawVirtualObject("the_plane");
```




meu while:


```c++
while (!glfwWindowShouldClose(window))

    {

        // Aqui executamos as operações de renderização



        // Definimos a cor do "fundo" do framebuffer como branco.  Tal cor é

        // definida como coeficientes RGBA: Red, Green, Blue, Alpha; isto é:

        // Vermelho, Verde, Azul, Alpha (valor de transparência).

        // Conversaremos sobre sistemas de cores nas aulas de Modelos de Iluminação.

        //

        //           R     G     B     A

        glClearColor(0.9f, 0.9f, 1.0f, 1.0f);



        // "Pintamos" todos os pixels do framebuffer com a cor definida acima,

        // e também resetamos todos os pixels do Z-buffer (depth buffer).

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



        // Pedimos para a GPU utilizar o programa de GPU criado acima (contendo

        // os shaders de vértice e fragmentos).

        glUseProgram(g_GpuProgramID);



        // Computamos a posição da câmera utilizando coordenadas esféricas.  As

        // variáveis g_CameraDistance, g_CameraPhi, e g_CameraTheta são

        // controladas pelo mouse do usuário. Veja as funções CursorPosCallback()

        // e ScrollCallback().

        float r = g_CameraDistance;

        float y = r * sin(g_CameraPhi);

        float z = r * cos(g_CameraPhi) * cos(g_CameraTheta);

        float x = r * cos(g_CameraPhi) * sin(g_CameraTheta);



        // Abaixo definimos as varáveis que efetivamente definem a câmera virtual.

        // Veja slides 195-227 e 229-234 do documento Aula_08_Sistemas_de_Coordenadas.pdf.

        glm::vec4 camera_position_c = glm::vec4(x, y, z, 1.0f);             // Ponto "c", centro da câmera

        glm::vec4 camera_lookat_l = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);      // Ponto "l", para onde a câmera (look-at) estará sempre olhando

        glm::vec4 camera_view_vector = camera_lookat_l - camera_position_c; // Vetor "view", sentido para onde a câmera está virada

        glm::vec4 camera_up_vector = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);     // Vetor "up" fixado para apontar para o "céu" (eito Y global)



        // Computamos a matriz "View" utilizando os parâmetros da câmera para

        // definir o sistema de coordenadas da câmera.  Veja slides 2-14, 184-190 e 236-242 do documento Aula_08_Sistemas_de_Coordenadas.pdf.

        glm::mat4 view = Matrix_Camera_View(camera_position_c, camera_view_vector, camera_up_vector);



        // Agora computamos a matriz de Projeção.

        glm::mat4 projection;



        // Note que, no sistema de coordenadas da câmera, os planos near e far

        // estão no sentido negativo! Veja slides 176-204 do documento Aula_09_Projecoes.pdf.

        float nearplane = -0.1f; // Posição do "near plane"

        float farplane = -500.0f; // Posição do "far plane"



        if (g_UsePerspectiveProjection)

        {

            // Projeção Perspectiva.

            // Para definição do field of view (FOV), veja slides 205-215 do documento Aula_09_Projecoes.pdf.

            float field_of_view = 3.141592 / 3.0f;

            projection = Matrix_Perspective(field_of_view, g_ScreenRatio, nearplane, farplane);

        }

        else

        {

            // Projeção Ortográfica.

            // Para definição dos valores l, r, b, t ("left", "right", "bottom", "top"),

            // PARA PROJEÇÃO ORTOGRÁFICA veja slides 219-224 do documento Aula_09_Projecoes.pdf.

            // Para simular um "zoom" ortográfico, computamos o valor de "t"

            // utilizando a variável g_CameraDistance.

            float t = 1.5f * g_CameraDistance / 2.5f;

            float b = -t;

            float r = t * g_ScreenRatio;

            float l = -r;

            projection = Matrix_Orthographic(l, r, b, t, nearplane, farplane);

        }



        glm::mat4 model = Matrix_Identity(); // Transformação identidade de modelagem



        // Enviamos as matrizes "view" e "projection" para a placa de vídeo

        // (GPU). Veja o arquivo "shader_vertex.glsl", onde estas são

        // efetivamente aplicadas em todos os pontos.

        glUniformMatrix4fv(g_view_uniform, 1, GL_FALSE, glm::value_ptr(view));

        glUniformMatrix4fv(g_projection_uniform, 1, GL_FALSE, glm::value_ptr(projection));



        // Desenhamos o modelo da esfera

        // model = Matrix_Translate(-1.0f, 0.0f, 0.0f) * Matrix_Rotate_Z(0.6f) * Matrix_Rotate_X(0.2f) * Matrix_Rotate_Y(g_AngleY + (float)glfwGetTime() * 0.1f);

        // glUniformMatrix4fv(g_model_uniform, 1, GL_FALSE, glm::value_ptr(model));

        // glUniform1i(g_object_id_uniform, SPHERE);

        // DrawVirtualObject("the_sphere");



        // Desenhamos o modelo do coelho

        // model = Matrix_Translate(1.0f, 0.0f, 0.0f) * Matrix_Rotate_X(g_AngleX + (float)glfwGetTime() * 0.1f);

        // glUniformMatrix4fv(g_model_uniform, 1, GL_FALSE, glm::value_ptr(model));

        // glUniform1i(g_object_id_uniform, BUNNY);

        // DrawVirtualObject("the_bunny");



        // Desenhamos o plano do chão

        // model = Matrix_Translate(0.0f, -1.1f, 0.0f);

        // glUniformMatrix4fv(g_model_uniform, 1, GL_FALSE, glm::value_ptr(model));

        // glUniform1i(g_object_id_uniform, PLANE);

        // DrawVirtualObject("the_plane");



        glm::mat4 modelground = Matrix_Translate(0.0f, 0.0f, 0.0f) * Matrix_Scale(

                                                                         GROUND_DEFAULT_SX,

                                                                         GROUND_DEFAULT_SY,

                                                                         GROUND_DEFAULT_SZ);

        glUniformMatrix4fv(g_model_uniform, 1, GL_FALSE, glm::value_ptr(modelground));

        glUniform1i(g_object_id_uniform, PLANE);

        DrawVirtualObject("the_plane");



        // DESENHANDO PARTES DO PERSONAGEM

        glUniform1i(g_object_id_uniform, CHARACTER_BODY);

        DrawVirtualObject("the_peakchar_body");



        glUniform1i(g_object_id_uniform, CHARACTER_CLOTHES);

        DrawVirtualObject("the_peakchar_clothes");



        glUniform1i(g_object_id_uniform, CHARACTER_HEAD);

        DrawVirtualObject("the_peakchar_head");



        glUniform1i(g_object_id_uniform, CHARACTER_HAT);

        DrawVirtualObject("the_peakchar_hat");



        // Imprimimos na tela os ângulos de Euler que controlam a rotação do

        // terceiro cubo.

        TextRendering_ShowEulerAngles(window);



        // Imprimimos na informação sobre a matriz de projeção sendo utilizada.

        TextRendering_ShowProjection(window);



        // Imprimimos na tela informação sobre o número de quadros renderizados

        // por segundo (frames per second).

        TextRendering_ShowFramesPerSecond(window);



        // O framebuffer onde OpenGL executa as operações de renderização não

        // é o mesmo que está sendo mostrado para o usuário, caso contrário

        // seria possível ver artefatos conhecidos como "screen tearing". A

        // chamada abaixo faz a troca dos buffers, mostrando para o usuário

        // tudo que foi renderizado pelas funções acima.

        // Veja o link: https://en.wikipedia.org/w/index.php?title=Multiple_buffering&oldid=793452829#Double_buffering_in_computer_graphics

        glfwSwapBuffers(window);



        // Verificamos com o sistema operacional se houve alguma interação do

        // usuário (teclado, mouse, ...). Caso positivo, as funções de callback

        // definidas anteriormente usando glfwSet*Callback() serão chamadas

        // pela biblioteca GLFW.

        glfwPollEvents();

    }
```    

## Resposta:
O problema ocorre porque o OpenGL funciona como uma máquina de estados: quando você envia a matriz modelground (que provavelmente tem um valor de escala enorme para criar o chão) para a placa de vídeo usando o glUniformMatrix4fv, essa mesma matriz continua ativa para tudo o que for desenhado logo em seguida.

Como você não definiu e enviou uma nova matriz de modelo antes de chamar o DrawVirtualObject das partes do personagem, o seu personagem está sendo desenhado com a exata mesma escala gigante do chão. É por isso que ele fica esquisito ou some da tela (como visto na sua captura "image_9c1b05.png").

Para resolver isso, você precisa criar uma matriz para o personagem e enviá-la para a GPU logo após desenhar o chão.

Veja como corrigir o seu código:

```C++
        // Desenhamos o plano do chão
        glm::mat4 modelground = Matrix_Translate(0.0f, 0.0f, 0.0f) * Matrix_Scale(
                                                                 GROUND_DEFAULT_SX,
                                                                 GROUND_DEFAULT_SY,
                                                                 GROUND_DEFAULT_SZ);
        glUniformMatrix4fv(g_model_uniform, 1, GL_FALSE, glm::value_ptr(modelground));
        glUniform1i(g_object_id_uniform, PLANE);
        DrawVirtualObject("the_plane");


        // --- CORREÇÃO AQUI ---
        // Criamos uma nova matriz para o personagem (sem a escala gigante do chão)
        // Se o chão estiver em Y = 0.0f, você pode precisar subir o personagem um pouco no eixo Y
        // para ele não ficar enterrado pela metade (ex: Matrix_Translate(0.0f, 1.0f, 0.0f))
        glm::mat4 model_character = Matrix_Translate(0.0f, 0.0f, 0.0f) * Matrix_Scale(1.0f, 1.0f, 1.0f); 
        
        // Enviamos a nova matriz do personagem para substituir a matriz do chão na GPU
        glUniformMatrix4fv(g_model_uniform, 1, GL_FALSE, glm::value_ptr(model_character));
        // ---------------------


        // DESENHANDO PARTES DO PERSONAGEM
        glUniform1i(g_object_id_uniform, CHARACTER_BODY);
        DrawVirtualObject("the_peakchar_body");

        glUniform1i(g_object_id_uniform, CHARACTER_CLOTHES);
        DrawVirtualObject("the_peakchar_clothes");

        glUniform1i(g_object_id_uniform, CHARACTER_HEAD);
        DrawVirtualObject("the_peakchar_head");

        glUniform1i(g_object_id_uniform, CHARACTER_HAT);
        DrawVirtualObject("the_peakchar_hat");
```

Resumo da regra de ouro do OpenGL: Sempre que você for desenhar um objeto diferente que está em uma posição ou tem um tamanho diferente, você precisa atualizar a variável g_model_uniform com a matriz específica dele antes de chamar a função que o desenha.

___

# Prompt 2

No momento ele esta so pulando, quero que ele pule para a direcao que eu estiver me movimentando quando pular (ou no mesmo lugar se parado). <br><br>
Considere meu codigo:


```C++
#ifndef CHARACTER_H

#define CHARACTER_H



#include <GLFW/glfw3.h>

#include <cmath>



#define DASH_MOMENTUM 18.0f

#define GRAVITY -23.0f



class Player

{



public:

  float posX, posY, posZ;



  float velocidade;

  float velocidadeCorrida;

  float velocidadeY;



  float estamina;

  float estaminaMaxima;



  bool isNoChao;

  bool isJaDeuImpulsoNoAr;



  float impulsoX;

  float impulsoZ;



  float gravidade;

  float forcaPulo;

  float forcaImpulsoDash;

  float forcaImpulsoPuloCorrendo;

  float alturaChao;



  Player(float startX = 0.0f, float startY = 0.0f, float startZ = 0.0f)

      : posX(startX), posY(startY), posZ(startZ),

        velocidade(0.1f), velocidadeCorrida(0.2f),

        estamina(100.0f), estaminaMaxima(100.0f),

        velocidadeY(0.0f), isNoChao(true), isJaDeuImpulsoNoAr(false),

        impulsoX(0.0f), impulsoZ(0.0f),

        gravidade(GRAVITY), forcaPulo(10.0f),

        forcaImpulsoDash(DASH_MOMENTUM),

        forcaImpulsoPuloCorrendo(6.5f),

        alturaChao(0.0f)

  {

  }



  void mover(float dx, float dz)

  {

    posX += dx;

    posZ += dz;

  }



  void pular(GLFWwindow *window, float cameraTheta)

  {

    if (isNoChao)

    {

      bool isCorrendo = (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && estamina > 0.0f);



      velocidadeY = forcaPulo;

      isNoChao = false;



      // Calcula direção baseada nas teclas pressionadas (igual ao processaInput)

      float frenteX = sin(cameraTheta);

      float frenteZ = -cos(cameraTheta);

      float direitaX = cos(cameraTheta);

      float direitaZ = sin(cameraTheta);



      float dirX = 0.0f;

      float dirZ = 0.0f;



      if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)

      {

        dirX += frenteX;

        dirZ += frenteZ;

      }

      else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)

      {

        dirX -= frenteX;

        dirZ -= frenteZ;

      }



      if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)

      {

        dirX -= direitaX;

        dirZ -= direitaZ;

      }

      else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)

      {

        dirX += direitaX;

        dirZ += direitaZ;

      }



      // Normaliza (importante pro caso de diagonal, tipo W+D)

      float mag = sqrt(dirX * dirX + dirZ * dirZ);

      if (mag > 0.0001f)

      {

        dirX /= mag;

        dirZ /= mag;



        float forcaImpulso = isCorrendo ? forcaImpulsoDash : forcaImpulsoPuloCorrendo;



        impulsoX = dirX * forcaImpulso;

        impulsoZ = dirZ * forcaImpulso;

      }

      else

      {

        // Parado: pulo vertical puro, sem impulso horizontal

        impulsoX = 0.0f;

        impulsoZ = 0.0f;

      }

    }

  }



  void atualizarFisica(float deltaT)

  {

    velocidadeY += gravidade * deltaT;

    posY += velocidadeY * deltaT;



    posX += impulsoX * deltaT;

    posZ += impulsoZ * deltaT;



    if (posY <= alturaChao)

    {

      posY = alturaChao;

      velocidadeY = 0.0f;

      isNoChao = true;

      isJaDeuImpulsoNoAr = false;

    }

  }



  void processaInput(GLFWwindow *window, float cameraTheta, float deltaT)

  {



    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)

    {

      pular(window, cameraTheta);

    }



    float velocidadeAtual = velocidade;

    if (isNoChao && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && estamina > 0.0f)

    {

      velocidadeAtual = velocidadeCorrida;

      estamina -= 20.0f * deltaT;

      if (estamina < 0.0f)

        estamina = 0.0f;

    }



    if (isNoChao)

    {

      float frenteX = sin(cameraTheta);

      float frenteZ = -cos(cameraTheta);

      float direitaX = cos(cameraTheta);

      float direitaZ = sin(cameraTheta);



      if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)

      {

        mover(frenteX * velocidadeAtual, frenteZ * velocidadeAtual);

      }

      else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)

      {

        mover(-frenteX * velocidadeAtual, -frenteZ * velocidadeAtual);

      }



      if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)

      {

        mover(-direitaX * velocidadeAtual, -direitaZ * velocidadeAtual);

      }

      else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)

      {

        mover(direitaX * velocidadeAtual, direitaZ * velocidadeAtual);

      }

    }

  }

};
```


#endif // CHARACTER_H


## Resposta

O motivo principal do seu personagem parecer estar "só pulando no mesmo lugar" ocorre devido a dois problemas no gerenciamento de movimentação e no deltaT:

### Incompatibilidade do deltaT (Chão vs. Ar):
- No chão (processaInput), a função mover() adicionava a velocidade diretamente sem multiplicar por deltaT (posX += dx). Se seu jogo rodava a 60 FPS, o personagem andava $0.1 \times 60 = 6.0$ unidades/segundo.
- No ar (atualizarFisica), você aplicava impulsoX * deltaT. Se a força do pulo era $6.5$, a velocidade no ar ficava $6.5 \times 0.016 = 0.10$ por frame. Em taxas de quadros mais altas (ex: 120 FPS+), o movimento no ar ficava microscópico comparado ao movimento do chão, dando a sensação de que ele pulava parado.

### Impulso não era zerado ao pousar:
- Em atualizarFisica(), quando o personagem tocava o chão, impulsoX e impulsoZ não eram redefinidos para 0.0f, fazendo o personagem deslizar indefinidamente no chão após pousar.

### Movimentação na diagonal no chão:
- No chão, ao apertar W + D, a função mover era chamada duas vezes seguidas, fazendo o personagem andar mais rápido na diagonal do que em linha reta.

```C++
Player(float startX = 0.0f, float startY = 0.0f, float startZ = 0.0f)
    : posX(startX), posY(startY), posZ(startZ),
      velocidade(6.0f),          // Alterado de 0.1f para 6.0f (unidades/s)
      velocidadeCorrida(12.0f),  // Alterado de 0.2f para 12.0f (unidades/s)
      estamina(100.0f), estaminaMaxima(100.0f),
      velocidadeY(0.0f), isNoChao(true),
      impulsoX(0.0f), impulsoZ(0.0f),
      gravidade(GRAVITY), forcaPulo(10.0f),
      alturaChao(0.0f)
{
}```

2. Método pular() (Simplificação e conservação de momento)
Agora recebe a direção e a velocidade atual pré-calculadas em vez de processar o teclado novamente:

```C++
void pular(float dirX, float dirZ, float velocidadeAtual)
{
    if (isNoChao)
    {
        velocidadeY = forcaPulo;
        isNoChao = false;

        float mag = sqrt(dirX * dirX + dirZ * dirZ);
        if (mag > 0.0001f)
        {
            dirX /= mag;
            dirZ /= mag;

            // Define o impulso no ar com base na velocidade que ele já estava (andando ou correndo)
            impulsoX = dirX * velocidadeAtual;
            impulsoZ = dirZ * velocidadeAtual;
        }
        else
        {
            // Parado: pulo estático
            impulsoX = 0.0f;
            impulsoZ = 0.0f;
        }
    }
}
```

3. Método atualizarFisica() (Reset do impulso ao pousar)
Adicionada a limpeza do impulso ao tocar o chão para impedir que o personagem deslize infinitamente:

```C++
void atualizarFisica(float deltaT)
{
    velocidadeY += gravidade * deltaT;
    posY += velocidadeY * deltaT;

    // Atualiza posição no ar
    if (!isNoChao)
    {
        posX += impulsoX * deltaT;
        posZ += impulsoZ * deltaT;
    }

    // Colisão com o chão
    if (posY <= alturaChao)
    {
        posY = alturaChao;
        velocidadeY = 0.0f;
        isNoChao = true;

        // NOVO: Zera o impulso ao tocar o chão
        impulsoX = 0.0f;
        impulsoZ = 0.0f;
    }
}
```

4. Método processaInput() (Cálculo unificado e multiplicação por deltaT)
A direção é calculada uma única vez, a movimentação na diagonal é normalizada e o movimento no chão agora usa deltaT:

```C++
void processaInput(GLFWwindow *window, float cameraTheta, float deltaT)
{
    // 1. Vetores de direção calculados uma vez no início
    float frenteX = sin(cameraTheta), frenteZ = -cos(cameraTheta);
    float direitaX = cos(cameraTheta), direitaZ = sin(cameraTheta);

    float dirX = 0.0f, dirZ = 0.0f;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { dirX += frenteX; dirZ += frenteZ; }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { dirX -= frenteX; dirZ -= frenteZ; }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { dirX -= direitaX; dirZ -= direitaZ; }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { dirX += direitaX; dirZ += direitaZ; }

    // 2. Velocidade atual
    float velocidadeAtual = velocidade;
    if (isNoChao && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && estamina > 0.0f)
    {
        velocidadeAtual = velocidadeCorrida;
        estamina -= 20.0f * deltaT;
        if (estamina < 0.0f) estamina = 0.0f;
    }

    // 3. Pulo repassando direção e velocidade
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && isNoChao)
    {
        pular(dirX, dirZ, velocidadeAtual);
    }

    // 4. Movimento no chão normalizado e com deltaT
    if (isNoChao)
    {
        float mag = sqrt(dirX * dirX + dirZ * dirZ);
        if (mag > 0.0001f)
        {
            dirX /= mag;
            dirZ /= mag;

            posX += dirX * velocidadeAtual * deltaT;
            posZ += dirZ * velocidadeAtual * deltaT;
        }
    }
```
---
# Prompt 3

[Arquivo de codigo main.cpp]<br><br>
Preciso implementar uma camera para que ela fique seguindo as costas do meu personagem (terceira pessoa) e tambem mudar para o ponto de vista do personagem (primeira pessoa).

## Resposta

Vou implementar isso no camera.h, aproveitando as variáveis g_CameraTheta e g_CameraPhi que você já controla pelo mouse — elas vão servir tanto para orbitar a câmera (3ª pessoa) quanto para olhar ao redor (1ª pessoa).

```C++
#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <cmath>

struct Camera
{
  glm::vec4 position_c;
  glm::vec4 lookat_l;
  glm::vec4 view_vector;
  glm::vec4 up_vector = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);

  bool primeira_pessoa = false;

  // Agora recebemos theta (esquerda/direita) e phi (cima/baixo)
  void atualizar(float player_x, float player_y, float player_z, float theta, float phi)
  {

    const float limite = (3.141592f / 2.0f) - 0.05f;
    if (phi > limite)
      phi = limite;
    if (phi < -limite)
      phi = -limite;
    // 1. Usamos a matemática esférica para criar um "vetor de direção" 3D
    // Isso nos diz exatamente para qual ponto no espaço o mouse está apontando

    float dir_x = sin(theta) * cos(phi);
    float dir_y = sin(phi);
    float dir_z = cos(theta) * cos(phi);

    glm::vec4 direcao_mouse = glm::vec4(dir_x, dir_y, dir_z, 0.0f);

    if (primeira_pessoa)
    {
      float altura_olhos = 4.0f; // Ajuste fino da altura da cabeça

      // A câmera fica exatamente onde o corpo do boneco está
      position_c = glm::vec4(player_x, player_y + altura_olhos, player_z, 1.0f);

      // E o "alvo" para onde ela olha é a posição dela + a direção do mouse
      lookat_l = position_c + direcao_mouse;
    }
    else
    {
      // Em TERCEIRA PESSOA, a câmera fica flutuando ATRÁS do personagem.
      // Para isso, multiplicamos a direção do mouse por uma distância e subtraímos da posição.
      float distancia = 7.0f;
      float altura_extra = 3.0f;

      position_c = glm::vec4(player_x - (dir_x * distancia),
                             player_y + altura_extra - (dir_y * distancia),
                             player_z - (dir_z * distancia), 1.0f);

      // A câmera de 3ª pessoa olha diretamente para o pescoço/costas do player
      lookat_l = glm::vec4(player_x, player_y + 3.0f, player_z, 1.0f);
    }

    // Calcula o view vector final
    view_vector = lookat_l - position_c;
  }
};

#endif
```

A lógica: a câmera calcula uma direção de "olhar" a partir de theta/phi (mesma matemática esférica que já existe no seu código). Em primeira pessoa, a câmera fica na posição da cabeça do personagem olhando nessa direção. Em terceira pessoa, ela fica posicionada atrás do personagem (na direção oposta ao olhar) a uma certa distância, e mira nele.

```C++
#include "camera.h"

// ...

Camera camera;

float tempoAnterior = (float)glfwGetTime();

int main(int argc, char *argv[]){

```
1. Adiciona dependencia e inicializa Camera

```C++
        // ...
        player.processaInput(window, g_CameraTheta, deltaT);
        player.atualizarFisica(deltaT);

        // 3. CÂMERA
        camera.atualizar(player.posX, player.posY, player.posZ, g_CameraTheta, g_CameraPhi);
        glm::mat4 view = Matrix_Camera_View(camera.position_c, camera.view_vector, camera.up_vector);
```
2. Inicialica visão da camera na função principal

```C++
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mod)
{
    // ...

    if (key == GLFW_KEY_C && action == GLFW_PRESS)
    {
        camera.primeira_pessoa = !camera.primeira_pessoa; // Inverte o estado
    }
}
```
3. Permite com que o jogador consiga fazer a troca entre as cameras
