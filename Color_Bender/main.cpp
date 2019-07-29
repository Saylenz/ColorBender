#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <regex>
#include <string>

#include "menu.h"
#include "hero.h"
#include "structure.h"

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

void LoadTexture(sf::Texture &texture ,std::string &image, std::vector<Structure> &structure){
    for (int i=0;i<structure.size();i++) { 
        texture.loadFromFile(image);
        if (!texture.loadFromFile(image)) {
            std::cerr << "Could not load texture" << std::endl;
        }
        texture.setRepeated(true);
        structure[i].setTexture(texture);
    }
}

void LoadMap(std::vector<Structure> &Walls,std::vector<Structure> &StickyWalls, std::vector<Structure> &Gates,
             std::vector<Structure> &Spikes, std::vector<Structure> &Beacons){
    std::string linia;

    std::string structure_type;
    int a,b,c,d,e,f,g;


    std::fstream plik("level1.txt", std::ios::in);
        if (!plik.is_open()) {
            std::cout << "Blad" << std::endl;
        }

        std::smatch matches;
        while (getline(plik, linia)) {


            std::regex wzorzec("([a-z]);([0-9]+);([0-9]+);([0-9]+);([0-9]+);([0-9]+);([0-9]+);([0-9]+)");

            if (regex_search(linia, matches, wzorzec)) {
                std::cout << "Znaleziono: " << matches.size() << " dopasowania" << std::endl;
                for (int i = 0; i < (int)matches.size(); i++) {
                    std::string linia1;
                    structure_type = matches[1];
                    linia1 = matches[2];
                    a = atoi(linia1.c_str());
                    linia1 = matches[3];
                    b = atoi(linia1.c_str());
                    linia1 = matches[4];
                    c = atoi(linia1.c_str());
                    linia1 = matches[5];
                    d = atoi(linia1.c_str());
                    linia1 = matches[6];
                    e = atoi(linia1.c_str());
                    linia1 = matches[7];
                    f = atoi(linia1.c_str());
                    linia1 = matches[8];
                    g = atoi(linia1.c_str());

                    if(structure_type=="w"){
                        Walls.emplace_back(Structure(sf::Vector2f(a,b), sf::Vector2f(c,d), sf::Color(e,f,g)));
                    }
                    else if(structure_type=="s"){
                        StickyWalls.emplace_back(Structure(sf::Vector2f(a,b), sf::Vector2f(c,d), sf::Color(e,f,g)));
                    }
                    else if(structure_type=="g"){
                        Gates.emplace_back(Structure(sf::Vector2f(38,b), sf::Vector2f(c,d), sf::Color(e,f,g)));
                    }
                    else if(structure_type=="k"){
                        Spikes.emplace_back(Structure(sf::Vector2f(a,b), sf::Vector2f(c, d), sf::Color(255,255,255)));
                    }
                    else if(structure_type=="b"){
                        Beacons.emplace_back(Structure(sf::Vector2f(90,101), sf::Vector2f(c, d), sf::Color(255,255,255)));
                    }
                    linia = matches.suffix().str();
                }

            }
        }
        plik.close();
}

int main() {
    unsigned int window_width = 1200, window_height = 800;
   // create the window
   sf::RenderWindow window(sf::VideoMode(window_width, window_height), "My window");
   Menu menu(window.getSize().x,window.getSize().y);
   //Ladowanie tekstur

   //Hero
   sf::Texture herotexture;
   herotexture.loadFromFile("hero.png");
   if (!herotexture.loadFromFile("hero.png")) {
       std::cerr << "Could not load texture" << std::endl;
       return 1;
   }
   sf::Vector2f beg_pos(50,400);
   Hero hero(beg_pos);
   hero.set_stick(0);
   sf::Color hColor = sf::Color::Yellow;
   hero.setHeroColor(hColor);
   hero.setPosition(beg_pos);
   hero.setTexture(herotexture);
   hero.setTextureRect(sf::IntRect(0,0,56,54));
   //Hero

   std::vector<Structure> Walls;
   std::vector<Structure> StickyWalls;
   std::vector<Structure> Gates;
   std::vector<Structure> Spikes;
   std::vector<Structure> Beacons;

   LoadMap(Walls,StickyWalls,Gates, Spikes, Beacons);


   sf::Texture wall;
   std::string texture = "wall.png";
   LoadTexture(wall,texture,Walls);

   sf::Texture stickywall;
   std::string texture2 = "wall2.png";
   LoadTexture(stickywall,texture2,StickyWalls);

   sf::Texture gate;
   std::string texture3 = "gatetexture.png";
   LoadTexture(gate,texture3,Gates);

   sf::Texture spike;
   std::string texture4 = "spike.png";
   LoadTexture(spike,texture4,Spikes);

   sf::Texture beacon;
   std::string texture5 = "beacon.png";
   LoadTexture(beacon,texture5,Beacons);
   //Ladowanie tekstur

   sf::Clock clock;

   while (window.isOpen()) {
       window.setFramerateLimit(200);
       bool StartGame=1;

       sf::Event event;
       while (window.pollEvent(event)) {

       //Menu
           if(StartGame!=1){
                SetMenu(event,menu,window,StartGame);
           }
       //Menu

           if (event.type == sf::Event::Closed)
               window.close();
       }

       //Gameplay
       if(StartGame!=1){
            menu.draw(window);
            std::cout << "StartGame: " << StartGame << std::endl;
       }
       else{
           float delta_t = float(clock.getElapsedTime().asSeconds());
           clock.restart();

       for (int i=0;i<StickyWalls.size();i++) {
           StickyWalls[i].Stick(hero);
           StickyWalls[i].collision(hero);
           std::cout << i << "structure: " << hero.stick() << std::endl;
       }
       for (int i=0;i<Walls.size();i++) {
           Walls[i].collision(hero);
       }

       for (int i=0;i<Gates.size();i++) {
           Gates[i].ColorGate(hero);
       }
       for (int i=0;i<Spikes.size();i++) {
           Spikes[i].Spike(hero);
       }
       for (int i=0;i<Spikes.size();i++) {
           Spikes[i].Spike(hero);
       }
       for (int i=0;i<Beacons.size();i++) {
           Beacons[i].LoadColor(hero);
       }

       hero.step(delta_t);
       hero.Bounds(window_width, window_height);

       std::cout << "Skok: " << hero.ground() << std::endl;
       std::cout << "Stick: " << hero.stick() << std::endl;
       std::cout << "Walls vector size: " << Walls.size() << std::endl;
       //std::cout << "Znaleziono: " << matches.size() << " dopasowania" << std::endl;
       std::system("cls");

       window.clear(sf::Color(95,95,95));

       for(int i=0;i<Walls.size();i++){
           window.draw(Walls[i]);
       }
       for(int i=0;i<StickyWalls.size();i++){
           window.draw(StickyWalls[i]);
       }
       for(int i=0;i<Gates.size();i++){
           window.draw(Gates[i]);
       }
       for(int i=0;i<Spikes.size();i++){
           window.draw(Spikes[i]);
       }


       window.draw(hero);
       }
       //Gameplay
       window.display();

   }

   return 0;
}





