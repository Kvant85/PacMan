#pragma once
#include <SFML/Graphics.hpp>
using namespace std;

class Actor
{
public:
	Actor() { }
	sf::Vector2f position;
protected: sf::RectangleShape rect;

public: void setPosition(sf::Vector2f _pos)
	{
		position = _pos;
		rect.setPosition(sf::Vector2f(_pos.x * 25, _pos.y * 25));
	}
};