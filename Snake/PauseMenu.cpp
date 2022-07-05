#include "PauseMenu.hpp"
#include<SFML/Window/Event.hpp>

PauseMenu::PauseMenu(std::shared_ptr<Context>& context) : m_context(context)
{
}

PauseMenu::~PauseMenu()
{
}


void PauseMenu::Init()
{


	m_pauseTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));

	//TITLE
	m_pauseTitle.setString("GAME PAUSED");
	m_pauseTitle.setOrigin(m_pauseTitle.getLocalBounds().width / 2, m_pauseTitle.getLocalBounds().height / 2);
	m_pauseTitle.setPosition(m_context->m_window->getSize().x / 2 - 50.f , m_context->m_window->getSize().y / 2 - 70.f);
	m_pauseTitle.setCharacterSize(50);
	m_pauseTitle.setFillColor(sf::Color::Color(228, 229, 163, 255));
	m_pauseTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));

}

void PauseMenu::ProcessInput()
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
			case sf::Keyboard::Escape:
			{
				m_context->m_states->PopCurrent();
				break;
			}


			default:
				break;
			}
		}
	}
}

void PauseMenu::Update(sf::Time deltaTime)
{

}

void PauseMenu::Draw()
{

	m_context->m_window->draw(m_pauseTitle);
	m_context->m_window->display();
}
