#pragma once
#include "component.hpp"
#include <functional>
#include <SFML/Audio.hpp>
#include<iostream>

namespace GUI{
class Button : public component
{
private:
    std::string id;
    sf::RenderWindow* ButtonWindowCopy;
    sf::SoundBuffer* source;
    sf::Sound* audio;
    std::function<void()> action;
public:
    Button(std::string id,sf::RenderWindow* window);
    ~Button();

    void align(short);
    void hover();
    void onClick();
    void setAction(std::function<void()> statements);
    bool cursorOverButton();
    void render();
    bool Clicked();
    void ButtonSizeAccordingToText();
    void setSound(std::string); // I think that each button can have seprated sound
    void Play();
    std::string getID();

};
}

