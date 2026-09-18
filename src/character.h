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

  void mover(float dx, float dz)
  {
    posX += dx;
    posZ += dz;
  }

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

  void processaInput(GLFWwindow *window, float cameraTheta, float deltaT)
  {
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
      float frenteZ = cos(cameraTheta);
      float direitaX = cos(cameraTheta);
      float direitaZ = -sin(cameraTheta);

      if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
      {
        mover(-frenteX * velocidadeAtual, -frenteZ * velocidadeAtual);
      }
      else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
      {
        mover(frenteX * velocidadeAtual, frenteZ * velocidadeAtual);
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

#endif // CHARACTER_H