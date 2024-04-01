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

			//����� ������ (�������� ����� ������� �� ������� ������� ������)
			sf::Vector2i searchView(0, 0);
			int mapSizeX = gameMap->getMapSizeHorizontal(), mapSizeY = gameMap->getMapSizeVertical();
			for (int i = 0; i < 4; i++)	//0 - �����, 1 - ������, 2 - ����, 3 - �����
			{
				searchView = sf::Vector2i(0, 0);
				while (true)
				{
					//�������� �� ���� ������� � �����
					if (gameMap->getWallsData(sf::Vector2i(position.x + searchView.x, position.y + searchView.y)))
					{
						//�������� �� ������ �� ������						
						if (sf::Vector2i(position.x + searchView.x, position.y + searchView.y) == gameMap->getPlayerPosition())
						{
							//����� ������
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

			//��������
			sf::Vector2i movement(0, 0);
			//��������� ��������
			if (!haveTarget)
			{
				while (true)
				{
					//��������� ����������� ��������
					movement.x = (rand() % 3) - 1;
					movement.y = (rand() % 3) - 1;
					if (movement.x != 0 && movement.y != 0)	//��������� �������� �� ���������
					{
						int rnd = rand() % 2;
						if (rnd == 1) movement.x = 0;
						else movement.y = 0;
					}
					movement.x += position.x;
					movement.y += position.y;

					if (movement.x >= 0 && movement.y >= 0 &&	//����� �� ������� ����� (������ �������)
						movement.x < gameMap->getMapSizeHorizontal() && movement.y < gameMap->getMapSizeVertical() &&	//����� �� ������� ����� (������� �������)
						gameMap->getWallsData(sf::Vector2i(movement.x, movement.y)))	//������������ ������
					{
						//��������
						setPosition(sf::Vector2i(movement.x, movement.y));
						break;
					}
				}
			}
			//������ ����� - �������� � ������� ��� ��� ������ ��������� ���
			else
			{
				//�������� � ����
				if (position.x > target.x) movement.x = -1;
				else if (position.x == target.x) movement.x = 0;
				else movement.x = 1;

				if (position.y > target.y) movement.y = -1;
				else if (position.y == target.y) movement.y = 0;
				else movement.y = 1;

				setPosition(sf::Vector2i(position.x + movement.x, position.y + movement.y));

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