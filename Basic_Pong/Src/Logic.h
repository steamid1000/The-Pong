#pragma once

/// <summary>
///	This file contains logic and basic function of the game.
/// </summary

template<typename t>
void logData(t data) //logs input to the console
{
	std::cout << data << '\n';
}

void setSound(sf::SoundBuffer& buffer, sf::Sound& src, const std::string filePath)
{

	if (!buffer.loadFromFile(filePath))
	{
		logData("file cannot be loaded\n");

	}
	src.setBuffer(buffer);
}

void setText(sf::Font& fontObject, sf::Text& textObject, std::string filepath, short characterSize, std::string data = "null")
{
	if (!fontObject.loadFromFile(filepath))
	{
		logData("Font file for text was not found\n");
		return;
	}
	textObject.setFont(fontObject);
	textObject.setCharacterSize(characterSize);
	textObject.setString(data);
}

// This stops the rendering of items and show the last position of them before calling the function
// I dont think the pause is a problem as the game will be reset anyway.
bool keyWasPressed(sf::Keyboard::Key key)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(key)))
	{
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(key)))
		{
			continue;
		}

		return true;
	}

	return false;
}

//The function is for development only, so that I dont have to restart the game again and again
void reset(float& Angle, Sphere& gameBall, short& leftHearts, short& rightHearts, short& leftScore, short& rightScore,short width,short height)
{
	gameBall.ball.setPosition(width / 2, height / 2);
	Angle = std::rand() + 1 % 20;
	leftHearts = 5;
	rightHearts = 5;
	leftScore = 0;
	rightScore = 0;
	
}


/*bool TimerEnded(short allowedTime, short timer)
{
	return allowedTime - timer < 1;
}*/

void endScreen(sf::Font &font,sf::RenderWindow &window)
{
	sf::Text endText("Game-Has-Ended",font,20);
	endText.setPosition((600 / 3.1) - endText.getPosition().x, 400 / 2);
	window.clear();
	window.draw(endText);
	window.display();
	
}

