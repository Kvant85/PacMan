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
	sf::Vector2f target;

	Enemy()
	{
		texture.loadFromFile("Data/textures/enemy.png");
		rect.setSize(sf::Vector2f(25, 25));
		rect.setTexture(&texture);
	}

	void move(Map* gameMap)
	{
		if (timer.getElapsedTime().asSeconds() >= speed)
		{
			timer.restart();

			//ПОИСК ИГРОКА (проверка линий взгляда на предмет наличия игрока)
			sf::Vector2f searchView;
			int mapSizeX = gameMap->getMapSizeHorizontal(), mapSizeY = gameMap->getMapSizeVertical();
			for (int i = 0; i < 4; i++)	//0 - вверх, 1 - вправо, 2 - вниз, 3 - влево
			{
				searchView.x = 0;
				searchView.y = 0;
				while (true)
				{
					//Проверка на упор взгляда в стену
					if (gameMap->getWallsData(sf::Vector2f(position.x + searchView.x, position.y + searchView.y)))
					{
						//Проверка на взгляд на игрока						
						if (sf::Vector2f(position.x + searchView.x, position.y + searchView.y) == gameMap->getPlayerPosition())
						{
							//Нашли игрока
							target = sf::Vector2f(position.x + searchView.x, position.y + searchView.y);
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

			float movX = 0, movY = 0;
			//ДВИЖЕНИЕ
			//Рандомное движение
			if (!haveTarget)
			{
				while (true)
				{
					//Рандомное направление движения
					movX = (rand() % 3) - 1;
					movY = (rand() % 3) - 1;
					if (movX != 0 && movY != 0)	//Запрещаем движение по диагонали
					{
						int rnd = rand() % 2;
						if (rnd == 1) movX = 0;
						else movY = 0;
					}
					movX += position.x;
					movY += position.y;

					if (movX >= 0 && movY >= 0 &&	//Выход за пределы карты (нижняя граница)
						movX < gameMap->getMapSizeHorizontal() && movY < gameMap->getMapSizeVertical() &&	//Выход за пределы карты (верхняя граница)
						gameMap->getWallsData(sf::Vector2f(movX, movY)))	//Проходимость клетки
					{
						//Движение
						setPosition(sf::Vector2f(movX, movY));
						break;
					}
				}
			}
			//Найден игрок - движение в сторону где его видели последний раз
			else
			{
				//Движение к цели
				if (position.x > target.x) movX = -1;
				else if (position.x == target.x) movX = 0;
				else movX = 1;

				if (position.y > target.y) movY = -1;
				else if (position.y == target.y) movY = 0;
				else movY = 1;

				setPosition(sf::Vector2f(position.x + movX, position.y + movY));

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