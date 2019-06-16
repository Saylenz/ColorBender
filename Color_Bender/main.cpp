#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <cstdlib>

class AnimatedSprite : public sf::Sprite{
    public:
       AnimatedSprite() : sf::Sprite() {}
       void set_vel_y(float vel_y_){
           vel_y = vel_y_;
       }
       void set_vel_x(float vel_x_){
           vel_x = vel_x_;
       }
       void set_ground(bool ground){
           ground_ = ground;
       }
       void set_stick(bool stick){
           stick_=stick;
       }
       void set_acc_y(float acc_y_){
           acc_y = acc_y_;
       }
       bool ground() {return ground_;}
       bool stick() {return stick_;}

       void step(float &delta_t){
           vel_x += acc_x*delta_t;
           vel_y += acc_y*delta_t;
           if(vel_y>500){
               vel_y = vel_y - (vel_y-450);
           }
           if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && sf::Keyboard::isKeyPressed(sf::Keyboard::A) && (ground_==1)){
               vel_x=-100.0;
               vel_y = -300.0;
               this->move(vel_x*delta_t, vel_y*delta_t);
               set_ground(false);
           }
           else if((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) && (ground_==1)){
               vel_x=100.0;
               vel_y = -300.0;
               this->move(vel_x*delta_t, vel_y*delta_t);
               set_ground(false);
           }
           else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                   vel_x=-100.0;
                   this->move(vel_x*delta_t, 0);
           }
           else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                   vel_x=100.0;
                   this->move(vel_x*delta_t, 0);
           }
           else if((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && (ground_==1)){
               vel_y = -300.0;
               set_ground(false);
           }
           else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (stick_==1)){
                   vel_y=-100.0;
                   this->move(0,vel_y*delta_t);
           }
           else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (stick_==1)){
                   vel_y=100.0;
                   this->move(0,vel_y*delta_t);
           }


           this->move(vel_x*delta_t, vel_y*delta_t);
       }
       sf::Color color_;
       void setHeroColor(sf::Color color){
           this->setColor(color);
           color_=color;
       }


    private:
       bool ground_;
       bool stick_;
       float vel_x = 0.0;
       float vel_y = 0.0;

       float acc_x = 0.0;
       float acc_y = 800.0;

    };


class Structure : public sf::Sprite{
public:
    Structure(sf::Vector2f size, sf::Vector2f pos, sf::Color color){
        setTextureRect(sf::IntRect(0.0,0.0,size.x,size.y));
        setPosition(pos);
        setColor(color);
        s_color_=color;
    }

    void collision(AnimatedSprite &hero){
        float hLeftside = hero.getPosition().x;
        float hRightside = hero.getPosition().x + hero.getGlobalBounds().width;
        float hTopside = hero.getPosition().y;
        float hDownside = hero.getPosition().y + hero.getGlobalBounds().height;

        float sLeftside = this->getPosition().x;
        float sRightside = this->getPosition().x + this->getGlobalBounds().width;
        float sTopside = this->getPosition().y;
        float sDownside = this->getPosition().y + this->getGlobalBounds().height;

    int position;
        if(hDownside < sTopside+10)    {position=1;}
        if(hLeftside > sRightside-5)  {position=2;}
        if(hTopside > sDownside-10)    {position=3;}
        if(hRightside < sLeftside+5)  {position=4;}
    switch(position){
    case 1:{
        if(hero.getGlobalBounds().intersects(this->getGlobalBounds())){
            hero.setPosition(hLeftside,sTopside - hero.getGlobalBounds().height);
            hero.set_vel_y(0);
            hero.set_vel_x(0);
            hero.set_ground(true);
        }
        break;
    }
    case 2:{
        if(hero.getGlobalBounds().intersects(this->getGlobalBounds())){
            hero.setPosition(sRightside,hTopside);
        }
        break;
    }
    case 3:{
        if(hero.getGlobalBounds().intersects(this->getGlobalBounds())){
            hero.setPosition(hLeftside,sDownside);
        }
        break;
    }
    case 4:{
        if(hero.getGlobalBounds().intersects(this->getGlobalBounds())){
            hero.setPosition(sLeftside - hero.getGlobalBounds().width,hTopside);
        }
        break;
    }
    }
    }

    void Stick(AnimatedSprite &hero){
        if(hero.color_==s_color_){
            float hLeftside = hero.getPosition().x;
            float hRightside = hero.getPosition().x + hero.getGlobalBounds().width;
            float sLeftside = this->getPosition().x;
            float sRightside = this->getPosition().x + this->getGlobalBounds().width;

            if(sLeftside == hRightside || sRightside == hLeftside){
                hero.set_vel_y(0.0);
                hero.set_vel_x(0.0);
                hero.set_acc_y(0.0);
                hero.set_ground(true);
                hero.set_stick(true);
            }
            else{
                hero.set_stick(false);
                hero.set_acc_y(800.0);
            }
        }
    }

    void ColorGate(AnimatedSprite &hero){
        if(hero.getGlobalBounds().intersects(this->getGlobalBounds())){
            hero.setHeroColor(s_color_);
        }
    }

    sf::Vector2f size;
    sf::Vector2f pos;
private:
    sf::Color s_color_;

};


