#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <cstdlib>

#include "menu.h"
#include "hero.h"
#include "structure.h"

void Bounds(Hero &hero){
    if(hero.getPosition().x<0){
        hero.setPosition(0,hero.getPosition().y);
    }
    if(hero.getPosition().x + hero.getGlobalBounds().width>1024){
        hero.setPosition(1024-hero.getGlobalBounds().width, hero.getPosition().y);
    }
    if(hero.getPosition().y<0){
        hero.setPosition(hero.getPosition().x, 0);
    }
    if(hero.getPosition().y + hero.getGlobalBounds().height>768){
       hero.setPosition(hero.getPosition().x, 768-hero.getGlobalBounds().height);
    }
}

void SetMenu(sf::Event &event, Menu &menu, sf::Window &window, bool &StartGame){
    switch (event.type) {
    case sf::Event::KeyReleased:{
        switch (event.key.code) {
             case sf::Keyboard::Up:{
                    menu.Up();
                    break;
             }
             case sf::Keyboard::Down:{
                    menu.Down();
                    break;
             }
             case sf::Keyboard::Return:{
                 switch (menu.GetPressedItemIndex()) {
                 case 0:{
                     std::cout << "Kliknales Graj" <<  std::endl;
                     StartGame=1;
                     break;
                 }
                 case 1:{
                     break;
                 }
                 case 2:{
                     window.close();
                     break;
                 }
                 }
             }


    }
        break;
    }
}
}

int main() {
   // create the window
   sf::RenderWindow window(sf::VideoMode(1200, 800), "My window");

   Menu menu(window.getSize().x,window.getSize().y);
   //Ladowanie tekstur
   std::vector<sf::Sprite> Figures;

   //Background
   /*sf::Texture grass;
   grass.loadFromFile("grass.png");
   if (!grass.loadFromFile("grass.png")) {
       std::cerr << "Could not load texture" << std::endl;
       return 1;
   }
   sf::Sprite sprite;
   sprite.setTexture(grass);
   grass.setRepeated(true);
   sprite.setTextureRect(sf::IntRect(0,0,1024, 768));
   Figures.emplace_back(sprite);*/

   //Hero
   sf::Texture guy;
   guy.loadFromFile("guy.png");
   if (!guy.loadFromFile("guy.png")) {
       std::cerr << "Could not load texture" << std::endl;
       return 1;
   }
   Hero hero;
   sf::Color hColor = sf::Color::White;
   hero.setHeroColor(hColor);
   hero.setPosition(50,400);
   hero.setTexture(guy);
   hero.setTextureRect(sf::IntRect(0,0,40,70));

   std::vector<Structure> Walls;
   std::vector<Structure> StickyWalls;
   std::vector<Structure> Gates;

   //Walls {size, position, color}

   Walls.emplace_back(Structure(sf::Vector2f(1200,25), sf::Vector2f(0, 775), sf::Color::White)); //1
   Walls.emplace_back(Structure(sf::Vector2f(25,200), sf::Vector2f(300,575), sf::Color::Yellow)); //2
   Walls.emplace_back(Structure(sf::Vector2f(25,500), sf::Vector2f(500,425), sf::Color::White)); //3

   //Sticky Walls
   StickyWalls.emplace_back(Structure(sf::Vector2f(25,200), sf::Vector2f(500,500), sf::Color::Red)); //1
   StickyWalls.emplace_back(Structure(sf::Vector2f(25,25), sf::Vector2f(120,500), sf::Color::Red)); //2

   //Gates
   Gates.emplace_back(Structure(sf::Vector2f(10,125), sf::Vector2f(300,625), sf::Color::Red)); //7
   Gates.emplace_back(Structure(sf::Vector2f(100,10), sf::Vector2f(275,300), sf::Color::Red)); //7

   sf::Texture wall;
   for (int i=0;i<Walls.size();i++) {

       wall.loadFromFile("wall.png");
       if (!wall.loadFromFile("wall.png")) {
           std::cerr << "Could not load texture" << std::endl;
           return 1;
       }
       wall.setRepeated(true);
       Walls[i].setTexture(wall);
   }
   for (int i=0;i<StickyWalls.size();i++) {

       wall.loadFromFile("wall.png");
       if (!wall.loadFromFile("wall.png")) {
           std::cerr << "Could not load texture" << std::endl;
           return 1;
       }
       wall.setRepeated(true);
       StickyWalls[i].setTexture(wall);
   }
   for (int i=0;i<Gates.size();i++) {
       sf::Texture wall;
       wall.loadFromFile("wall.png");
       if (!wall.loadFromFile("wall.png")) {
           std::cerr << "Could not load texture" << std::endl;
           return 1;
       }
       wall.setRepeated(true);
       Gates[i].setTexture(wall);
   }
   //Ladowanie tekstur

   sf::Clock clock;

   while (window.isOpen()) {
       window.setFramerateLimit(120);

       bool StartGame;

       sf::Event event;
       while (window.pollEvent(event)) {

       //Menu
       SetMenu(event,menu,window,StartGame);
       //Menu
           if (event.type == sf::Event::Closed)
               window.close();
       }
       //Gameplay
       if(StartGame==0){
            menu.draw(window);
            std::cout << "StartGame: " << StartGame << std::endl;
       }
       else{
           float delta_t = float(clock.getElapsedTime().asSeconds());
           //cout << time1.asSeconds() << endl;
           clock.restart();

       for (int i=0;i<Walls.size();i++) {
           Walls[i].collision(hero);
       }
       for (int i=0;i<StickyWalls.size();i++) {
           StickyWalls[i].collision(hero);
           StickyWalls[i].Stick(hero);
       }
       for (int i=0;i<Gates.size();i++) {
             Gates[i].ColorGate(hero);
       }

       hero.step(delta_t);
       Bounds(hero);

       std::cout << "Skok: " << hero.ground() << std::endl;

       std::system("cls");

       window.clear(sf::Color::Black);

       for(int i=0;i<Walls.size();i++){
           window.draw(Walls[i]);
       }
       for(int i=0;i<StickyWalls.size();i++){
           window.draw(StickyWalls[i]);
       }
       for(int i=0;i<Gates.size();i++){
           window.draw(Gates[i]);
       }

       window.draw(hero);
       }
       //Gameplay
       window.display();

   }

   return 0;
}





