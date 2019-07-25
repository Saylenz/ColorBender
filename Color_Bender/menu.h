#pragma once

#include "SFML/Graphics.hpp"

#define NUMBER_OF_ITEMS 4

class Menu
{
public:
    Menu(float width, float height);
    //~Menu();

    void draw(sf::RenderWindow &window);
    void Up();
    void Down();
    int GetPressedItemIndex(){return item_index;}

private:
    int item_index;
    sf::Font font;
    sf::Text menu[NUMBER_OF_ITEMS];


};
