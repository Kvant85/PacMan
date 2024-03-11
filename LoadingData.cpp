#include <fstream>
#include <SFML/Graphics.hpp>

#include "Map.h"
#include "Player.h"
#include "Enemy.h"

void loadingData(Map* gameMap, Player* player, vector<Enemy*>* enemy)
{
	//�������� �����
	ifstream mapFile("Data/map.mp", ios::binary);
	char t1[2], t2[2];

	//2 �����: ������ ���� �� ����������� � �� ���������
	mapFile.read(t1, 2);
	mapFile.read(t2, 2);
	gameMap->setMapSize(atoi(t1), atoi(t2));

	//������ ������������ �����
	for (int i = 0; i < gameMap->getMapSizeVertical(); i++)
	{
		vector<int> c;
		for (int j = 0; j < gameMap->getMapSizeHorizontal(); j++)
		{
			//2 ����� - ���������� ������
			mapFile.read(t1, 2);
			if (t1[0] != ' ' || t1[1] != ' ') c.push_back(atoi(t1));
			else c.push_back(0);
		}
		gameMap->getCells()->push_back(c);
	}

	//������ ������ �� ���
	//4 �����: ����������
	mapFile.read(t1, 2);
	mapFile.read(t2, 2);
	int numOfFood = atoi(t1) * 100 + atoi(t2);
	//4 ����� - �������
	for (int i = 0; i < numOfFood; i++)
	{
		mapFile.read(t1, 2);
		mapFile.read(t2, 2);
		gameMap->setFood(sf::Vector2f(stof(t2), stof(t1)));
	}

	//������ ������ �� ������ ������ - 4 �����
	mapFile.read(t1, 2);
	mapFile.read(t2, 2);
	player->setPosition(sf::Vector2f(stof(t1), stof(t2)));
	gameMap->setPlayerPosition(sf::Vector2f(stof(t1), stof(t2)));

	//������ ������ �� ������
	//����� ������ - 2 �����
	mapFile.read(t1, 2);
	int numOfEnemies = atoi(t1);
	//4 ����� - ������� ������
	for (int i = 0; i < numOfEnemies; i++)
	{
		mapFile.read(t1, 2);
		mapFile.read(t2, 2);
		Enemy* e = new Enemy();
		e->setPosition(sf::Vector2f(stof(t1), stof(t2)));
		enemy->push_back(e);
	}

	mapFile.close();
}