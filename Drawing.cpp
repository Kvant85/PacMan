#include <SFML/Graphics.hpp>

#include "Map.h"
#include "Enemy.h"
#include "Player.h"
#include "Caption.h"

sf::RectangleShape rect;

void drawing(sf::RenderWindow* window, vector<sf::Texture>* texture, Map* gameMap, Player* player, 
			vector<Enemy*>* enemy, sf::Clock* animationTimer, int gameState, Caption* score)
{
	gameMap->draw(window);	//��������� ����, ��� � ������

	for (int i = 0; i < enemy->size(); i++)	//��������� ������
		enemy->at(i)->draw(window);

	if (gameState == 0 || gameState == 1) player->draw(window, 0);	//��������� ������ ������ (����, ������)
	else	//��������� ���������� � ������� ������
	{
		float t = animationTimer->getElapsedTime().asSeconds();
		if (t < 0.5f) player->draw(window, 1);
		else if (t >= 0.5f && t < 1.0f) player->draw(window, 2);
		else if (t >= 1.0f) player->draw(window, 3);
	}

	//��������� �����
	window->draw(score->getText());

	//��������� ������� ������/���������
	if (gameState != 0)
	{
		Caption resultText;
		if (gameState == 1)
		{
			resultText.setText("YOU WIN!");
			resultText.setColor(sf::Color(3, 145, 255));
			resultText.setPosition(sf::Vector2f(gameMap->getMapSizeHorizontal() * 12.5f - 120, gameMap->getMapSizeVertical() * 12.5f - 30));
		}
		else if (gameState == 2)
		{
			resultText.setText("YOU LOOSE!");
			resultText.setColor(sf::Color(255, 0, 0));
			resultText.setPosition(sf::Vector2f(gameMap->getMapSizeHorizontal() * 12.5f - 150, gameMap->getMapSizeVertical() * 12.5f - 30));
		}
		resultText.setSize(50);
		window->draw(resultText.getText());
	}
}