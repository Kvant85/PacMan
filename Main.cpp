//Классы
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "Caption.h"

//Функции
#include "LoadingData.h"
#include "Drawing.h"

Player player;	//Игрок
vector<Enemy*> enemy;	//Враги
Map gameMap;	//Карта
int gameState = 0;	//0 - игра, 1 - победа, 2 - поражение

vector<sf::Texture> texture;
Caption score;
sf::Clock animationTimer;

void key_pressing(sf::Event event, sf::RenderWindow* window)
{
	//Закрытие игры
	if (event.key.code == sf::Keyboard::Escape) window->close();

	if (event.type == sf::Event::KeyPressed && gameState == 0)
	{
		if (event.key.code == sf::Keyboard::W)	//Движение вверх
			player.move(sf::Vector2f(player.position.x, player.position.y - 1), &gameMap);
		else if (event.key.code == sf::Keyboard::S)	//Движение вниз
			player.move(sf::Vector2f(player.position.x, player.position.y + 1), &gameMap);
		else if (event.key.code == sf::Keyboard::A)	//Движение влево
			player.move(sf::Vector2f(player.position.x - 1, player.position.y), &gameMap);
		else if (event.key.code == sf::Keyboard::D)	//Движение вправо
			player.move(sf::Vector2f(player.position.x + 1, player.position.y), &gameMap);
	}
}

void gamelogic()
{
	//Передача счёта
	score.setText("Score: " + to_string(player.getScore()));

	//Попадание во врага: поражение
	for (Enemy* e : enemy)
		if (player.position == e->position)
		{
			gameState = 2;
			animationTimer.restart();
			return;
		}
	
	//Вся еда собрана: победа
	if (gameMap.getNumOfFood() == 0)
	{
		gameState = 1;
		return;
	}

	//Движение врагов
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
			//Закрытие окна
			if (event.type == sf::Event::Closed) window.close();
			//Нажатие кнопок
			key_pressing(event, &window);
		}

		window.clear();

		//Игровая логика
		if (gameState == 0) gamelogic();

		//Отрисовка
		drawing(&window, &texture, &gameMap, &player, &enemy, &animationTimer, gameState, &score);

		window.display();
	}
}