#pragma once
#include <SFML/graphics.hpp>

class paddels {
	int speed = 180;
	// 0 is the left side and 1 is the right side

public:
	sf::RectangleShape paddel;
	paddels(sf::Vector2f sizes, bool side)
	{
		paddel.setSize(sizes);
		paddel.setFillColor(sf::Color(std::rand() +208 % 255, std::rand() + 20 % 255, std::rand()+10 % 255));

		if (side == 0)
		{
			paddel.setPosition(0, 40);
			
		}
		else
		{
			paddel.setPosition(600-sizes.x,400 - sizes.y);
		
		}
	}

	 void displace(paddels &pad,sf::Time &dt,bool side,const short &vertical_height,bool part) // the inline might or might not helo at all
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) and side==0 and within_bounds(pad,vertical_height,part))
		{
			pad.paddel.move(0, speed * dt.asSeconds());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) and side==0 and within_bounds(pad,vertical_height,part))
		{
			pad.paddel.move(0, -(speed * dt.asSeconds()));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) and side==1 and within_bounds(pad,vertical_height,part))
		{
			pad.paddel.move(0, -(speed * dt.asSeconds()));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) and side==1 and within_bounds(pad,vertical_height,part))
		{
			pad.paddel.move(0, (speed * dt.asSeconds()));
		}
	}

	 bool within_bounds(paddels& pad,const short &window_height,bool side)
	 {
		 if ((side==false and pad.paddel.getPosition().y < 0.f))
		 {
			 pad.paddel.setPosition(pad.paddel.getPosition().x, 1.f); // setting the y to 0 will relieve the shaking but let it be for some feel right now
			 return false;
		 }
		 if (side==false and (pad.paddel.getPosition().y + pad.paddel.getGlobalBounds().height) >  window_height)
		 {
			 pad.paddel.setPosition(0.f, window_height - pad.paddel.getGlobalBounds().height);
			 return false;
		 } 
		 if (side==true and pad.paddel.getPosition().y < 0.f)
		 {
			 pad.paddel.setPosition(pad.paddel.getPosition().x, 1.f);
			 return false;
		 }
		 if (side==true and (pad.paddel.getPosition().y + pad.paddel.getGlobalBounds().height) >  window_height)
		 {
			 pad.paddel.setPosition(pad.paddel.getPosition().x, window_height - pad.paddel.getGlobalBounds().height);
			 return false;
		 }
		 
		 return true;
		 
	 }
	
	 
	
};