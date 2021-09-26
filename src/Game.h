
#ifndef SPACEINVADERS_GAME_H
#define SPACEINVADERS_GAME_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "GameObject.h"

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);
  bool collisionCheck(sf::Sprite& sprite1, sf::Sprite& sprite2);
  void laserAction();

 private:
  sf::RenderWindow& window;
  sf::Font font;
  sf::Sprite title;
  sf::Texture title_texture;
  sf::Sprite background;
  sf::Texture background_texture;
  sf::Texture player_texture;
  sf::Texture laser_texture;
  sf::Texture alien_texture_black;
  sf::Texture alien_texture_blue;
  sf::Texture alien_texture_green;
  sf::Texture alien_texture_red;
  sf::Text menu_text;
  sf::Text controls_text;
  sf::Text score_text;
  sf::Text score_text_number;
  sf::Text win_text;
  sf::Text lose_text;
  sf::Text continue_text;

  GameObject* aliens = nullptr;
  GameObject* player = nullptr;
  GameObject* laser = nullptr;

  int player_lives = 5;
  int player_score = 0;
  int alien_score = 10;
  int grid_size = 6;
  int game_mode = 0;
  float add_height = 0;
  float y_val;
  float x_val;
  float a_val;
  float b_val;
  float collision_y_point;
  float player_speed;
  float laser_speed;
  float alien_speed;
  float gravity;
  bool in_menu;
  bool game_over = false;
  bool alien_wins = false;
  bool player_wins = false;
  bool laser_fired = false;
  //sf::Sprite ball;
  //sf::Texture ball_texture;

};

#endif // SPACEINVADERS_GAME_H
