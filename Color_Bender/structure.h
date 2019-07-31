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
    void Spike(Hero &hero, Structure &beacon);
    void LoadColor(Hero &hero);
    void ActivePlatform(Structure &beacon);
    void Finish(Hero &hero, int &Level);
    sf::Vector2f size;
    sf::Vector2f pos;
    bool Beacon_active;
    sf::Color BeaconColor;
private:
    sf::Color s_color_;
};
