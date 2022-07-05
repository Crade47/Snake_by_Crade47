#include "GameOver.hpp"
#include <SFML/Window/Event.hpp>
#include "Gameplay.hpp"

GameOver::GameOver(std::shared_ptr<Context>& context) : m_context(context), m_isRetryButtonSelected(true), m_isRetryButtonPressed(false),
m_isExitButtonPressed(false), m_isExitButtonSelected(false)
{
}

GameOver::~GameOver()
{
}


void GameOver::Init()
{

	m_context->m_assets->AddFont(MAIN_FONT, "assets/fonts/Quicksand-Regular.ttf");

	//TITLE
	m_gameOverTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_gameOverTitle.setString("GAME OVER");
	m_gameOverTitle.setOrigin(m_gameOverTitle.getLocalBounds().width / 2, m_gameOverTitle.getLocalBounds().height / 2);
	m_gameOverTitle.setPosition(m_context->m_window->getSize().x / 2 - 50.f, m_context->m_window->getSize().y / 2 - 150.f);
	m_gameOverTitle.setCharacterSize(50);
	m_gameOverTitle.setFillColor(sf::Color::Color(228, 229, 163, 255));


	//PLAY

	m_retryButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_retryButton.setString("RETRY");
	m_retryButton.setOrigin(m_retryButton.getLocalBounds().width / 2, m_retryButton.getLocalBounds().height / 2);
	m_retryButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 25.f);

	//EXIT

	m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_exitButton.setString("EXIT");
	m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2, m_exitButton.getLocalBounds().height / 2);
	m_exitButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 + 25.f);

}

void GameOver::ProcessInput()
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
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
			{
				if (!m_isRetryButtonSelected)
				{
					m_isRetryButtonSelected = true;
					m_isExitButtonSelected = false;
				}
				break;
			}
			case sf::Keyboard::Down:
			{
				if (!m_isExitButtonSelected)
				{
					m_isRetryButtonSelected = false;
					m_isExitButtonSelected = true;
				}
				break;
			}

			case sf::Keyboard::Return:
			{
				m_isExitButtonPressed = false;
				m_isRetryButtonPressed = false;

				if (m_isRetryButtonSelected)
				{
					m_isRetryButtonPressed = true;
				}
				else
				{
					m_isExitButtonPressed = true;
				}
				break;
			}




			default:
				break;
			}
		}
	}
}

void GameOver::Update(sf::Time deltaTime)
{
	if (m_isRetryButtonSelected)
	{
		m_retryButton.setFillColor(sf::Color::White);
		m_exitButton.setFillColor(sf::Color::Color(73, 88, 86, 255));
	}
	else
	{
		m_exitButton.setFillColor(sf::Color::White);
		m_retryButton.setFillColor(sf::Color::Color(73, 88, 86, 255));
	}

	if (m_isRetryButtonPressed)
	{
		//GOTO Play State
		m_context->m_states->Add(std::make_unique<Gameplay>(m_context), true);
	}

	else if (m_isExitButtonPressed)
	{
		m_context->m_window->close();
	}
}

void GameOver::Draw()
{
	m_context->m_window->clear(sf::Color::Color(123, 156, 152, 255));
	m_context->m_window->draw(m_gameOverTitle);
	m_context->m_window->draw(m_retryButton);
	m_context->m_window->draw(m_exitButton);
	m_context->m_window->display();
}
