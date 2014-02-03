#include "entity/enemy_ship.hpp"

#include "entity/entity_manager.hpp"
#include "entity/player_ship.hpp"
#include "entity/bullet.hpp"
#include "util/time.hpp"

namespace {
	std::unique_ptr<sf::Texture> ship_texture(nullptr);
}

EnemyShip::EnemyShip(std::weak_ptr<EntityManager> entity_manager, std::shared_ptr<PlayerShip> player_ship, sf::Vector2f position, float health) :
	_ship_sprite(),
	_entity_manager(entity_manager),
	_player_ship(player_ship),
	_reload(80.f),
	_ship_health(health)
{
	// Load the texture
	if(!ship_texture) {
		ship_texture.reset(new sf::Texture);
		ship_texture->loadFromFile("resources/graphics/player_ship.png");
	}

	// Setup the sprite
	_ship_sprite.setTexture(*ship_texture, true);
	_ship_sprite.setOrigin(32.f, 32.f);
	_ship_sprite.setPosition(position);
}

EnemyShip::~EnemyShip() {
}

bool EnemyShip::update(float globalTimeMultiplier) {
	float dtime = getTimeMultiplier(getPosition()) / globalTimeMultiplier;
	// Move and rotate the ship
	{
		auto diff = getPosition() - sf::Vector2f(320.f, 3000.f);
		float r = sqrt(diff.x*diff.x + diff.y*diff.y);
		float theta = atan(diff.x / diff.y);
		float angle = r / 2700.f * std::max(std::min(theta * 10.f, 1.57f), -1.57f);
		sf::Vector2f velocity = dtime * 2.f * sf::Vector2f(sin(angle), cos(angle));

		// Convert the angle for SFML
		angle = -angle * 57.296;
		if(diff.y < 0.f) {
			angle += 180.f;
		}

		_ship_sprite.setRotation(angle);
		_ship_sprite.move(velocity);
	}

	// Fire bullets
	_reload -= dtime;
	if(_reload < 0) {
		_reload = 30.f;
		std::shared_ptr<EntityManager> entity_manager(_entity_manager.lock());
		if(entity_manager) {
			sf::Vector2f diff = _player_ship->getPosition() - getPosition();
			sf::Vector2f velocity = diff / (float)sqrt(diff.x*diff.x + diff.y*diff.y);
			entity_manager->add(std::unique_ptr<Entity>(new Bullet(BulletType::HOSTILE, 10.f, getPosition() + 40.f * velocity, 3.0f*velocity)));
		}
	}

	return _ship_health <= 0.f;
}

bool EnemyShip::contains(sf::Vector2f point) const {
	auto diff = (_ship_sprite.getPosition() - point);
	return diff.x*diff.x + diff.y*diff.y < 32.f * 32.f;
}

bool EnemyShip::collide(const std::unique_ptr<Entity>& entity) {
	_ship_health -= entity->getDamage();
	if(_ship_health <= 0.f) {
		_ship_health = 0.f;
		return true;
	}

	return false;
}

void EnemyShip::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_ship_sprite, states);
}

sf::Vector2f EnemyShip::getPosition() const {
	return _ship_sprite.getPosition();
}

