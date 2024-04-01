//������
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "Caption.h"

//�������
#include "LoadingData.h"

Player player;	//�����
vector<Enemy*> enemy;	//�����
Map gameMap;	//�����
int gameState = 0;	//0 - ����, 1 - ������, 2 - ��������� (��������), 3 - ��������� (����� ��������)
sf::Vector2i windowSize;

vector<sf::Texture> texture;
Caption score;	//���� (�����)
Caption txt_Win, txt_Loose;	//����� ������ � ���������
sf::Clock animationTimer;

void key_pressing(sf::Event event, sf::RenderWindow* window)
{
	//�������� ����
	if (event.key.code == sf::Keyboard::Escape) window->close();

	if (event.type == sf::Event::KeyPressed && gameState == 0)
	{
		if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)	//�������� �����
			player.move(sf::Vector2i(player.position.x, player.position.y - 1), &gameMap);
		else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)	//�������� ����
			player.move(sf::Vector2i(player.position.x, player.position.y + 1), &gameMap);
		else if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)	//�������� �����
			player.move(sf::Vector2i(player.position.x - 1, player.position.y), &gameMap);
		else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)	//�������� ������
			player.move(sf::Vector2i(player.position.x + 1, player.position.y), &gameMap);
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
			enemy.erase(remove(enemy.begin(), enemy.end(), e));
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
	windowSize = sf::Vector2i(gameMap.getMapSizeHorizontal() * 25, gameMap.getMapSizeVertical() * 25 + 40);

	sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "PacMan");
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	txt_Win.setText("YOU WIN!");
	txt_Win.setSize(50);
	txt_Win.setColor(sf::Color(3, 145, 255));
	txt_Win.setPosition(sf::Vector2f(windowSize.x / 2 - txt_Win.getTextSize().x / 2, windowSize.y / 2 - txt_Win.getTextSize().y / 2 - 20));
	txt_Loose.setText("YOU LOOSE!");
	txt_Loose.setSize(50);
	txt_Loose.setColor(sf::Color(255, 0, 0));
	txt_Loose.setPosition(sf::Vector2f(windowSize.x / 2 - txt_Loose.getTextSize().x / 2, windowSize.y / 2 - txt_Loose.getTextSize().y / 2 - 20));

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
		gameMap.draw(&window);					//��������� ���� � ���
		for (auto e : enemy) e->draw(&window);	//��������� ������

		if (gameState == 0 || gameState == 1) player.setState(0);	//��������� ������ ������ (����, ������)
		else if (gameState == 2)	//��������� ���������� ������
		{
			float t = animationTimer.getElapsedTime().asMilliseconds();
			if (t < 500) player.setState(1);
			else if (t >= 500 && t < 1000) player.setState(2);
			else if (t >= 1000)
			{
				player.setState(3);	//̸����� �����
				gameState = 3;
			}
		}
		player.draw(&window);

		window.draw(score.getText());	//����
		if (gameState == 1) window.draw(txt_Win.getText());			//����� ������
		else if (gameState == 2 || gameState == 3) window.draw(txt_Loose.getText());	//����� ���������

		window.display();
	}
}