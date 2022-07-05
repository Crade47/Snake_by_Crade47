#pragma once
#include "State.hpp"
#include "Game.hpp"
#include <memory>
#include <SFML/Graphics/Text.hpp>

class PauseMenu : public Engine::State
{

private:
	std::shared_ptr<Context> m_context;
	sf::Text m_pauseTitle;


public:
	PauseMenu(std::shared_ptr<Context>& context);
	~PauseMenu();




	void Init() override;
	void ProcessInput() override;
	void Update(sf::Time deltaTime) override;
	void Draw() override;

};


