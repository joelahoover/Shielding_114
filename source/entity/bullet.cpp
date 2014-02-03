#include "entity/bullet.hpp"

#include <cmath>
#include <iostream>

#include "util/time.hpp"

namespace {
	std::unique_ptr<sf::Texture> texture(nullptr);
}

Bullet::Bullet(BulletType bullet_type, float damage, sf::Vector2f position, sf::Vector2f velocity) :
	_sprite(),
	_type(bullet_type),
	_velocity(velocity),
	_ttl(300.f), // 5 seconds in normal time
	_damage(damage)
{
	// Load the texture
	if(!texture) {
		texture.reset(new sf::Texture);
		texture->loadFromFile("resources/graphics/bullet.png");
	}

	// Setup the sprite
	_sprite.setTexture(*texture, true);
	_sprite.setPosition(position);
	_sprite.setRotation(atan(velocity.y / velocity.x) * 57.296f);
	switch(_type) {
		case BulletType::FRIENDLY:
			_sprite.setColor({240, 200, 180});
			break;
		case BulletType::HOSTILE:
			_sprite.setColor({240, 60, 60});
			break;
		default:
			_sprite.setColor(sf::Color::White);
			break;
	}
}

Bullet::~Bullet() {
}

bool Bullet::update(float globalTimeMultiplier) {
	float dtime = getTimeMultiplier(getPosition()) / globalTimeMultiplier;
	_sprite.move(_velocity * dtime);

	// Update transparency based on time-to-live
	auto color = _sprite.getColor();
	color.a = std::min((unsigned int)(10.f*_ttl + 120.f), (unsigned int)255);
	_sprite.setColor(color);

	_ttl -= dtime;
	return _ttl < 0.f;
}

bool Bullet::contains(sf::Vector2f) const {
	return false;
}

bool Bullet::collide(const std::unique_ptr<Entity>&) {
	return true;
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_sprite, states);
}

sf::Vector2f Bullet::getPosition() const {
	return _sprite.getPosition();
}

float Bullet::getDamage() const {
	return _damage;
}

