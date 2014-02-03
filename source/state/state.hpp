#ifndef _STATE__STATE_HPP_
#define _STATE__STATE_HPP_

#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class State : public sf::Drawable {
	public:
		virtual ~State() { };

		// Process an event
		virtual void handleEvent(sf::Event&) = 0;

		// Update the state
		virtual void update(std::unique_ptr<State>& current_state) = 0;

		// Draw the state -- called once per frame
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;
};

#endif // _STATE_HPP_
