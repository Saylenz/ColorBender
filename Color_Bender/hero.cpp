#include "hero.h"

Hero::Hero(){};

    void Hero::set_vel_y(float vel_y_){
        vel_y = vel_y_;
    }
    void Hero::set_vel_x(float vel_x_){
        vel_x = vel_x_;
    }
    void Hero::set_ground(bool ground){
        ground_ = ground;
    }
    void Hero::set_stick(bool stick){
        stick_=stick;
    }
    void Hero::set_acc_y(float acc_y_){
        acc_y = acc_y_;
    }
    bool Hero::ground() {return ground_;}
    bool Hero::stick() {return stick_;}

    void Hero::step(float &delta_t){
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
    void Hero::setHeroColor(sf::Color &color){
        this->setColor(color);
        color_=color;
    }

