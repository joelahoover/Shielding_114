#ifndef _STATE__WIN_STATE_HPP_
#define _STATE__WIN_STATE_HPP_

#include <memory>

#include <SFML/Graphics.hpp>

#include "state/state.hpp"

class GameState;

class WinState : public State {
	public:
		WinState(std::unique_ptr<State>);
		virtual ~WinState();

		// Process an event
		virtual void handleEvent(sf::Event&) override;

		// Update the state
		virtual void update(std::unique_ptr<State>& current_state) override;

		// Draw the state -- called once per frame
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	private:
		sf::Texture _message_texture;
		sf::Texture _back_texture;
		sf::Sprite _message_sprite;
		sf::Sprite _back_sprite;
		sf::RectangleShape _dimmer;

		std::unique_ptr<State> _game_state;
		std::unique_ptr<State> _next_state;
};

#endif // _STATE__WIN_STATE_HPP_
