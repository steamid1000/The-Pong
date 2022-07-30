#pragma once

#include <SFML/graphics.hpp>

float pi = 3.1415;
short window_height,window_width;

class Sphere {
public:
	float size;
	sf::CircleShape ball;


	Sphere(float radius,short window_hieghts,short window_widths)
	{
		size = radius;
		window_height = window_hieghts;
		window_width = window_widths;

		ball.setRadius(radius);
		ball.setFillColor(sf::Color::White);
		//ball.setOrigin(800/2,window_height/4);
		ball.setPosition(window_width/2, -window_height);
	}

	

};

void logCollision(paddels pad,Sphere gameball) //Just logs the collision information on the console
{
	std::cout << "ball has collided\n";
	std::cout << "Ball position: " << gameball.ball.getPosition().x << "\n";

	std::cout << "Position of collided paddel: " << pad.paddel.getPosition().y << "\n";
}

bool onCollision(paddels& pad, Sphere& gameball)
{
	if (gameball.ball.getPosition().x - gameball.ball.getRadius() < pad.paddel.getPosition().x + pad.paddel.getSize().x / 2 and
		gameball.ball.getPosition().x - gameball.ball.getRadius() > pad.paddel.getPosition().x and
		gameball.ball.getPosition().y + gameball.ball.getRadius() >= pad.paddel.getPosition().y - pad.paddel.getSize().y / 2 and
		gameball.ball.getPosition().y - gameball.ball.getRadius() <= pad.paddel.getPosition().y + pad.paddel.getSize().y / 2)
	{
		logCollision(pad, gameball);
		return true;
	}
	if (gameball.ball.getPosition().x + gameball.ball.getRadius() > pad.paddel.getPosition().x - pad.paddel.getSize().x / 2 and
		gameball.ball.getPosition().x + gameball.ball.getRadius() < pad.paddel.getPosition().x and
		gameball.ball.getPosition().y + gameball.ball.getRadius() >= pad.paddel.getPosition().y - pad.paddel.getSize().y / 2 and
		gameball.ball.getPosition().y - gameball.ball.getRadius() <= pad.paddel.getPosition().y + pad.paddel.getSize().y / 2)
	{
		logCollision(pad, gameball);
		return true;
	}


	return false;


}

void checkCollision(float& dt, Sphere& gameball, paddels& leftpad, paddels& rightpad,float &Angle)
{
	float factor = 180.f * dt;


	if (!onCollision(leftpad, gameball) and !onCollision(rightpad, gameball) and gameball.ball.getPosition().y + gameball.ball.getRadius() > window_height) //Bottom Collision
	{
		gameball.ball.setPosition(gameball.ball.getPosition().x, window_height - gameball.ball.getRadius() - 0.1f);
		Angle = -Angle;
	}
	else if (!onCollision(leftpad, gameball) and !onCollision(rightpad, gameball) and gameball.ball.getPosition().y < 0) //Top Collision
	{
		gameball.ball.setPosition(gameball.ball.getPosition().x, 0.1f);
		Angle = -Angle;
	}
	else if (onCollision(leftpad, gameball) or onCollision(rightpad, gameball))
	{
		std::cout << "Value of angle: " << Angle << "\n";

		if (onCollision(leftpad, gameball)) 
		{ Angle = pi - Angle + std::rand() % 15; gameball.ball.setPosition(gameball.ball.getPosition().x + 0.2f, gameball.ball.getPosition().y); }

		Angle = pi - Angle - std::rand() % 15;
		gameball.ball.setPosition(gameball.ball.getPosition().x - 0.2f, gameball.ball.getPosition().y);

	}

	gameball.ball.move(std::cos(Angle) * factor, std::sin(Angle) * factor);
}


void collidedWithWall(Sphere& gameball) //This function is a early version of the life system, which will be added in future commits
{
	if (gameball.ball.getPosition().x + gameball.ball.getRadius() > window_width)
	{
		gameball.ball.setPosition(window_width/2,window_height/2);
	}
	else if (gameball.ball.getPosition().x < 0)
	{
		gameball.ball.setPosition(window_width/2,window_height/2);
		
	}
}