#ifndef BACKPACK_H
#define BACKPACK_H

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "matrices.h"

struct Item
{
  int id;
  std::string nome;
  float pesoKG;

  Item() : id(0), nome(), pesoKG(0.0f) {}
  Item(int id_, const std::string &nome_, float peso_) : id(id_), nome(nome_), pesoKG(peso_) {}
};

enum class AddingResult
{
  Ok,
  NoSlots,
};

class Backpack
{
public:
  enum class Estado
  {
    Ground,
    Equipped
  };

  int availableSlots = 4;
  float rangeToGrabInGround = 3.0f;
  float rangeToReleaseInGround = 1.5f;
  float escala = 0.28f;
  float yawEquipada = 1.5708f;

  glm::vec3 offsetBack = glm::vec3(0.0f, 2.2f, -0.9f);
  Estado estado = Estado::Ground;
  glm::vec3 pos = glm::vec3(0.0f); 
  float anguloY = 0.0f;
  std::vector<Item> itens;

  float pesoItens()
  {
    float total = 0.0f;
    for (const Item &it : itens)
      total += it.pesoKG;
    return total;
  }

  AddingResult verificar(const Item &item)
  {
    if ((int)itens.size() >= availableSlots)
    {
      return AddingResult::NoSlots;
    }
    return AddingResult::Ok;
  }

  AddingResult adicionar(const Item &item)
  {
    AddingResult r = verificar(item);
    if (r == AddingResult::Ok)
      itens.push_back(item);
    return r;
  }

  bool removerItem(size_t indice, Item *removido = nullptr)
  {
    if (indice >= itens.size())
      return false;
    if (removido)
      *removido = itens[indice];
    itens.erase(itens.begin() + indice);
    return true;
  }

  bool removerItemPorId(int id, Item *removido = nullptr)
  {
    for (size_t i = 0; i < itens.size(); ++i)
      if (itens[i].id == id)
        return removerItem(i, removido);
    return false;
  }

  void esvaziar() { itens.clear(); }

  void colocarNoChao(const glm::vec3 &p, float angulo = 0.0f)
  {
    estado = Estado::Ground;
    pos = p;
    anguloY = angulo;
  }

  bool jogadorPerto(float px, float py, float pz)
  {
    if (estado != Estado::Ground)
      return false;
    float dx = px - pos.x;
    float dz = pz - pos.z;
    bool pertoHorizontal = (dx * dx + dz * dz) <= rangeToGrabInGround * rangeToGrabInGround;
    bool mesmaAltura = std::fabs(py - pos.y) < 4.0f;
    return pertoHorizontal && mesmaAltura;
  }

  bool equipar()
  {
    if (estado == Estado::Equipped)
      return false;
    estado = Estado::Equipped;
    return true;
  }


  bool soltar(float px, float chaoY, float pz, float anguloJogador)
  {
    if (estado == Estado::Ground)
      return false;

    float fx = std::sin(anguloJogador);
    float fz = std::cos(anguloJogador);

    estado = Estado::Ground;
    pos = glm::vec3(px + fx * rangeToReleaseInGround, chaoY, pz + fz * rangeToReleaseInGround);
    anguloY = anguloJogador;
    return true;
  }

  glm::mat4 modeloNoChao()
  {
    float escalaChao = 0.40f; 
    return Matrix_Translate(pos.x, pos.y, pos.z) *
           Matrix_Rotate_Y(anguloY) *
           Matrix_Scale(escalaChao, escalaChao, escalaChao);
  }

  glm::mat4 modeloEquipada(const glm::mat4 &modeloPersonagem)
  {
    return modeloPersonagem *
           Matrix_Translate(offsetBack.x, offsetBack.y, offsetBack.z) *
           Matrix_Rotate_Y(yawEquipada) *
           Matrix_Scale(escala, escala, escala);
  }

  std::string textoHud()
  {
  
    if (estado != Estado::Equipped)
    {
      return "";
    }

    char buf[96];
    std::snprintf(buf, sizeof(buf), "Mochila: %d/%d itens | %.1f kg",
                  (int)itens.size(), availableSlots, pesoItens());
    return std::string(buf);
  }
};

#endif // BACKPACK_H