///
/// Animation.cpp
/// starlight
///
/// Created by reworks on 31/10/2017.
/// MIT License.
/// Refer to LICENSE.txt for more details.
///

#include "sl/libs/sol2/sol.hpp"
#include "sl/libs/loguru/loguru.hpp"

#include "Animation.hpp"

namespace sl
{
	Animation::Animation()
	:m_isLooped(false), m_speed(1.0f), m_totalFrames(0), m_currentFrame(0)
	{
		m_frames.clear();
	}

	Animation::Animation(sol::table& table)
		:m_currentFrame(0)
	{
		// Set values based off of lua table.
		m_isLooped = table.get<bool>("looped");
		m_speed = table.get<float>("speed");
		m_totalFrames = table.get<unsigned int>("totalFrames");

		// Get frame data...
		sol::table frames = table.get<sol::table>("frames");
		if (!frames.empty())
		{
			// ...then loop over each frame and insert it into the frame map.
			frames.for_each([&](std::pair<sol::object, sol::object> pair)
			{
				sol::table frameTable = pair.second.as<sol::table>();
				m_frames.emplace_back(frameTable.get<std::uint32_t>("timePerFrame"), frameTable.get<std::string>("frameTextureID"));
			});
		}
		else
		{
			LOG_S(WARNING) << "Tried to load animation with no frames!";
		}
	}

	Animation::Animation(bool isLooped, float speed, unsigned int totalFrames, unsigned int currentFrame, const std::vector<AnimationFrame>& frames)
		:m_isLooped(isLooped), m_speed(speed), m_totalFrames(totalFrames), m_currentFrame(currentFrame), m_frames(frames)
	{
		// Argument constructor.
	}

	Animation::Animation(Animation&& animation)
	:m_isLooped(animation.m_isLooped), m_speed(animation.m_speed), m_totalFrames(animation.m_totalFrames), m_currentFrame(animation.m_currentFrame), m_frames(animation.m_frames)
	{
		// Explicit copy constructor.
	}

	Animation::Animation(const Animation& animation)
	: m_isLooped(animation.m_isLooped), m_speed(animation.m_speed), m_totalFrames(animation.m_totalFrames), m_currentFrame(animation.m_currentFrame), m_frames(animation.m_frames)
	{
		// Explicit move constructor.
	}
}