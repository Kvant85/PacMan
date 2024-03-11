#include <fstream>
#include <SFML/Graphics.hpp>

#include "Map.h"
#include "Player.h"
#include "Enemy.h"

void loadingData(Map* gameMap, Player* player, vector<Enemy*>* enemy)
{
	//«агрузка карты
	ifstream mapFile("Data/map.mp", ios::binary);
	char t1[2], t2[2];

	//2 байта: размер пол€ по горизонтали и по вертикали
	mapFile.read(t1, 2);
	mapFile.read(t2, 2);
	gameMap->setMapSize(atoi(t1), atoi(t2));

	//„тение проходимости карты
	for (int i = 0; i < gameMap->getMapSizeVertical(); i++)
	{
		vector<int> c;
		for (int j = 0; j < gameMap->getMapSizeHorizontal(); j++)
		{
			//2 байта - содержимое €чейки
			mapFile.read(t1, 2);
			if (t1[0] != ' ' || t1[1] != ' ') c.push_back(atoi(t1));
			else c.push_back(0);
		}
		gameMap->getCells()->push_back(c);
	}

	//„тение данных по еде
	//4 байта: количество
	mapFile.read(t1, 2);
	mapFile.read(t2, 2);
	int numOfFood = atoi(t1) * 100 + atoi(t2);
	//4 байта - позици€
	for (int i = 0; i < numOfFood; i++)
	{
		mapFile.read(t1, 2);
		mapFile.read(t2, 2);
		gameMap->setFood(sf::Vector2f(stof(t2), stof(t1)));
	}

	//„тение данных по старту игрока - 4 байта
	mapFile.read(t1, 2);
	mapFile.read(t2, 2);
	player->setPosition(sf::Vector2f(stof(t1), stof(t2)));
	gameMap->setPlayerPosition(sf::Vector2f(stof(t1), stof(t2)));

	//„тение данных по врагам
	//„исло врагов - 2 байта
	mapFile.read(t1, 2);
	int numOfEnemies = atoi(t1);
	//4 байта - позици€ врагов
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