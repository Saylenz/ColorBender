#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "hero.h"

class Structure : public sf::Sprite
{
public:
    Structure(sf::Vector2f size, sf::Vector2f pos, sf::Color color);
    void collision(Hero &hero);
    void Stick(Hero &hero);
    void ColorGate(Hero &hero);
    sf::Vector2f size;
    sf::Vector2f pos;
private:
    sf::Color s_color_;
};
