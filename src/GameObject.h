
#ifndef SPACEINVADERS_GAMEOBJECT_H
#define SPACEINVADERS_GAMEOBJECT_H
#include <SFML/Graphics.hpp>
#include "Vector2.h"

class GameObject
{
 public:
  GameObject();
  ~GameObject();
  bool initialiseSprite(sf::Texture &texture, std::string filename);
  sf::Sprite* getSprite();
  bool getVisibility() const;
  void setVisibility(bool value);
  Vector2* alien_position = nullptr;
  Vector2* alien_direction = nullptr;
  Vector2* player_position = nullptr;
  Vector2* player_direction = nullptr;
  Vector2* laser_position = nullptr;
  Vector2* laser_direction = nullptr;

 private:
  sf::Sprite* sprite = nullptr;
  bool is_visible = true;

};

#endif // SPACEINVADERS_GAMEOBJECT_H
