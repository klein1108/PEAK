#ifndef CHARACTER_H
#define CHARACTER_H

#include <GLFW/glfw3.h>
#include <cmath>

#define DASH_MOMENTUM 14.0f
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
  bool tocandoParede;
  bool escalando;

  float velocidadeEscalada;        // velocidade vertical na escalada (W/S)
  float velocidadeEscaladaLateral; // velocidade lateral na escalada (A/D)

  float impulsoX;
  float impulsoZ;

  // Normal horizontal da superfície escalável em contato (aponta da superfície
  // para o jogador). É preenchida pelo main.cpp (UpdatePlayerClimbState) a
  // cada frame em que tocandoParede == true. O Player não sabe qual forma
  // geométrica está sendo escalada: só precisa da normal.
  float paredeNX;
  float paredeNZ;

  float gravidade;
  float forcaPulo;
  float alturaChao;

  Player(float startX = 0.0f, float startY = 0.0f, float startZ = 0.0f)
      : posX(startX), posY(startY), posZ(startZ),
        velocidade(8.0f),
        velocidadeCorrida(12.0f),
        velocidadeY(0.0f),
        estamina(100.0f), estaminaMaxima(100.0f),
        isNoChao(true), tocandoParede(false), escalando(false),
        velocidadeEscalada(5.0f), velocidadeEscaladaLateral(4.0f),
        impulsoX(0.0f), impulsoZ(0.0f),
        paredeNX(0.0f), paredeNZ(1.0f),
        gravidade(GRAVITY), forcaPulo(10.0f),
        alturaChao(0.0f)
  {
  }

  void pular(float dirX, float dirZ, float velocidadeAtual)
  {
    if (isNoChao)
    {
      velocidadeY = forcaPulo;
      isNoChao = false;

      float mag = sqrt(dirX * dirX + dirZ * dirZ);
      if (mag > 0.0001f)
      {
        // Normaliza a direção do movimento
        dirX /= mag;
        dirZ /= mag;

        // O impulso horizontal no ar mantém a velocidade atual do movimento
        impulsoX = dirX * velocidadeAtual;
        impulsoZ = dirZ * velocidadeAtual;
      }
      else
      {
        // Parado: pulo estático (vertical puro)
        impulsoX = 0.0f;
        impulsoZ = 0.0f;
      }
    }
  }

  void atualizarFisica(float deltaT)
  {

    if (escalando)
    {
        velocidadeY = 0.0f;
        return; // enquanto escala, a física normal (gravidade) não roda
    }

    // Gravidade e movimento vertical
    velocidadeY += gravidade * deltaT;
    posY += velocidadeY * deltaT;

    // Movimento horizontal durantes o pulo
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

      // Zera os impulsos horizontais ao tocar o chão para evitar deslizamentos
      impulsoX = 0.0f;
      impulsoZ = 0.0f;
    }
  }

  void processaInput(GLFWwindow *window, float cameraTheta, float deltaT)
  {

    // Escalada: só entra se estiver encostado numa superfície escalável E
    // segurando o botão esquerdo do mouse.
    if (tocandoParede && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        escalando = true;
        isNoChao = false;
        impulsoX = 0.0f;
        impulsoZ = 0.0f;
        velocidadeY = 0.0f;

        // Eixos locais da superfície. O jogador "olha" para dentro dela
        // (frente = -normal) e a direita é frente x cima, a mesma convenção
        // usada na movimentação normal abaixo.
        float frenteX = -paredeNX;
        float frenteZ = -paredeNZ;
        float direitaX = -frenteZ;
        float direitaZ = frenteX;

        float lateral = 0.0f;  // + = direita, - = esquerda
        float vertical = 0.0f; // + = sobe,    - = desce
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) lateral += 1.0f;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) lateral -= 1.0f;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) vertical += 1.0f;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) vertical -= 1.0f;

        // Evita andar mais rápido na diagonal
        float mag = sqrt(lateral * lateral + vertical * vertical);
        if (mag > 1.0f)
        {
            lateral /= mag;
            vertical /= mag;
        }

        // O deslocamento lateral é feito ao longo da tangente da superfície.
        // Quem "gruda" o jogador de volta na superfície (e troca de face ao
        // passar de uma quina) é UpdatePlayerClimbState(), no main.cpp.
        posX += direitaX * lateral * velocidadeEscaladaLateral * deltaT;
        posZ += direitaZ * lateral * velocidadeEscaladaLateral * deltaT;
        posY += vertical * velocidadeEscalada * deltaT;

        // Não deixa descer para dentro do chão
        if (posY < alturaChao)
            posY = alturaChao;

        return; // não executa a movimentação normal enquanto escala
    }
    else
    {
        escalando = false;
    }

    // Frente = mesma direção horizontal que a câmera olha (ver camera.h)
    float frenteX = sin(cameraTheta);
    float frenteZ = cos(cameraTheta);
    // Direita = frente x cima
    float direitaX = -cos(cameraTheta);
    float direitaZ = sin(cameraTheta);

    float dirX = 0.0f;
    float dirZ = 0.0f;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { dirX += frenteX;  dirZ += frenteZ; }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { dirX -= frenteX;  dirZ -= frenteZ; }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { dirX += direitaX; dirZ += direitaZ; }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { dirX -= direitaX; dirZ -= direitaZ; }

    // Determina a velocidade atual (andando ou correndo)
    float velocidadeAtual = velocidade;
    if (isNoChao && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && estamina > 0.0f)
    {
      velocidadeAtual = velocidadeCorrida;
      estamina -= 20.0f * deltaT;
      if (estamina < 0.0f)
        estamina = 0.0f;
    }

    // Executa o Pulo se a tecla ESPAÇO for pressionada
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && isNoChao)
    {
      pular(dirX, dirZ, velocidadeAtual);
    }

    // Movimentação no chão (normalizada e multiplicada por deltaT)
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
  }
};

#endif // CHARACTER_H