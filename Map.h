#pragma once
using namespace std;

struct VectorCompare
{
	bool operator() (const sf::Vector2i& a, const sf::Vector2i& b) const {
		if (a.y < b.y) return true;
		if (a.y > b.y) return false;
		return (a.x < b.x);
	}
};

class Map
{
	sf::Vector2i mapSize;

	vector<vector<int>> cells;	//������ ����
	map<sf::Vector2i, bool, VectorCompare> food; //���
	sf::Vector2i playerPosition;

	vector<sf::Texture> texture;
	sf::RectangleShape rect;

public:
	Map()
	{
		rect.setSize(sf::Vector2f(25, 25));

		sf::Texture tex;
		tex.loadFromFile("Data/textures/food.png");
		texture.push_back(tex);	//#0 - ���
		tex.loadFromFile("Data/textures/borders/border-h.png");
		texture.push_back(tex);	//#1 - ����� ��������������
		tex.loadFromFile("Data/textures/borders/border-v.png");
		texture.push_back(tex);	//#2 - ����� ������������

		tex.loadFromFile("Data/textures/borders/border-corner_dr.png");
		texture.push_back(tex);	//#3 - ����� ������� ������ ����
		tex.loadFromFile("Data/textures/borders/border-corner_dl.png");
		texture.push_back(tex);	//#4 - ����� ������� ����� ����
		tex.loadFromFile("Data/textures/borders/border-corner_tl.png");
		texture.push_back(tex);	//#5 - ����� ������� ����� �����
		tex.loadFromFile("Data/textures/borders/border-corner_tr.png");
		texture.push_back(tex);	//#6 - ����� ������� ����� ������

		tex.loadFromFile("Data/textures/borders/border-h-l.png");
		texture.push_back(tex);	//#7 - ����� �������� �������������� �����
		tex.loadFromFile("Data/textures/borders/border-h-r.png");
		texture.push_back(tex);	//#8 - ����� �������� �������������� ������
		tex.loadFromFile("Data/textures/borders/border-v-d.png");
		texture.push_back(tex);	//#9 - ����� �������� ������������ �����
		tex.loadFromFile("Data/textures/borders/border-v-t.png");
		texture.push_back(tex);	//#10 - ����� �������� ������������ ������

		tex.loadFromFile("Data/textures/borders/border-bigTU.png");
		texture.push_back(tex);	//#11 - ����� ����� � - �����
		tex.loadFromFile("Data/textures/borders/border-bigTR.png");
		texture.push_back(tex);	//#12 - ����� ����� � - ������
		tex.loadFromFile("Data/textures/borders/border-bigTD.png");
		texture.push_back(tex);	//#13 - ����� ����� � - ����
		tex.loadFromFile("Data/textures/borders/border-bigTL.png");
		texture.push_back(tex);	//#14 - ����� ����� � - �����
	};

	int getMapSizeVertical() { return mapSize.x; }
	int getMapSizeHorizontal() { return mapSize.y; }
	bool getWallsData(sf::Vector2i _pos)
	{
		if (cells.at(_pos.y).at(_pos.x) != 0) return false;
		else return true;
	}
	bool getFoodData(sf::Vector2i _pos)
	{
		map<sf::Vector2i, bool>::iterator it = food.find(_pos);
		if (it != food.end()) return true;
		else return false;
	}
	vector<vector<int>>* getCells() { return &cells; }
	sf::Vector2i getPlayerPosition() { return playerPosition; }

	void setMapSize(int _x, int _y)
	{
		mapSize.x = _x;
		mapSize.y = _y;
	}
	void setFood(sf::Vector2i vecFood) { food[vecFood] = true; }
	void setPlayerPosition(sf::Vector2i _pos) { playerPosition.x = _pos.x; playerPosition.y = _pos.y; }

	void eraseFood(sf::Vector2i _pos) { food.erase(_pos); }

	int getNumOfFood() { return food.size(); }

	void draw(sf::RenderWindow* window)
	{
		//��������� ����
		for (int i = 0; i < mapSize.y; i++)
		{
			for (int j = 0; j < mapSize.x; j++)
			{
				rect.setPosition(sf::Vector2f(i * 25.0f, j * 25.0f));
				if (cells.at(j).at(i) != 0)
				{
					rect.setTexture(&texture[cells.at(j).at(i)]);
					window->draw(rect);
				}
			}
		}

		//��������� ���
		rect.setTexture(&texture[0]);
		for (const auto& un : food)
			if (un.second)
			{
				rect.setPosition(sf::Vector2f(un.first.x * 25, un.first.y * 25));
				window->draw(rect);
			}
	}
};