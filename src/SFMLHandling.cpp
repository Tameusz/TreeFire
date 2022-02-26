//
// Created by szust on 23.02.2022.
//

#include "../headers/SFMLHandling.h"
#include <fstream>
#include <iostream>

unsigned sizeS=20;
Arena arena(sizeS);
int selectedItemIndexST=0;
int selectedItemIndexSTO=0;
int selectedItemIndexSI=0;
int selectedItemIndexWDCH=0;
void SFMLHandling::createArena()
{
    arena.create(sizeS);
}
SFMLHandling::SFMLHandling()
{
    window= new sf::RenderWindow(sf::VideoMode(1400,900), "Symulator pozaru lasu");


    if (!fontMenu.loadFromFile("../fonts/times-new-roman.ttf")) {}

    menuST[0] = createMenuField(menuST[0], "Sasiedztwo Moore'a", sf::Color::Red, sf::Vector2f(300,30));
    menuST[1] = createMenuField(menuST[1], "Sasiedztwo von Neumanna", sf::Color::Black, sf::Vector2f(300,70));
    menuST[2] = createMenuField(menuST[2], "Losowe spalanie", sf::Color::Black, sf::Vector2f(300,110));

    menuSTO[0] = createMenuField(menuSTO[0], "25", sf::Color::Red, sf::Vector2f(300,30));
    menuSTO[1] = createMenuField(menuSTO[1], "50", sf::Color::Black, sf::Vector2f(300,70));
    menuSTO[2] = createMenuField(menuSTO[2], "75", sf::Color::Black, sf::Vector2f(300,110));

    menuSI[0] = createMenuField(menuSI[0],"10x10",sf::Color::Red,sf::Vector2f(300,30));
    menuSI[1] = createMenuField(menuSI[1],"15x15",sf::Color::Black,sf::Vector2f(300,70));
    menuSI[2] = createMenuField(menuSI[2],"20x20",sf::Color::Black,sf::Vector2f(300,110));

    menuWDCH[0] = createMenuField(menuWDCH[0], "Bez wiatru", sf::Color::Red, sf::Vector2f(300,70));
    menuWDCH[1] = createMenuField(menuWDCH[1], "Wiatr z N", sf::Color::Black, sf::Vector2f(300,110));
    menuWDCH[2] = createMenuField(menuWDCH[2], "Wiatr z E", sf::Color::Black, sf::Vector2f(300,150));
    menuWDCH[3] = createMenuField(menuWDCH[3], "Wiatr z S", sf::Color::Black, sf::Vector2f(300,190));
    menuWDCH[4] = createMenuField(menuWDCH[4], "Wiatr z W", sf::Color::Black, sf::Vector2f(300,230));
}
SFMLHandling::~SFMLHandling()
= default;
sf::Text SFMLHandling::createMenuField(sf::Text menuTextField, std::string string, sf::Color color, sf::Vector2<float> vector2) const
{
    menuTextField.setFont(fontMenu);
    menuTextField.setString(string);
    menuTextField.setFillColor(color);
    menuTextField.setPosition(vector2);
    return menuTextField;
}
void SFMLHandling::handleEvents_()
{
    while(window->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            window->close();
        if((event.type == sf::Event::KeyReleased)&&(event.key.code == sf::Keyboard::Escape))
            window->close();
        if((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::F) && isSelected[0] &&
           isSelected[1] && isSelected[2])
        {
            time_as_miliseconds/=2;
        }

        if((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::S) && isSelected[0] && isSelected[1] && isSelected[2])
        {
            time_as_miliseconds*=2;
        }
        if((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::X) && isSelected[0] && isSelected[1] && isSelected[2])
        {
            SFMLHandling::setFire();
        }
        if((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::R) && isSelected[0] && isSelected[1] && isSelected[2])
        {
            reset();
            setStone();
            std::ofstream logs;
            logs.open("../Rejestr_zdarzen.txt",std::ios_base::app);
            logs<<"\n\n----------RESTARTOWANIE SYMULACJI----------\n\n";
            logs.close();
        }
        if((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::P) && isSelected[0] && isSelected[1] && isSelected[2])
        {
            if(!isPause)
                isPause=true;
            else
                isPause=false;
        }
        if((event.type==sf::Event::KeyReleased) && (event.key.code==sf::Keyboard::E) && isSelected[0] && isSelected[1] && isSelected[2])
        {
            screenshot();
        }
        if((event.type==sf::Event::MouseButtonPressed) && (event.mouseButton.button==sf::Mouse::Left) && isSelected[0] && isSelected[1] && isSelected[2])
        {
            if(((sf::Mouse::getPosition(*window).x)/35==0)&&((sf::Mouse::getPosition(*window).y)/35)==24)
            {
                if(!isPressed[0])
                {
                    isPressed[0]=true;
                    isPressed[1]=false;
                    isPressed[2]=false;
                }
                else
                    isPressed[0]=false;
            }
            if(((sf::Mouse::getPosition(*window).x)/35==1) && ((sf::Mouse::getPosition(*window).y)/35==24) && isSelected[0] && isSelected[1] && isSelected[2])
            {
                if(!isPressed[1])
                {
                    isPressed[1]=true;
                    isPressed[0]=false;
                    isPressed[2]=false;
                }
                else
                    isPressed[1]=false;
            }
            if(((sf::Mouse::getPosition(*window).x)/35==2) && ((sf::Mouse::getPosition(*window).y)/35==24) && isSelected[0] && isSelected[1] && isSelected[2])
            {
                if(!isPressed[2])
                {
                    isPressed[2]=true;
                    isPressed[0]=false;
                    isPressed[1]=false;
                }
                else
                    isPressed[2]=false;
            }
        }
        if((sf::Mouse::isButtonPressed(sf::Mouse::Left)) && isSelected[0] && isSelected[1] && isSelected[2])
        {
            if(isPressed[0] && (sf::Mouse::getPosition(*window).x > 30) && (sf::Mouse::getPosition(*window).x <= 30 + (int)sizeS * 35) && (sf::Mouse::getPosition(*window).y > 30) && (sf::Mouse::getPosition(*window).y <= 30 + (int)sizeS * 35))
            {
                int xTK=(sf::Mouse::getPosition(*window).x-30)/35;
                int yTK=(sf::Mouse::getPosition(*window).y-30)/35;
                arena(xTK,yTK).setCurrState(Field::states::BURNING);
            }
            if(isPressed[1] && (sf::Mouse::getPosition(*window).x > 30) && (sf::Mouse::getPosition(*window).x <= 30 + (int)sizeS * 35) && (sf::Mouse::getPosition(*window).y > 30) && (sf::Mouse::getPosition(*window).y <= 30 + (int)sizeS * 35))
            {
                int xTK=(sf::Mouse::getPosition(*window).x-30)/35;
                int yTK=(sf::Mouse::getPosition(*window).y-30)/35;
                arena(xTK,yTK).setCurrState(Field::states::ROCK);
            }
            if(isPressed[2] && (sf::Mouse::getPosition(*window).x > 30) && (sf::Mouse::getPosition(*window).x <= 30 + (int)sizeS * 35) && (sf::Mouse::getPosition(*window).y > 30) && (sf::Mouse::getPosition(*window).y <= 30 + (int)sizeS * 35))
            {
                int xTK=(sf::Mouse::getPosition(*window).x-30)/35;
                int yTK=(sf::Mouse::getPosition(*window).y-30)/35;
                arena(xTK,yTK).setCurrState(Field::states::UNTOUCHED);
            }
        }
        if((event.type == sf::Event::KeyReleased)&&(event.key.code == sf::Keyboard::Up))
        {
            if(!isSelected[1] && !isSelected[0] && !isSelected[2] && selectedItemIndexSI != 0){
                moveOnMenuFieldsUp(menuSI,selectedItemIndexSI);
                if(selectedItemIndexSI == 0)
                    selectedItemIndexSI = 0;
                else selectedItemIndexSI--;
            }
            if(!isSelected[2] && isSelected[1] && !isSelected[0] && selectedItemIndexSTO != 0){
                moveOnMenuFieldsUp(menuSTO,selectedItemIndexSTO);
                if(selectedItemIndexSTO == 0)
                    selectedItemIndexSTO = 0;
                else selectedItemIndexSTO--;
            }
            if(!isSelected[0] && isSelected[1] && isSelected[2]) {
                moveOnMenuFieldsUp(menuST, selectedItemIndexST);
                if(selectedItemIndexST == 0)
                    selectedItemIndexST = 0;
                else selectedItemIndexST--;
            }
            if(!isSelected[3] && isSelected[0]){
                moveOnMenuFieldsUp(menuWDCH,selectedItemIndexWDCH);
                if(selectedItemIndexWDCH == 0)
                    selectedItemIndexWDCH = 0;
                else selectedItemIndexWDCH--;
            }
        }
        if((event.type == sf::Event::KeyReleased)&&(event.key.code == sf::Keyboard::Down))
        {
            if(!isSelected[1] && !isSelected[0] && !isSelected[2]) {
                moveOnMenuFieldsDown(menuSI, selectedItemIndexSI, MAX_ROW);
                if(selectedItemIndexSI == MAX_ROW-1)
                    selectedItemIndexSI = MAX_ROW-1;
                else selectedItemIndexSI++;
            }
            if(!isSelected[2] && isSelected[1] && !isSelected[0]) {
                moveOnMenuFieldsDown(menuSTO,selectedItemIndexSTO,MAX_ROW);
                if(selectedItemIndexSTO == MAX_ROW-1)
                    selectedItemIndexSTO = MAX_ROW-1;
                else selectedItemIndexSTO++;
            }
            if(!isSelected[0] && isSelected[1] && isSelected[2]) {
                moveOnMenuFieldsDown(menuST, selectedItemIndexST, MAX_ROW);
                if(selectedItemIndexST == MAX_ROW-1)
                    selectedItemIndexST = MAX_ROW-1;
                else selectedItemIndexST++;
            }
            if(!isSelected[3] && isSelected[0]){
                moveOnMenuFieldsDown(menuWDCH,selectedItemIndexWDCH,5);
                if(selectedItemIndexWDCH == 5-1)
                    selectedItemIndexWDCH = 5-1;
                else selectedItemIndexWDCH++;
            }
        }
        if((event.type == sf::Event::KeyReleased)&&(event.key.code == sf::Keyboard::Enter))
        {
            pressedTimes++;
            if(pressedTimes==1)
            {
                isSelected[1]=true;
                sizeS=(selectedItemIndexSI+2)*5;
            }
            if(pressedTimes==2)
            {
                isSelected[2]=true;
                setStone();
            }
            if(pressedTimes==3)
            {
                isSelected[0]=true;
                simulationType=selectedItemIndexST+1;
                cllogs.restart();
            }
            if(pressedTimes==4&&simulationType==3)
            {
                isSelected[3]=true;
                wind=selectedItemIndexWDCH;
                cllogs.restart();
            }

        }
        if((sf::Mouse::isButtonPressed(sf::Mouse::Left)))
        {
            if(((sf::Mouse::getPosition(*window).x)>=35)&&((sf::Mouse::getPosition(*window).y)>=770)&&((sf::Mouse::getPosition(*window).x)<=235)&&((sf::Mouse::getPosition(*window).y)<=805))
            {
                mouseClicked=true;
                sliderX=(sf::Mouse::getPosition(*window).x);
                wind_to_string=((sliderX-35)/2);
            }
        }
        if((event.type==sf::Event::MouseButtonReleased)&&(event.mouseButton.button==sf::Mouse::Left))
        {
            if(((sf::Mouse::getPosition(*window).x)/35==8)&&((sf::Mouse::getPosition(*window).y)/35==22))
            {
                wind=3;
            }
            if(((sf::Mouse::getPosition(*window).x)/35==9)&&((sf::Mouse::getPosition(*window).y)/35==22))
            {
                wind=1;
            }
            if(((sf::Mouse::getPosition(*window).x)/35==10)&&((sf::Mouse::getPosition(*window).y)/35==22))
            {
                wind=2;
            }
            if(((sf::Mouse::getPosition(*window).x)/35==11)&&((sf::Mouse::getPosition(*window).y)/35==22))
            {
                wind=4;
            }
        }
        if((event.type==sf::Event::MouseButtonPressed)&&(event.mouseButton.button==sf::Mouse::Left))
        {
            if(((sf::Mouse::getPosition(*window).x)/35==3)&&((sf::Mouse::getPosition(*window).y)/35==24))
                time_as_miliseconds*=2;
            if(((sf::Mouse::getPosition(*window).x)/35==4) && ((sf::Mouse::getPosition(*window).y)/35==24) && !isPause)
                isPause=true;
            if(((sf::Mouse::getPosition(*window).x)/35==5) && ((sf::Mouse::getPosition(*window).y)/35==24) && isPause)
                isPause=false;
            if(((sf::Mouse::getPosition(*window).x)/35==6)&&((sf::Mouse::getPosition(*window).y)/35==24))
                time_as_miliseconds/=2;
        }
    }
}
//dla elementów planszy: i = i*35.f+3*SIZE, j = j*35.f+3*SIZE
//dla elementów przybornika:
//palące - i = 0, j = 840, "../textures/burning.bmp"
//skała - i = 35, j = 840, "../textures/rock.bmp"
//drzewo - i = 70, j = 840, "../textures/untouched.bmp"
//wolniej i = 105, j = 840, "../textures/slower.bmp"
//pauza i = 140, j = 840, "../textures/pause.bmp"
//start i = 175, j = 840, "../textures/play.bmp"
//szybciej i = 210, j = 840, "../textures/faster.bmp"
void SFMLHandling::createText(sf::Text text, std::string string, sf::Color color, float x, float y) const {
    sf::Font font;
    if(!font.loadFromFile("../fonts/times-new-roman.ttf")) {}
    text.setFont(font);
    text.setString(string);
    text.setFillColor(color);
    text.setPosition(x,y);
    window->draw(text);
}
void SFMLHandling::placeTexture(std::string resourceDirectory, int i, int j) const
{
    sf::Sprite sprite;
    sf::Texture texture;
    texture.loadFromFile(resourceDirectory);
    sprite.setTexture(texture);
    sprite.setPosition( (float) i,(float) j);
    window->draw(sprite);
}
void SFMLHandling::toolkit() const
{
    placeTexture( "../textures/burning.bmp", 0, 840);
    placeTexture( "../textures/rock.bmp", 35, 840);
    placeTexture( "../textures/untouched.bmp", 70, 840);
    placeTexture( "../textures/slower.bmp", 105, 840);
    placeTexture( "../textures/pause.bmp", 140, 840);
    placeTexture( "../textures/play.bmp", 175, 840);
    placeTexture( "../textures/faster.bmp", 210, 840);

    sf::Text toolkitText;
    createText(toolkitText, "Przybornik", sf::Color::Black, 0, 805);
    if(simulationType==3)
    {
        frame(200,35,35,770,sf::Color(158,106,28,100));

        //przybornik wiatru
        placeTexture( "../textures/zero.bmp", 0, 770);
        placeTexture( "../textures/sto.bmp", 235, 770);
        placeTexture( "../textures/arrow_up.bmp", 270, 770);
        placeTexture( "../textures/arrow_down.bmp", 305, 770);
        placeTexture( "../textures/arrow_left.bmp", 340, 770);
        placeTexture( "../textures/arrow_right.bmp", 375, 770);

        sf::Text windText;
        createText(windText, "Kierunek wiatru:   Sila wiatru:"+std::to_string(wind_to_string), sf::Color::Black, 405, 765);
        if(wind==3)
            placeTexture("../textures/arrow_up.bmp", 600, 770);
        if(wind==1)
            placeTexture("../textures/arrow_down.bmp", 600, 770);
        if(wind==2)
            placeTexture("../textures/arrow_left.bmp", 600, 770);
        if(wind==4)
            placeTexture("../textures/arrow_right.bmp", 600, 770);
    }

}
void SFMLHandling::toolkitFrame(int x,int y) const
{
    frame(35.f,35.f,x,y,sf::Color(255, 0, 0,100));
}
void SFMLHandling::print_speed(double s,unsigned x) const
{
    sf::Text text;
    text.setCharacterSize(25);
    createText(text,"Biezaca predkosc spalania:\n"+std::to_string(s)+"milisekund/klatke\nSkroty klawiszowe:\nF- Przyspiesz symulacje (x2)\nS- Zwolnij symulacje (x2)\nX- Podpalenie losowego drzewa\nP- Zatrzymaj symulacje (Ponownie nacisnij P by wznowic)\nR- Restart symulacji\nE- Zrob zrzut ekranu\nZapisane w folderze screenshots", sf::Color::Black, (float) x*35.f+5*SIZE,(float) 52+3*SIZE);
}
void SFMLHandling::frame(float rectangle_x,float rectangle_y,int startingposition_x,int startingposition_y,sf::Color Color) const
{
    sf::RectangleShape rectangle(sf::Vector2<float>(rectangle_x,rectangle_y));
    rectangle.setFillColor(Color);
    rectangle.setPosition((float) startingposition_x,(float) startingposition_y);
    window->draw(rectangle);
}
void SFMLHandling::printArena() const
{
    for(unsigned i=0; i<sizeS; i++)
    {
        for(unsigned j=0; j<sizeS; j++)
        {

            if(arena(i,j).getCurrState()==Field::states::UNTOUCHED)
                placeTexture("../textures/untouched.bmp", i*35.f+3*SIZE, j*35.f+3*SIZE);

            if(arena(i,j).getCurrState()==Field::states::BURNING)
                placeTexture("../textures/burning.bmp", i*35.f+3*SIZE, j*35.f+3*SIZE);

            if(arena(i,j).getCurrState()==Field::states::BURNING2)
                placeTexture("../textures/burning2.bmp", i*35.f+3*SIZE, j*35.f+3*SIZE);

            if(arena(i,j).getCurrState()==Field::states::BURNT)
                placeTexture("../textures/burnt.bmp", i*35.f+3*SIZE, j*35.f+3*SIZE);

            if(arena(i,j).getCurrState()==Field::states::ROCK)
                placeTexture( "../textures/rock.bmp", i*35.f+3*SIZE, j*35.f+3*SIZE);

        }
    }
}
float laststep=0;
void SFMLHandling::logs() const
{

    int treesBurnt=0;
    for(unsigned i=0; i<sizeS; i++)
    {
        for(unsigned j=0; j<sizeS; j++)
        {
            if(arena(i,j).getCurrState()==Field::states::BURNT)
                treesBurnt++;
        }
    }

    if(laststep!=treesBurnt)
    {
        if(tm.asMilliseconds()>=time_as_miliseconds)
        {
            unsigned stones = 0;
            for(unsigned i=0; i<sizeS; i++)
            {
                for(unsigned j=0; j<sizeS; j++)
                {
                    if(arena(i,j).getCurrState() == Field::states::ROCK)
                        stones++;

                }
            }
            std::ofstream logs;
            logs.open("../Rejestr_zdarzen.txt",std::ios_base::app);
            logs<<"Procent spalonych drzew:"<<(treesBurnt/(sizeS*sizeS-(float)stones))*100.f<<"%\nSpalonych drzew:"<<treesBurnt<<"\nCzas:"<<cllogs.getElapsedTime().asSeconds()<<" s\n"<<"Ilość kamieni:"<< stones<<"\n\n";
            logs.close();
        }
        laststep=treesBurnt;
    }
    else if(laststep==treesBurnt) { if(!tm.asMilliseconds()) {}}

}
void SFMLHandling::nextState() const
{
    if(simulationType==1)
        calculateAndSetNextStatesForFieldMatrix(arena.field_matrix,sizeS);
    if(simulationType==2)
        calculateAndSetNextStatesForFieldMatrixSTAR(arena.field_matrix,sizeS);
    if(simulationType==3)
    {
        calculateAndSetNextStatesForFieldMatrixRANDOMandWIND(arena.field_matrix,sizeS);///POZA PETLA
    }
    for(unsigned i=0; i<sizeS; i++)
    {
        for(unsigned j=0; j<sizeS; j++)
        {
            arena(i,j).set_wind_direction(wind);
            arena(i,j).set_wind_power((sliderX-35)/2);
            arena(i,j).forwardState();
        }
    }
}
void SFMLHandling::setFire()
{
    unsigned x = rand()%sizeS;
    unsigned y = rand()%sizeS;
    if(arena(x,y).getCurrState() != Field::BURNING && arena(x,y).getCurrState() != Field::ROCK && arena(x,y).getCurrState() != Field::BURNT && arena(x,y).getCurrState() != Field::BURNING2)
        arena(x,y).setCurrState(Field::states::BURNING);
    else
        setFire();
}
void SFMLHandling::setStone() const
{
    for(unsigned o = 0; o <(selectedItemIndexSTO+1)*25;  o++)
    {
        unsigned x = rand()%sizeS;
        unsigned y = rand()%sizeS;
        if(arena(x,y).getCurrState() != Field::states::ROCK)
            arena(x,y).setCurrState(Field::states::ROCK);
        else
            o--;
    }
}
void SFMLHandling::screenshot()
{
    sf::Texture t;
    t.create(1400,900);
    t.update(*window);
    sf::Image image=t.copyToImage();
    image.saveToFile("../screenshots/screenshot"+std::to_string(iterator_)+".png");
    iterator_++;
}
void SFMLHandling::handleTime(int time_,bool isPause)
{
    if(!isPause)
        if(tm.asMilliseconds()>=time_)
        {
            nextState();
            tm=cl.restart();
        }
    if(isPause)
        if(!tm.asMilliseconds())
        {
            nextState();
        }
}

