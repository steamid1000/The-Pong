#pragma once
#include "Scene.hpp"

extern short sceneIndex;
extern sf::Font font;

class MenuScene : public Scene
{
private:
    sf::RenderWindow *internalwindow;
    GUI::Button* play;
    GUI::Button* quit;
    GUI::Button* settings;
    GUI::Lable* greet;
    
public:
    MenuScene(sf::RenderWindow&);
    
    ~MenuScene();
    void setup();
    void render();
};

MenuScene::MenuScene(sf::RenderWindow& window)
{
    
    internalwindow = &window;
    printf("The internalwindow has been captured\n");


    setup();
}

MenuScene::~MenuScene()
{
    delete internalwindow;
}

void MenuScene::setup()
{
    play = new GUI::Button("play", internalwindow);
    quit = new GUI::Button("quit", internalwindow);
    settings = new GUI::Button("Authors", internalwindow);
    greet = new GUI::Lable(internalwindow);
   

    auto lam = [&]()
    {sceneIndex++; }; 
    auto quitaction = [&](){internalwindow->close();return;};

    quit->setAction(quitaction);
    play->SetInnerText("Play", 10);
    greet->SetInnerText("PONG - THE GAME");
    quit->SetInnerText("Quit");
    settings->SetInnerText("Authors");
  
    //Colors
    greet->SetColor(Vector4i(216, 186, 13));
    quit->SetColor(Vector4i(37, 23, 77));
    play->SetColor(Vector4i(15, 153, 142));

    play->SetSize(sf::Vector2f(100, 30));
    // // settings.SetSize(sf::Vector2f(100,30));
    quit->SetSize(sf::Vector2f(100, 30));
    greet->SetSize(35);


  

    play->align(0);

    settings->SetPosition(sf::Vector2f(quit->center.x - settings->getBounds().width / 2, play->GetPosition().y + settings->GetSize().y + 10));
    quit->SetPosition(sf::Vector2f(quit->center.x - quit->getBounds().width / 2, settings->GetPosition().y + play->GetSize().y + 10));

    greet->SetPosition(sf::Vector2f(greet->center.x, play->GetPosition().y - 60));

    play->setAction(lam);
    printf("The Scene has been setup\n");
}

void MenuScene::render()
{
            internalwindow->clear(sf::Color(41, 41, 41));
            play->render();
            greet->render();
            quit->render();
            settings->render();
         
}