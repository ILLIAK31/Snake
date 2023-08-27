#pragma once
#include <SFML/Graphics.hpp>
#include <deque>

class Snake
{
public:
	Snake();
	void Run();
	~Snake();
private:
	void Spawn_Food();
	void Process();
	void Update();
	void Render();
	sf::RenderWindow window;
	int X, Y, Score;
	std::deque<sf::Vector2i> snake;
	sf::Vector2i food;
	bool Check_Collision();
	sf::Texture Background_Texture , Fruit_Texture;
	sf::Sprite Background_Sprite , Fruit_Sprite;
};