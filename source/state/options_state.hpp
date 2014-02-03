#ifndef _STATE__OPTIONS_STATE_HPP_
#define _STATE__OPTIONS_STATE_HPP_

#include <memory>

#include <SFML/Graphics.hpp>

#include "state/state.hpp"

class GameState;

class OptionsState : public State {
	public:
		OptionsState(std::unique_ptr<State>);
		virtual ~OptionsState();

		// Process an event
		virtual void handleEvent(sf::Event&) override;

		// Update the state
		virtual void update(std::unique_ptr<State>& current_state) override;

		// Draw the state -- called once per frame
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	private:
		sf::Texture _easy_texture;
		sf::Texture _medium_texture;
		sf::Texture _hard_texture;
		sf::Texture _back_texture;
		sf::Sprite _easy_sprite;
		sf::Sprite _medium_sprite;
		sf::Sprite _hard_sprite;
		sf::Sprite _back_sprite;
		sf::RectangleShape _dimmer;

		std::unique_ptr<State> _menu_state;
		std::unique_ptr<State> _next_state;
		bool _back;
};

#endif // _STATE__OPTIONS_STATE_HPP_
