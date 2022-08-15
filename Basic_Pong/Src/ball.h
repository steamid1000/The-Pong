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
		ball.setPosition(window_width/2, window_height/2);
		
	}

	

};

void logCollision(paddels pad,Sphere gameball) //Just logs the collision information on the console
{
	std::cout << "ball has collided\n";
	std::cout << "X-Position of Ball: " << gameball.ball.getPosition().x << "\n";
	std::cout << "Y-Position of collided paddel: " << pad.paddel.getPosition().y << "\n";
}

bool onCollision(paddels& pad, Sphere& gameball,sf::Sound &collision) //return true and calls the log function
{
	if (gameball.ball.getPosition().x - gameball.ball.getRadius() < pad.paddel.getPosition().x + pad.paddel.getSize().x and
		gameball.ball.getPosition().x - gameball.ball.getRadius() > pad.paddel.getPosition().x and
		gameball.ball.getPosition().y + gameball.ball.getRadius() >= pad.paddel.getPosition().y - pad.paddel.getSize().y and
		gameball.ball.getPosition().y - gameball.ball.getRadius() <= pad.paddel.getPosition().y + pad.paddel.getSize().y)
	{
		logCollision(pad, gameball);
		collision.play();
		return true;
	}
	if (gameball.ball.getPosition().x + gameball.ball.getRadius() > pad.paddel.getPosition().x - pad.paddel.getSize().x/2.9f and
		gameball.ball.getPosition().x + gameball.ball.getRadius() < pad.paddel.getPosition().x and
		gameball.ball.getPosition().y + gameball.ball.getRadius() >= pad.paddel.getPosition().y - pad.paddel.getSize().y/2.9f and
		gameball.ball.getPosition().y - gameball.ball.getRadius() <= pad.paddel.getPosition().y + pad.paddel.getSize().y/2.9f)
	{
		logCollision(pad, gameball);
		collision.play();
		return true;
	}


	return false;


}

void checkCollision(float& dt, Sphere& gameball, paddels& leftpad, paddels& rightpad,float &Angle,sf::Sound &collisionSound)
{
	float factor = 260.f * dt;


	if (!onCollision(leftpad, gameball,collisionSound) and !onCollision(rightpad, gameball, collisionSound) and gameball.ball.getPosition().y + gameball.ball.getRadius() > window_height) //Bottom Collision
	{
		gameball.ball.setPosition(gameball.ball.getPosition().x, window_height - gameball.ball.getRadius() - 0.1f);
		Angle = -Angle;
	}
	else if (!onCollision(leftpad, gameball, collisionSound) and !onCollision(rightpad, gameball, collisionSound) and gameball.ball.getPosition().y < 0) //Top Collision
	{
		gameball.ball.setPosition(gameball.ball.getPosition().x, 0.1f);
		Angle =-Angle;
	}
	else if (onCollision(leftpad, gameball, collisionSound) or onCollision(rightpad, gameball, collisionSound))
	{
		std::cout << "Value of angle: " << Angle << "\n";

		if (onCollision(leftpad, gameball, collisionSound)) //This has to be changed in the future
		{ Angle = pi-Angle; gameball.ball.setPosition(gameball.ball.getPosition().x + gameball.ball.getRadius()/3+ 0.1f, gameball.ball.getPosition().y); }
		else
		{
			Angle = pi-Angle;
			gameball.ball.setPosition(gameball.ball.getPosition().x - gameball.ball.getRadius()/3-0.1, gameball.ball.getPosition().y);
		}

	}

	gameball.ball.move(std::cos(Angle) * factor, std::sin(Angle) * factor);
}


void collidedWithWall(Sphere& gameball,short &numberOfHeartsOnLeft,short &numberOfHeartsOnRight,sf::Sound &sound) //This function is a early version of the life system, which will be added in future commits
{
	if (gameball.ball.getPosition().x + gameball.ball.getRadius() > window_width)
	{
		gameball.ball.setPosition(window_width/2,window_height/2);
		--numberOfHeartsOnRight; //this will reduce the rendered hearts by 1 same is below
		sound.play();
	}
	else if (gameball.ball.getPosition().x < 0)
	{
		gameball.ball.setPosition(window_width/2,window_height/2);
		--numberOfHeartsOnLeft;
		sound.play();
	}
}

