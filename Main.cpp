//������
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "Caption.h"

//�������
#include "LoadingData.h"
#include "Drawing.h"

Player player;	//�����
vector<Enemy*> enemy;	//�����
Map gameMap;	//�����
int gameState = 0;	//0 - ����, 1 - ������, 2 - ���������

vector<sf::Texture> texture;
Caption score;
sf::Clock animationTimer;

void key_pressing(sf::Event event, sf::RenderWindow* window)
{
	//�������� ����
	if (event.key.code == sf::Keyboard::Escape) window->close();

	if (event.type == sf::Event::KeyPressed && gameState == 0)
	{
		if (event.key.code == sf::Keyboard::W)	//�������� �����
			player.move(sf::Vector2f(player.position.x, player.position.y - 1), &gameMap);
		else if (event.key.code == sf::Keyboard::S)	//�������� ����
			player.move(sf::Vector2f(player.position.x, player.position.y + 1), &gameMap);
		else if (event.key.code == sf::Keyboard::A)	//�������� �����
			player.move(sf::Vector2f(player.position.x - 1, player.position.y), &gameMap);
		else if (event.key.code == sf::Keyboard::D)	//�������� ������
			player.move(sf::Vector2f(player.position.x + 1, player.position.y), &gameMap);
	}
}

void gamelogic()
{
	//�������� �����
	score.setText("Score: " + to_string(player.getScore()));

	//��������� �� �����: ���������
	for (Enemy* e : enemy)
		if (player.position == e->position)
		{
			gameState = 2;
			animationTimer.restart();
			return;
		}
	
	//��� ��� �������: ������
	if (gameMap.getNumOfFood() == 0)
	{
		gameState = 1;
		return;
	}

	//�������� ������
	if (gameState == 0)
		for (Enemy* e : enemy)
			e->move(&gameMap);
}

int main()
{
	srand(std::time(nullptr));
	loadingData(&gameMap, &player, &enemy);
	score.setPosition(sf::Vector2f(10.0f, gameMap.getMapSizeVertical() * 25.0f));
		
	sf::RenderWindow window(sf::VideoMode(gameMap.getMapSizeHorizontal() * 25, gameMap.getMapSizeVertical() * 25 + 40), "Game");
	window.setFramerateLimit(60);
	window.setTitle("PacMan");
	window.setKeyRepeatEnabled(false);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			//�������� ����
			if (event.type == sf::Event::Closed) window.close();
			//������� ������
			key_pressing(event, &window);
		}

		window.clear();

		//������� ������
		if (gameState == 0) gamelogic();

		//���������
		drawing(&window, &texture, &gameMap, &player, &enemy, &animationTimer, gameState, &score);

		window.display();
	}
}