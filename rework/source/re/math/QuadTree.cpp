//
//  QuadTree.cpp
//  REngine3
//
//  Created by reworks on 28/08/2017.
//  Code ported from:
//  https://gamedevelopment.tutsplus.com/tutorials/quick-tip-use-quadtrees-to-detect-likely-collisions-in-2d-space--gamedev-374

#include "entityx/Entity.h"
#include "re/components/TransformComponent.hpp"
#include "re/components/CollisionComponent.hpp"

#include "QuadTree.hpp"

namespace re
{
	QuadTree::QuadTree(int level, Rect<int>& bounds, int maxLevels, int maxObjects)
	:m_level(level), m_bounds(bounds), m_maxLevels(maxLevels), m_maxObjects(maxObjects)
	{
		for (auto& elem : m_nodes)
		{
			elem = nullptr;
		}
	}

	void QuadTree::clear()
	{
		m_objects.clear();

		for (size_t i = 0; i < m_nodes.size(); ++i)
		{
			if (m_nodes[i] != nullptr)
			{
				m_nodes[i]->clear();
				delete m_nodes[i];
				m_nodes[i] = nullptr;
			}
		}
	}

	void QuadTree::insert(ex::Entity& e)
	{
		auto tc_handle = e.component<TransformComponent>();
		auto cc_handle = e.component<CollisionComponent>();

		Rect<int> rect(tc_handle.m_x, tc_handle.m_y, cc_handle.m_width, cc_handle.m_height);

		if (m_nodes[0] != nullptr)
		{
			int index = getIndex(tc_rect);
			if (index != -1)
			{
				m_nodes[index]->insert(entity);
				
				return;
			}
		}

		m_objects.push_back(entity);

		if (m_objects.size() > m_maxObjects && m_level < m_maxLevels)
		{
			if (m_nodes[0] == nullptr)
			{
				split();
			}

			size_t i = 0;
			while (i < m_objects.size())
			{
				int index = getIndex(m_objects[i]->get<TransformComponent>()->m_rect);
				if (index != -1)
				{
					m_nodes[index]->insert(m_objects[i]);
					m_objects.erase(m_objects.begin() + i);
				}
				else
				{
					++i;
				}
			}
		}
	}

	void QuadTree::retrieve(std::vector<Entity*>& returnObjects, Entity* entity)
	{
		auto rect = entity->get<TransformComponent>()->m_rect;

		int index = getIndex(rect);
		if (index != -1 && m_nodes[0] != nullptr)
		{
			m_nodes[index]->retrieve(returnObjects, entity);
		}

		returnObjects.insert(returnObjects.begin(), m_objects.begin(), m_objects.end());
	}

	void QuadTree::split()
	{
		int subWidth = (m_bounds.width / 2);
		int subHeight = (m_bounds.height / 2);
		int x = m_bounds.left;
		int y = m_bounds.top;
		
		m_nodes[0] = new QuadTree(m_level + 1, Rect<int>(x + subWidth, y, subWidth, subHeight), m_maxLevels, m_maxObjects);
		m_nodes[1] = new QuadTree(m_level + 1, Rect<int>(x, y, subWidth, subHeight), m_maxLevels, m_maxObjects);
		m_nodes[2] = new QuadTree(m_level + 1, Rect<int>(x, y + subHeight, subWidth, subHeight), m_maxLevels, m_maxObjects);
		m_nodes[3] = new QuadTree(m_level + 1, Rect<int>(x + subWidth, y + subHeight, subWidth, subHeight), m_maxLevels, m_maxObjects);
	}

	int QuadTree::getIndex(Rect<int>& rect)
	{
		int index = -1;
		double verticalMidpoint = m_bounds.left + (m_bounds.width / 2);
		double horizontalMidpoint = m_bounds.top + (m_bounds.height / 2);

		bool topQuadrant = (rect.top < horizontalMidpoint && rect.top + rect.height < horizontalMidpoint);
		bool bottomQuadrant = (rect.top > horizontalMidpoint);

		if (rect.left < verticalMidpoint && rect.left + rect.width < verticalMidpoint)
		{
			if (topQuadrant)
			{
				index = 1;
			}
			else if (bottomQuadrant)
			{
				index = 2;
			}
		}
		else if (rect.left > verticalMidpoint)
		{
			if (topQuadrant)
			{
				index = 0;
			}
			else if (bottomQuadrant)
			{
				index = 3;
			}
		}

		return index;
	}
}