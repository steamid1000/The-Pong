#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <random>
#include "Paddels.h"
#include "ball.h"
#include "Lives.h"


void setSound(sf::SoundBuffer& buffer, sf::Sound& src,const std::string filePath)
{
	std::cout << "came here\n";
	if (!buffer.loadFromFile(filePath))
	{
		std::cout << "file cannot be loaded\n";

	}
	src.setBuffer(buffer);
} 

int main()
{
	srand(time(0));

	const short width = 600, height = 400;
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

	sf::CircleShape gameball;
	gameball.setRadius(10.f);
	gameball.setFillColor(sf::Color::White);
	gameball.setOrigin(gameball.getRadius() / 2, gameball.getRadius() / 2);
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
		

	}
	return EXIT_SUCCESS;
}




