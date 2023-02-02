#include "Lables.hpp"

namespace GUI{
Lable::Lable(sf::RenderWindow* windowPointer) : component(windowPointer,false)
{
    LableWindowCopy = windowPointer;
}

Lable::~Lable(){}

void Lable::SetInnerText(std::string innerText) 
{
    component::SetInnerText(innerText);
}

void Lable::SetSize(short charactersize){
    component::SetSize(sf::Vector2f(charactersize,0));
}
}