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

			//����� ������ (�������� ����� ������� �� ������� ������� ������)
			sf::Vector2f searchView;
			int mapSizeX = gameMap->getMapSizeHorizontal(), mapSizeY = gameMap->getMapSizeVertical();
			for (int i = 0; i < 4; i++)	//0 - �����, 1 - ������, 2 - ����, 3 - �����
			{
				searchView.x = 0;
				searchView.y = 0;
				while (true)
				{
					//�������� �� ���� ������� � �����
					if (gameMap->getWallsData(sf::Vector2f(position.x + searchView.x, position.y + searchView.y)))
					{
						//�������� �� ������ �� ������						
						if (sf::Vector2f(position.x + searchView.x, position.y + searchView.y) == gameMap->getPlayerPosition())
						{
							//����� ������
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
			//��������
			//��������� ��������
			if (!haveTarget)
			{
				while (true)
				{
					//��������� ����������� ��������
					movX = (rand() % 3) - 1;
					movY = (rand() % 3) - 1;
					if (movX != 0 && movY != 0)	//��������� �������� �� ���������
					{
						int rnd = rand() % 2;
						if (rnd == 1) movX = 0;
						else movY = 0;
					}
					movX += position.x;
					movY += position.y;

					if (movX >= 0 && movY >= 0 &&	//����� �� ������� ����� (������ �������)
						movX < gameMap->getMapSizeHorizontal() && movY < gameMap->getMapSizeVertical() &&	//����� �� ������� ����� (������� �������)
						gameMap->getWallsData(sf::Vector2f(movX, movY)))	//������������ ������
					{
						//��������
						setPosition(sf::Vector2f(movX, movY));
						break;
					}
				}
			}
			//������ ����� - �������� � ������� ��� ��� ������ ��������� ���
			else
			{
				//�������� � ����
				if (position.x > target.x) movX = -1;
				else if (position.x == target.x) movX = 0;
				else movX = 1;

				if (position.y > target.y) movY = -1;
				else if (position.y == target.y) movY = 0;
				else movY = 1;

				setPosition(sf::Vector2f(position.x + movX, position.y + movY));

				//�������� ���� - ���������� ��
				if (position.x == target.x && position.y == target.y) haveTarget = false;
			}
		}
	}

	void draw(sf::RenderWindow* window)
	{
		window->draw(rect);
	}
};