void SFMLHandling::updateS()
{
    sf::Sprite bsprite;
    sf::Texture btexture;
    btexture.loadFromFile("../textures/Back.png");
    bsprite.setTexture(btexture);
    window->draw(bsprite);

    if(!isSelected[1])
    {
        menuSIZE = createMenuField(menuSIZE,"Podaj rozmiar lasu:",sf::Color::Black,sf::Vector2f(300,0));
        window->draw(menuSIZE);
        drawMenuFields(menuSI,MAX_ROW);
    }
    else if(!isSelected[2])
    {
        menuSTONES = createMenuField(menuSTONES,"Podaj ilosc kamieni", sf::Color::Black,sf::Vector2f(300,0));
        window->draw(menuSTONES);
        drawMenuFields(menuSTO,MAX_ROW);
    }
    else if(!isSelected[0])
    {
        menuSIMTYPE = createMenuField(menuSIMTYPE,"Podaj sposob przeprowadzenia symulacji",sf::Color::Black,sf::Vector2f(300,0));
        window->draw(menuSIMTYPE);
        drawMenuFields(menuST, MAX_ROW);

    }
    else if(!isSelected[3] && (selectedItemIndexST + 1) == 3)
    {
        menuWIND = createMenuField(menuWIND,"Podaj kierunek wiatru",sf::Color::Black,sf::Vector2f(300,0));
        window->draw(menuWIND);
        drawMenuFields(menuWDCH, 5);
        cllogs.restart();
    }
    else if(isSelected[0] && isSelected[1] && isSelected[2])
        simulationRun();
    if(mouseClicked && simulationType == 3)
        frame(sliderX-35,35,35,770,sf::Color(110, 255, 170,255));

    window->display();

}

