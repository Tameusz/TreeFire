//
// Created by szust on 23.02.2022.
//

#ifndef TREEFIRE_SFMLHANDLING_H
#define TREEFIRE_SFMLHANDLING_H

#include <SFML/Graphics.hpp>
#include "Arena.h"
#define SIZE 10
#define MAX_ROW 3
class SFMLHandling
{
public:
    SFMLHandling();
    ~SFMLHandling();

    sf::RenderWindow *window;
    sf::Clock cllogs;

    sf::Event event{};
    sf::Clock cl;
    sf::Time tm;
    bool isPause=false;
    bool isPressed[3]= {false,false,false}; ///0-palenie ,1-kamienie,2-niepalace
    bool isSelected[4]= {false,false,false,false}; ///sprawdzamy wykonanie menu 0-styl,1 rozmiar 2-kamienie
    int iterator_=1;
    float time_as_miliseconds=1000;


    int wind_to_string=0;
    int wind=0;
    int pressedTimes=0;
    int simulationType=1;
    int sliderX=0;
    bool mouseClicked=false;

    void updateS();
    sf::Text createMenuField(sf::Text menuTextField, std::string string, sf::Color color, sf::Vector2<float> vector2) const;
    void handleEvents_();
    void run();
    void logs() const;
    void createText(sf::Text text, std::string string, sf::Color color, float x, float y) const;
    void placeTexture(std::string resourceDirectory, int i, int j) const;
    void toolkit() const;
    void toolkitFrame(int x,int y) const;
    void print_speed(double s,unsigned x) const;///wypisanie predkosci
    void frame(float rectangle_x,float rectangle_y,int startingposition_x,int startingposition_y,sf::Color Color) const;///ramki
    void printArena() const;
    void nextState() const;
    static void setFire();
    void setStone() const;
    void screenshot();
    void handleTime(int time_as_miliseconds,bool isPause);
    ///menu symulacji
    void drawMenuFields(sf::Text *matrix, int maxRows);
    static void moveOnMenuFieldsUp(sf::Text *matrix, int selectedItem);
    static void moveOnMenuFieldsDown(sf::Text *matrix, int selectedItem, int bounds);
    sf::Font fontMenu;
    sf::Text menuST[MAX_ROW];
    sf::Text menuSTO[MAX_ROW];
    sf::Text menuSI[MAX_ROW];
    sf::Text menuWDCH[5];
    sf::Text menuWIND;
    sf::Text menuSIZE;
    sf::Text menuSIMTYPE;
    sf::Text menuSTONES;
    static void createArena();
    void simulationRun();
    void reset();
};

#endif //TREEFIRE_SFMLHANDLING_H
