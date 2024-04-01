#pragma once
#include "Actor.h"
#include "Map.h"

class Player : public Actor
{
	vector<sf::Texture> texture;
	int score = 0;

public:
	Player()
	{
		sf::Texture tex;
		tex.loadFromFile("Data/textures/pacman.png");
		texture.push_back(tex);
		tex.loadFromFile("Data/textures/pacman_state1.png");
		texture.push_back(tex);
		tex.loadFromFile("Data/textures/pacman_state2.png");
		texture.push_back(tex);
		tex.loadFromFile("Data/textures/pacman_dead.png");
		texture.push_back(tex);

		rect.setTexture(&texture[0]);
	};

	int getScore() { return score; }

	void move(sf::Vector2i _pos, Map* gameMap)
	{
		if (_pos.x >= 0 && _pos.y >= 0 &&	//����� �� ������� ����� (������ �������)
			_pos.x < gameMap->getMapSizeHorizontal() && _pos.y < gameMap->getMapSizeVertical() &&	//����� �� ������� ����� (������� �������)
			gameMap->getWallsData(_pos))	//������������ ������
		{
			//��������
			setPosition(_pos);
			gameMap->setPlayerPosition(_pos);
			//������� ��� � ������
			if (gameMap->getFoodData(_pos))
			{
				gameMap->eraseFood(_pos);
				score++;
			}
		}		
	}

	//�������� ������
	void setState(int _state) { rect.setTexture(&texture[_state]); }

	void draw(sf::RenderWindow* window)
	{
		window->draw(rect);
	}
};