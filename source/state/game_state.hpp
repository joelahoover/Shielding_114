#ifndef _STATE__GAME_STATE_HPP_
#define _STATE__GAME_STATE_HPP_

#include <memory>
#include <random>

#include "entity/entity_manager.hpp"
#include "entity/player_ship.hpp"
#include "entity/base.hpp"
#include "state/state.hpp"

enum class GameDifficulty { EASY, MEDIUM, HARD };

class GameState : public State {
	public:
		GameState(GameDifficulty);
		virtual ~GameState();

		// Handle an event
		virtual void handleEvent(sf::Event&) override;

		// Update the state
		virtual void update(std::unique_ptr<State>& current_state) override;

		// Draw the state -- called once per frame
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::Texture _background_texture;
		sf::Sprite _far_background_sprite;
		sf::Sprite _close_background_sprite;
		sf::RectangleShape _left_meter[3]; // Ship's health meter
		sf::RectangleShape _bottom_meter[3]; // Energy meter

		GameDifficulty _difficulty;
		std::shared_ptr<EntityManager> _entity_manager;
		std::shared_ptr<Base> _base;
		std::shared_ptr<PlayerShip> _player_ship;

		std::default_random_engine _random_generator;
		std::uniform_real_distribution<float> _uniform_distribution;
		float _current_time;
		float _spawn_time;
};

#endif // _STATE__GAME_STATE_HPP_
