#include "menu.h"
#include <iostream>

Menu::Menu(float width, float height)
{
    if(!font.loadFromFile("arial.ttf")){
        std::cout << "Font loading error" << std::endl;
    }

    menu[3].setFont(font);
    menu[3].setCharacterSize(100);
    menu[3].setStyle(sf::Text::Bold);
    menu[3].setFillColor(sf::Color::Blue);
    menu[3].setString("Color Bender");
    menu[3].setPosition(sf::Vector2f(width/2-300, (height/(NUMBER_OF_ITEMS +1) *1)-30));

    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Red);
    menu[0].setStyle(sf::Text::Bold);
    menu[0].setString("Graj");
    menu[0].setPosition(sf::Vector2f(width/2-50, height/(NUMBER_OF_ITEMS +1) *2));

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);
    menu[1].setStyle(sf::Text::Bold);
    menu[1].setString("Sterowanie");
    menu[1].setPosition(sf::Vector2f(width/2-100, height/(NUMBER_OF_ITEMS +1) *3));

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setStyle(sf::Text::Bold);
    menu[2].setString("Wyjscie");
    menu[2].setPosition(sf::Vector2f(width/2-75, height/(NUMBER_OF_ITEMS +1) *4));

    item_index = 0;
}

void Menu::draw(sf::RenderWindow &window){
    for(int i=0;i<NUMBER_OF_ITEMS;i++){
        window.draw(menu[i]);
    }
}

void Menu::Up(){
    menu[item_index].setFillColor(sf::Color::White);
    item_index = ((item_index-1)+3)%3;
    menu[item_index].setFillColor(sf::Color::Red);
}

void Menu::Down(){
    menu[item_index].setFillColor(sf::Color::White);
    item_index = ((item_index+1)+3)%3;
    menu[item_index].setFillColor(sf::Color::Red);
}


