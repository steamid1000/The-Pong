#pragma once
#include <SFML/Graphics.hpp>

class hearts {
private:
	bool side;
	sf::Texture heartImg;
	sf::Font font;
	sf::Text text;
	sf::Sprite lives[5]; // needs initilization
	 
public:
	short numberOfLivesLeft;
	short score;
	short width, height;
	hearts(bool side,short width,short height)
	{
		// Setting up the files used
		heartImg.loadFromFile("Resources\\heart.png");
		font.loadFromFile("Resources\\VeraBd.ttf");
		text.setFont(font);
		text.setCharacterSize(35);

		//Initializing the variables.
		this->side = side;
		this->width = width;
		this->height = height;
		numberOfLivesLeft = 5;
		score = 0;
		initiateHearts(); // ! Warning ! ,Dont call this function from outside 
	}

	void initiateHearts() {
		sf::Vector2f size(0.19, 0.19);
		text.setString(std::to_string(score));
		float x_position;

		if (side == false) //for hearts on the left side
		{
			//setting the first heart size and position as all the other hearts 
			//will have a offset according to the first hearts position
			lives[0].setTexture(heartImg);
			lives[0].setScale(size);
			lives[0].setPosition(80.f, 10.f);

			x_position = 80.f;
			text.setPosition(width/4, height-60);

		}
		else // for hearts on the right side
		{
			lives[0].setTexture(heartImg);
			lives[0].setScale(size);
			lives[0].setPosition(375.f, 10.f);

			x_position = 375.f;
			text.setPosition(width/1.4f, height-60);
		}

		//drawing the remaning hearts
		for (short i = 1; i < 5; i++)
		{
			lives[i].setTexture(heartImg);
			lives[i].setScale(size);
			lives[i].setPosition(x_position + 30.f*i, 10.f); //offsetting the position accodring to the 1st position
		}
	}
	
	void drawHearts(sf::RenderWindow &window) //Drawn the hearts on the screen
	{
		for (short i = 0; i < numberOfLivesLeft; i++)
		{ 
			window.draw(lives[i]);

		}
		text.setString(std::to_string(score));
		window.draw(text);
	}
};
 