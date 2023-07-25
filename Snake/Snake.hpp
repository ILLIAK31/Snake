#pragma once

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
	std::vector<sf::Vector2i> snake;
	sf::Vector2i food;
	bool Check_Collision();
	sf::Texture Background_Texture , Fruit_Texture;
	sf::Sprite Background_Sprite , Fruit_Sprite;
};