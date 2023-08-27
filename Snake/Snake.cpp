#include <algorithm>
#include <iostream>
#include <vector>
#include "Snake.hpp"

Snake::Snake() :
	window(sf::VideoMode(410, 410), "Snake"), X(0), Y(0),
	Score(0), random(std::random_device{}())
{
	if (!Background_Texture.loadFromFile("1.jpg")) {}
	Background_Sprite.setTexture(Background_Texture);
	if (!Fruit_Texture.loadFromFile("2.png")) {}
	Fruit_Sprite.setTexture(Fruit_Texture);
	float Fruit_Scale = 0.085f;
	Fruit_Sprite.setScale(Fruit_Scale, Fruit_Scale);
	window.setFramerateLimit(9);
	sf::Vector2i head(10, 10);
	snake.push_back(head);
	Spawn_Food();
}

void Snake::Run()
{
	while (window.isOpen())
	{
		Process();
		Update();
		Render();
	}
}

void Snake::Spawn_Food()
{
	// Find all possible points on the grid
	std::vector<sf::Vector2i> possible_positions;
	for (int x = 0; x < 20; ++x)
	{
		for (int y = 0; y < 20; ++y)
		{
			sf::Vector2i point(x, y);
			if (std::find(snake.begin(), snake.end(), point) == snake.end())
				possible_positions.push_back(point);
		}
	}
	// Choose one point randomly
	std::uniform_int_distribution<int> dist(0, possible_positions.size());
	food = possible_positions[dist(random)];
	Fruit_Sprite.setPosition(food.x * 20, food.y * 20);
}

void Snake::Process()
{
	sf::Event event;
	while (window.pollEvent(event))
		if (event.type == sf::Event::Closed)
			window.close();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && X != 1)
	{
		X = -1;
		Y = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && X != -1)
	{
		X = 1;
		Y = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && Y != 1)
	{
		X = 0;
		Y = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && Y != -1)
	{
		X = 0;
		Y = 1;
	}
}

void Snake::Update()
{
	int newX = snake[0].x + X;
	int newY = snake[0].y + Y;
	if (newX < 0 || newX >= 20 || newY < 0 || newY >= 20 || Check_Collision())
	{
		std::cout << "Game Over!\nScore: " << Score << std::endl;
		window.close();
	}
	if (newX == food.x && newY == food.y)
	{
		Score += 10;
		Spawn_Food();
	}
	else
		snake.pop_back();
	sf::Vector2i newHead(newX, newY);
	snake.push_front(newHead);
}

void Snake::Render()
{
	window.clear();
	window.draw(Background_Sprite);
	window.draw(Fruit_Sprite);
	sf::CircleShape Body_Segment;
	Body_Segment.setFillColor(sf::Color::Red);
	Body_Segment.setRadius(10);
	for (const auto& segment : snake)
	{
		Body_Segment.setPosition(segment.x * 20, segment.y * 20);
		window.draw(Body_Segment);
	}
	window.display();
}

bool Snake::Check_Collision()
{
	return std::find(snake.begin() + 1, snake.end(), snake[0]) != snake.end();
}

Snake::~Snake() {}


