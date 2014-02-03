#ifndef _ENTITY__ENTITY_HPP_
#define _ENTITY__ENTITY_HPP_

#include <memory>

#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable {
	public:
		virtual ~Entity() { };

		virtual bool update(float globalTimeMultiplier) = 0; // True if dead
		virtual bool contains(sf::Vector2f) const = 0;
		virtual bool collide(const std::unique_ptr<Entity>&) = 0; // True if dead
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

		virtual int getAggressionLevel() const = 0;
		virtual sf::Vector2f getPosition() const = 0;
		virtual float getDamage() const = 0;
};

#endif // _ENTITY__ENTITY_HPP_
