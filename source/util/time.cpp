#include "util/time.hpp"

#include <cmath>

float getTimeMultiplier(sf::Vector2f position) {
	auto diff1 = position - sf::Vector2f(320.f, 3000.f);
	float r1 = sqrt(diff1.x*diff1.x + diff1.y*diff1.y);
	auto diff2 = position - sf::Vector2f(320.f, 3000.f - 2700.f);
	float r2 = sqrt(diff2.x*diff2.x + diff2.y*diff2.y);
	//auto theta = atan(diff.x / diff.y);
	if(r1 < 2700.f) {
		r2 = 0.f;
	} else if(r1 < 2800.f) {
		r2 *= .01f * (r1 - 2700.f);
	}

	return 20.f * std::min(75.f / r2, 1.f);
}

