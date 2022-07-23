#pragma once

#include <SFML/graphics.hpp>
		

class Sphere {
public:
	sf::Vector2f size;
	short window_height,window_width;
	sf::RectangleShape ball;
	

	Sphere(float radius,short window_hieght,short window_width)
	{
		size.x = radius;
		size.y = radius;
		this->window_height = window_height;
		this->window_width = window_width;

		ball.setSize(size);
		ball.setFillColor(sf::Color::White);
		//ball.setOrigin(800/2,window_height/4);
		ball.setPosition(800/2, -window_height);
	}

	

};

bool onCollision(paddels& pad, Sphere& gameball, float& dt)
{
	if (pad.paddel.getGlobalBounds().intersects(gameball.ball.getGlobalBounds()))
	{

		std::cout << "ball has collided\n";
		std::cout << "Ball position: " << gameball.ball.getPosition().x << "\n";

		std::cout << "Position of collided paddel: " << pad.paddel.getPosition().y << "\n";

		return true;
	}


	return false;


}

void checkCollision(float& dt, Sphere& gameball, paddels& leftpad, paddels& rightpad,float &Angle)
{
	float factor = 150.f * dt;


	if (!onCollision(leftpad, gameball, dt) and !onCollision(rightpad, gameball, dt) and gameball.ball.getPosition().y + gameball.ball.getSize().y > 600) //Bottom Collision
	{
		gameball.ball.setPosition(gameball.ball.getPosition().x, 600 - gameball.ball.getSize().y - 0.1f);
		Angle = -Angle;
	}
	else if (!onCollision(leftpad, gameball, dt) and !onCollision(rightpad, gameball, dt) and gameball.ball.getPosition().y < 0) //Top Collision
	{
		gameball.ball.setPosition(gameball.ball.getPosition().x, 0.1f);
		Angle = -Angle;
	}
	else if (onCollision(leftpad, gameball, dt) or onCollision(rightpad, gameball, dt))
	{
		std::cout << "Value of angle: " << Angle << "\n";

		if (onCollision(leftpad, gameball, dt)) 
		{ Angle = 3.1415 - Angle + std::rand() % 45; gameball.ball.setPosition(gameball.ball.getPosition().x + 0.2f, gameball.ball.getPosition().y); }

		Angle = 3.1415 - Angle - std::rand() % 45;
		gameball.ball.setPosition(gameball.ball.getPosition().x - 0.2f, gameball.ball.getPosition().y);


	}

	gameball.ball.move(std::cos(Angle) * factor, std::sin(Angle) * factor);
}


void collidedWithWall(Sphere& gameball) //This function is a early version of the life system, which will be added in future commits
{
	if (gameball.ball.getPosition().x + gameball.ball.getSize().x > gameball.window_width)
	{
		gameball.ball.setPosition(rand() + 100 % 250, rand() + 100 % 300);
	}
	else if (gameball.ball.getPosition().x < 0)
	{
		gameball.ball.setPosition(rand() + 100 % 250, rand() + 150 % 300);
		
	}
}