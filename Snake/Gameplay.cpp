#include "Gameplay.hpp"
#include "GameOver.hpp"
#include "PauseMenu.hpp"
#include <SFML/Window/Event.hpp>
#include <stdlib.h>
#include <time.h>
#include <algorithm>


Gameplay::Gameplay(std::shared_ptr<Context>& context)
	: m_context(context), 
	m_snakeDirection(32.f, 0.f), 
	m_elaspedTime(sf::Time::Zero), 
	m_score(0)
{
	srand(time(nullptr));
}

Gameplay::~Gameplay()
{
}

void Gameplay::Init()
{
	m_context->m_assets->AddTexture(GRASS, "assets/textures/grass.png", true);
	m_context->m_assets->AddTexture(FOOD, "assets/textures/food.png");
	m_context->m_assets->AddTexture(WALL, "assets/textures/wall.png", true);
	m_context->m_assets->AddTexture(SNAKE, "assets/textures/snake.png");

	m_grass.setTexture(m_context->m_assets->GetTexture(GRASS));
	m_grass.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));

	for (auto& wall : m_walls)
	{
		wall.setTexture(m_context->m_assets->GetTexture(WALL));

	}

	m_walls[0].setTextureRect({ 0, 0, (int)m_context->m_window->getSize().x, 32}); /////Calculation
	m_walls[1].setTextureRect({ 0, 0, (int)m_context->m_window->getSize().x, 32 });
	m_walls[1].setPosition(0, m_context->m_window->getSize().y - 32);

	m_walls[2].setTextureRect({ 0, 0, 32, (int)m_context->m_window->getSize().y });
	m_walls[3].setTextureRect({ 0, 0, 32, (int)m_context->m_window->getSize().y });
	m_walls[3].setPosition((int)m_context->m_window->getSize().x - 32, 0);

	m_food.setTexture(m_context->m_assets->GetTexture(FOOD));
	m_food.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2);

	m_snake.Init(m_context->m_assets->GetTexture(SNAKE));

	m_scoreText.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_scoreText.setString("Score: " + std::to_string(m_score));
	m_scoreText.setFillColor(sf::Color::White);
	m_scoreText.setCharacterSize(47);

}

void Gameplay::ProcessInput()
{
	sf::Event event;
	while (m_context->m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_context->m_window->close();


		}
		else if (event.type == sf::Event::KeyPressed)
		{
			sf::Vector2f newDirection = m_snakeDirection;

			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				newDirection = { 0.f, -32.f };
				break;

			case sf::Keyboard::Down:
				newDirection = { 0.f, 32.f };
				break;

			case sf::Keyboard::Left:
				newDirection = { -32.f, 0.f };
				break;

			case sf::Keyboard::Right:
				newDirection = { 32.f, 0.f };
				break;

			case sf::Keyboard::Escape:
				//Pause
				m_context->m_states->Add(std::make_unique<PauseMenu>(m_context));
				break;	 

			default:
				break;
			}

			if (std::abs(m_snakeDirection.x) != std::abs(newDirection.x) || std::abs(m_snakeDirection.y) != std::abs(newDirection.y))
			{
				m_snakeDirection = newDirection; 
			}
		}
	}

	
}

void Gameplay::Update(sf::Time deltaTime)
{
	m_elaspedTime += deltaTime;

	if (m_elaspedTime.asSeconds() > 0.75)
	{
		
		bool isOnWall = false;
		for (auto& wall : m_walls)
		{
			
			if (m_snake.IsOn(wall))
			{
				//GAMEOVERSTATE
				m_context->m_states->Add(std::make_unique<GameOver>(m_context), true);
				break;

			}
		}

		if (m_snake.IsOn(m_food))
		{
			m_snake.Grow(m_snakeDirection);

			int x = 0, y = 0;

			x = std::clamp<int>(rand() % m_context->m_window->getSize().x, 32, m_context->m_window->getSize().x - 2 * 64);
			y = std::clamp<int>(rand() % m_context->m_window->getSize().y, 32, m_context->m_window->getSize().y - 2 * 64);


			m_food.setPosition(x, y);
			m_score += 20;
			m_scoreText.setString("Score: " + std::to_string(m_score));

		}
		else
		{
			m_snake.Move(m_snakeDirection);
		}

		if (m_snake.IsSelfIntersecting())
		{
			m_context->m_states->Add(std::make_unique<GameOver>(m_context), true);
		}


		m_elaspedTime = sf::Time::Zero;
	}
}

void Gameplay::Draw()
{
	m_context->m_window->clear();
	m_context->m_window->draw(m_grass);

	for (auto& wall : m_walls)
	{
		m_context->m_window->draw(wall);
	}

	m_context->m_window->draw(m_food);

	m_context->m_window->draw(m_snake);

	m_context->m_window->draw(m_scoreText);


	m_context->m_window->display();
}

void Gameplay::Pause()
{
	
}

void Gameplay::Start()
{
}


