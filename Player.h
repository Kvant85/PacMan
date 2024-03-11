#pragma once
#include "Actor.h"
#include "Map.h"

class Player : public Actor
{
	vector<sf::Texture> texture;
	int score;

public:
	Player()
	{
		sf::Texture tex;
		tex.loadFromFile("Data/textures/pacman.png");
		texture.push_back(tex);
		tex.loadFromFile("Data/textures/pacman_state1.png");
		texture.push_back(tex);
		tex.loadFromFile("Data/textures/pacman_state2.png");
		texture.push_back(tex);
		tex.loadFromFile("Data/textures/pacman_dead.png");
		texture.push_back(tex);

		rect.setSize(sf::Vector2f(25, 25));
		rect.setTexture(&texture[0]);
	};

	int getScore() { return score; }

	void move(sf::Vector2f _pos, Map* gameMap)
	{
		if (_pos.x >= 0 && _pos.y >= 0 &&	//Выход за пределы карты (нижняя граница)
			_pos.x < gameMap->getMapSizeHorizontal() && _pos.y < gameMap->getMapSizeVertical() &&	//Выход за пределы карты (верхняя граница)
			gameMap->getWallsData(_pos))	//Проходимость клетки
		{
			//Движение
			setPosition(_pos);
			gameMap->setPlayerPosition(_pos);
			//Наличие еды в клетке
			if (gameMap->getFoodData(_pos))
			{
				gameMap->eraseFood(_pos);
				score++;
			}
		}
		
	}

	void draw(sf::RenderWindow* window, int state)
	{
		if (state == 0) window->draw(rect);
		else
		{
			rect.setTexture(&texture[state]);
			window->draw(rect);
		}
	}
};