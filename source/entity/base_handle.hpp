#ifndef _ENTITY__BASE_HANDLE_HPP_
#define _ENTITY__BASE_HANDLE_HPP_

#include <memory>

#include "entity/player_ship.hpp"
#include "entity/entity.hpp"

class BaseHandle : public Entity {
	public:
		BaseHandle(std::shared_ptr<Base> player_ship) : _base(player_ship) { }
		virtual ~BaseHandle() override { }

		virtual bool update(float globalTimeMultiplier) override { return _base->update(globalTimeMultiplier); }
		virtual bool contains(sf::Vector2f point) const override { return _base->contains(point); }
		virtual bool collide(const std::unique_ptr<Entity>& entity) override { return _base->collide(entity); }
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override { target.draw(*_base, states); }

		virtual int getAggressionLevel() const override { return _base->getAggressionLevel(); }
		virtual sf::Vector2f getPosition() const override { return _base->getPosition(); }
		virtual float getDamage() const override { return _base->getDamage(); }

	private:
		std::shared_ptr<Base> _base;
};

#endif // _ENTITY__BASE_HANDLE_HPP_
