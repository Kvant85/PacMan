#pragma once

void drawing(sf::RenderWindow* window, vector<sf::Texture>* texture, Map* gameMap, Player* player,
				vector<Enemy*>* enemy, sf::Clock* animationTimer, int gameState, Caption* score);