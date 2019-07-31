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

void SetMenu(sf::Event &event, Menu &menu, sf::RenderWindow &window, int &StartGame){
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
                     StartGame=1;
                     break;
                 }
                 case 1:{
                     sf::Texture texture;
                     sf::Sprite image;
                     texture.loadFromFile("sterowanie.png");
                     if (!texture.loadFromFile("sterowanie.png")) {
                         std::cerr << "Could not load texture" << std::endl;
                     }
                     image.setTextureRect(sf::IntRect(0,0,1200,800));
                     image.setTexture(texture);
                         window.draw(image);

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
             std::vector<Structure> &Spikes, std::vector<Structure> &Beacons, std::vector<Structure> &Platform, std::vector<Structure> &Finish, std::string file){
    std::string linia;

    std::string structure_type;
    int a,b,c,d,e,f,g;


    std::fstream plik(file, std::ios::in);
        if (!plik.is_open()) {
            std::cout << "Blad" << std::endl;
        }

        std::smatch matches;
        while (getline(plik, linia)) {


            std::regex wzorzec("([a-z]);([0-9]+);([0-9]+);([0-9]+);([0-9]+);([0-9]+);([0-9]+);([0-9]+)");

            if (regex_search(linia, matches, wzorzec)) {
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
                        Gates.emplace_back(Structure(sf::Vector2f(a,b), sf::Vector2f(c,d), sf::Color(e,f,g)));
                    }
                    else if(structure_type=="k"){
                        Spikes.emplace_back(Structure(sf::Vector2f(a,b), sf::Vector2f(c, d), sf::Color(255,255,255)));
                    }
                    else if(structure_type=="b"){
                        Beacons.emplace_back(Structure(sf::Vector2f(90,101), sf::Vector2f(c, d), sf::Color(255,255,255)));
                    }
                    else if(structure_type=="p"){
                        Platform.emplace_back(Structure(sf::Vector2f(a,b), sf::Vector2f(c, d), sf::Color(255,255,255)));
                    }
                    else if(structure_type=="f"){
                        Finish.emplace_back(Structure(sf::Vector2f(a,b), sf::Vector2f(c, d), sf::Color(255,255,255)));
                    }
                    linia = matches.suffix().str();
                }

            }
        }
        plik.close();
}

void Update(std::vector<Structure> &Walls,std::vector<Structure> &StickyWalls, std::vector<Structure> &Gates,
            std::vector<Structure> &Spikes, std::vector<Structure> &Beacons, std::vector<Structure> &Platforms,
            std::vector<Structure> &Finish, Hero &hero, sf::RenderWindow &window, sf::Clock &clock, int &Level){
    float delta_t = float(clock.getElapsedTime().asSeconds());
    clock.restart();

    for (int i=0;i<Walls.size();i++) {
        Walls[i].collision(hero);
    }
    for (int i=0;i<StickyWalls.size();i++) {
        StickyWalls[i].Stick(hero);
        StickyWalls[i].collision(hero);
    }
    for (int i=0;i<Gates.size();i++) {
        Gates[i].ColorGate(hero);
    }
    for (int i=0;i<Spikes.size();i++) {
        Spikes[i].Spike(hero, Beacons[0]);
    }
    for (int i=0;i<Beacons.size();i++) {
        Beacons[i].LoadColor(hero);
    }
    for (int i=0;i<Platforms.size();i++) {
        Platforms[i].ActivePlatform(Beacons[i]);
        if(Beacons[i].Beacon_active==1){
            Platforms[i].collision(hero);
        }
    }
    for (int i=0;i<Finish.size();i++) {
        Finish[i].Finish(hero, Level);
    }

    hero.step(delta_t);
    hero.Bounds(window_width, window_height);

    std::cout << "Skok: " << hero.ground() << std::endl;
    std::cout << "Startgame: " << Level << std::endl;
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
    for(int i=0;i<Beacons.size();i++){
        window.draw(Beacons[i]);
    }
    for(int i=0;i<Platforms.size();i++){
        window.draw(Platforms[i]);
    }
    for(int i=0;i<Finish.size();i++){
        window.draw(Finish[i]);
    }



    window.draw(hero);
}

