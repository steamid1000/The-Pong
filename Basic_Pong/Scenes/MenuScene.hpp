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
    GUI::Button* help;
    GUI::Button* test;

    //^ temp
    GUI::Button* check; 
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
    help = new GUI::Button("help", internalwindow);
    test = new GUI::Button("test", internalwindow);

    //^temp
    check = new GUI::Button("check",internalwindow);
    check->SetInnerText("Checked",40);
    check->align(2);
    check->SetColor(Vector4i(120,90,136,255));

    auto lam = [&]()
    {sceneIndex++; }; 
    auto quitaction = [&](){internalwindow->close();return;};

    quit->setAction(quitaction);
    play->SetInnerText("Play", 10);
    greet->SetInnerText("PONG - THE GAME");
    quit->SetInnerText("Quit");
    settings->SetInnerText("Authors");
    help->SetInnerText("game like why not now", 90); // The size 90 will not applied as the SetSize function is called on this object

    // testing the function
    test->SetInnerText("Working", 90); // This size will be set as the user havent provided any size for the button object

    play->SetSize(sf::Vector2f(100, 30));
    // // settings.SetSize(sf::Vector2f(100,30));
    quit->SetSize(sf::Vector2f(100, 30));
    greet->SetSize(25);
    help->SetSize(sf::Vector2f(500, 40));

    greet->SetColor(Vector4i(10, 10, 10));
    help->SetColor(Vector4i(190, 145, 160));

    play->align(0);
    help->SetPosition(sf::Vector2f(help->center.x - help->getBounds().width / 2, height - help->getBounds().height - 10));

    settings->SetPosition(sf::Vector2f(quit->center.x - settings->getBounds().width / 2, play->GetPosition().y + settings->GetSize().y + 10));
    quit->SetPosition(sf::Vector2f(quit->center.x - quit->getBounds().width / 2, settings->GetPosition().y + play->GetSize().y + 10));

    greet->SetPosition(sf::Vector2f(greet->center.x, play->GetPosition().y - 60));

    play->setAction(lam);
    printf("The Scene has been setup\n");
}

void MenuScene::render()
{
        // internalwindow->clear(sf::Color(110,110,190));
            play->render();
            greet->render();
            test->render();
            help->render();
            quit->render();
            settings->render();

            //^temp
            check->render();
        // internalwindow->display();
         
}