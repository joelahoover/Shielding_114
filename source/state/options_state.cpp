#include "state/options_state.hpp"

#include "state/game_state.hpp"
#include "state/main_menu.hpp"

OptionsState::OptionsState(std::unique_ptr<State> menu_state) :
	_easy_texture(),
	_medium_texture(),
	_hard_texture(),
	_back_texture(),
	_easy_sprite(),
	_medium_sprite(),
	_hard_sprite(),
	_back_sprite(),
	_dimmer(),
	_menu_state(std::move(menu_state)),
	_next_state(nullptr),
	_back(false)
{
	// Load the textures
	_easy_texture.loadFromFile("resources/graphics/easy.png");
	_easy_texture.setSmooth(true);
	_medium_texture.loadFromFile("resources/graphics/medium.png");
	_medium_texture.setSmooth(true);
	_hard_texture.loadFromFile("resources/graphics/hard.png");
	_hard_texture.setSmooth(true);
	_back_texture.loadFromFile("resources/graphics/back.png");
	_back_texture.setSmooth(true);

	// Setup the easy sprite
	_easy_sprite.setTexture(_easy_texture, true);
	_easy_sprite.setPosition({120.f, 20.f});
	_easy_sprite.setScale({.6f, .6f});

	// Setup the medium sprite
	_medium_sprite.setTexture(_medium_texture, true);
	_medium_sprite.setPosition({120.f, 140.f});
	_medium_sprite.setScale({.6f, .6f});

	// Setup the hard sprite
	_hard_sprite.setTexture(_hard_texture, true);
	_hard_sprite.setPosition({120.f, 260.f});
	_hard_sprite.setScale({.6f, .6f});

	// Setup the back sprite
	_back_sprite.setTexture(_back_texture, true);
	_back_sprite.setPosition({20.f, 400.f});
	_back_sprite.setScale({.6f, .6f});

	// Setup the dimmer
	_dimmer.setSize({640, 480});
	_dimmer.setFillColor({96, 96, 96, 192});
}

OptionsState::~OptionsState() {
}

void OptionsState::handleEvent(sf::Event& event) {
	if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		if(_easy_sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
			// The player clicked the easy button
			_next_state.reset(new GameState(GameDifficulty::EASY));
			return;
		}
		if(_medium_sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
			// The player clicked the medium button
			_next_state.reset(new GameState(GameDifficulty::MEDIUM));
			return;
		}
		if(_hard_sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
			// The player clicked the hard button
			_next_state.reset(new GameState(GameDifficulty::HARD));
			return;
		}
		if(_back_sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
			// The player clicked the back button
			_back = true;
			return;
		}
	}
}

void OptionsState::update(std::unique_ptr<State>& current_state) {
	if(_next_state) {
		current_state.reset(_next_state.release());
		return;
	}

	if(_back) {
		_back = false;
		current_state.reset(_menu_state.release());
		return;
	}
}

void OptionsState::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(*_menu_state, states);
	target.draw(_dimmer);
	target.draw(_easy_sprite);
	target.draw(_medium_sprite);
	target.draw(_hard_sprite);
	target.draw(_back_sprite);
}
