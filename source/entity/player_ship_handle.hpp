#ifndef _ENTITY__PLAYER_SHIP_HANDLE_HPP_
#define _ENTITY__PLAYER_SHIP_HANDLE_HPP_

#include <memory>

#include "entity/player_ship.hpp"
#include "entity/entity.hpp"

class PlayerShipHandle : public Entity {
	public:
		PlayerShipHandle(std::shared_ptr<PlayerShip> player_ship) : _player_ship(player_ship) { }
		virtual ~PlayerShipHandle() override { }

		virtual bool update(float globalTimeMultiplier) override { return _player_ship->update(globalTimeMultiplier); }
		virtual bool contains(sf::Vector2f point) const override { return _player_ship->contains(point); }
		virtual bool collide(const std::unique_ptr<Entity>& entity) override { return _player_ship->collide(entity); }
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override { target.draw(*_player_ship, states); }

		virtual int getAggressionLevel() const override { return _player_ship->getAggressionLevel(); }
		virtual sf::Vector2f getPosition() const override { return _player_ship->getPosition(); }
		virtual float getDamage() const override { return _player_ship->getDamage(); }

	private:
		std::shared_ptr<PlayerShip> _player_ship;
};

#endif // _ENTITY__PLAYER_SHIP_HANDLE_HPP_
