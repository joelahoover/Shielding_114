#include "state/win_state.hpp"

#include "state/game_state.hpp"
#include "state/main_menu.hpp"

WinState::WinState(std::unique_ptr<State> game_state) :
	_message_texture(),
	_back_texture(),
	_message_sprite(),
	_back_sprite(),
	_dimmer(),
	_game_state(std::move(game_state))
{
	// Load the textures
	_message_texture.loadFromFile("resources/graphics/objective_complete.png");
	_back_texture.loadFromFile("resources/graphics/back.png");

	// Setup the message sprite
	_message_sprite.setTexture(_message_texture, true);
	_message_sprite.setOrigin({256.f, 128.f});
	_message_sprite.setPosition({320.f, 120.f});

	// Setup the back sprite
	_back_sprite.setTexture(_back_texture, true);
	_back_sprite.setPosition({20.f, 400.f});
	_back_sprite.setScale({.6f, .6f});

	// Setup the dimmer
	_dimmer.setSize({640, 480});
	_dimmer.setFillColor({96, 96, 96, 192});
}

WinState::~WinState() {
}

void WinState::handleEvent(sf::Event& event) {
	if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		if(_back_sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
			// The player clicked the back button
			_next_state.reset(new MainMenu);
			return;
		}
	}
}

void WinState::update(std::unique_ptr<State>& current_state) {
	if(_next_state) {
		current_state.reset(_next_state.release());
	}
}

void WinState::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(*_game_state, states);
	target.draw(_dimmer);
	target.draw(_message_sprite);
	target.draw(_back_sprite);
}
