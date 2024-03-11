#pragma once
#include "Player.h"

class Caption
{
	sf::Font font;
	sf::Text text;

public:
	Caption()
	{
		font.loadFromFile("Data/font.TTF");
		text.setFont(font);
		text.setCharacterSize(24);
		text.setFillColor(sf::Color(200, 200, 200));
		text.setString("Score");
	}

	void setPosition(sf::Vector2f position) { text.setPosition(position); }
	void setText(string t) { text.setString(t); }
	void setColor(sf::Color color)
	{
		text.setFillColor(color);
		text.setOutlineColor(sf::Color(255, 255, 255));
		text.setOutlineThickness(1.5f);
	}
	void setSize(int size) { text.setCharacterSize(size); }
	sf::Text getText() { return text; }
};