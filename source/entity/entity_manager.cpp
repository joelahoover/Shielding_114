#include "entity/entity_manager.hpp"

#include <iostream>

bool entityLessAggression(const std::unique_ptr<Entity>& entity1, const std::unique_ptr<Entity>& entity2) {
	return entity1->getAggressionLevel() < entity2->getAggressionLevel();
}

EntityManager::EntityManager() :
	_entity_list()
{
}

EntityManager::~EntityManager() {
}

void EntityManager::add(std::unique_ptr<Entity> entity) {
	/*std::list<std::unique_ptr<Entity>> temp_list;
	temp_list.push_back(std::move(entity));
	_entity_list.merge(temp_list, entityLessAggression);*/
	_entity_list.push_back(std::move(entity));
	_entity_list.sort(entityLessAggression);
}

void EntityManager::update(float globalTimeMultiplier) {
	for(auto it = _entity_list.begin(); it != _entity_list.end(); ) {
		if((*it++)->update(globalTimeMultiplier)) {
			_entity_list.erase((--it)++);
		}
	}

	// Yup, the collision detection is n-squared int the worst case ;)
	for(auto it1 = _entity_list.begin(); it1 != _entity_list.end(); ) {
		auto& entity1 = *it1++;
		for(auto it2 = _entity_list.begin(); it2 != _entity_list.end(); ) {
			auto& entity2 = *it2++;

			if(!entityLessAggression(entity2, entity1)) {
				break;
			}

			//std::cout << "Testing for collision." << std::endl;
			if(entity2->contains(entity1->getPosition())) {
				// Collision!
				bool remove_entity1 = entity1->collide(entity2);
				bool remove_entity2 = entity2->collide(entity1);

				if(remove_entity2) {
					_entity_list.erase((--it2)++);
				}
				if(remove_entity1) {
					_entity_list.erase((--it1)++);
					return;
				}
			}
		}
	}
}

void EntityManager::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for(auto& entity : _entity_list) {
		target.draw(*entity, states);
	}
}