void SFMLHandling::run()
{
    window->setFramerateLimit(60);
    mouseClicked=false;
    for(int i=0; i<3; i++)
    {
        isPressed[i]=false;
        isSelected[i]=false;
    }
    isSelected[3]=false;
    isPause=false;
    pressedTimes=0;

    remove("../Rejestr_zdarzen.txt");
    while(window->isOpen())
    {
        updateS();
        handleEvents_();
    }
}
void SFMLHandling::drawMenuFields(sf::Text *matrix, int maxRows)
{
    for(int i = 0; i < maxRows; i++)
        window->draw(matrix[i]);
}
void SFMLHandling::moveOnMenuFieldsUp(sf::Text *matrix, int selectedItem)
{
    if(selectedItem-1>=0)
    {
        matrix[selectedItem].setFillColor(sf::Color::Black);
        selectedItem--;
        matrix[selectedItem].setFillColor(sf::Color::Red);
    }
}
void SFMLHandling::moveOnMenuFieldsDown(sf::Text *matrix, int selectedItem, int bounds)
{
    if(selectedItem+1<bounds)
    {
        matrix[selectedItem].setFillColor(sf::Color::Black);
        selectedItem++;
        matrix[selectedItem].setFillColor(sf::Color::Red);
    }
}
void SFMLHandling::simulationRun()
{
    ///ramki
    frame(sizeS*35.f+4*SIZE,sizeS*35.f+4*SIZE,SIZE,SIZE,sf::Color(50,123,168,255));
    frame(sizeS*35.f+2*SIZE,sizeS*35.f+2*SIZE,2*SIZE,2*SIZE,sf::Color(50,168,162,255));

    ///bazowa prekdosc wyswietlanie
    print_speed(time_as_miliseconds,sizeS);
    toolkit();
    if(isPressed[0])
        toolkitFrame(0,24*35.f);
    if(isPressed[1])
        toolkitFrame(1*35.f,24*35.f);
    if(isPressed[2])
        toolkitFrame(2*35.f,24*35.f);
    if(isPause)
        toolkitFrame(4*35,24*35);
    else
        toolkitFrame(5*35,24*35);
    ///cala symulacja
    tm=cl.getElapsedTime();
    cllogs.getElapsedTime();
    printArena();
    handleTime(time_as_miliseconds,isPause);
    logs();
}
void SFMLHandling::reset()
{
    for(unsigned i=0;i<sizeS;i++)
    {
        for(unsigned j=0;j<sizeS;j++)
            arena(i,j).setCurrState(Field::states::UNTOUCHED);
    }
    cllogs.restart();
}