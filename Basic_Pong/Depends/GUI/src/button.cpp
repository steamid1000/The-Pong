#include "Buttons.hpp"
namespace GUI{
Button::Button(std::string idString, sf::RenderWindow *windowPointer) : component(windowPointer, true)
{
    ButtonWindowCopy = windowPointer;
    id = idString;
    source = new sf::SoundBuffer;
    audio = new sf::Sound;

    setSound("Resources/click.wav");
}

Button::~Button()
{
    delete ButtonWindowCopy;
    delete source;
    delete audio;
}

void Button::align(short side) // Align the button to the sides of the window or the center of the window
{
    // ! call this function only after deciding the size of the button. !
    /*
      0 -  Center of the screen
      1 - left Top corner of the window
      2 - right top corner of the window
      3 - left bottom corner of the window
      4 - right bottom corner of the window
    */

    switch (side)
    {
    case 0:
        SetPosition(sf::Vector2f(width / 2 - GetSize().x / 2, height / 2 - GetSize().y / 2));
        break;
    case 1:
        SetPosition(sf::Vector2f(GetSize().x, 10));
        break;
    case 2:
        SetPosition(sf::Vector2f(width - GetSize().x - 10, 10));
        break;
    case 3:
        SetPosition(sf::Vector2f(10, height - GetSize().y * 1.5f));
        break;
    case 4:
        SetPosition(sf::Vector2f(width - GetSize().x - 10, height - GetSize().y - 10));
        break;
    default:
        SetPosition(sf::Vector2f(10, 10));
        break;
    }

    OnSizeChange();
}

bool Button::cursorOverButton()
{
    sf::Vector2f mousePosition(sf::Mouse::getPosition(*ButtonWindowCopy).x, sf::Mouse::getPosition(*ButtonWindowCopy).y);
    sf::FloatRect buttonArea = getBounds();
    if (buttonArea.contains(mousePosition))
    {
        return true;
    }

    return false;
}

void Button::onClick() // for now let me just send the lamda code right here later it will be sent to the scene class
{
    Play();
    try
    {
        if (action==nullptr)
        {
            throw "Action Not Found";
        }
        else
        {
            action();
        }
        
    }
    catch(const char * ex)
    {
        // printf("%s : ",ex);
        std::cout<<ex<<" ,  ButtonID: "<<getID()<<'\n';
    }
}
void Button::setAction(std::function<void()> statements)
{ //^ Sets the Action to be performed after clicking the button
    action = statements;
}
void Button::hover()
{
    sf::Vector3i originalColor = GetColor();
    if (cursorOverButton() == true)
    {
        SetColor(Vector4i(originalColor.x, originalColor.y, originalColor.z, 200));
    }
    else
    {
        SetColor(Vector4i(originalColor.x, originalColor.y, originalColor.z, 255));
    }
}

bool Button::Clicked()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and cursorOverButton())
    {
        return true;
    }

    return false;
}

std::string Button::getID()
{
    return id;
}

void Button::setSound(std::string path)
{
    source->loadFromFile(path);
    audio->setBuffer(*source);
}

void Button::Play()
{
    audio->play();
}
void Button::render()
{
    component::render(); // calling the base class render function and then the button class functions are called..👍🏼
    hover();

    if (Clicked())
    {

        onClick();
    }
}
}