#include "Buttons.hpp"
#include "Lables.hpp"
#include "MenuScene.hpp"
// #include "GameScene.hpp"

//^ Useful functions

#ifndef SetFont
void SetFont(sf::Font &font,std::string path)
{
    if (!font.loadFromFile(path))
    {
        printf("The font file was not found\n");
        return;
    }
    
}
#endif

#ifndef assignFont
void assignFont(sf::Text &text, sf::Font &font) // Just sets the font to the text object
{
    text.setFont(font);
}
#endif

#ifndef SetText
void SetText(sf::Text &text,std::string subject) // sets the given text to the text object (string only)
{
    text.setString(subject);
}
#endif


