#include "state/main_menu.hpp"

#include <iostream>

#include "state/options_state.hpp"
#include "state/quit_state.hpp"

MainMenu::MainMenu() :
	_play_button_texture(),
	_quit_button_texture(),
	_background_texture(),
	_play_button_sprite(),
	_quit_button_sprite(),
	_far_background_sprite(),
	_close_background_sprite(),
	_background_offset(0.f),
	_next_state(nullptr),
	_goto_play(false)
{
	// Load the textures
	_play_button_texture.loadFromFile("resources/graphics/play_button.png");
	_play_button_texture.setSmooth(true);
	_quit_button_texture.loadFromFile("resources/graphics/quit_button.png");
	_quit_button_texture.setSmooth(true);
	_background_texture.loadFromFile("resources/graphics/starfield.png");
	_background_texture.setRepeated(true);
	_background_texture.setSmooth(true);

	// Setup the play button sprite
	_play_button_sprite.setTexture(_play_button_texture, true);
	_play_button_sprite.setOrigin(256.f, 128.f);
	_play_button_sprite.setPosition(320.f, 180.f);

	// Setup the quit button sprite
	_quit_button_sprite.setTexture(_quit_button_texture, true);
	_quit_button_sprite.setOrigin(128.f, 128.f);
	_quit_button_sprite.setPosition(320.f, 360.f);
	_quit_button_sprite.setScale(.75f, .75f);

	// Setup the background sprites
	_far_background_sprite.setTexture(_background_texture);
	_far_background_sprite.setTextureRect({0, 0, 640, 480});
	_close_background_sprite.setTexture(_background_texture);
	_close_background_sprite.setTextureRect({0, 0, 640, 480});
}

MainMenu::~MainMenu() {
}

void MainMenu::handleEvent(sf::Event& event) {
	if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		if(_play_button_sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
			// The player clicked the play button
			_goto_play = true;
			return;
		}
		if(_quit_button_sprite.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
			// The player clicked the quit button
			_next_state.reset(new QuitState);
			return;
		}
	}
	if(event.type == sf::Event::KeyPressed) {
		switch(event.key.code) {
			case sf::Keyboard::Escape:
			case sf::Keyboard::Q:
				_next_state.reset(new QuitState);
				return;
			default:
				break;
		}
	}
}

void MainMenu::update(std::unique_ptr<State>& current_state) {
	if(_next_state) {
		current_state.reset(_next_state.release());
		return;
	}

	if(_goto_play) {
		_goto_play = false;
		current_state.reset(new OptionsState(std::move(current_state)));
		return;
	}

	// Update the starfield positions
	_background_offset += 1.0;
	auto rect = _close_background_sprite.getTextureRect();
	rect.left = _background_offset * .5f + 300;
	rect.top = _background_offset * .2f;
	_close_background_sprite.setTextureRect(rect);

	rect = _far_background_sprite.getTextureRect();
	rect.left = _background_offset * .3f;
	rect.top = _background_offset * .12f;
	_far_background_sprite.setTextureRect(rect);
}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_far_background_sprite);
	target.draw(_close_background_sprite);
	target.draw(_play_button_sprite);
	target.draw(_quit_button_sprite);
}

