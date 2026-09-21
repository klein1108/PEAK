#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <cmath>

#define CAMERA_LIMITE 0.5f

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

    const float limite = (3.141592f / 2.0f) - CAMERA_LIMITE;
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