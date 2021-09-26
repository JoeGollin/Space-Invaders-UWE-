#include "GameObject.h"
#include <iostream>

GameObject::GameObject()
{
  alien_position = new Vector2(200,50);
  alien_direction = new Vector2(1, 0);
  player_position = new Vector2(1080.0f / 2, 640);
  player_direction = new Vector2(0, 0);
  laser_position = new Vector2(0,0);
  laser_direction = new Vector2(0,-1);
}

GameObject::~GameObject()
{

}

bool GameObject::initialiseSprite(sf::Texture& texture, std::string filename)
{
  if(!texture.loadFromFile(filename))
  {
    std::cout << filename << " failed to load \n";
  }
  sprite = new sf::Sprite(texture);
  return true;
}

sf::Sprite* GameObject::getSprite()
{
  return sprite;
}

bool GameObject::getVisibility() const
{

  return is_visible;
}

void GameObject::setVisibility(bool value)
{
  is_visible = value;
}