int main() {


   sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Color Bender");
   Menu menu(window.getSize().x,window.getSize().y);

   //Ladowanie tekstur
   //Hero
   sf::Texture herotexture;
   herotexture.loadFromFile("hero.png");
   if (!herotexture.loadFromFile("hero.png")) {
       std::cerr << "Could not load texture" << std::endl;
       return 1;
   }
   sf::Vector2f beg_pos(600,50);
   Hero hero(beg_pos);
   sf::Color hColor = sf::Color::Yellow;
   hero.setHeroColor(hColor);
   hero.setPosition(beg_pos);
   hero.setTexture(herotexture);
   hero.setTextureRect(sf::IntRect(0,0,50,48));
   //Hero

   std::vector<Structure> Walls;
   std::vector<Structure> StickyWalls;
   std::vector<Structure> Gates;
   std::vector<Structure> Spikes;
   std::vector<Structure> Beacons;
   std::vector<Structure> Platforms;
   std::vector<Structure> Finish;

   std::vector<Structure> Walls2;
   std::vector<Structure> StickyWalls2;
   std::vector<Structure> Gates2;
   std::vector<Structure> Spikes2;
   std::vector<Structure> Beacons2;
   std::vector<Structure> Platforms2;
   std::vector<Structure> Finish2;


   LoadMap(Walls,StickyWalls,Gates, Spikes, Beacons, Platforms, Finish, "level1.txt");
   LoadMap(Walls2,StickyWalls2,Gates2, Spikes2, Beacons2, Platforms2, Finish2, "level2.txt");

   sf::Texture wall;
   std::string texture = "wall.png";
   LoadTexture(wall,texture,Walls);
   LoadTexture(wall,texture,Walls2);

   sf::Texture stickywall;
   std::string texture2 = "wall2.png";
   LoadTexture(stickywall,texture2,StickyWalls);
   LoadTexture(stickywall,texture2,StickyWalls2);

   sf::Texture gate;
   std::string texture3 = "gatetexture.png";
   LoadTexture(gate,texture3,Gates);
   LoadTexture(gate,texture3,Gates2);

   sf::Texture spike;
   std::string texture4 = "spike.png";
   LoadTexture(spike,texture4,Spikes);
   LoadTexture(spike,texture4,Spikes2);

   sf::Texture beacon;
   std::string texture5 = "beacon.png";
   LoadTexture(beacon,texture5,Beacons);
   LoadTexture(beacon,texture5,Beacons2);

   sf::Texture platform;
   std::string texture6 = "platform.png";
   LoadTexture(platform,texture6,Platforms);
   LoadTexture(platform,texture6,Platforms2);

   sf::Texture finish;
   std::string texture7 = "finish.png";
   LoadTexture(finish, texture7, Finish);
   LoadTexture(finish, texture7, Finish2);
   //Ladowanie tekstur

   sf::Clock clock;

   while (window.isOpen()) {
       window.setFramerateLimit(300);
       int Level;

       sf::Event event;
       while (window.pollEvent(event)) {

           SetMenu(event,menu,window,Level);

           if (event.type == sf::Event::Closed)
               window.close();
       }

       //Gameplay
       if(Level!=1 && Level!=2 && Level!=3){

            menu.draw(window);
       }
       else if(Level==1){
            Update(Walls,StickyWalls,Gates, Spikes, Beacons, Platforms, Finish,hero,window,clock, Level);
       }
       else if(Level==2){
           Update(Walls2,StickyWalls2,Gates2, Spikes2, Beacons2, Platforms2, Finish2,hero,window,clock,Level);
       }
       else if(Level==3){
           sf::Texture texture;
           sf::Sprite image;
           image.setPosition(0,0);

           texture.loadFromFile("victory.png");
           if (!texture.loadFromFile("victory.png")) {
               std::cerr << "Could not load texture" << std::endl;
           }
           image.setTextureRect(sf::IntRect(0,0,1200,800));
           image.setTexture(texture);
           window.clear(sf::Color::Black);
           window.draw(image);
           if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
               window.close();
           }
       }
       //Gameplay
       window.display();

   }

   return 0;
}





