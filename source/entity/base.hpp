#ifndef _ENTITY__BASE_HPP_
#define _ENTITY__BASE_HPP_

#include <memory>

#include <SFML/Graphics.hpp>

#include "entity/entity.hpp"

class Base : public Entity {
	public:
		Base();
		virtual ~Base() override;

		virtual bool update(float globalTimeMultiplier) override;
		virtual bool contains(sf::Vector2f) const override;
		virtual bool collide(const std::unique_ptr<Entity>&) override;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		virtual int getAggressionLevel() const override { return 0; }
		virtual sf::Vector2f getPosition() const override;
		virtual float getDamage() const override { return 1000.f; }

		float getHealth() const;
		void setHealth(float);

	private:
		sf::Texture _placeholder_texture;
		sf::RectangleShape _draw_area;
		mutable sf::Shader _shader;

		float _health;
};

#endif // _ENTITY__BASE_HPP_
