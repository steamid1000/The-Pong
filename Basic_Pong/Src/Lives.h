#pragma once
#include <SFML/Graphics.hpp>

class hearts {
private:
	bool side;
	sf::Texture heartImg;
	sf::Sprite lives[5]; // needs initilization
	 
public:
	short numberOfLivesLeft;
	hearts(bool side)
	{
		heartImg.loadFromFile("Resources\\heart.png");
		this->side = side;
		numberOfLivesLeft = 5;
		initiateHearts(); // ! Warning ! ,Dont call this function from outside 
	}

	void initiateHearts() {
		sf::Vector2f size(0.19, 0.19);
		float x_position;
		if (side == false) //for hearts on the left side
		{
			//setting the first heart size and position as all the other hearts 
			//will have a offset according to the first hearts position
			lives[0].setTexture(heartImg);
			lives[0].setScale(size);
			lives[0].setPosition(80.f, 10.f);

			x_position = 80.f;

		}
		else // for hearts on the right side
		{
			lives[0].setTexture(heartImg);
			lives[0].setScale(size);
			lives[0].setPosition(375.f, 10.f);

			x_position = 375.f;
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
	}
};
 