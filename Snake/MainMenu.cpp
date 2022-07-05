#include "MainMenu.hpp"
#include "Gameplay.hpp"
#include<SFML/Window/Event.hpp>

MainMenu::MainMenu(std::shared_ptr<Context>& context) : m_context(context), m_isPlayButtonSelected(true), m_isPlayButtonPressed(false), 
m_isExitButtonPressed(false), m_isExitButtonSelected(false)
{
}

MainMenu::~MainMenu()
{

}

void MainMenu::Init()
{
	
	m_context->m_assets->AddFont(MAIN_FONT, "assets/fonts/Quicksand-Regular.ttf");

	//TITLE
	m_gameTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_gameTitle.setString("SNAKE GAME");
	m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().width / 2, m_gameTitle.getLocalBounds().height / 2);
	m_gameTitle.setPosition(m_context->m_window->getSize().x / 2 - 50.f, m_context->m_window->getSize().y / 2 - 150.f);
	m_gameTitle.setCharacterSize(50);
	m_gameTitle.setFillColor(sf::Color::Color(228, 229, 163, 255));
	

	//PLAY
	
	m_playButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_playButton.setString("PLAY");
	m_playButton.setOrigin(m_playButton.getLocalBounds().width / 2, m_playButton.getLocalBounds().height / 2);
	m_playButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 - 25.f);

	//EXIT
	
	m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_exitButton.setString("EXIT");
	m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2, m_exitButton.getLocalBounds().height / 2);
	m_exitButton.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2 + 25.f);

}

void MainMenu::ProcessInput()
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
			case sf::Keyboard::Up :
			{
				if (!m_isPlayButtonSelected)
				{
					m_isPlayButtonSelected = true;
					m_isExitButtonSelected = false;
				}
				break;
			}
			case sf::Keyboard::Down :
			{
				if (!m_isExitButtonSelected)
				{
					m_isPlayButtonSelected = false;
					m_isExitButtonSelected = true;
				}
				break;
			}

			case sf::Keyboard::Return:
			{
				m_isExitButtonPressed = false;
				m_isPlayButtonPressed = false;

				if (m_isPlayButtonSelected)
				{
					m_isPlayButtonPressed = true;
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

void MainMenu::Update(sf::Time deltaTime)
{
	if (m_isPlayButtonSelected)
	{
		m_playButton.setFillColor(sf::Color::White);
		m_exitButton.setFillColor(sf::Color::Color(73, 88, 86, 255));
	}
	else
	{
		m_exitButton.setFillColor(sf::Color::White);
		m_playButton.setFillColor(sf::Color::Color(73, 88, 86, 255));
	}

	if (m_isPlayButtonPressed)
	{
		//GOTO Play State
		m_context->m_states->Add(std::make_unique<Gameplay>(m_context), true);	
	}
	
	else if (m_isExitButtonPressed)
	{
		m_context->m_window->close();
	}
}

void MainMenu::Draw()
{
	m_context->m_window->clear(sf::Color :: Color(123, 156, 152, 255));
	m_context->m_window->draw(m_gameTitle);
	m_context->m_window->draw(m_playButton);
	m_context->m_window->draw(m_exitButton);
	m_context->m_window->display();
}
