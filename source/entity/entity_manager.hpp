#ifndef _ENTITY__ENTITY_MANAGER_
#define _ENTITY__ENTITY_MANAGER_

#include <memory>
#include <list>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "entity/entity.hpp"

class EntityManager : public sf::Drawable {
	public:
		EntityManager();
		~EntityManager();

		void add(std::unique_ptr<Entity>);
		void update(float globalTimeMultiplier);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		void list() {
			for(auto& entity : _entity_list) {
				std::cout << "Entity: " << entity.get() << std::endl;
			}
		}

	private:
		std::list<std::unique_ptr<Entity>> _entity_list;
};

#endif // _ENTITY__ENTITY_MANAGER_
