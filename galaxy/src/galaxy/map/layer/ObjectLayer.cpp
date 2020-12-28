///
/// ObjectLayer.cpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#include <nlohmann/json.hpp>

#include "galaxy/error/Log.hpp"

#include "ObjectLayer.hpp"

namespace galaxy
{
	namespace map
	{
		ObjectLayer::ObjectLayer()
		{
			GALAXY_LOG(GALAXY_FATAL, "Cannot instantiate a default constructed ObjectLayer.");
		}

		ObjectLayer::ObjectLayer(const nlohmann::json& json)
		    : Layer {json}, m_draw_order {""}
		{
			if (json.count("draworder") > 0)
			{
				m_draw_order = json.at("draworder");
			}

			if (json.count("objects") > 0)
			{
				auto object_array = json.at("objects");
				for (const auto& object : object_array)
				{
					m_objects.emplace_back(object);
				}
			}
		}

		ObjectLayer::~ObjectLayer()
		{
			m_objects.clear();
		}

		std::string ObjectLayer::get_compression() const
		{
			return m_draw_order;
		}

		const auto& ObjectLayer::get_objects() const
		{
			return m_objects;
		}
	} // namespace map
} // namespace galaxy