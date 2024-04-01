#pragma once
#include <SFML/Graphics.hpp>
using namespace std;

class Actor
{
protected: sf::RectangleShape rect;
public:
	Actor()
	{
		rect.setSize(sf::Vector2f(25, 25));
	}
	sf::Vector2i position;

	void setPosition(sf::Vector2i _pos)
	{
		position = _pos;
		rect.setPosition(sf::Vector2f(_pos.x * 25, _pos.y * 25));
	}
};