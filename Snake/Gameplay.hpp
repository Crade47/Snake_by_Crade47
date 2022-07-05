#pragma once
#include "State.hpp"
#include <memory>
#include <array>
#include "Game.hpp"
#include "Snake.hpp"
#include<SFML/Graphics/Sprite.hpp>
#include<SFML/Graphics/Text.hpp>

class Gameplay : public Engine ::State
{
private:
	std::shared_ptr<Context> m_context;
	sf::Sprite m_grass;
	sf::Sprite m_food;	
	std::array<sf::Sprite, 4> m_walls;

	Snake m_snake;

	sf::Vector2f m_snakeDirection; 

	sf::Time m_elaspedTime;

	sf::Text m_scoreText;
	int m_score;


public:
	Gameplay(std::shared_ptr<Context>& context);
	~Gameplay();

	void Init() override;
	void ProcessInput() override;
	void Update(sf::Time deltaTime) override;
	void Draw() override;
	void Pause() override;
	void Start() override;

};

