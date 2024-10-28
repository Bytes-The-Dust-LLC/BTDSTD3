#pragma once

//defines a series of functions for handling ECS

#include <unordered_map>

namespace BTD::ECS
{
	// Component storage
	template <typename ComponentType>
	std::unordered_map<uint64_t, ComponentType>& getComponentMap() {
		static std::unordered_map<uint64_t, ComponentType> componentMap;
		return componentMap;
	}

	// Add a component to an entity
	template <typename ComponentType>
	void addComponent(uint64_t entity, ComponentType component)
	{
		auto& componentMap = getComponentMap<ComponentType>();
		componentMap[entity] = component;
	}

	// Get a reference to a component for a given entity
	template <typename ComponentType>
	ComponentType* getComponent(uint64_t entity)
	{
		auto& componentMap = getComponentMap<ComponentType>();
		if (componentMap.find(entity) != componentMap.end()) {
			return &componentMap[entity];
		}
		return nullptr;
	}

	// Remove a component from an entity
	template <typename ComponentType>
	void removeComponent(uint64_t entity) 
	{
		auto& componentMap = getComponentMap<ComponentType>();
		componentMap.erase(entity);
	}

	// Query entities that have all of the specified components
	template <typename... ComponentTypes>
	std::vector<uint64_t> queryEntities()
	{
		std::vector<uint64_t> result;

		if constexpr (sizeof...(ComponentTypes) == 0) {
			return result;  // No components specified, return empty list
		}

		std::vector<uint64_t> potentialEntities = getEntitiesWith<ComponentTypes...>();
		for (uint64_t entity : potentialEntities) {
			if (hasComponents<ComponentTypes...>(entity)) {
				result.push_back(entity);
			}
		}

		return result;
	}

	// Check if an entity has all of the specified components
	template <typename... ComponentTypes>
	bool hasComponents(uint64_t entity) 
	{
		return (... && (getComponent<ComponentTypes>(entity) != nullptr));
	}

	// Get the entities that have the first component type (used to limit the search space)
	template <typename FirstComponentType, typename... RestComponentTypes>
	std::vector<uint64_t> getEntitiesWith() 
	{
		auto& componentMap = getComponentMap<FirstComponentType>();
		std::vector<uint64_t> entities;

		for (const auto& [entity, component] : componentMap) {
			entities.push_back(entity);
		}

		return entities;
		}
}