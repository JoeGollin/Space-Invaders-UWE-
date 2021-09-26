
#include "Game.h"
#include <cmath>
#include <iostream>
#include <cmath>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(nullptr));
}

Game::~Game()
{
  delete [] aliens;
  aliens = nullptr;

}

bool Game::init()
{
  in_menu = true;
  sf::Vector2f window_size(1080.0f, 720.0f);
  player_score = 0;
  player_speed = 500;
  laser_speed = 400;
  alien_speed = 150;
  gravity = 0.01f;
  add_height = 0;
  x_val = 0;
  y_val = 0;

  if (!background_texture.loadFromFile(
        "Data/Images/SpaceShooterRedux/Backgrounds/darkPurple.png"))
  {
    std::cout << "Background texture cannot be loaded\n";
  }
  background.setTexture(background_texture);
  background.setScale(window_size.x / background.getLocalBounds().width,
                      window_size.y / background.getLocalBounds().height);

  if(!title_texture.loadFromFile("Data/Images/spaceInvaders.png"))
  {
    std::cout << "Title texture cannot be loaded\n";
  }
  title.setTexture(title_texture);
  title.setScale(0.5,0.5);
  title.setPosition(window.getSize().x / 2.0f - title.getGlobalBounds().width / 2,
                    window.getSize().y / 5.0f - title.getGlobalBounds().height / 2);

  if (!font.loadFromFile("Data/Fonts/8-bit-hud/8-bit-hud.ttf"))
  {
    std::cout << "Font did not load \n";
  }
  menu_text.setString("[Enter] to start the game\n"
                      "[1] For Gravity Mode\n"
                      "[2] For Quadratic Mode\n"
                      "[3] For Curve Mode\n"
                      "[Esc] to quit");
  menu_text.setFont(font);
  menu_text.setCharacterSize(15);
  menu_text.setFillColor(sf::Color::White);
  menu_text.setPosition(
    window.getSize().x / 2.0f - menu_text.getGlobalBounds().width / 2,
    window.getSize().y / 2.0f - menu_text.getGlobalBounds().height / 2);

  controls_text.setString("[A] to move spaceship left\n"
                          "[D] to move spaceship right\n"
                          "[Space] to fire laser\n"
                          "[Esc] to quit at anytime");
  controls_text.setFont(font);
  controls_text.setCharacterSize(15);
  controls_text.setFillColor(sf::Color::White);
  controls_text.setPosition(10, 630);

  score_text.setString("Score: ");
  score_text.setFont(font);
  score_text.setCharacterSize(15);
  score_text.setFillColor(sf::Color::White);
  score_text.setPosition(10, 10);

  score_text_number.setString(std::to_string(player_score));
  score_text_number.setFont(font);
  score_text_number.setCharacterSize(15);
  score_text_number.setFillColor(sf::Color::White);
  score_text_number.setPosition(120, 10);

  win_text.setString("Congratulations, you win!");
  win_text.setFont(font);
  win_text.setCharacterSize(15);
  win_text.setFillColor(sf::Color::White);
  win_text.setPosition(
    window.getSize().x / 2.0f - win_text.getGlobalBounds().width / 2,
    window.getSize().y / 2.0f - win_text.getGlobalBounds().height / 2);

  lose_text.setString("Congratulations, you lose!");
  lose_text.setFont(font);
  lose_text.setCharacterSize(15);
  lose_text.setFillColor(sf::Color::White);
  lose_text.setPosition(
    window.getSize().x / 2.0f - lose_text.getGlobalBounds().width / 2,
    window.getSize().y / 2.0f - lose_text.getGlobalBounds().height / 2);

  continue_text.setString("Press [Enter] to continue");
  continue_text.setFont(font);
  continue_text.setCharacterSize(15);
  continue_text.setFillColor(sf::Color::White);
  continue_text.setPosition(
    window.getSize().x / 2.0f - continue_text.getGlobalBounds().width / 2,
    window.getSize().y / 1.50f - continue_text.getGlobalBounds().height / 2);

  player = new GameObject();
  player->initialiseSprite(
    player_texture,"Data/Images/SpaceShooterRedux/PNG/playerShip1_blue.png");
  player->getSprite()->setScale(0.5,0.5);
  player->getSprite()->setPosition(player->player_position->x,
                                   player->player_position->y);

  laser = new GameObject();
  laser->initialiseSprite(
    laser_texture,"Data/Images/SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
  laser->getSprite()->setScale(0.5,0.5);


  aliens = new GameObject[grid_size*grid_size];
  for (int i = 0; i < grid_size; i++)
  {
    for (int j = 0; j < grid_size; j++) // Y Axis
    {
      if((i*grid_size*j)% 4 == 0)
      {
        aliens[i*grid_size+j].initialiseSprite(alien_texture_red,"Data/Images/SpaceShooterRedux/PNG/Enemies/enemyRed1.png");
      }
      if((i*grid_size*j)% 4 == 1)
      {
        aliens[i*grid_size+j].initialiseSprite(alien_texture_blue,"Data/Images/SpaceShooterRedux/PNG/Enemies/enemyBlue1.png");
      }
      if((i*grid_size*j)% 4 == 2)
      {
        aliens[i*grid_size+j].initialiseSprite(alien_texture_green,"Data/Images/SpaceShooterRedux/PNG/Enemies/enemyGreen1.png");
      }
      if((i*grid_size*j)% 4 == 3)
      {
        aliens[i*grid_size+j].initialiseSprite(alien_texture_black,"Data/Images/SpaceShooterRedux/PNG/Enemies/enemyBlack1.png");
      }
      aliens[i*grid_size+j].getSprite()->setScale(0.5, 0.5);
      aliens[i*grid_size+j].getSprite()->setPosition(
        aliens->alien_position->x + 100 * i,
        aliens->alien_position->y + 40 *j);

    }
  }
  return true;
}

void Game::update(float dt)
{
  player->getSprite()->move(player->player_direction->x * player_speed * dt,
                            player->player_direction->y * player_speed * dt);

  if (laser_fired)
  {
    laser->getSprite()->move(laser->laser_direction->x * laser_speed * dt,
                             laser->laser_direction->y * laser_speed * dt);
  }

  for (int i = 0; i < grid_size*grid_size; i++)
  {
    //Border Collision
    if(aliens[i].getSprite()->getPosition().x >=
          window.getSize().x - aliens[i].getSprite()->getGlobalBounds().width
         || aliens[i].getSprite()->getPosition().x <= 0)
    {
      if(game_mode == 1) // Gravity Mode
      {
        aliens[i].getSprite()->setPosition(
          aliens[i].getSprite()->getPosition().x,
          aliens[i].getSprite()->getPosition().y +
          aliens[i].getSprite()->getGlobalBounds().height / 2);
        gravity += 0.005f;
      }
      if(game_mode == 2)
      {
        add_height += 1.5;
      }
      if(game_mode == 3)
      {
        add_height += 2;
        aliens[i].alien_direction->x = -aliens[i].alien_direction->x;
      }
      else
      {
        aliens[i].getSprite()->setPosition(
          aliens[i].getSprite()->getPosition().x,
          aliens[i].getSprite()->getPosition().y +
            aliens[i].getSprite()->getGlobalBounds().height);
        aliens[i].alien_direction->x = -aliens[i].alien_direction->x;
      }
    }



    if (game_mode == 1) // Gravity Movement - Works (but basic)!
    {
      aliens[i].getSprite()->move(
        aliens[i].alien_direction->x * alien_speed * dt,
        aliens[i].alien_direction->y + gravity * alien_speed * dt );
    }
    else if (game_mode == 2) // Quadratic Movement
    {
      aliens[i].getSprite()->move(
        aliens[i].alien_direction->x * alien_speed * dt,
        aliens[i].alien_direction->y * alien_speed * dt);

      x_val = aliens[i].getSprite()->getPosition().x;
      y_val = -0.0002 * pow(x_val - 540, 2) + add_height; // y = ax2 // add_height makes it move down on border collision
      aliens[i].getSprite()->setPosition(aliens[i].getSprite()->getPosition().x,y_val);

    }
    else if (game_mode == 3) // Curve Movement
    {

      aliens[i].getSprite()->move(
        aliens[i].alien_direction->x * alien_speed * dt,
        aliens[i].alien_direction->y * alien_speed * dt);

      x_val = aliens[i].getSprite()->getPosition().x;
      y_val = 10.0f *sinf(10 * x_val) + add_height; // y = a sin(bx),
      aliens[i].getSprite()->setPosition(aliens[i].getSprite()->getPosition().x,y_val);
      //y_val = 0.01f * x_val - 10 * 2 + 10;
    }
    else // Normal Line Movement
    {
      aliens[i].getSprite()->move(
        aliens[i].alien_direction->x * alien_speed * dt,
        aliens[i].alien_direction->y * alien_speed * dt);
    }




    // If Aliens Reach Player Level = Alien Wins
    if(aliens->getSprite()->getPosition().y >= player->player_position->y
        || collisionCheck(*aliens[i].getSprite(), *player->getSprite())
             && aliens[i].getVisibility())  // Aliens are at ship height, game over
    {
      game_over = true;
      alien_wins = true;
    }

    // If No Aliens left = Player Wins
    if(player_score == alien_score * grid_size*grid_size)
    {
      game_over = true;
      player_wins = true;
    }
  }

  // Laser Collision
  for (int i = 0; i < grid_size*grid_size; i++)
  {
    if(collisionCheck(*laser->getSprite(),*aliens[i].getSprite())
        && aliens[i].getVisibility() && laser->getVisibility())
    {
      aliens[i].setVisibility(false);
      laser->setVisibility(false);
      player_score += 10;
      score_text_number.setString(std::to_string(player_score));
    }
  }
}

void Game::render()
{
  if(in_menu)
  {
    window.draw(background);
    window.draw(title);
    window.draw(menu_text);
    window.draw(controls_text);
  }
  if(game_over)
  {
    window.draw(background);
    window.draw(title);
    if (player_wins)
    {
      window.draw(win_text);
      window.draw(continue_text);
    }
    else
    {
      window.draw(lose_text);
      window.draw(continue_text);
    }
  }
  else if(!in_menu and !game_over) // In game
  {
    window.draw(background);
    window.draw(score_text);
    window.draw(score_text_number);
    window.draw(*player->getSprite());
    for(int i = 0; i < grid_size*grid_size; ++i)
    {
      if(aliens[i].getVisibility())
      {
        window.draw(*aliens[i].getSprite());
      }
    }
    if (laser_fired)
    {
      if (laser->getVisibility())
      {
        window.draw(*laser->getSprite());
      }
    }
  }
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);
}

