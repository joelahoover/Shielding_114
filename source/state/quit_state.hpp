#ifndef _STATE__QUIT_STATE_HPP_
#define _STATE__QUIT_STATE_HPP_

#include "state/state.hpp"

class QuitState : public State {
		virtual ~QuitState() { };

		// Process an event
		virtual void handleEvent(sf::Event&) override { }

		// Update the state
		virtual void update(std::unique_ptr<State>& current_state) override { current_state.reset(); }

		// Draw the state -- called once per frame
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override { }
};

#endif // _STATE__QUIT_STATE_HPP_
