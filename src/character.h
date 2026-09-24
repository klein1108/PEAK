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

  float impulsoX;
  float impulsoZ;

  float gravidade;
  float forcaPulo;
  float alturaChao;

  Player(float startX = 0.0f, float startY = 0.0f, float startZ = 0.0f)
      : posX(startX), posY(startY), posZ(startZ),
        velocidade(8.0f),
        velocidadeCorrida(12.0f),
        estamina(100.0f), estaminaMaxima(100.0f),
        velocidadeY(0.0f), isNoChao(true),
        impulsoX(0.0f), impulsoZ(0.0f),
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