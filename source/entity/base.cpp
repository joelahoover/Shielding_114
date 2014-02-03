#include "entity/base.hpp"

Base::Base() :
	_placeholder_texture(),
	_draw_area({640.f, 480.f}),
	_shader(),
	_health(1000.f)
{
	// Setup the drawing area
	_placeholder_texture.loadFromFile("resources/graphics/placeholder.png");
	_draw_area.setTexture(&_placeholder_texture);
	_draw_area.setFillColor({20, 40, 240});

	// Setup the shader
	_shader.loadFromFile("resources/shaders/base.glslf", sf::Shader::Type::Fragment);
}

Base::~Base() {
}

bool Base::update(float globalTimeMultiplier) {
	if(_health > 0.f) {
		_health += 8.f / globalTimeMultiplier;
	}

	return false;
}

bool Base::contains(sf::Vector2f point) const {
	point -= sf::Vector2f(320.f, 3000.f);
	float r = sqrt(point.x*point.x + point.y*point.y);
	point += sf::Vector2f(0.f, 2750.f);
	float r2 = sqrt(point.x*point.x + point.y*point.y);

	return 2650.f*50.f/r - 49.f - 100.f*5.f/r2 + 4.f > 2.f;
}

bool Base::collide(const std::unique_ptr<Entity>& entity) {
	_health -= entity->getDamage();
	if(_health < 0.f) {
		_health = 0.f;
	}

	return false;
}

void Base::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	_shader.setParameter("position", states.transform.getInverse().transformPoint(0.f, 0.f) - sf::Vector2f(320.f, 3000.f));
	states.transform = sf::Transform::Identity;
	states.shader = &_shader;
	target.draw(_draw_area, states);
}

sf::Vector2f Base::getPosition() const {
	return {320.f, 3000.f};
}

float Base::getHealth() const {
	return _health;
}

void Base::setHealth(float health) {
	_health = health;
}

