#ifndef _ENTITY__BULLET_HPP_
#define _ENTITY__BULLET_HPP_

#include <memory>

#include <SFML/Graphics.hpp>

#include "entity/entity.hpp"

enum class BulletType {
	FRIENDLY,
	HOSTILE,
	NEUTRAL
};

class Bullet : public Entity {
	public:
		Bullet(BulletType, float damage, sf::Vector2f position, sf::Vector2f velocity);
		virtual ~Bullet() override;

		virtual bool update(float globalTimeMultiplier) override; // True if dead
		virtual bool contains(sf::Vector2f) const override;
		virtual bool collide(const std::unique_ptr<Entity>&) override; // True if dead
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		virtual int getAggressionLevel() const override { return 8; }
		virtual sf::Vector2f getPosition() const override;
		virtual float getDamage() const override;

	private:
		sf::Sprite _sprite;

		BulletType _type;
		sf::Vector2f _velocity;
		float _ttl;
		float _damage;
};

#endif // _ENTITY__BULLET_HPP_
