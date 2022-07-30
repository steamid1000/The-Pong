#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>
#include "Paddels.h"
#include "ball.h"


int main()
{
	srand(time(0));

	const short width = 600, height = 400;
	sf::RenderWindow window(sf::VideoMode(width, height), "Pong");
	

	sf::RectangleShape middleLine;
	middleLine.setPosition(width / 2, 0);
	middleLine.setFillColor(sf::Color::White);
	middleLine.setSize(sf::Vector2f(1.1f, height));
	
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
	Angle = std::rand() + 100 % 145;
	float seconds;

	

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

		
	
		checkCollision(seconds, gameBall, left, right,Angle); //More precision required in collision
		collidedWithWall(gameBall);

		

		window.clear();
		window.draw(middleLine);
		window.draw(left.paddel);
		window.draw(right.paddel);
		window.draw(gameBall.ball);
		window.display();
		

	}
	return EXIT_SUCCESS;
}





