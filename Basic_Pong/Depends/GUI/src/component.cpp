#include "component.hpp"

component::component(sf::RenderWindow *windowPointer, bool isvisible = true)
{
    IsVisible = isvisible; // this will tell if the outer rectangle will be valid or not
    SizeGiven = false;     // by default this will be false until the user calls the SetSize function
    internalWindow = windowPointer;
    center = {width / 2, height / 2};
    // setting the default size to be 1

    body = new sf::RectangleShape;
    body->setSize(sf::Vector2f(10, 10));
    body->setFillColor(sf::Color(60,60,60));
    body->setPosition(sf::Vector2f(10, 10));
    body->setOutlineThickness(1.2f);

    // text object settingss
    text = new sf::Text;
    text->setFont(font);
    text->setFillColor(sf::Color::White);
}

component::~component()
{
    delete body;
    delete text;
}

sf::FloatRect component::getBounds(short index)
{ // 0 means the bounds of the button and 0 means the bound of the text - this is for the button objects
    if (IsVisible)
    {
        if (index == 0)
        {
            return body->getGlobalBounds();
        }
        else
        {
            return text->getGlobalBounds();
        }
    }

    return text->getGlobalBounds();
}
void component::OnSizeChange(bool calledFromTextSize) // this function when setsSize function is called
{
    if (!calledFromTextSize)
    {
        text->setCharacterSize(GetSize().y / 2); // if this function is called by the accordingtotext function then we will not change the text size
    }

    text->setPosition(GetPosition().x + (GetSize().x / 2 - text->getGlobalBounds().width / 2), GetPosition().y + text->getGlobalBounds().height / 2);
}

// Auto size based on the text size
void component::ButtonSizeAccordingToText()
{
    if (!SizeGiven)
    {
        SetSize(sf::Vector2f(text->getGlobalBounds().width + 5, text->getGlobalBounds().height + 10));
        OnSizeChange();
    }
}

void component::SetSize(sf::Vector2f size)
{
    if (IsVisible)
    {
        body->setSize(size);
        SizeGiven = true;
    }
    else
    {
        text->setCharacterSize(size.x);
    }
}
void component::SetPosition(sf::Vector2f position)
{

    if (IsVisible)
    {
        body->setPosition(position);
        OnSizeChange();
    }
    else
    {
        text->setPosition(position.x - getBounds().width / 2, position.y);
    }
}

void component::SetInnerText(std::string innertext, short characterSize)
{ // call the set font function before this
    text->setString(innertext);
    if (characterSize != 30) 
    {
        text->setCharacterSize(characterSize);
    }

    ButtonSizeAccordingToText();
}

void component::SetColor(Vector4i rgb)
{
    if (IsVisible)
    {
        body->setFillColor(sf::Color(rgb.a, rgb.b, rgb.c, rgb.d));
    }
    else
    {
        text->setFillColor(sf::Color(rgb.a, rgb.b, rgb.c, rgb.d));
    }
}

void component::ChangeTextColor(Vector4i rgb)
{
    text->setFillColor(sf::Color(rgb.a, rgb.b, rgb.c, rgb.d));
}

sf::Vector3i component::GetColor()
{
    return sf::Vector3i(body->getFillColor().r, body->getFillColor().g, body->getFillColor().b);
}

sf::Vector2f component::GetPosition()
{
    return body->getPosition();
}

sf::Vector2f component::GetSize()
{
    return body->getSize();
}

void component::render()
{

    if (IsVisible)
    {
        internalWindow->draw(*body);
    }
    internalWindow->draw(*text);
}