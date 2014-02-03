#ifndef _ENTITY__ENEMY_SHIP_HPP_
#define _ENTITY__ENEMY_SHIP_HPP_

#include <memory>

#include "entity/entity.hpp"

class EntityManager;
class PlayerShip;

class EnemyShip : public Entity {
	public:
		EnemyShip(std::weak_ptr<EntityManager>, std::shared_ptr<PlayerShip>, sf::Vector2f position, float health);
		virtual ~EnemyShip() override;

		virtual bool update(float globalTimeMultiplier) override; // True if dead
		virtual bool contains(sf::Vector2f) const override;
		virtual bool collide(const std::unique_ptr<Entity>&) override; // True if dead
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		virtual int getAggressionLevel() const override { return 4; }
		virtual sf::Vector2f getPosition() const override;
		virtual float getDamage() const override { return 200.f; }

	private:
		sf::Sprite _ship_sprite;

		std::weak_ptr<EntityManager> _entity_manager;
		std::shared_ptr<PlayerShip> _player_ship;
		float _reload;
		float _ship_health;
};

#endif // _ENTITY__ENEMY_SHIP_HPP_
