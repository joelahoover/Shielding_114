#ifndef _ENTITY__PLAYER_SHIP_HPP_
#define _ENTITY__PLAYER_SHIP_HPP_

#include <memory>

#include <SFML/Graphics.hpp>

#include "entity/entity.hpp"

class EntityManager;

class PlayerShip : public Entity {
	public:
		PlayerShip(std::weak_ptr<EntityManager>);
		virtual ~PlayerShip();

		virtual bool update(float globalTimeMultiplier) override; // True if dead
		virtual bool contains(sf::Vector2f) const override;
		virtual bool collide(const std::unique_ptr<Entity>&) override; // True if dead
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		virtual int getAggressionLevel() const override { return 2; }
		virtual sf::Vector2f getPosition() const override;
		virtual float getDamage() const override { return 100.f; }

		void handleEvent(sf::Event&);

		sf::Vector2f getScreenPosition() const;
		float getLocalTimeMultiplier() const;
		float getShipHealth() const;

	private:
		sf::Texture _ship_texture;
		sf::Texture _shield_texture;
		sf::Sprite _ship_sprite;
		sf::Sprite _shield_sprite;

		std::weak_ptr<EntityManager> _entity_manager;

		sf::Vector2f _screen_position;
		sf::Vector2f _velocity;
		sf::Vector2f _acceleration;
		float _reload;
		float _ship_health;

		sf::Vector2f _mouse_position;
};

#endif // _ENTITY__PLAYER_SHIP_HPP_