void Bounds(AnimatedSprite &hero){
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

int main() {
   // create the window
   sf::RenderWindow window(sf::VideoMode(1024, 768), "My window");
   window.setFramerateLimit(300);
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
   AnimatedSprite hero;
   sf::Color hColor = sf::Color::White;
   hero.setHeroColor(hColor);
   hero.setPosition(0,650);
   hero.setTexture(guy);
   hero.setTextureRect(sf::IntRect(0,0,40,70));

   std::vector<Structure> Walls;
   std::vector<Structure> StickyWalls;
   std::vector<Structure> Gates;
   //Walls

   /*Walls[0]=(Structure(sf::Vector2f(300,25), sf::Vector2f(0,400), sf::Color::White));
   Walls[1]=(Structure(sf::Vector2f(300,25), sf::Vector2f(0,200), sf::Color::White));
   Walls.resize(2);*/


   /*for (int i=0;i<Walls.size();i++) {
       sf::Texture wall;
       wall.loadFromFile("wall.png");
       if (!wall.loadFromFile("wall.png")) {
           std::cerr << "Could not load texture" << std::endl;
           return 1;
       }

       wall.setRepeated(true);
       Walls[i].setTexture(wall);
       Figures.emplace_back(Walls[i]);
   }

       //StickyWalls
   StickyWalls[0]=(Structure(sf::Vector2f(25,150), sf::Vector2f(400,200),sf::Color::Blue));
   for (int i=0;i<StickyWalls.size();i++) {
       sf::Texture wall;
       wall.loadFromFile("wall.png");
       if (!wall.loadFromFile("wall.png")) {
           std::cerr << "Could not load texture" << std::endl;
           return 1;
       }

       wall.setRepeated(true);
       StickyWalls[i].setTexture(wall);
       Figures.emplace_back(StickyWalls[i]);
   }


   //Gates
   Gates[0]=(Structure(sf::Vector2f(25,150), sf::Vector2f(400,200),sf::Color::Blue));
   for (int i=0;i<Walls.size();i++) {
       sf::Texture wall;
       wall.loadFromFile("wall.png");
       if (!wall.loadFromFile("wall.png")) {
           std::cerr << "Could not load texture" << std::endl;
           return 1;
       }

       wall.setRepeated(true);
       Gates[i].setTexture(wall);
       Figures.emplace_back(Gates[i]);
   }
*/

   //Wall

   Walls.emplace_back(Structure(sf::Vector2f(500,25), sf::Vector2f(0,750), sf::Color::White)); //1
   Walls.emplace_back(Structure(sf::Vector2f(400,25), sf::Vector2f(0,600), sf::Color::White)); //2
   Walls.emplace_back(Structure(sf::Vector2f(25,500), sf::Vector2f(500,425), sf::Color::White)); //3
   Walls.emplace_back(Structure(sf::Vector2f(250,25), sf::Vector2f(250,450), sf::Color::White)); //4
   Walls.emplace_back(Structure(sf::Vector2f(100,25), sf::Vector2f(0,450), sf::Color::White)); //5
   Walls.emplace_back(Structure(sf::Vector2f(50,25), sf::Vector2f(120,400), sf::Color::White)); //6
   Walls.emplace_back(Structure(sf::Vector2f(400,25), sf::Vector2f(0,75), sf::Color::White)); //7

   StickyWalls.emplace_back(Structure(sf::Vector2f(25,200), sf::Vector2f(500,500), sf::Color::Red)); //1
   StickyWalls.emplace_back(Structure(sf::Vector2f(25,25), sf::Vector2f(120,500), sf::Color::Red)); //2
   StickyWalls.emplace_back(Structure(sf::Vector2f(25,100), sf::Vector2f(250,250), sf::Color::Red)); //3
   StickyWalls.emplace_back(Structure(sf::Vector2f(25,250), sf::Vector2f(375,100), sf::Color::Red)); //4
   StickyWalls.emplace_back(Structure(sf::Vector2f(25,300), sf::Vector2f(500,150), sf::Color::Red)); //5

   Gates.emplace_back(Structure(sf::Vector2f(10,125), sf::Vector2f(300,625), sf::Color::Red)); //7
   Gates.emplace_back(Structure(sf::Vector2f(100,10), sf::Vector2f(275,300), sf::Color::Red)); //7

   for (int i=0;i<Walls.size();i++) {
       sf::Texture wall;
       wall.loadFromFile("wall.png");
       if (!wall.loadFromFile("wall.png")) {
           std::cerr << "Could not load texture" << std::endl;
           return 1;
       }
       wall.setRepeated(true);
       Walls[i].setTexture(wall);
   }

   for (int i=0;i<StickyWalls.size();i++) {
       sf::Texture wall;
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

   sf::Clock clock;

   while (window.isOpen()) {
       window.setFramerateLimit(120);
       float delta_t = float(clock.getElapsedTime().asSeconds());
       //cout << time1.asSeconds() << endl;
       clock.restart();

       sf::Event event;
       while (window.pollEvent(event)) {
           if (event.type == sf::Event::Closed)
               window.close();
       }

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
      // std::cout <<
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
       window.display();
   }

   return 0;
}




