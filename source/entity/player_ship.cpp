#include "player_ship.hpp"

#include <cmath>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "entity/entity_manager.hpp"
#include "entity/bullet.hpp"
#include "util/time.hpp"

namespace {
	const sf::Vector2f default_screen_position(320.f, 360.f);
}

PlayerShip::PlayerShip(std::weak_ptr<EntityManager> entity_manager) :
	_ship_texture(),
	_shield_texture(),
	_ship_sprite(),
	_shield_sprite(),
	_entity_manager(entity_manager),
	_screen_position(default_screen_position),
	_reload(30.f),
	_ship_health(500.f),
	_mouse_position(0.f, 0.f)
{
	// Load the textures
	_ship_texture.loadFromFile("resources/graphics/player_ship.png");
	_shield_texture.loadFromFile("resources/graphics/shield.png");

	// Setup the ship sprite
	_ship_sprite.setTexture(_ship_texture, true);
	_ship_sprite.setOrigin(32.f, 32.f);
	_ship_sprite.setPosition(_screen_position);
	_ship_sprite.setScale(.6f, .6f);

	// Setup the shield sprite
	_shield_sprite.setTexture(_shield_texture, true);
	_shield_sprite.setOrigin(32.f, 32.f);
	_shield_sprite.setPosition(_screen_position);
}

PlayerShip::~PlayerShip() {
}

bool PlayerShip::update(float globalTimeMultiplier) {
	// Rotating the ship
	{
		auto diff = _mouse_position - _screen_position;
		float angle = atan(diff.y / diff.x) * 57.296f + 90.f;
		if(diff.x < 0.f) {
			angle += 180.f;
		}
		_ship_sprite.setRotation(angle);
	}

	// Move the ship
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
		   sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			_acceleration.y -= .1f;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
		   sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			_acceleration.y += .1f;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
		   sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			_acceleration.x -= .1f;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		   sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			_acceleration.x += .1f;
		}

		_acceleration *= .8f;
		_velocity += _acceleration;
		_velocity *= .9f; // Friction in space :P
		_ship_sprite.move(_velocity);
		_shield_sprite.move(_velocity);
		_screen_position = default_screen_position + 5.f * _velocity;
	}

	// Fire bullets
	if(--_reload < 0 && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		_reload = 10.f;
		std::shared_ptr<EntityManager> entity_manager(_entity_manager.lock());
		if(entity_manager) {
			sf::Vector2f diff = _mouse_position - _screen_position;
			sf::Vector2f velocity = diff / (float)sqrt(diff.x*diff.x + diff.y*diff.y);
			sf::Vector2f perpendicular(-velocity.y, velocity.x);
			entity_manager->add(std::unique_ptr<Entity>(new Bullet(BulletType::FRIENDLY, 10.f, _shield_sprite.getPosition() + 40.f * velocity + 20.f * perpendicular, 5.0f*velocity)));
			entity_manager->add(std::unique_ptr<Entity>(new Bullet(BulletType::FRIENDLY, 10.f, _shield_sprite.getPosition() + 40.f * velocity - 20.f * perpendicular, 5.0f*velocity)));
		}
	}

	return getShipHealth() <= 0.f;
}

bool PlayerShip::contains(sf::Vector2f point) const {
	auto diff = (_ship_sprite.getPosition() - point);
	return diff.x*diff.x + diff.y*diff.y < 32.f * 32.f;
}

bool PlayerShip::collide(const std::unique_ptr<Entity>& entity) {
	_ship_health -= entity->getDamage();
	if(_ship_health <= 0.f) {
		_ship_health = 0.f;
		return true;
	}

	return false;
}

void PlayerShip::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_ship_sprite, states);
	states.blendMode = sf::BlendAdd;
	target.draw(_shield_sprite, states);
}

sf::Vector2f PlayerShip::getPosition() const {
	return _ship_sprite.getPosition();
}

void PlayerShip::handleEvent(sf::Event& event) {
	// Handle mouse events
	if(event.type == sf::Event::MouseMoved) {
		_mouse_position.x = event.mouseMove.x;
		_mouse_position.y = event.mouseMove.y;
	}
}

sf::Vector2f PlayerShip::getScreenPosition() const {
	return _screen_position;
}

float PlayerShip::getLocalTimeMultiplier() const {
	if(getShipHealth() <= 0.f) {
		return 2.f;
	} else {
		return getTimeMultiplier(getPosition());
	}
}

float PlayerShip::getShipHealth() const {
	return _ship_health;
}

