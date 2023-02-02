#pragma once
#include <SFML/Graphics.hpp>

// using external global variables
extern const short width, height;
extern sf::Font font;

struct Vector4i
{
    int a, b, c, d;
    Vector4i(int ab, int bc, int cd, int de = 255)
    {
        a = ab;
        b = bc;
        c = cd;
        d = de;
    }
};

class component
{
private:
    sf::RectangleShape *body;
    sf::Text *text;
    bool IsVisible;
    bool SizeGiven; // If the size is fixed by the user
    sf::RenderWindow *internalWindow = nullptr;

public:
    sf::Vector2i center;
    component(sf::RenderWindow *windowPointer, bool);
    ~component();

    virtual void SetSize(sf::Vector2f); // this should be either a sf::vector or short for button and lable respectively
    void SetPosition(sf::Vector2f);
    void SetColor(Vector4i);
    virtual void SetInnerText(std::string,short= 30);
    void OnSizeChange(bool=false);
    void ButtonSizeAccordingToText();
    sf::FloatRect getBounds(short = 0);
    sf::Vector2f GetPosition();
    sf::Vector2f GetSize();
    virtual sf::Vector3i GetColor();
    virtual void render(); // maybe move this function to the gui file, should each component have render funvtion
    void ChangeTextColor(Vector4i);
};
