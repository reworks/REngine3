///
/// PlayerMoveEvent.hpp
/// starlight
///
/// Created by reworks on 04/02/2018.
/// MIT License.
/// Refer to LICENSE.txt for more details.
///

#ifndef STARLIGHT_PLAYERMOVEEVENT_HPP_
#define STARLIGHT_PLAYERMOVEEVENT_HPP_

#include <cinttypes>

#include "sl/libs/entt/entity/registry.hpp"

namespace sl
{
	struct PlayerMoveEvent
	{
		///
		/// Constructor.
		///
		inline PlayerMoveEvent(float horizontalSpeed, float verticalSpeed, entt::DefaultRegistry::entity_type playerEntity)
			:m_horizontalSpeed(horizontalSpeed), m_verticalSpeed(verticalSpeed), m_playerEntity(playerEntity)
		{
		}

		///
		/// How much to move the player by horizontally.
		///
		float m_horizontalSpeed;

		///
		/// How much to move the player by vertically.
		///
		float m_verticalSpeed;

		///
		/// The player entity.
		///
		entt::DefaultRegistry::entity_type m_playerEntity;
	};
}

#endif