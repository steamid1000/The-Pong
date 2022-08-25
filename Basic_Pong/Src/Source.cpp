#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <random>
#include "Paddels.h"
#include "ball.h"
#include "Lives.h"

// Global variables
const short width = 600, height = 400;

void setSound(sf::SoundBuffer& buffer, sf::Sound& src,const std::string filePath)
{
	std::cout << "came here\n";
	if (!buffer.loadFromFile(filePath))
	{
		std::cout << "file cannot be loaded\n";

	}
	src.setBuffer(buffer);
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
void reset(float &Angle, Sphere &gameBall, short &leftHearts, short &rightHearts,short &leftScore,short &rightScore)
{
	gameBall.ball.setPosition(width / 2, height / 2);
	Angle = std::rand() + 1 % 20;
	leftHearts = 5;
	rightHearts = 5;
	leftScore = 0;
	rightScore = 0;
}

int main()
{
	srand(time(0));

	
	sf::RenderWindow window(sf::VideoMode(width, height), "Pong");
	//window.setFramerateLimit(60);

	sf::Texture middleline;
	middleline.loadFromFile("Resources\\middle-Line.png");
	sf::Sprite middleLine(middleline);
	middleLine.setScale(0.8,1.1);
	middleLine.setPosition(width / 2, 0);
	
	
	sf::Event event;
	sf::Clock deltaclock;
	sf::Time dt;

	paddels left(sf::Vector2f(20,60), 0);
	paddels right(sf::Vector2f(20, 60), 1);
	Sphere gameBall(11.f,height,width);

	float Angle;
	Angle = std::rand() % 10;
	float seconds;

	//lives code here
	hearts leftHearts(0,width,height);
	hearts rightHearts(1,width,height);

	//sounds
	const std::string wallCollisionfile = "Resources\\collision.wav";
	const std::string paddleCollisionfile = "Resources\\paddel_hit.wav";
	
	sf::SoundBuffer wallCollision;
	sf::SoundBuffer paddleCollision;
	sf::Sound wallSound;
	sf::Sound paddleHitSound;

	setSound(wallCollision, wallSound, wallCollisionfile);
	setSound(paddleCollision,paddleHitSound,paddleCollisionfile);
	


	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
				std::cout << "The window has closed successfully\n";
				return EXIT_SUCCESS;
			}
		}
		
		

		dt = deltaclock.restart();
		seconds = dt.asSeconds();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) or sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			left.displace(left,dt,false,height,0);
			//False means the paddle is on the left and vice versa
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) or sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			right.displace(right,dt,true,height,1);
		}

		
	
		checkCollision(seconds, gameBall, left, right,Angle,paddleHitSound); //More precision required in collision
		collidedWithWall(gameBall,leftHearts.numberOfLivesLeft,leftHearts.score,rightHearts.numberOfLivesLeft,rightHearts.score,wallSound);

		 

		window.clear();
		window.draw(middleLine);
		window.draw(left.paddel);
		window.draw(right.paddel);
		window.draw(gameBall.ball);
		leftHearts.drawHearts(window);
		rightHearts.drawHearts(window);
		window.display();
		

		// Resets the required game objects like the ball,lives and the heart counters
		if (keyWasPressed(sf::Keyboard::Key::R))
		{
			reset(Angle,gameBall,leftHearts.numberOfLivesLeft ,rightHearts.numberOfLivesLeft,leftHearts.score,rightHearts.score);
		}

		// game-quit option
		if (keyWasPressed(sf::Keyboard::Key::Escape))
		{
			break;
		}
	}

	return EXIT_SUCCESS;
}




