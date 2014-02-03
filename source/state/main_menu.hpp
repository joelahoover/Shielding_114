#ifndef _STATE__MAIN_MENU_HPP_
#define _STATE__MAIN_MENU_HPP_

#include <memory>

#include <SFML/Graphics.hpp>

#include "state/state.hpp"

class MainMenu : public State {
	public:
		MainMenu();
		virtual ~MainMenu() override;

		// Process an event
		virtual void handleEvent(sf::Event&) override;

		// Update the state
		virtual void update(std::unique_ptr<State>& current_state) override;

		// Draw the state -- called once per frame
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::Texture _play_button_texture;
		sf::Texture _quit_button_texture;
		sf::Texture _background_texture;
		sf::Sprite _play_button_sprite;
		sf::Sprite _quit_button_sprite;
		sf::Sprite _far_background_sprite;
		sf::Sprite _close_background_sprite;

		float _background_offset;

		std::unique_ptr<State> _next_state;
		bool _goto_play;
};

#endif // _STATE__MAIN_MENU_HPP_
