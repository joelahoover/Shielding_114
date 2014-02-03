#include "state/game_state.hpp"

#include "entity/player_ship_handle.hpp"
#include "entity/base_handle.hpp"
#include "entity/enemy_ship.hpp"
#include "state/lose_state.hpp"
#include "state/win_state.hpp"
#include "entity/bullet.hpp"

GameState::GameState(GameDifficulty difficulty) :
	_background_texture(),
	_far_background_sprite(),
	_close_background_sprite(),
	_left_meter(),
	_bottom_meter(),
	_difficulty(difficulty),
	_entity_manager(new EntityManager),
	_base(new Base),
	_player_ship(new PlayerShip(_entity_manager)),
	_random_generator(),
	_uniform_distribution(0.f, 1.f),
	_current_time(-2.f),
	_spawn_time(_uniform_distribution(_random_generator))
{
	// Load the background texture
	_background_texture.loadFromFile("resources/graphics/starfield.png");
	_background_texture.setRepeated(true);
	_background_texture.setSmooth(true);

	// Setup the background sprites
	_far_background_sprite.setTexture(_background_texture);
	_far_background_sprite.setTextureRect({0, 0, 640, 480});
	_close_background_sprite.setTexture(_background_texture);
	_close_background_sprite.setTextureRect({0, 0, 640, 480});

	// Setup the left meter
	_left_meter[0].setSize({25.f, 200.f});
	_left_meter[0].setPosition({20.f , 200.f});
	_left_meter[0].setFillColor({10, 50, 60, 192});
	_left_meter[1].setSize({25.f, 200.f});
	_left_meter[1].setPosition({20.f, 400.f});
	_left_meter[1].setFillColor({40, 200, 240, 192});
	_left_meter[2].setSize({25.f, 200.f});
	_left_meter[2].setPosition({20.f , 200.f});
	_left_meter[2].setFillColor(sf::Color::Transparent);
	_left_meter[2].setOutlineColor({20, 60, 80, 192});
	_left_meter[2].setOutlineThickness(3);

	// Setup the bottom meter
	_bottom_meter[0].setSize({400.f, 25.f});
	_bottom_meter[0].setPosition({120.f , 435.f});
	_bottom_meter[0].setFillColor({10, 120, 100, 192});
	_bottom_meter[1].setSize({400.f, 25.f});
	_bottom_meter[1].setPosition({120.f, 435.f});
	_bottom_meter[1].setFillColor({80, 255, 255, 192});
	_bottom_meter[2].setSize({400.f, 25.f});
	_bottom_meter[2].setPosition({120.f , 435.f});
	_bottom_meter[2].setFillColor(sf::Color::Transparent);
	_bottom_meter[2].setOutlineColor({40, 40, 40, 192});
	_bottom_meter[2].setOutlineThickness(3);

	// Create the game world
	_entity_manager->add(std::unique_ptr<Entity>(new PlayerShipHandle(_player_ship)));
	_entity_manager->add(std::unique_ptr<Entity>(new BaseHandle(_base)));
}

GameState::~GameState() {
}

void GameState::handleEvent(sf::Event& event) {
	if(event.type == sf::Event::MouseMoved) {
		// Forward this event to the player ship
		_player_ship->handleEvent(event);
	}
}

void GameState::update(std::unique_ptr<State>& current_state) {
	float globalTimeMultiplier = _player_ship->getLocalTimeMultiplier();

	// Update the starfield positions
	auto background_offset = 0.5f * (_player_ship->getPosition() - _player_ship->getScreenPosition());
	auto rect = _close_background_sprite.getTextureRect();
	rect.left = background_offset.x * .5f + 320;
	rect.top = background_offset.y * .5f + 240;
	_close_background_sprite.setTextureRect(rect);

	rect = _far_background_sprite.getTextureRect();
	rect.left = background_offset.x * .3f;
	rect.top = background_offset.y * .3f;
	_far_background_sprite.setTextureRect(rect);

	// Spawn a new enemy ship
	{
		switch(_difficulty) {
			case GameDifficulty::EASY:   _current_time += .1f  / globalTimeMultiplier; break;
			case GameDifficulty::MEDIUM: _current_time += .15f / globalTimeMultiplier; break;
			case GameDifficulty::HARD:   _current_time += .2f  / globalTimeMultiplier; break;
			default:                                                                   break;
		}
		if(_current_time > _spawn_time) {
			// Update the spawn time
			_spawn_time = _uniform_distribution(_random_generator);
			switch(_difficulty) {
				case GameDifficulty::EASY:   _current_time = -1.f; break;
				case GameDifficulty::MEDIUM: _current_time = -.5f; break;
				case GameDifficulty::HARD:   _current_time = -.5f; break;
				default:                                           break;
			}

			// Create the new enemy
			float angle = (_uniform_distribution(_random_generator) - .5f);
			switch(_difficulty) {
				case GameDifficulty::EASY:   angle *= 1.f;   break;
				case GameDifficulty::MEDIUM: angle *= 2.f;   break;
				case GameDifficulty::HARD:   angle *= 2.75f; break;
				default:                                     break;
			}

			sf::Vector2f position = sf::Vector2f(320.f, 300.f) + 600.f * sf::Vector2f(sin(angle), -cos(angle));

			_entity_manager->add(std::unique_ptr<Entity>(new EnemyShip(_entity_manager, _player_ship, position, 100.f)));
		}
	}

	// Update all the game objects
	_entity_manager->update(globalTimeMultiplier);

	// Update the meters
	_left_meter[1].setScale(1.f, -_player_ship->getShipHealth() / 500.f);
	_bottom_meter[1].setScale(_base->getHealth() / 5000.f, 1.f);

	// Update the state if won or lost
	if(_base->getHealth() >= 4990.f) {
		current_state.reset(new WinState(std::move(current_state)));
	}
	if(_base->getHealth() <= 0.f) {
		current_state.reset(new LoseState(std::move(current_state)));
	}
}

void GameState::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_far_background_sprite);
	target.draw(_close_background_sprite);
	states.transform.translate(_player_ship->getScreenPosition() - _player_ship->getPosition());
	target.draw(*_entity_manager, states);

	for(auto drawable : _left_meter) {
		target.draw(drawable);
	}
	for(auto drawable : _bottom_meter) {
		target.draw(drawable);
	}
}

