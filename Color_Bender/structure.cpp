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

    if(hero.getGlobalBounds().intersects(this->getGlobalBounds())){
switch(position){
case 1:{
        hero.setPosition(hLeftside,sTopside - hero.getGlobalBounds().height);
        hero.set_vel_y(0.0);
        hero.set_vel_x(0.0);
        hero.set_ground(true);
        hero.set_acc_y(0.0);
    break;
}
case 2:{
        hero.setPosition(sRightside,hTopside);
    break;
}
case 3:{
        hero.setPosition(hLeftside,sDownside);
    break;
}
case 4:{
        hero.setPosition(sLeftside - hero.getGlobalBounds().width,hTopside);
    }
}
}
}

void Structure::Stick(Hero &hero){
    if(hero.color_==s_color_){
        float hLeftside = hero.getPosition().x;
        float hRightside = hero.getPosition().x + hero.getGlobalBounds().width;
        float hTopside = hero.getPosition().y;
        float hDownside = hero.getPosition().y + hero.getGlobalBounds().height;

        float sLeftside = this->getPosition().x;
        float sRightside = this->getPosition().x + this->getGlobalBounds().width;
        float sTopside = this->getPosition().y;
        float sDownside = this->getPosition().y + this->getGlobalBounds().height;

        bool Contains_Horizontal=1;
        bool Sticks_Left=0;
        bool Sticks_Right=0;
        if(hDownside < sTopside || hTopside > sDownside){
            Contains_Horizontal=0;
        }
        else if(sLeftside -2 <= hRightside && sLeftside + 5 >= hRightside){
            Sticks_Right=1;
            hero.LockRight=1;
        }
        else if(sRightside -5 <= hLeftside && sRightside +2 >= hLeftside){
            Sticks_Left=1;
            hero.LockLeft=1;
        }
        else {
            hero.LockRight=0;
            hero.LockLeft=0;
        }

        if(Contains_Horizontal==1 && (Sticks_Left==1 || Sticks_Right==1)){
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

void Structure::Spike(Hero &hero){
    if(hero.getGlobalBounds().intersects(this->getGlobalBounds())){
        hero.setPosition(hero.beg_pos_);
    }
}

void Structure::LoadColor(Hero &hero){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E) && hero.getGlobalBounds().intersects(this->getGlobalBounds())){
        this->setColor(hero.color_);
        hero.setColor(sf::Color(255,255,255));
}
}

