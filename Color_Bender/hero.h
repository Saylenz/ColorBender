#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#define gravity 800
#define window_width 1200
#define window_height 800

class Hero : public sf::Sprite
{
public:
    Hero(sf::Vector2f &beg_pos);
    void set_vel_y(float vel_y_);
    void set_vel_x(float vel_x_);
    void set_acc_y(float acc_y_);

    void set_ground(bool ground);
    void set_stick(bool stick);

    bool ground();
    bool stick();

    bool LockLeft=0;
    bool LockRight=0;

    sf::Color color_;
    sf::Vector2f beg_pos_;
    std::vector<bool> v_stick;

    void step(float &delta_t);
    void setHeroColor(sf::Color &color);
    void Bounds(unsigned int w_width, unsigned int w_height);

private:
   bool ground_;
   bool stick_=1;


   float vel_x = 0.0;
   float vel_y = 0.0;

   float acc_x = 0.0;
   float acc_y = gravity;

};
