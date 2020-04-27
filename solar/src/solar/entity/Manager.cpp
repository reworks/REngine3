///
/// Manager.cpp
///
/// solar
/// See LICENSE.txt.
///

#include "Manager.hpp"

namespace sr
{
	Manager::Manager() noexcept
		:m_nextID(0)
	{
	}

	Manager::~Manager() noexcept
	{
		clear();
	}

	const sr::Entity Manager::create() noexcept
	{
		// Bit masks the unsigned interger id with the valid_entity flag
		// to make sure when an unsigned integer is passed it can be
		// verified as an actual entity.
		SR_INTEGER free = m_nextID++;
		sr::Entity entity = free << 16 | sr::VALID_ENTITY;
		
		m_entities.insert(entity);

		return entity;
	}

	const bool Manager::has(const sr::Entity entity) noexcept
	{
		// Do not need to verify since parameter wont match unless entity flag is present.
		return m_entities.has(entity);
	}

	const bool Manager::validate(const sr::Entity entity)
	{
		// Checks if flag exists.
		return (entity & 0xFFFF) == sr::VALID_ENTITY;
	}

	void Manager::destroy(const sr::Entity entity)
	{
		m_entities.remove(entity);

		for (auto&& ptr : m_data)
		{
			ptr->remove(entity);
		}
	}

	void Manager::event(const sr::Event& event)
	{
		for (auto&& ptr : m_systems)
		{
			ptr->event(event);
		}
	}

	void Manager::update(const sr::DeltaTime time)
	{
		for (auto&& ptr : m_systems)
		{
			ptr->update(time, *this);
		}
	}

	void Manager::clear() noexcept
	{
		m_nextID = 0;

		m_entities.clear();
		m_data.clear();
		m_systems.clear();
	}
}