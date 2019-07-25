#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Hero : public sf::Sprite
{
public:
    Hero();
    void set_vel_y(float vel_y_);
    void set_vel_x(float vel_x_);
    void set_acc_y(float acc_y_);

    void set_ground(bool ground);
    void set_stick(bool stick);

    bool ground();
    bool stick();

    sf::Color color_;
    void step(float &delta_t);
    void setHeroColor(sf::Color &color);

private:
   bool ground_;
   bool stick_;
   float vel_x = 0.0;
   float vel_y = 0.0;

   float acc_x = 0.0;
   float acc_y = 800.0;
};
