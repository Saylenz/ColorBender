#include "structure.h"

Structure::Structure(sf::Vector2f size, sf::Vector2f pos, sf::Color color){
    setTextureRect(sf::IntRect(0.0,0.0,size.x,size.y));
    setPosition(pos);
    setColor(color);
    s_color_=color;
}

void Structure::collision(Hero &hero){
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
        hero.set_vel_y(0.0);
        hero.set_vel_x(0.0);
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

void Structure::Stick(Hero &hero){
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

void Structure::ColorGate(Hero &hero){
    if(hero.getGlobalBounds().intersects(this->getGlobalBounds())){
        hero.setHeroColor(s_color_);
    }
}
