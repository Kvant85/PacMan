#pragma once
#include "Actor.h"
#include "Map.h"

class Enemy : public Actor
{
	sf::Texture texture;
	sf::Clock timer;

public:
	float speed = 0.3f;
	bool haveTarget = false;
	sf::Vector2i target;

	Enemy()
	{
		texture.loadFromFile("Data/textures/enemy.png");
		rect.setTexture(&texture);
	}

	void move(Map* gameMap)
	{
		if (timer.getElapsedTime().asSeconds() >= speed)
		{
			timer.restart();

			//ПОИСК ИГРОКА (проверка линий взгляда на предмет наличия игрока)
			sf::Vector2i searchView(0, 0);
			int mapSizeX = gameMap->getMapSizeHorizontal(), mapSizeY = gameMap->getMapSizeVertical();
			for (int i = 0; i < 4; i++)	//0 - вверх, 1 - вправо, 2 - вниз, 3 - влево
			{
				searchView = sf::Vector2i(0, 0);
				while (true)
				{
					//Проверка на упор взгляда в стену
					if (gameMap->getWallsData(sf::Vector2i(position.x + searchView.x, position.y + searchView.y)))
					{
						//Проверка на взгляд на игрока						
						if (sf::Vector2i(position.x + searchView.x, position.y + searchView.y) == gameMap->getPlayerPosition())
						{
							//Нашли игрока
							target = sf::Vector2i(position.x + searchView.x, position.y + searchView.y);
							haveTarget = true;
							break;
						}
						else
						{
							if (i == 0) searchView.x--;
							else if (i == 1) searchView.y++;
							else if (i == 2) searchView.x++;
							else if (i == 3) searchView.y--;
						}
					}
					else break;	
				}
			}

			//ДВИЖЕНИЕ
			sf::Vector2i movement(0, 0);
			//Рандомное движение
			if (!haveTarget)
			{
				while (true)
				{
					//Рандомное направление движения
					movement.x = (rand() % 3) - 1;
					movement.y = (rand() % 3) - 1;
					if (movement.x != 0 && movement.y != 0)	//Запрещаем движение по диагонали
					{
						int rnd = rand() % 2;
						if (rnd == 1) movement.x = 0;
						else movement.y = 0;
					}
					movement.x += position.x;
					movement.y += position.y;

					if (movement.x >= 0 && movement.y >= 0 &&	//Выход за пределы карты (нижняя граница)
						movement.x < gameMap->getMapSizeHorizontal() && movement.y < gameMap->getMapSizeVertical() &&	//Выход за пределы карты (верхняя граница)
						gameMap->getWallsData(sf::Vector2i(movement.x, movement.y)))	//Проходимость клетки
					{
						//Движение
						setPosition(sf::Vector2i(movement.x, movement.y));
						break;
					}
				}
			}
			//Найден игрок - движение в сторону где его видели последний раз
			else
			{
				//Движение к цели
				if (position.x > target.x) movement.x = -1;
				else if (position.x == target.x) movement.x = 0;
				else movement.x = 1;

				if (position.y > target.y) movement.y = -1;
				else if (position.y == target.y) movement.y = 0;
				else movement.y = 1;

				setPosition(sf::Vector2i(position.x + movement.x, position.y + movement.y));

				//Достигли цели - сбрасываем ее
				if (position.x == target.x && position.y == target.y) haveTarget = false;
			}
		}
	}

	void draw(sf::RenderWindow* window)
	{
		window->draw(rect);
	}
};