void Game::keyPressed(sf::Event event)
{
  if (in_menu) // In Menu
  {
    init();
    if(event.key.code == sf::Keyboard::Enter) // Normal Mode
    {
      game_mode = 0;
      in_menu = false;
    }
    if(event.key.code == sf::Keyboard::Escape) // Close Game
    {
      window.close();
    }
    if (event.key.code == sf::Keyboard::Num1) // Gravity Mode
    {
      game_mode = 1;
      alien_speed = 100;
      laser_speed = 500;
      in_menu = false;
    }
    if(event.key.code == sf::Keyboard::Num2) // Quadratic Mode
    {
      game_mode = 2;
      alien_speed = 200;
      laser_speed = 500;
      in_menu = false;
    }
    if(event.key.code == sf::Keyboard::Num3) // Curve Mode
    {
      alien_speed = 150;
      laser_speed = 500;
      game_mode = 3;
      in_menu = false;
    }
  }

  if(!in_menu and !game_over) // In Game
  {
    if(event.key.code == sf::Keyboard::Escape) // Return To Menu
    {
      in_menu = true;
    }
    if (event.key.code == sf::Keyboard::A) // Move Left
    {
      player->player_direction->x = -1;
    }
    // Move paddle right
    if (event.key.code == sf::Keyboard::D) // Move Right
    {
      player->player_direction->x = 1;
    }
    if (event.key.code == sf::Keyboard::Space) // Fire Laser
    {
      laser_fired = true;
      laserAction();
    }
  }

  if(game_over) // Game Over Screen
  {
    if(event.key.code == sf::Keyboard::Enter) // Return To Menu
    {
      game_over = false;
      player_wins = false;
      alien_wins = false;
      in_menu = true;
    }
  }
}

void Game::keyReleased(sf::Event event)
{
  player->player_direction->x = 0;
  player->player_direction->y = 0;
}


void Game::laserAction()
{
  laser->laser_position->x = player->getSprite()->getPosition().x + 22;
  laser->laser_position->y = player->getSprite()->getPosition().y -20;
  laser->getSprite()->setPosition(laser->laser_position->x,
                                  laser->laser_position->y);
  laser->setVisibility(true);
}

bool Game::collisionCheck(sf::Sprite& sprite1, sf::Sprite& sprite2)
{
  if(sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds()))
  {
    return true;
  }
  else
  {
    return false;
  }
}
